//=============================================================================
//
// ���f�� �N���X��` [Model.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once
#include "../Core/GameObj.h"
#include "AssimpModel.h"

enum EModel {
	MODEL_PLAYER = 0,	// �v���C���[ ���f��
	MODEL_ENEMY,		// �G���f��
	MODEL_SKY,			// �X�J�C�h�[��

	MAX_MODEL
};

class CModel : public CGameObj
{
private:
	static CAssimpModel* m_pModels[MAX_MODEL];
	CAssimpModel* m_pModel;

public:
	CModel(CScene* pScene);
	virtual ~CModel();

	static HRESULT LoadAll();
	static void ReleaseAll();

	virtual HRESULT Init();
	virtual void Fin();
	virtual void Update();
	virtual void Draw();
	virtual void DrawAlpha();

	void SetModel(EModel model);
	static CAssimpModel* GetAssimp(EModel model);
};
