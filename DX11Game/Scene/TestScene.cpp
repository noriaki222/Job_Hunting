#include "TestScene.h"

TestScene::TestScene()
{
	m_pTest2D = CreateObj(m_pTest2D);
	m_pTest3D = CreateObj(m_pTest3D);
	m_pSky = CreateObj(m_pSky);
	CCamera::Set(&m_camera);
}

TestScene::~TestScene()
{
	SAFE_DELETE(m_pSky);
	SAFE_DELETE(m_pTest2D);
	SAFE_DELETE(m_pTest3D);
}