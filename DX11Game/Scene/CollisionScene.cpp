#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	m_p3D = CreateObj<Test3D>();
	m_p3D2 = CreateObj<TestCollision>();
	m_p3D2->SetTarget(m_p3D);
	m_pEnemy = CreateObj<TestEnemy>();
	m_cam.Init();
	CCamera::Set(&m_cam);
}

CollisionScene::~CollisionScene()
{
}
