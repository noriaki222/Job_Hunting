#include "Logo.h"

Logo::Logo() : ObjectUI(L"data/texture/twitter_header_photo_1.png")
{
	m_transform.scale = DirectX::XMFLOAT3(500.0f, 200.0f, 1.0f);
	m_transform.pos = DirectX::XMFLOAT3(350.0f, 0.0f, 0.0f);
}

Logo::~Logo()
{
}
