#include "SceneManager.h"
#include "../Base/Camera.h"
#include "../Scene/TestScene.h"
#include "../Scene/CollisionScene.h"
#include "../Scene/Title.h"
#include "../Scene/LightScene.h"

#include "../Core/Debug/Debug_Collision.h"

SceneManager* SceneManager::pInstance = nullptr;

SceneManager * SceneManager::GetInstance()
{
	return pInstance;
}

HRESULT SceneManager::Create()
{
	if (!pInstance)
	{
		pInstance = new SceneManager;
		CCamera::Get()->Init();
		return S_OK;
	}
	return S_FALSE;
}

void SceneManager::Destroy()
{
	delete pInstance;
	pInstance = nullptr;
}

void SceneManager::Update()
{
	m_pActiceScene->Update();
	m_pActiceScene->ConstUpdate();
	m_pActiceScene->LateUodate();
	
	m_pSceneFade->Update();
	m_monitor.Update();

	if (m_isChange)
	{
		if (m_pSceneFade->GetFadeScene() == FADESTATE_NONE)
		{
			// 現在の画面を終了
			delete m_pActiceScene;
#ifdef _DEBUG
			Debug_Collision::GetInstance()->ListClear();
#endif // _DEBUG

			m_eScene = m_eNextScene;

			// 次の画面を初期化
			switch (m_eScene)
			{
			case SCENE_TEST:
				m_pActiceScene = new TestScene;
				break;
			case SCENE_COLLISION:
				m_pActiceScene = new CollisionScene;
				break;
			case SCENE_LIGHT:
				m_pActiceScene = new LightScene;
				break;
			case SCENE_TITLE:
				m_pActiceScene = new Title;
				break;
			case SCENE_NONE:
				break;
			}
			m_pSceneFade->FadeInScene();
			CCamera::Get()->Init();
			m_isChange = false;
		}
	}
}

void SceneManager::Draw()
{
	// シーンの描画
	m_pActiceScene->Draw();
	SetBlendState(BS_ALPHABLEND);
	// フェードの描画
	m_pSceneFade->Draw();
	SetBlendState(BS_NONE);

#ifdef _DEBUG
	// 当たり判定の描画
	SetBlendState(BS_ALPHABLEND);
	SetZWrite(false);
	SetRenderTarget(RT_GAME);
	Debug_Collision::GetInstance()->Draw();
	SetZWrite(true);
	SetBlendState(BS_NONE);
#endif // _DEBUG

	m_monitor.Draw();
}

void SceneManager::SetSecne(EScene scene)
{
	m_isChange = true;
	m_pSceneFade->FadeOutScene();
	m_eNextScene = scene;
}

SceneManager::SceneManager():m_eScene(SCENE_TEST),m_isChange(false)
{
	SceneFade::Create();
	m_pSceneFade = SceneFade::GetInstance();
	m_pActiceScene = new TestScene;
}

SceneManager::~SceneManager()
{
	delete m_pActiceScene;
	m_pActiceScene = nullptr;
	SceneFade::Destroy();
}
