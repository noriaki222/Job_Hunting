// モデル処理
#pragma once
#include "AssimpModel.h"

enum EModel
{
	MODEL_TEST = 0,	// テストモデル

	MAX_MODEL
};

class CModel
{
public:
	CModel();
	virtual ~CModel();

	static HRESULT LoadModel();
	static void ReleseModel();

	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	virtual void DrawAlpha();

	void SetModel(EModel eModel);

private:
	CAssimpModel* m_pModel;
	static CAssimpModel* m_pModels[MAX_MODEL];
};