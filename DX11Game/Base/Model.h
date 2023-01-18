// モデルデータ
#pragma once
#include "AssimpModel.h"

enum EModel
{
	MODEL_TEST = 0,	// テストモデル
	MODE_TEST2,
	MODEL_SKY,		// スカイボックス
	MODEL_LAND,
	MODEL_SWORD,
	MODEL_ENEMY0,
	MAX_MODEL
};

class CModel
{
public:
	CModel();
	virtual ~CModel();

	static HRESULT LoadModel();
	static void ReleseModel();

	static CAssimpModel* GetModel(EModel eModel);

private:
	static CAssimpModel* m_pModels[MAX_MODEL];
};