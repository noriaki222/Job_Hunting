#pragma once
#include "../main.h"

enum EObjTag
{
	TAG_NONE = 0,

	MAX_TAG
};

class ObjectBase
{
public:
	ObjectBase();
	virtual ~ObjectBase() {};

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void UpdateMatrix();

	EObjTag GetTag() { return m_tag; }
	bool GetEnable() { return m_enable; }
	Transform GetTransform() { return m_transform; }
	RigidBody GetRigidbody() { return m_rigidbody; }
	DirectX::XMFLOAT4 GetColor() { return m_color; }

	DirectX::XMFLOAT4X4 GetWorld() { return m_mWorld; }
	DirectX::XMFLOAT3 GetLocalX() { return DirectX::XMFLOAT3(m_mWorld._11, m_mWorld._12, m_mWorld._13); }
	DirectX::XMFLOAT3 GeLocalY() { return DirectX::XMFLOAT3(m_mWorld._21, m_mWorld._22, m_mWorld._23); }
	DirectX::XMFLOAT3 GetLocalZ() { return DirectX::XMFLOAT3(m_mWorld._31, m_mWorld._32, m_mWorld._33); }

	void SetTag(EObjTag tag) { m_tag = tag; }
	void SetEnable(bool flg) { m_enable = flg; }
	void SetTransform(Transform transform) { m_transform = transform; }
	void SetRigidbody(RigidBody rb) { m_rigidbody = rb; }
	void SetColor(DirectX::XMFLOAT4 color) { m_color = color; }
	
	void SetWorld(DirectX::XMFLOAT4X4 mtx) { m_mWorld = mtx; }

protected:
	EObjTag m_tag;					// タグ
	bool m_enable;					// シーンに存在するか(true: Update/Draw中止)
	Transform m_transform;			// 座標 回転 大きさ
	RigidBody m_rigidbody;			// 速度 加速度
	DirectX::XMFLOAT4 m_color;		// 色

	DirectX::XMFLOAT4X4 m_mWorld;	// ワールド変換
};