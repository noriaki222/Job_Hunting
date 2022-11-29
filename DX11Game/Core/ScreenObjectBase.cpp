#include "ScereenObjectBase.h"

ScereenObjectBase::ScereenObjectBase():m_pTexture(nullptr),m_color(1.0f, 1.0f, 1.0f, 1.0f), m_uv(0.0f ,0.0f)
{
	m_transform = Transform::Zero();
}

ScereenObjectBase::ScereenObjectBase(const char * texPath): m_color(1.0f, 1.0f, 1.0f, 1.0f), m_uv(0.0f, 0.0f)
{
	m_transform = Transform::Zero();
	LoadTexture(texPath);
}

ScereenObjectBase::~ScereenObjectBase()
{
}

void ScereenObjectBase::Update()
{
}

void ScereenObjectBase::Draw()
{
	SetZBuffer(false);
	ID3D11DeviceContext* pDC = GetDeviceContext();
	Polygon::SetSize(SCREEN_WIDTH * m_transform.scale.x, SCREEN_HEIGHT * m_transform.scale.y);
	Polygon::SetPos(m_transform.pos.x, m_transform.pos.y);
	Polygon::SetAngle(0.0f);
	Polygon::SetColor(m_color.x, m_color.y, m_color.z, m_color.w);
	Polygon::SetTexture(m_pTexture);
	Polygon::SetFrameSize(1.0f, 1.0f);
	Polygon::SetUV(m_uv.x, m_uv.y);
	Polygon::Draw(pDC);
	SetZBuffer(true);
}

void ScereenObjectBase::LoadTexture(const char* texPath)
{
	CreateTextureFromFile(GetDevice(), texPath, &m_pTexture);
}
