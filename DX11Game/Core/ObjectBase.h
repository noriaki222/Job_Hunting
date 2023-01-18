// オブジェクト継承用クラス
#pragma once
#include "../main.h"
#include "../Core/shaderList.h"
#include <list>
#include <vector>

#define DEFAULT_2D_ORDER	(0)
#define DEFAULT_3D_ORDER	(10)
#define DEFAULT_UI_ORDER	(20)

enum EObjTag
{
	TAG_COLLTEST = -1,
	TAG_NONE = 0,
	TAG_SKY,
	TAG_LAND,
	TAG_PLAYER,
	TAG_ENEMY,

	MAX_TAG
};

enum EObjType
{
	TYPE_2D = 0,
	TYPE_3D,
	TYPE_UI,

	MAX_TYPE
};

class ObjectBase
{
public:
	ObjectBase();
	virtual ~ObjectBase();

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void UpdateMatrix();
	
	virtual void SetRendreTargets();

	// OBBでの当たり判定
	bool Collision(EObjTag tag, ObjectBase* null);	// 第二引数は使わない
	bool Collision(ObjectBase* obj);

	EObjTag GetTag() { return m_tag; }
	EObjType GetType() { return m_type; }
	bool GetEnable() { return m_enable; }
	bool GetVisible() { return m_visible; }
	Transform GetTransform() { return m_transform; }
	void SetPos(DirectX::XMFLOAT3 pos) { m_transform.pos = pos; }
	DirectX::XMFLOAT3 GetPos() { return m_transform.pos; }
	RigidBody GetRigidbody() { return m_rigidbody; }
	Collider GetCollider() { return m_coll; }
	DirectX::XMFLOAT4 GetColor() { return m_color; }
	int GetDrawOrder() { return m_drawOrder; }
	ObjectBase* GetObj() { return *m_it; }
	std::list<ObjectBase*>::iterator GetIt() { return m_it; }

	DirectX::XMFLOAT4X4 GetWorld() { return m_mWorld; }
	DirectX::XMFLOAT3 GetLocalX() { return DirectX::XMFLOAT3(m_mWorld._11, m_mWorld._12, m_mWorld._13); }
	DirectX::XMFLOAT3 GetLocalY() { return DirectX::XMFLOAT3(m_mWorld._21, m_mWorld._22, m_mWorld._23); }
	DirectX::XMFLOAT3 GetLocalZ() { return DirectX::XMFLOAT3(m_mWorld._31, m_mWorld._32, m_mWorld._33); }
	void RotAxisX(float angle);
	void RotAxisY(float angle);
	void RotAxisZ(float angle);

	void SetTag(EObjTag tag) { m_tag = tag; }
	void SetType(EObjType type) { m_type = type; }
	void SetEnable(bool flg) { m_enable = flg; }
	void SetVisible(bool flg) { m_visible = flg; }
	void SetTransform(Transform transform) { m_transform = transform; }
	void SetRigidbody(RigidBody rb) { m_rigidbody = rb; }
	void SetCollider(Collider col) { m_coll = col; }
	void SetColor(DirectX::XMFLOAT4 color) { m_color = color; }
	
	void SetWorld(DirectX::XMFLOAT4X4 mtx) { m_mWorld = mtx; }

	virtual void SetVS(VertexShaderKind kind) = 0;
	virtual void SetPS(PixelShaderKind kind) = 0;

protected:
	EObjTag m_tag;					// タグ
	EObjType m_type;				// 3Dか2Dか
	bool m_enable;					// シーンに存在するか(false: Update/Draw中止)
	bool m_visible;					// シーンに表示されるか(false: Draw中止)
	Transform m_transform;			// 座標 回転 大きさ
	RigidBody m_rigidbody;			// 速度 加速度
	Collider m_coll;				// 当たり判定
	DirectX::XMFLOAT4 m_color;		// 色

	DirectX::XMFLOAT3 m_axisRot;	// ローカル座標軸での回転(.x:xを軸としての回転の大きさ
	DirectX::XMFLOAT3 m_startRot;	// 初期角度
	DirectX::XMFLOAT4X4 m_mWorld;	// ワールド変換

	int m_updateOrder;				// 更新順番(小さい程先に処理される)(default: 2D = 0, 3D = 10, UI = 20
	int m_drawOrder;				// 描画順番(小さい程先に処理される)(default: 2D = 0, 3D = 10, UI = 20

	std::vector<ERenderTarget> m_useRT;

	std::list<ObjectBase*>::iterator m_it;
};

bool comp(ObjectBase* c1, ObjectBase* c2);	// 処理順ソート用