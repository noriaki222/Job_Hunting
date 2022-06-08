#include "Object2D.h"
#include "../Base/Texture.h"

Object2D::Object2D()
{
	m_blendState = BS_ALPHABLEND;
	m_pTex = nullptr;
}

Object2D::Object2D(const LPCWSTR path)
{
	m_blendState = BS_ALPHABLEND;
	m_pTex = nullptr;
	LoadTexture(path);
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
	Polygon::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	Polygon::SetPos(0.0f, 0.0f);
	Polygon::SetUV(0.0f, 0.0f);
	Polygon::SetSize(500.0f, 500.0f);
	Polygon::SetTexture(m_pTex);
	Polygon::Draw(pDC);
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
