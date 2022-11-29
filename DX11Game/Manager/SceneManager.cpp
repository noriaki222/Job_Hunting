#include "SceneManager.h"
#include "../Base/Camera.h"
#include "../Scene/TestScene.h"

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
	
	m_pSceneFade->Update();
	if (m_isChange)
	{
		if (m_pSceneFade->GetFadeScene() == FADESTATE_NONE)
		{
			// Œ»Ý‚Ì‰æ–Ê‚ðI—¹
			delete m_pActiceScene;
			CCamera::Get()->Init();
			m_eScene = m_eNextScene;

			// ŽŸ‚Ì‰æ–Ê‚ð‰Šú‰»
			switch (m_eScene)
			{
			case SCENE_TEST:
				m_pActiceScene = new TestScene;
				break;
			case SCENE_NONE:
				break;
			case MAX_SCENE:
				break;
			}
			m_pSceneFade->FadeInScene();
			m_isChange = false;
		}
	}
}

void SceneManager::Draw()
{
	m_pActiceScene->Draw();
	SetBlendState(BS_ALPHABLEND);
	m_pSceneFade->Draw();
	SetBlendState(BS_NONE);
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
