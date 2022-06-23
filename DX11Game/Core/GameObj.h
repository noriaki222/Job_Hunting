//=============================================================================
//
// オブジェクト クラス定義 [GameObj.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once
#include "../main.h"

// 定数定義
enum EGameObjType {		// オブジェクト型
	GOT_GAMEOBJ = 0,	// 型無し
	GOT_PLAYER,			// プレイヤー
	GOT_ENEMY,			// 敵
	GOT_EXPLOSION,

	MAX_GAMEOBJTYPE
};

// クラス定義
class CScene;
class CGameObj
{
private:
	CGameObj* m_pBack;		// 前のオブジェクト
	CGameObj* m_pNext;		// 次のオブジェクト

protected:
	EGameObjType m_id;		// オブジェクト型

	CScene* m_pScene;		// 所属シーン

	DirectX::XMFLOAT3 m_vPos;		// 座標
	DirectX::XMFLOAT3 m_vVel;		// 速度
	DirectX::XMFLOAT3 m_vAccel;		// 加速度
	DirectX::XMFLOAT3 m_vAngle;		// 角度
	DirectX::XMFLOAT3 m_vScale;		// 拡縮

	DirectX::XMFLOAT4X4 m_mWorld;	// ワールド変換

	bool m_bVisible;		// 表示フラグ

public:
	CGameObj(CScene* pScene);
	virtual ~CGameObj(void);

	virtual HRESULT Init();		// 初期化
	virtual void Update();		// 更新
	virtual void Draw();		// 不透明部分描画
	virtual void DrawAlpha();	// 半透明部分描画
	virtual void Fin();			// 終了処理

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
