#include "Test2DObj.h"

Test2DObj::Test2DObj() : Object2D(L"data/texture/title_logo.png")
{
	m_transform.scale = DirectX::XMFLOAT3(500.0f, 500.0f, 1.0f);
}

Test2DObj::~Test2DObj()
{
}