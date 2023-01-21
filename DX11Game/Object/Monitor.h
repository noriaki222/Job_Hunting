// �����_�[�^�[�Q�b�g��`�悷��N���X
#pragma once
#include "../main.h"
#include <vector>

enum PostEffect
{
	PE_EDGE,

	MAX_PE
};

class Monitor
{
public:
	Monitor();
	~Monitor();

	void Update();
	void Draw();

private:
	ERenderTarget m_target;
	bool m_useEffect;	// �|�X�g�G�t�F�N�g���g�p���邩
	std::vector<PostEffect> m_postEffects;
};