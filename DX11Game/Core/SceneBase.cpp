#include "SceneBase.h"
#include "../Manager/SceneManager.h"
#include "../Base/Input.h"

SceneBase::SceneBase()
{
	ObjectManager::Create();
	m_pObjMng = ObjectManager::GetInstance();
	CCamera::Set(&m_camera);
}

SceneBase::~SceneBase()
{
	ObjectManager::Destory();
}

void SceneBase::Update()
{
}

void SceneBase::ConstUpdate()
{
	m_pObjMng->Update();

#ifdef _DEBUG
	// デバック時のシーン切り替え
	if (IsKeyPress(VK_LSHIFT))
	{
		if (IsKeyPress('0'))
		{
			SceneManager::GetInstance()->SetSecne(SCENE_TITLE);
		}
		if (IsKeyPress('1'))
		{
			SceneManager::GetInstance()->SetSecne(SCENE_COLLISION);
		}
		if (IsKeyPress('2'))
		{
			SceneManager::GetInstance()->SetSecne(SCENE_TEST);
		}
		if (IsKeyPress('3'))
		{
			SceneManager::GetInstance()->SetSecne(SCENE_TEST);
		}
		if (IsKeyPress('4'))
		{
			SceneManager::GetInstance()->SetSecne(SCENE_TEST);
		}
		if (IsKeyPress('5'))
		{
			SceneManager::GetInstance()->SetSecne(SCENE_TEST);
		}
	}
#endif // _DEBUG

}

void SceneBase::Draw()
{
	m_pObjMng->Sort();
	m_pObjMng->Draw();
}
