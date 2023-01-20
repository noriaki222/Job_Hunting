#include "ObjectBase.h"

#include "../Manager/ObjectManager.h"

using namespace DirectX;

ObjectBase::ObjectBase()
{
	m_transform = Transform::Zero();
	m_rigidbody = RigidBody::Zero();
	m_coll = Collider::Zero();
	m_enable = true;
	m_visible = true;
	m_color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_tag = TAG_NONE;
	m_type = TYPE_2D;
	XMStoreFloat4x4(&m_mWorld, XMMatrixIdentity());
	m_axisRot = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_startRot = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

	int m_updateOrder = 0;
	int m_drawOrder = 0;

	m_it = ObjectManager::GetInstance()->AddManager(this);
}

ObjectBase::~ObjectBase()
{
	ObjectManager::GetInstance()->Release(m_it);
}

void ObjectBase::UpdateMatrix()
{
	m_rigidbody.spd.x += m_rigidbody.acc.x;
	m_rigidbody.spd.y += m_rigidbody.acc.y;
	m_rigidbody.spd.z += m_rigidbody.acc.z;

	if (m_rigidbody.isGravity)
	{
		m_rigidbody.spd.y -= GRAVITY;
	}

	m_transform.pos.x += m_rigidbody.spd.x;
	m_transform.pos.y += m_rigidbody.spd.y;
	m_transform.pos.z += m_rigidbody.spd.z;

	if (m_transform.rot.x > 180.0f)
	{
		m_transform.rot.x -= 360.f;
	}
	if (m_transform.rot.x < -180.0f)
	{
		m_transform.rot.x += 360.0f;
	}
	if (m_transform.rot.y > 180.0f)
	{
		m_transform.rot.y -= 360.f;
	}
	if (m_transform.rot.y < -180.0f)
	{
		m_transform.rot.y += 360.0f;
	}
	if (m_transform.rot.z > 180.0f)
	{
		m_transform.rot.z -= 360.f;
	}
	if (m_transform.rot.z < -180.0f)
	{
		m_transform.rot.z += 360.0f;
	}

	XMMATRIX mtxWorld, mtxRot, mtxAxisRot, mtxTranslate;

	// ワールドマトリックスの初期化
	mtxWorld = XMMatrixIdentity();

	mtxWorld = XMMatrixMultiply(mtxWorld, XMMatrixScaling(m_transform.scale.x, m_transform.scale.y, m_transform.scale.z));

	// 回転を反映
	mtxRot = XMMatrixRotationRollPitchYaw(XMConvertToRadians(m_transform.rot.x),
		XMConvertToRadians(m_transform.rot.y), XMConvertToRadians(m_transform.rot.z));
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

	// 移動を反映
	mtxTranslate = XMMatrixTranslation(m_transform.pos.x, m_transform.pos.y, m_transform.pos.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

	// ワールドマトリックス設定
	XMStoreFloat4x4(&m_mWorld, mtxWorld);

	// 任意軸回転
	XMVECTOR axis;
	bool flg = false;
	if (m_axisRot.x != 0.0f)
	{
		flg = true;
		axis = XMVectorSet(m_mWorld._11, m_mWorld._12, m_mWorld._13, 0.0f);
		mtxAxisRot = XMMatrixRotationAxis(axis, XMConvertToRadians(m_axisRot.x));
	}
	if (m_axisRot.y != 0.0f)
	{
		flg = true;
		axis = XMVectorSet(m_mWorld._21, m_mWorld._22, m_mWorld._23, 0.0f);
		mtxAxisRot = XMMatrixRotationAxis(axis, XMConvertToRadians(m_axisRot.y));
	}
	if (m_axisRot.z != 0.0f)
	{
		flg = true;
		axis = XMVectorSet(m_mWorld._31, m_mWorld._32, m_mWorld._33, 0.0f);
		mtxAxisRot = XMMatrixRotationAxis(axis, XMConvertToRadians(m_axisRot.z));
	}
	if(flg)
		XMStoreFloat4x4(&m_mWorld, XMMatrixMultiply(XMLoadFloat4x4(&m_mWorld), mtxAxisRot));
}

void ObjectBase::SetRendreTargets()
{
	if (m_useRT.size() <= 0)
	{
		SetRenderTarget(RT_GAME);
		return;
	}
	ID3D11RenderTargetView** rts = new ID3D11RenderTargetView*[m_useRT.size()];

	for (int i = 0; i < m_useRT.size(); ++i)
	{
		if (m_useRT[i] == RT_UI)
		{
			rts[0] = GetRenderTargetView(RT_UI);
			GetDeviceContext()->OMSetRenderTargets(1, rts, GetDepthStencilView(DSV_2D));
			delete[] rts;
			rts = nullptr;
			return;
		}
		rts[i] = GetRenderTargetView(m_useRT[i]);
	}
	GetDeviceContext()->OMSetRenderTargets(m_useRT.size(), rts, GetDepthStencilView(DSV_3D));

	delete[] rts;
	rts = nullptr;
}

bool ObjectBase::Collision(EObjTag tag, ObjectBase* null = nullptr)
{
	ObjectBase* obj = ObjectManager::GetInstance()->FindObj(tag, null);
	if (obj)
	{
		if (Collision(obj))
		{
			return true;
		}
		Collision(tag, obj);
	}
	return false;
}

bool ObjectBase::Collision(ObjectBase * obj)
{
	if (obj == nullptr) { return false; }
	if (obj == this) { return false; }
	if (!(*m_it)->m_coll.isCollision || !obj->m_coll.isCollision) { return false; }

	
	// ワールドマトリックス取得
	XMFLOAT4X4 mW1 = m_mWorld;
	XMFLOAT4X4 mW2 = obj->GetWorld();
	// 中心座標取得
	XMFLOAT3 vP1, vP2;
	XMStoreFloat3(&vP1, XMVector3TransformCoord(XMLoadFloat3(&m_coll.center), XMLoadFloat4x4(&mW1)));
	XMStoreFloat3(&vP2, XMVector3TransformCoord(XMLoadFloat3(&obj->m_coll.center), XMLoadFloat4x4(&mW2)));

	// 中心座標間のベクトルを求める
	XMVECTOR vD;
	vD = XMVectorSet(vP2.x - vP1.x, vP2.y - vP1.y, vP2.z - vP1.z, 0.0f);
	// モデル座標軸取得
	XMVECTOR vN[6];
	vN[0] = XMVectorSet(GetLocalX().x, GetLocalX().y, GetLocalX().z, 0.0f);
	vN[1] = XMVectorSet(GetLocalY().x, GetLocalY().y, GetLocalY().z, 0.0f);
	vN[2] = XMVectorSet(GetLocalZ().x, GetLocalZ().y, GetLocalZ().z, 0.0f);
	vN[3] = XMVectorSet(obj->GetLocalX().x, obj->GetLocalX().y, obj->GetLocalX().z, 0.0f);
	vN[4] = XMVectorSet(obj->GetLocalY().x, obj->GetLocalY().y, obj->GetLocalY().z, 0.0f);
	vN[5] = XMVectorSet(obj->GetLocalZ().x, obj->GetLocalZ().y, obj->GetLocalZ().z, 0.0f);
	// OBBの大きさを掛けたベクトルを求める
	XMFLOAT3& vBox1 = m_coll.size;
	XMFLOAT3& vBox2 = obj->m_coll.size;
	XMVECTOR vL[6];
	vL[0] = XMVectorSet(GetLocalX().x * vBox1.x, GetLocalX().y * vBox1.x, GetLocalX().z * vBox1.x, 0.0f);
	vL[1] = XMVectorSet(GetLocalY().x * vBox1.y, GetLocalY().y * vBox1.y, GetLocalY().z * vBox1.y, 0.0f);
	vL[2] = XMVectorSet(GetLocalZ().x * vBox1.z, GetLocalZ().y * vBox1.z, GetLocalZ().z * vBox1.z, 0.0f);
	vL[3] = XMVectorSet(obj->GetLocalX().x * vBox2.x, obj->GetLocalX().y * vBox2.x, obj->GetLocalX().z * vBox2.x, 0.0f);
	vL[4] = XMVectorSet(obj->GetLocalY().x * vBox2.y, obj->GetLocalY().y * vBox2.y, obj->GetLocalY().z * vBox2.y, 0.0f);
	vL[5] = XMVectorSet(obj->GetLocalZ().x * vBox2.z, obj->GetLocalZ().y * vBox2.z, obj->GetLocalZ().z * vBox2.z, 0.0f);

	// 分解軸候補が面の法線ベクトル(モデル座標軸
	float fL, f, fD;
	for (int i = 0; i < 6; ++i)
	{
		XMVECTOR& vS = vN[i];	// 分解軸候補
		// OBBが分解軸へ落とす影の合計
		fL = 0.0f;
		for (int j = 0; j < 6; ++j)
		{
			XMStoreFloat(&f, XMVector3Dot(vS, vL[j]));
			fL += fabsf(f);
		}

		// 中心座標間の距離と比較
		XMStoreFloat(&fD, XMVector3Dot(vS, vD));
		fD = fabsf(fD);
		if (fL < fD) return false;
	}
	// 分解軸候補がそれぞれの辺に垂直なベクトル
	XMVECTOR vS;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 3; j < 6; ++j)
		{
			// 分解軸候補を求める
			vS = XMVector3Normalize(XMVector3Cross(vN[i], vN[j]));
			// OBBが分解軸へ落とす影の合計
			fL = 0.0f;
			for (int k = 0; k < 6; ++k)
			{
				XMStoreFloat(&f, XMVector3Dot(vS, vL[k]));
				fL += fabsf(f);
			}

			// 中心座標間の距離と比較
			XMStoreFloat(&fD, XMVector3Dot(vS, vD));
			fD = fabsf(fD);
			if (fL < fD) return false;
		}
	}

	return true;
	
}

void ObjectBase::RotAxisX(float angle)
{
	XMVECTOR axis;
	XMMATRIX mtxAxisRot;
	axis = XMVectorSet(m_mWorld._11, m_mWorld._12, m_mWorld._13, 0.0f);
	mtxAxisRot = XMMatrixRotationAxis(axis, XMConvertToRadians(angle));
	XMStoreFloat4x4(&m_mWorld, XMMatrixMultiply(XMLoadFloat4x4(&m_mWorld), mtxAxisRot));
}

void ObjectBase::RotAxisY(float angle)
{
	XMVECTOR axis;
	XMMATRIX mtxAxisRot;
	axis = XMVectorSet(m_mWorld._21, m_mWorld._22, m_mWorld._23, 0.0f);
	mtxAxisRot = XMMatrixRotationAxis(axis, XMConvertToRadians(angle));
	XMStoreFloat4x4(&m_mWorld, XMMatrixMultiply(XMLoadFloat4x4(&m_mWorld), mtxAxisRot));
}

void ObjectBase::RotAxisZ(float angle)
{
	XMVECTOR axis;
	XMMATRIX mtxAxisRot;
	axis = XMVectorSet(m_mWorld._31, m_mWorld._32, m_mWorld._33, 0.0f);
	mtxAxisRot = XMMatrixRotationAxis(axis, XMConvertToRadians(angle));
	XMStoreFloat4x4(&m_mWorld, XMMatrixMultiply(XMLoadFloat4x4(&m_mWorld), mtxAxisRot));
}

bool comp(ObjectBase * c1, ObjectBase * c2)
{
	return c1->GetDrawOrder() < c2->GetDrawOrder();
}
