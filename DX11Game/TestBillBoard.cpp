#include "TestBillBoard.h"

TestBillBoard::TestBillBoard() : Object2D(L"data/texture/fog.png", DirectX::XMFLOAT2(20.0f, 10.0f))
{
	m_drawOrder = DEFAULT_3D_ORDER + 10;
	//m_visible = false;
}

TestBillBoard::~TestBillBoard()
{
}
