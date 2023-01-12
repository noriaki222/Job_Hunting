#include "Title.h"

Title::Title()
{
	m_pSky = CreateObj<SkyBox>();
	CCamera::Set(&m_camera);
	CCamera::Get()->SetSky(m_pSky);
	m_pLand = CreateObj<Land>();
	m_pSword = CreateObj<Sword>();
	for (int i = 0; i < 5; i++)
	{
		m_pFog = CreateObj<Fog>();
		m_pFog->SetPos(DirectX::XMFLOAT3(rand() % 20, 0.0f, rand() % 100));
		m_pFog->spd = (rand() % 10) * 0.01f;
	}
	m_pLogo = CreateObj<Logo>();
}

Title::~Title()
{
}
