#include "Sword.h"

Sword::Sword()
{
	SetModel(CModel::GetModel(MODEL_SWORD));
	m_transform.pos.y = -5.0f;
	m_transform.rot = DirectX::XMFLOAT3(90.0f, 0.0f, 0.0f);
}

Sword::~Sword()
{
}
