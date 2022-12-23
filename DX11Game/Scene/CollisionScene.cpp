#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	m_p3D = CreateObj(m_p3D);
	m_p3D2 = CreateObj(m_p3D2);
	m_p3D2->SetTarget(m_p3D);
	m_cam.Init();
	CCamera::Set(&m_cam);
}

CollisionScene::~CollisionScene()
{
	SAFE_DELETE(m_p3D2);
	SAFE_DELETE(m_p3D);
}
