#include "fog.h"

Fog::Fog() : Object2D(L"data/texture/fog.png", DirectX::XMFLOAT2(20.0f, 10.0f))
{
	m_drawOrder = DEFAULT_3D_ORDER + 10;
}

Fog::~Fog()
{
}

void Fog::Update()
{
	m_rigidbody.spd.x = spd;
}
