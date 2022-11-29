#pragma once
#include "../main.h"
#include "../Base/AssimpModel.h"
#include "../Base/Model.h"
#include "../Core/ObjectBase.h"

class Object3D : public ObjectBase
{
public:
	Object3D();
	~Object3D();

	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	void SetModel(CAssimpModel* model);
protected:
	CAssimpModel* m_model;
	bool m_isAnim;		// �A�j���[�V�������邩
	int m_animNo;		// �A�j���[�V����No.
	double m_animTime;	// �Đ�����
};