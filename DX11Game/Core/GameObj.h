//=============================================================================
//
// �I�u�W�F�N�g �N���X��` [GameObj.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once
#include "../main.h"

// �萔��`
enum EGameObjType {		// �I�u�W�F�N�g�^
	GOT_GAMEOBJ = 0,	// �^����
	GOT_PLAYER,			// �v���C���[
	GOT_ENEMY,			// �G
	GOT_EXPLOSION,

	MAX_GAMEOBJTYPE
};

// �N���X��`
class CScene;
class CGameObj
{
private:
	CGameObj* m_pBack;		// �O�̃I�u�W�F�N�g
	CGameObj* m_pNext;		// ���̃I�u�W�F�N�g

protected:
	EGameObjType m_id;		// �I�u�W�F�N�g�^

	CScene* m_pScene;		// �����V�[��

	DirectX::XMFLOAT3 m_vPos;		// ���W
	DirectX::XMFLOAT3 m_vVel;		// ���x
	DirectX::XMFLOAT3 m_vAccel;		// �����x
	DirectX::XMFLOAT3 m_vAngle;		// �p�x
	DirectX::XMFLOAT3 m_vScale;		// �g�k

	DirectX::XMFLOAT4X4 m_mWorld;	// ���[���h�ϊ�

	bool m_bVisible;		// �\���t���O

public:
	CGameObj(CScene* pScene);
	virtual ~CGameObj(void);

	virtual HRESULT Init();		// ������
	virtual void Update();		// �X�V
	virtual void Draw();		// �s���������`��
	virtual void DrawAlpha();	// �����������`��
	virtual void Fin();			// �I������

	static HRESULT InitAll(CGameObj* pTop);
	static void UpdateAll(CGameObj* pTop);
	static void DrawAll(CGameObj* pTop);
	static void FinAll(CGameObj* pTop);

	void SetPos(DirectX::XMFLOAT3 vPos) { m_vPos = vPos; }
	DirectX::XMFLOAT3& GetPos() { return m_vPos; }
	void SetAngle(DirectX::XMFLOAT3 vAngle) { m_vAngle = vAngle; }
	DirectX::XMFLOAT3& GetAngle() { return m_vAngle; }
	void SetScale(DirectX::XMFLOAT3 vScale) { m_vScale = vScale; }
	DirectX::XMFLOAT3& GetScale() { return m_vScale; }
	void SetWorld(DirectX::XMFLOAT4X4& mWorld) { m_mWorld = mWorld; }
	DirectX::XMFLOAT4X4& GetWorld() { return m_mWorld; }

	EGameObjType GetID() { return m_id; }
	CGameObj* GetNext() { return m_pNext; }

	void SetVisible(bool bVisible = true) { m_bVisible = bVisible; }
};
