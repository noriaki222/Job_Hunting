#pragma once
#include "../Manager/SceneManager.h"
#include "../TestCamera.h"
#include "../Object/SkyBox.h"
#include "../Object/Land.h"
#include "../Object/Title/Sword.h"

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
};