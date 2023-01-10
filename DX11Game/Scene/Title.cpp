#include "Title.h"

Title::Title()
{
	m_pSky = CreateObj(m_pSky);
	CCamera::Set(&m_camera);
	CCamera::Get()->SetSky(m_pSky);
	m_pLand = CreateObj(m_pLand);
	m_pSword = CreateObj(m_pSword);
}

Title::~Title()
{
	SAFE_DELETE(m_pSword);
	SAFE_DELETE(m_pLand);
	SAFE_DELETE(m_pSky);
}
