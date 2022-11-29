#include "SceneBase.h"

SceneBase::SceneBase()
{
	ObjectManager::Create();
	m_pObjMng = ObjectManager::GetInstance();
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
}

void SceneBase::Draw()
{
	m_pObjMng->Draw();
}
