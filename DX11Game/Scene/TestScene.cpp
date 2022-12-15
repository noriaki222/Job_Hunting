#include "TestScene.h"

TestScene::TestScene()
{
	m_pTest2D = new Test2DObj;
	m_pTest3D = new Test3D;
	m_pTest3D->Init();
	CCamera::Set(&m_camera);
}

TestScene::~TestScene()
{
	delete m_pTest2D;
	delete m_pTest3D;
}