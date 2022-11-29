// ÉVÅ[Éì
#pragma once
#include "../main.h"
#include "../Manager/ObjectManager.h"

class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase();

	virtual void Update();
	void ConstUpdate();
	virtual void Draw();

private:
	ObjectManager* m_pObjMng;
};