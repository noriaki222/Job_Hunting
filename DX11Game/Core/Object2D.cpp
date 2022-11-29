#include "Object2D.h"
#include "../Base/Texture.h"
#include "../Base/Camera.h"
#include "../Base/Light.h"

Object2D::Object2D()
{
	m_blendState = BS_ALPHABLEND;
	m_pTex = nullptr;
	m_billboard = BILLBOARD_ALL;
	m_color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_uv = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_updateOrder = DEFAULT_2D_ORDER;
	m_drawOrder = DEFAULT_2D_ORDER;
}

Object2D::Object2D(const LPCWSTR path)
{
	m_blendState = BS_ALPHABLEND;
	m_pTex = nullptr;
	m_billboard = BILLBOARD_ALL;
	LoadTexture(path);
	m_color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_uv = DirectX::XMFLOAT2(0.0f, 0.0f);

	m_updateOrder = 0;
	m_drawOrder = 0;
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
	
	CLight::Get()->SetDisable();
	DirectX::XMFLOAT4X4 mView = CCamera::Get()->GetViewMatrix();

	switch (m_billboard)
	{
	case BILLBOARD_NONE:
		break;
	case BILLBOARD_ALL:
		m_mWorld._21 = mView._12 * m_transform.scale.y;
		m_mWorld._22 = mView._22 * m_transform.scale.y;
		m_mWorld._23 = mView._32 * m_transform.scale.y;
		m_mWorld._24 = 0.0f;
		break;
	case BILLBOARD_NOT_Y:
		m_mWorld._11 = mView._11 * m_transform.scale.x;
		m_mWorld._12 = mView._21 * m_transform.scale.x;
		m_mWorld._13 = mView._31 * m_transform.scale.x;
		m_mWorld._14 = 0.0f;

		m_mWorld._31 = mView._13;
		m_mWorld._32 = mView._23;
		m_mWorld._33 = mView._33;
		m_mWorld._34 = 0.0f;
		break;
	default:
		break;
	}
	ID3D11DeviceContext* pDC = GetDeviceContext();
	SetZBuffer(false);
	SetBlendState(m_blendState);
	Polygon::SetColor(m_color.x, m_color.y, m_color.z, m_color.w);
	Polygon::SetUV(m_uv.x, m_uv.y);
	Polygon::SetTexture(m_pTex);
	Polygon::Draw(pDC, m_mWorld);

	CLight::Get()->SetEnable();
	SetBlendState(BS_NONE);
	SetZBuffer(true);
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