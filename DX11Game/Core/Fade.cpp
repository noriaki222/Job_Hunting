// �t�F�[�h �C��/�A�E�g [Fade.cpp]
#include "Fade.h"
#include "../Base/Polygon.h"

using namespace DirectX;

// �ÓI�����o
EFade CFade::m_fade = FADE_NONE;
EScene CFade::m_sceneNext = SCENE_TITLE;
XMFLOAT4 CFade::m_vColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
float CFade::m_fRate = 1.0f / (60.0f * 0.5f);

// ������
void CFade::Init()
{
	m_vColor.w = 1.0f;			// �s�����x
	m_fade = FADE_IN;			// ���
	m_sceneNext = SCENE_TITLE;	// ���̃V�[��
}

// �X�V
void CFade::Update()
{
	// �������Ă��Ȃ�
	if (m_fade == FADE_NONE) {
		return;
	}
	// �t�F�[�h�A�E�g����
	if (m_fade == FADE_OUT) {
		m_vColor.w += m_fRate;	// �s�����x�𑝉�
		if (m_vColor.w >= 1.0f) {
			// �t�F�[�h�C�������ɐؑ�
			m_vColor.w = 1.0f;
			m_fade = FADE_IN;
			// �V�[���ؑ�
			CScene::Change(m_sceneNext);
		}
		// �����t�F�[�h�A�E�g
		return;
	}
	// �t�F�[�h�C������
	m_vColor.w -= m_fRate;	// �s�����x��������
	if (m_vColor.w <= 0.0f) {
		// �t�F�[�h�����I��
		m_vColor.w = 0.0f;
		m_fade = FADE_NONE;
	}
	// �����t�F�[�h�C��
}

// �`��
void CFade::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);

	Polygon::SetColor(m_vColor);
	Polygon::SetTexture(nullptr);
	Polygon::SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	Polygon::SetUV(0.0f, 0.0f);
	Polygon::SetFrameSize(1.0f, 1.0f);
	Polygon::SetPos(0.0f, 0.0f);
	Polygon::Draw(pDC);

	Polygon::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// �t�F�[�h�A�E�g�J�n
void CFade::Out(EScene scene, float fSecond)
{
	if (m_fade != FADE_OUT) {
		m_fade = FADE_OUT;
		m_sceneNext = scene;
		m_fRate = 1.0f / (60.0f * fSecond);
	}
}

// �t�F�[�h�C�� �A�E�g �J���[�ݒ�
void CFade::SetColor(XMFLOAT3 vColor)
{
	m_vColor.x = vColor.x;
	m_vColor.y = vColor.y;
	m_vColor.z = vColor.z;
}
