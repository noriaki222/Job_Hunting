#include "Test2DObj.h"

Test2DObj::Test2DObj() : ObjectUI(L"data/texture/title_logo.png")
{
	m_transform.scale = DirectX::XMFLOAT3(500.0f, 500.0f, 1.0f);
	//m_visible = false;
}

Test2DObj::~Test2DObj()
{
}

void Test2DObj::Draw()
{
	//SetRenderTarget(RT_DEBUG);
	ObjectUI::Draw();
}
