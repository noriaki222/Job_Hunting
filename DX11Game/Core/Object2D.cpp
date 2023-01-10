#include "Object2D.h"
#include "../Base/Texture.h"
#include "../Base/Camera.h"
#include "../Base/Light.h"

using namespace DirectX;

#define M_DEFFUSE XMFLOAT4(1.0f,1.0f,1.0f,1.0f)
#define M_SPECULAR XMFLOAT4(0.0f,0.0f,0.0f,1.0f)
#define M_POWER (1.0f)
#define M_AMBIENT XMFLOAT4(0.0f,0.0f,0.0f,1.0f)
#define M_EMISSIVE XMFLOAT4(1.0f,1.0f,1.0f,1.0f)


Object2D::Object2D()
{
	m_type = TYPE_2D;
	m_billboard = BILLBOARD_NONE;
	m_defaultsize.x = 100.0f; m_defaultsize.y = 100.0f;

	MakeVertex();

	m_pTex = nullptr;
	m_blendState = BS_ALPHABLEND;

	m_material.m_Diffuse = M_DEFFUSE;
	m_material.m_Ambient = M_AMBIENT;
	m_material.m_Specular = M_SPECULAR;
	m_material.m_Emissive = M_EMISSIVE;
	m_material.m_Power = M_POWER;
	m_mesh.SetMaterial(&m_material);

	m_VS = VS_3D;
	m_PS = PS_3D;
}

Object2D::Object2D(const LPCWSTR path, XMFLOAT2 size) : m_defaultsize(size)
{
	m_type = TYPE_2D;
	m_billboard = BILLBOARD_NONE;

	MakeVertex();

	m_pTex = nullptr;
	m_blendState = BS_ALPHABLEND;

	m_material.m_Diffuse = M_DEFFUSE;
	m_material.m_Ambient = M_AMBIENT;
	m_material.m_Specular = M_SPECULAR;
	m_material.m_Emissive = M_EMISSIVE;
	m_material.m_Power = M_POWER;
	m_mesh.SetMaterial(&m_material);

	LoadTexture(path);

	m_VS = VS_3D;
	m_PS = PS_BILLBOARD;
}

Object2D::~Object2D()
{
	m_mesh.Fin();
	if (m_pTex)
	{
		SAFE_RELEASE(m_pTex);
	}
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
	SetBlendState(m_blendState);
	SetZWrite(false);

	ID3D11DeviceContext* pDC = GetDeviceContext();

	CLight::Get()->SetDisable();
	XMFLOAT4X4& mView = CCamera::Get()->GetViewMatrix();

	XMFLOAT4X4 mW = m_mWorld;

	switch (m_billboard)
	{
	case BILLBOARD_NONE:
		mW._11 = mW._11 * m_defaultsize.x * m_transform.scale.x;
		mW._12 = mW._12 * m_defaultsize.x * m_transform.scale.x;
		mW._13 = mW._13 * m_defaultsize.x * m_transform.scale.x;
		mW._14 = 0.0f;
		mW._21 = mW._21 * m_defaultsize.y * m_transform.scale.y;
		mW._22 = mW._22 * m_defaultsize.y * m_transform.scale.y;
		mW._23 = mW._23 * m_defaultsize.y * m_transform.scale.y;
		mW._24 = 0.0f;
		break;
	case BILLBOARD_ALL:
		mW._21 = mView._12 * m_defaultsize.y * m_transform.scale.y;
		mW._22 = mView._22 * m_defaultsize.y * m_transform.scale.y;
		mW._23 = mView._32 * m_defaultsize.y * m_transform.scale.y;
		mW._24 = 0.0f;
		break;
	case BILLBOARD_NOT_Y:
		mW._11 = mView._11 * m_defaultsize.x * m_transform.scale.x;
		mW._12 = mView._21 * m_defaultsize.x * m_transform.scale.x;
		mW._13 = mView._31 * m_defaultsize.x * m_transform.scale.x;
		mW._14 = 0.0f;

		mW._31 = mView._13;
		mW._32 = mView._23;
		mW._33 = mView._33;
		mW._34 = 0.0f;
		break;
	default:
		break;
	}

	m_mesh.SetWorld(&mW);
	m_mesh.SetTexture(m_pTex);

	m_material.m_Diffuse = m_color;
	m_mesh.SetMaterial(&m_material);
	m_mesh.SetVS(m_VS);
	m_mesh.SetPS(m_PS);
	m_mesh.Draw();
	
	CLight::Get()->SetEnable();
	SetZWrite(true);
	SetBlendState(BS_NONE);
}

void Object2D::LoadTexture(const LPCWSTR texPath)
{
	ID3D11Device* pDevice = GetDevice();
	HRESULT hr = CreateTextureFromFile(pDevice, texPath, &m_pTex);
}

void Object2D::MakeVertex()
{
	m_mesh.m_nNumVertex = 4;
	VERTEX_3D* pVertexWk = new VERTEX_3D[m_mesh.m_nNumVertex];
	pVertexWk[0].vtx = XMFLOAT3(-0.5f, 0.5f, 0.0f);
	pVertexWk[1].vtx = XMFLOAT3(0.5f, 0.5f, 0.0f);
	pVertexWk[2].vtx = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	pVertexWk[3].vtx = XMFLOAT3(0.5f, -0.5f, 0.0f);
	pVertexWk[0].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pVertexWk[1].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pVertexWk[2].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pVertexWk[3].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pVertexWk[0].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
	pVertexWk[1].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
	pVertexWk[2].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
	pVertexWk[3].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
	pVertexWk[0].tex = XMFLOAT2(0.0f, 0.0f);
	pVertexWk[1].tex = XMFLOAT2(1.0f, 0.0f);
	pVertexWk[2].tex = XMFLOAT2(0.0f, 1.0f);
	pVertexWk[3].tex = XMFLOAT2(1.0f, 1.0f);

	m_mesh.m_nNumIndex = 4;
	int* pIndexWk = new int[m_mesh.m_nNumIndex];

	pIndexWk[0] = 0;
	pIndexWk[1] = 1;
	pIndexWk[2] = 2;
	pIndexWk[3] = 3;

	HRESULT hr = m_mesh.Init(pVertexWk, 4, pIndexWk, 4);
	delete[] pIndexWk;
	delete[] pVertexWk;
}
