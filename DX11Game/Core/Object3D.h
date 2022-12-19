#pragma once
#include "../main.h"
#include "../Base/AssimpModel.h"
#include "../Base/Model.h"
#include "../Core/ObjectBase.h"

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

	void UpdateMatrix();

	void SetModel(CAssimpModel* model);
	void SetVS(VertexShaderKind kind) { m_model->SetVS(GetVS(kind)); }
	void SetPS(PixelShaderKind kind) { m_model->SetPS(GetPS(kind)); }
protected:
	bool m_isAnim;		// アニメーションするか
	int m_animNo;		// アニメーションNo.
	double m_animTime;	// 再生時間

#ifdef _DEBUG
	Debug_ColIT debug_collit;
#endif // _DEBUG

private:
	CAssimpModel* m_model;
	double m_lastTime = NULL;

};