#include "LightModel.h"

LightModel::LightModel()
{
	using namespace DirectX;
	SetModel(CModel::GetModel(MODEL_TEAPOT));
	m_isAnim = false;
	m_transform.pos = XMFLOAT3(0.0f, 15.0f, 0.0f);
	m_transform.scale = XMFLOAT3(10.0f, 10.0f, 10.0f);
	SetPS(PS_LIGHTING);
}

LightModel::~LightModel()
{
}
