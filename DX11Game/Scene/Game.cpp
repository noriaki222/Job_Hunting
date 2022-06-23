//=============================================================================
//
// �Q�[�� �N���X���� [Game.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "Game.h"
#include "../Core/GameObj.h"
#include "../Core/Fade.h"
#include "../Base/Texture.h"
#include "../Base/Polygon.h"

using namespace DirectX;

// �R���X�g���N�^
CGame::CGame() : CScene()
{
	m_id = SCENE_GAME;
	m_p3D = nullptr;
}

// �f�X�g���N�^
CGame::~CGame()
{
}

// ������
bool CGame::Init()
{
	m_bResult = false;

	m_cam.Init();
	CCamera::Set(&m_cam);
	m_p3D = new Test3D(this);

	// �S�I�u�W�F�N�g������
	if (FAILED(CGameObj::InitAll(m_pObj))) {
		return false;
	}


	// BGM�Đ��J�n


	return true;
}

// �I������
void CGame::Fin()
{
	// BGM�Đ���~

	// �S�I�u�W�F�N�g�I������
	CGameObj::FinAll(m_pObj);
}

// �X�V
void CGame::Update()
{
	// �S�L�����X�V
	CGameObj::UpdateAll(m_pObj);

}

// �`��
void CGame::Draw()
{
	// �S�L�����`��
	CGameObj::DrawAll(m_pObj);

	/*SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);
	CPolygon::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	CPolygon::SetTexture(m_pTex);
	CPolygon::SetPos(0.0f, 0.0f);
	CPolygon::SetSize(800.0f, 200.0f);
	CPolygon::Draw(GetDeviceContext());*/
}