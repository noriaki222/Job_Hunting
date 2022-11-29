#include "TestScene.h"

TestScene::TestScene()
{
	m_pTest2D = new Test2DObj;
	m_pTest3D = new Test3D;
}

TestScene::~TestScene()
{
	delete m_pTest2D;
	delete m_pTest3D;
}

void TestScene::Update()
{
}
