#pragma once
#include "../Core/SceneBase.h"
#include "../Object/LightScene/LightModel.h"
#include "../TestCamera.h"
#include "../Object/LightScene/TestLight.h"

class LightScene : public SceneBase
{
public:
	LightScene();
	~LightScene();

	void Update();

private:
	LightModel* m_pModel;
	TestCamera m_camera;
	TestLight m_light;
};