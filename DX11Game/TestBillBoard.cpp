#include "TestBillBoard.h"

TestBillBoard::TestBillBoard() : Object2D(L"data/texture/kianu2.png", DirectX::XMFLOAT2(20.0f, 10.0f))
{
	//m_transform.pos = DirectX::XMFLOAT3(40.0f, 0.0f, 0.0f);
	//m_visible = false;
	m_drawOrder = DEFAULT_3D_ORDER + 10;
}

TestBillBoard::~TestBillBoard()
{
}

void TestBillBoard::Draw()
{
	//SetRenderTarget(RT_DEBUG);
	Object2D::Draw();
}
