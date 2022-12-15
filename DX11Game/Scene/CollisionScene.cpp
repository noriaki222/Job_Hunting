#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	m_p3D = new Test3D;
	m_p3D->Init();
	m_p3D2 = new TestCollision;
	m_p3D2->Init();
	m_p3D2->SetTarget(m_p3D);
	m_cam.Init();
	CCamera::Set(&m_cam);
}

CollisionScene::~CollisionScene()
{
}
