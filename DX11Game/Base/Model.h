// ���f���f�[�^
#pragma once
#include "AssimpModel.h"

enum EModel
{
	MODEL_TEST = 0,	// �e�X�g���f��
	MODE_TEST2,
	MODEL_SKY,		// �X�J�C�{�b�N�X
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