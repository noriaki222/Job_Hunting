#include "Box.h"

namespace {
	const CMeshMaterial g_material = {
		DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 0.3f),
		DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 0.3f),
		DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f),
		DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f),
		1.0f
	};
	const DirectX::XMFLOAT4 g_vRed(1.0f, 0.0f, 0.0f, 0.3f);
	const DirectX::XMFLOAT4 g_vGreen(0.0f, 1.0f, 0.0f, 0.3f);
}

Box::Box()
{
}

Box::~Box()
{
}

void Box::Draw()
{
	// 平行移動マトリックス
	DirectX::XMMATRIX mMove = DirectX::XMMatrixTranslation(m_center->x, m_center->y, m_center->z);

	// ワールドマトリックスをかける
	DirectX::XMMATRIX mWorld = DirectX::XMLoadFloat4x4(m_world);
	mWorld = DirectX::XMMatrixMultiply(mMove, mWorld);

	DirectX::XMFLOAT4X4 mW;
	DirectX::XMStoreFloat4x4(&mW, mWorld);
	m_mesh.SetWorld(&mW);
	m_mesh.SetVS(VS_3D);
	m_mesh.SetPS(PS_BOX);
	m_mesh.Draw();
}

HRESULT Box::Init(DirectX::XMFLOAT3*box, DirectX::XMFLOAT3 * center, DirectX::XMFLOAT4X4* world, DirectX::XMFLOAT3* scale)
{
	HRESULT hr = S_OK;
	m_center = center;
	m_world = world;
	DirectX::XMFLOAT3 vSize;
	vSize.x = box->x * 2.0f;
	vSize.y = box->y * 2.0f;
	vSize.z = box->z * 2.0f;
	const static float vtx[] = {
		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
	};
	const static float nor[] = {
		 0.0f,  0.0f, -1.0f,
		 1.0f,  0.0f,  0.0f,
		 0.0f,  0.0f,  1.0f,
		-1.0f,  0.0f,  0.0f,
		 0.0f,  1.0f,  0.0f,
		 0.0f, -1.0f,  0.0f,
	};
	const static int face[] = {
		4, 0, 5, 1, 5, 0,
		5, 1, 7, 3, 7, 1,
		7, 3, 6, 2, 6, 3,
		6, 2, 4, 0, 4, 2,
		0, 2, 1, 3, 1, 2,
		6, 4, 7, 5, 7, 4,
	};
	const static float uv[] = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
	};
	VERTEX_3D* pVertexWk = new VERTEX_3D[24];
	int* pIndexWk = new int[36];
	VERTEX_3D* pVtx = pVertexWk;
	int nIdx = 0;
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 4; ++j) {
			pVtx->vtx.x = vtx[face[i * 6 + j] * 3 + 0] * box->x;
			pVtx->vtx.y = vtx[face[i * 6 + j] * 3 + 1] * box->y;
			pVtx->vtx.z = vtx[face[i * 6 + j] * 3 + 2] * box->z;
			pVtx->nor.x = nor[i * 3 + 0];
			pVtx->nor.y = nor[i * 3 + 1];
			pVtx->nor.z = nor[i * 3 + 2];
			pVtx->tex.x = uv[j * 2 + 0];
			pVtx->tex.y = uv[j * 2 + 1];
			pVtx->diffuse = DirectX::XMFLOAT4(1, 1, 1, 1);
			++pVtx;
			pIndexWk[i * 6 + j] = nIdx;
			++nIdx;
		}
		pIndexWk[i * 6 + 4] = pIndexWk[i * 6 + 2];
		pIndexWk[i * 6 + 5] = pIndexWk[i * 6 + 1];
	}
	hr = m_mesh.Init(pVertexWk, 24, pIndexWk, 36);
	m_mesh.SetMaterial(&g_material);
	delete[] pIndexWk;
	delete[] pVertexWk;
	return hr;
}

void Box::SetRed()
{
	CMeshMaterial mat = g_material;
	mat.m_Diffuse = mat.m_Ambient = g_vRed;
	m_mesh.SetMaterial(&mat);
}

void Box::SetGreen()
{
	CMeshMaterial mat = g_material;
	mat.m_Diffuse = mat.m_Ambient = g_vGreen;
	m_mesh.SetMaterial(&mat);
}
