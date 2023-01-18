#pragma once
#include "../main.h"
#include "../Base/AssimpModel.h"
#include "../Base/Model.h"
#include "../Core/ObjectBase.h"
#include "AnimData.h"

#include "../Core/Debug/Debug_Collision.h"

class Object3D : public ObjectBase
{
public:
	Object3D();
	~Object3D();

	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	virtual void UpdateMatrix();

	void SetModel(CAssimpModel* model);
	CAssimpModel* GetModel() { return m_model; }
	void SetVS(VertexShaderKind kind) { m_model->SetVS(GetVS(kind)); }
	void SetPS(PixelShaderKind kind) { m_model->SetPS(GetPS(kind)); }

	int GetAttack() { return m_attack; }
	int GetLife() { return m_life; }
	bool GetIsAttack() { return m_isAttack; }
protected:
	bool m_isAnim;		// アニメーションするか
	ANIM_DATA m_anim;		// アニメーションNo.
	ANIM_DATA m_nextAnim;	// 次のアニメーションNo.
	double m_animTime;	// 再生時間
	bool m_changeAnim;	 // アニメーションが変更できるか

	int m_life;
	int m_attack;
	bool m_isAttack;

#ifdef _DEBUG
	Debug_ColIT debug_collit;
#endif // _DEBUG

private:
	CAssimpModel* m_model;
	double m_lastTime = NULL;

};