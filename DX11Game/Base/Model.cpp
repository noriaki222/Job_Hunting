// モデルデータ
#include "Model.h"

namespace
{
	// ファイル名
	LPCSTR g_pszModelPath[MAX_MODEL] =
	{
		"data/model/Sword And Shield.fbx",
		"data/model/flyModel.x",
		"data/model/sky.fbx",
	};
}

CAssimpModel* CModel::m_pModels[MAX_MODEL] = { nullptr };

CModel::CModel()
{
}

CModel::~CModel()
{
}

HRESULT CModel::LoadModel()
{
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDC = GetDeviceContext();

	if (!CAssimpModel::InitShader(pDevice)) { return E_FAIL; }

	HRESULT hr = S_OK;
	for (int i = 0; i < MAX_MODEL; ++i)
	{
		SAFE_DELETE(m_pModels[i]);
		m_pModels[i] = new CAssimpModel();
		if (!m_pModels[i]->Load(pDevice, pDC, g_pszModelPath[i]))
		{
			hr = E_FAIL;
			break;
		}
	}
	return hr;
}

void CModel::ReleseModel()
{
	for (int i = 0; i < MAX_MODEL; ++i)
	{
		if (m_pModels[i])
		{
			m_pModels[i]->Release();
			delete m_pModels[i];
			m_pModels[i] = nullptr;
		}
	}

	CAssimpModel::UninitShader();
}

CAssimpModel * CModel::GetModel(EModel eModel)
{
	if (eModel >= EModel::MODEL_TEST && eModel < EModel::MAX_MODEL)
	{
		return m_pModels[eModel];
	}
	return nullptr;
}
