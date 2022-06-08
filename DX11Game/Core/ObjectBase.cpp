#include "ObjectBase.h"

using namespace DirectX;

ObjectBase::ObjectBase()
{
	m_transform = Transform::Zero();
	m_rigidbody = RigidBody::Zero();
	m_enable = true;
	m_color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_tag = TAG_NONE;
	XMMATRIX zeroMat = XMMatrixIdentity();
	XMStoreFloat4x4(&m_mWorld, zeroMat);
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

	XMMATRIX mtxWorld, mtxRot, mtxTranslate;

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
}