//=============================================================================
//
// ���f�� �N���X���� [Model.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "Model.h"
#include "../Core/Scene.h"

// �O���[�o���ϐ�
namespace {
	const float VALUE_MOVE_MODEL = 1.0f;
	const float VALUE_ROTATE_MODEL = 1.0f;

	// 3D���f�� �t�@�C����
	LPCSTR g_pszModelPath[MAX_MODEL] = {
		"data/model/flyModel.x",
		"data/model/flyModel.x",
		"data/model/sky.fbx",
	};
}

// �ÓI�����o
CAssimpModel* CModel::m_pModels[MAX_MODEL] = { nullptr };

// �R���X�g���N�^
CModel::CModel(CScene* pScene) : CGameObj(pScene)
{
	m_pModel = nullptr;
}

// �f�X�g���N�^
CModel::~CModel()
{
}

// �S���f���Ǎ�
HRESULT CModel::LoadAll()
{
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDC = GetDeviceContext();

	// Assimp�p�V�F�[�_������
	if (!CAssimpModel::InitShader(pDevice))
		return E_FAIL;

	// �S���f���Ǎ�
	HRESULT hr = S_OK;
	for (int i = 0; i < MAX_MODEL; ++i) {
		SAFE_DELETE(m_pModels[i]);
		m_pModels[i] = new CAssimpModel();
		if (!m_pModels[i]->Load(pDevice, pDC, g_pszModelPath[i])) {
			hr = E_FAIL;
			break;
		}
	}
	return hr;
}

// �S���f�����
void CModel::ReleaseAll()
{
	// �S���f�����
	for (int i = 0; i < MAX_MODEL; ++i) {
		if (m_pModels[i]) {
			m_pModels[i]->Release();
			delete m_pModels[i];
			m_pModels[i] = nullptr;
		}
	}

	// Assimp�p�V�F�[�_�I������
	CAssimpModel::UninitShader();
}

// ������
HRESULT CModel::Init()
{
	HRESULT hr = CGameObj::Init();
	if (FAILED(hr))
		return hr;

	return hr;
}

// �I������
void CModel::Fin()
{
	CGameObj::Fin();
}

// �X�V
void CModel::Update()
{

	CGameObj::Update();
}

// �`��
void CModel::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	if (m_pModel) {
		m_pModel->Draw(pDC, GetWorld(), eOpacityOnly);
	}
}

// �����������`��
void CModel::DrawAlpha()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	if (m_pModel) {
		m_pModel->Draw(pDC, GetWorld(), eTransparentOnly);
	}
	CGameObj::DrawAlpha();
}

// ���f���ݒ�
void CModel::SetModel(EModel model)
{
	if (model < 0 || model >= MAX_MODEL) {
		m_pModel = nullptr;
	} else {
		m_pModel = m_pModels[model];
	}
}

// Assimp���f���擾
CAssimpModel* CModel::GetAssimp(EModel model)
{
	if (model < 0 || model >= MAX_MODEL)
		return nullptr;
	return m_pModels[model];
}
