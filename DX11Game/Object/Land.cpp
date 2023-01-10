#include "Land.h"

using namespace DirectX;

Land::Land()
{
	SetModel(CModel::GetModel(MODEL_LAND));
	m_transform.scale = DirectX::XMFLOAT3(0.1f, 0.1f, 0.1f);
	m_tag = TAG_LAND;
	m_drawOrder = DEFAULT_2D_ORDER - 1;
}

Land::~Land()
{
	FInVertex();
}

void Land::Init()
{
	InitVertex();
}

void Land::InitVertex()
{
	CAssimpModel* pModel = GetModel();
	pModel->GetVertexCount(&m_nVertex, &m_nIndex);
	m_pVertex = new TAssimpVertex[m_nVertex];
	m_pIndex = new UINT[m_nIndex];
	pModel->GetVertex(m_pVertex, m_pIndex);
}

void Land::FInVertex()
{
	SAFE_DELETE_ARRAY(m_pIndex);
	SAFE_DELETE_ARRAY(m_pVertex);
}

bool Land::CollisionRay(DirectX::XMFLOAT3 vP0, DirectX::XMFLOAT3 vW, DirectX::XMFLOAT3 * pX, DirectX::XMFLOAT3 * pN)
{
	for (UINT i = 0; i < m_nIndex; )
	{
		// 三角形の頂点
		XMFLOAT3 vV0, vV1, vV2;
		XMFLOAT3& v0 = m_pVertex[m_pIndex[i++]].vPos;
		vV0.x = v0.x * m_transform.scale.x; vV0.y = v0.y * m_transform.scale.y; vV0.z = v0.z * m_transform.scale.z;
		XMFLOAT3& v1 = m_pVertex[m_pIndex[i++]].vPos;
		vV1.x = v1.x * m_transform.scale.x; vV1.y = v1.y * m_transform.scale.y; vV1.z = v1.z * m_transform.scale.z;
		XMFLOAT3& v2 = m_pVertex[m_pIndex[i++]].vPos;
		vV2.x = v2.x * m_transform.scale.x; vV2.y = v2.y * m_transform.scale.y; vV2.z = v2.z * m_transform.scale.z;

		// 法線ベクトル
		XMVECTOR v0v1 = XMVectorSet(vV1.x - vV0.x, vV1.y - vV0.y, vV1.z - vV0.z, 0.0f);
		XMVECTOR v1v2 = XMVectorSet(vV2.x - vV1.x, vV2.y - vV1.y, vV2.z - vV1.z, 0.0f);
		XMVECTOR n = XMVector3Normalize(XMVector3Cross(v0v1, v1v2));

		// 法線ベクトルとレイの方向ベクトルとの内積
		float base;
		XMStoreFloat(&base, XMVector3Dot(n, XMLoadFloat3(&vW)));
		// 分母が0なら平行
		if (base == 0.0f) {	continue; }
		
		// 媒介変数を求める
		float t;
		XMStoreFloat(&t, XMVector3Dot(n, XMVectorSet(vV0.x - vP0.x, vV0.y - vP0.y, vV0.z - vP0.z, 0.0f)));
		t /= base;
		// tが負ならばレイは後方
		if (t < 0.0f) { continue; }

		// 交点を求める
		XMFLOAT3 vX;
		vX.x = vP0.x + t * vW.x;
		vX.y = vP0.y + t * vW.y;
		vX.z = vP0.z + t * vW.z;
		// 交点が三角形の内部か比較
		float dot;
		XMStoreFloat(&dot, XMVector3Dot(n, XMVector3Cross(v0v1, XMVectorSet(vX.x - vV0.x, vX.y - vV0.y, vX.z - vV0.z, 0.0f))));
		if (dot < 0.0f) { continue; }
		XMStoreFloat(&dot, XMVector3Dot(n, XMVector3Cross(v1v2, XMVectorSet(vX.x - vV1.x, vX.y - vV1.y, vX.z - vV1.z, 0.0f))));
		if (dot < 0.0f) { continue; }
		XMVECTOR v2v0 = XMVectorSet(vV0.x - vV2.x, vV0.y - vV2.y, vV0.z - vV2.z, 0.0f);
		XMStoreFloat(&dot, XMVector3Dot(n, XMVector3Cross(v2v0, XMVectorSet(vX.x - vV2.x, vX.y - vV2.y, vX.z - vV2.z, 0.0f))));
		if (dot < 0.0f) { continue; }

		// 点が内側なためあたっている
		if (pX) { *pX = vX; }
		if (pN) { XMStoreFloat3(pN, n); }
		return true;
	}
	// あたっていない
	return false;
}
