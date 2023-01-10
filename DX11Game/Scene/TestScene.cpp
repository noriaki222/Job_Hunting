#include "TestScene.h"

TestScene::TestScene()
{
	m_pTest2D = CreateObj(m_pTest2D);
	m_pTest3D = CreateObj(m_pTest3D);
	m_pSky = CreateObj(m_pSky);
	CCamera::Set(&m_camera);
	CCamera::Get()->SetSky(m_pSky);
	m_pLand = CreateObj(m_pLand);
	m_pPlayer = CreateObj(m_pPlayer);
	m_pPlayer->SetLand(m_pLand);
	m_pBillboard = CreateObj(m_pBillboard);
}

TestScene::~TestScene()
{
	SAFE_DELETE(m_pBillboard);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pLand);
	SAFE_DELETE(m_pSky);
	SAFE_DELETE(m_pTest2D);
	SAFE_DELETE(m_pTest3D);
}