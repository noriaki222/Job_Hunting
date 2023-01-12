#include "TestScene.h"

TestScene::TestScene()
{
	m_pTest2D = CreateObj<Test2DObj>();
	m_pTest3D = CreateObj<Test3D>();
	m_pSky = CreateObj<SkyBox>();
	CCamera::Set(&m_camera);
	CCamera::Get()->SetSky(m_pSky);
	m_pLand = CreateObj<Land>();
	m_pPlayer = CreateObj<TestPlayer>();
	m_pPlayer->SetLand(m_pLand);
	m_pBillboard = CreateObj<TestBillBoard>();

}

TestScene::~TestScene()
{
}