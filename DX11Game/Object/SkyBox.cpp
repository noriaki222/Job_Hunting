#include "SkyBox.h"
#include "../Base/Light.h"
#include "../Base/Camera.h"

SkyBox::SkyBox()
{
	SetModel(CModel::GetModel(MODEL_SKY));
	m_tag = TAG_SKY;
	m_drawOrder = DEFAULT_2D_ORDER - 1;
}

SkyBox::~SkyBox()
{

}

void SkyBox::Draw()
{
	SetZBuffer(false);
	CLight* pLight = CLight::Get();
	pLight->SetDisable();
	Object3D::Draw();
	pLight->SetEnable();
	SetZBuffer(true);
}