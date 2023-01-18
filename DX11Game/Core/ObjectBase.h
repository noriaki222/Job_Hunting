// �I�u�W�F�N�g�p���p�N���X
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

	// OBB�ł̓����蔻��
	bool Collision(EObjTag tag, ObjectBase* null);	// �������͎g��Ȃ�
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
	EObjTag m_tag;					// �^�O
	EObjType m_type;				// 3D��2D��
	bool m_enable;					// �V�[���ɑ��݂��邩(false: Update/Draw���~)
	bool m_visible;					// �V�[���ɕ\������邩(false: Draw���~)
	Transform m_transform;			// ���W ��] �傫��
	RigidBody m_rigidbody;			// ���x �����x
	Collider m_coll;				// �����蔻��
	DirectX::XMFLOAT4 m_color;		// �F

	DirectX::XMFLOAT3 m_axisRot;	// ���[�J�����W���ł̉�](.x:x�����Ƃ��Ẳ�]�̑傫��
	DirectX::XMFLOAT3 m_startRot;	// �����p�x
	DirectX::XMFLOAT4X4 m_mWorld;	// ���[���h�ϊ�

	int m_updateOrder;				// �X�V����(����������ɏ��������)(default: 2D = 0, 3D = 10, UI = 20
	int m_drawOrder;				// �`�揇��(����������ɏ��������)(default: 2D = 0, 3D = 10, UI = 20

	std::vector<ERenderTarget> m_useRT;

	std::list<ObjectBase*>::iterator m_it;
};

bool comp(ObjectBase* c1, ObjectBase* c2);	// �������\�[�g�p