#pragma once
#include "Base\Model.h"

class Test3D : public CModel
{
public:
	Test3D(CScene* pScene);
	virtual ~Test3D();

	virtual HRESULT Init();
	virtual void Fin();
	virtual void Update();
	virtual void Draw();
	virtual void DrawAlpha();

private:
};