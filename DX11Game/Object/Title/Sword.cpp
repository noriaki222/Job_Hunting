#include "Sword.h"

Sword::Sword()
{
	SetModel(CModel::GetModel(MODEL_SWORD));
	m_transform.scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_transform.pos = DirectX::XMFLOAT3(-10.0f, -5.0f, -10.0f);
	m_transform.rot = DirectX::XMFLOAT3(90.0f, 0.0f, 0.0f);
}

Sword::~Sword()
{
}
