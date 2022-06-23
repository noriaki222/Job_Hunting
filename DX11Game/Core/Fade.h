// �t�F�[�h �C��/�A�E�g [Fade.h]
#pragma once
#include "../main.h"
#include "Scene.h"

// �萔��`
enum EFade {
	FADE_NONE = 0,	// �������Ă��Ȃ�
	FADE_IN,		// �t�F�[�h�C������
	FADE_OUT,		// �t�F�[�h�A�E�g����

	MAX_FADE
};

// �N���X��`
class CFade {
private:
	static EFade m_fade;
	static EScene m_sceneNext;
	static DirectX::XMFLOAT4 m_vColor;
	static float m_fRate;

public:
	static void Init();
	static void Update();
	static void Draw();

	static void Out(EScene scene, float fSecond = 0.5f);
	static EFade Get() { return m_fade; }
	static void SetColor(DirectX::XMFLOAT3 vColor);
};
