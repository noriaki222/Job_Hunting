#include "LightScene.h"

LightScene::LightScene()
{
	m_pModel = CreateObj<LightModel>();
	CCamera::Set(&m_camera);
	CLight::Set(&m_light);
}

LightScene::~LightScene()
{
	CLight::Set();
}

void LightScene::Update()
{
	m_light.Update();
}
