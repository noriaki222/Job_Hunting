#include "Object2D.h"
#include "../Base/Texture.h"

Object2D::Object2D()
{
	m_blendState = BS_ALPHABLEND;
	m_pTex = nullptr;
	m_billboard = BILLBOARD_NONE;
	m_color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_uv = DirectX::XMFLOAT2(0.0f, 0.0f);
}

Object2D::Object2D(const LPCWSTR path)
{
	m_blendState = BS_ALPHABLEND;
	m_pTex = nullptr;
	m_billboard = BILLBOARD_NONE;
	LoadTexture(path);
	m_color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_uv = DirectX::XMFLOAT2(0.0f, 0.0f);
}

Object2D::~Object2D()
{
	ReleseTexture();
}

void Object2D::Init()
{
}

void Object2D::Uninit()
{
}

void Object2D::Update()
{
}

void Object2D::Draw()
{
	UpdateMatrix();

	ID3D11DeviceContext* pDC = GetDeviceContext();
	SetZBuffer(false);
	SetBlendState(m_blendState);
	Polygon::SetColor(m_color.x, m_color.y, m_color.z, m_color.w);
	Polygon::SetUV(m_uv.x, m_uv.y);
	Polygon::SetTexture(m_pTex);
	Polygon::Draw(pDC, m_mWorld);
	SetBlendState(BS_NONE);
}

void Object2D::LoadTexture(const LPCWSTR texPath)
{
	ID3D11Device* pDevice = GetDevice();
	HRESULT hr = CreateTextureFromFile(pDevice, texPath, &m_pTex);
}

void Object2D::ReleseTexture()
{
	if (m_pTex)
	{
		SAFE_RELEASE(m_pTex);
	}
}