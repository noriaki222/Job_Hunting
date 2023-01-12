#pragma once
#include "../Manager/SceneManager.h"
#include "../TestCamera.h"
#include "../Object/SkyBox.h"
#include "../Object/Land.h"
#include "../Object/Title/Sword.h"
#include "../Object/Title/Fog.h"
#include "../Object/Title/Logo.h"

class Title : public SceneBase
{
public:
	Title();
	~Title();

private:
	TestCamera m_camera;
	SkyBox* m_pSky;
	Land* m_pLand;
	Sword* m_pSword;
	Fog* m_pFog;
	Logo* m_pLogo;
};