#include "Monitor.h"
#include "../Base/Input.h"
#include "../Core/ScereenObjectBase.h"
#include <algorithm>

Monitor::Monitor()
{
	m_target = RT_GAME_AND_UI;
	m_useEffect = false;
	m_postEffects.push_back(PE_EDGE);
}

Monitor::~Monitor()
{
}

void Monitor::Update()
{
#ifdef _DEBUG
	// �����_�[�^�[�Q�b�g�̐؂�ւ�
	if (IsKeyPress(VK_LCONTROL))
	{
		if (IsKeyPress('0'))
			m_target = RT_BACK;
		if (IsKeyPress('1'))
			m_target = RT_GAME_AND_UI;
		if (IsKeyPress('2'))
			m_target = RT_UI;
		if (IsKeyPress('3'))
			m_target = RT_GAME;
		if (IsKeyPress('4'))
			m_target = RT_NORMAL;
		if (IsKeyPress('5'))
			m_target = RT_Z;
		if (IsKeyPress('6'))
			m_target = RT_EDGE;
		if (IsKeyPress('9'))
			m_target = RT_DEBUG;
	}

	// �|�X�g�G�t�F�N�g�̐؂�ւ�
	if (IsKeyPress(VK_TAB))
		m_useEffect = m_useEffect ? false : true;

	if (IsKeyPress(VK_MENU))
	{
		if (IsKeyPress('1'))
			m_postEffects.push_back(PE_EDGE);
	}

	// ����̗v�f�̐�����̏ꍇ�z���1�����c��
	//             �@�@�����̏ꍇ�z�񂩂�폜
	//std::sort(m_postEffects.begin(), m_postEffects.end());
	//for (int i = 0; i < MAX_PE; ++i)
	//{
	//	int cnt = std::count(m_postEffects.begin(), m_postEffects.end(), i);
	//	if(cnt % 2)
	//}
	//m_postEffects.erase(std::unique(m_postEffects.begin(), m_postEffects.end()), m_postEffects.end());
#endif // _DEBUG
}

void Monitor::Draw()
{
	ScereenObjectBase screen;
	ID3D11ShaderResourceView* ptex;
	// Z�o�b�t�@��`��
	SetRenderTarget(RT_Z);
	screen.SetTexture(GetDepthTexture(DSV_3D));
	screen.SetPS(PS_Z);
	screen.Draw();

	// �G�b�W�`��
	SetRenderTarget(RT_EDGE);
	screen.SetTexture(GetRenderTexture(RT_NORMAL));
	ptex = GetRenderTexture(RT_Z);
	GetDeviceContext()->PSSetShaderResources(1, 1, &ptex);
	screen.SetPS(PS_EDGE);
	screen.Draw();

	// Game�����_�[�^�[�Q�b�g�ɃG�t�F�N�g��������
	if (m_useEffect)
	{
		for (int i = 0; i < m_postEffects.size(); ++i)
		{
			switch (m_postEffects[i])
			{
			case PE_EDGE:
				break;
			}
		}
	}

	// UI�ƃQ�[�����̂�1�̃����_�[�^�[�Q�b�g�ɕ`��
	SetRenderTarget(RT_GAME_AND_UI);
	screen.SetTexture(GetRenderTexture(RT_GAME));
	screen.SetPS(PS_2D);
	screen.Draw();

	SetBlendState(BS_ALPHABLEND);
	
	screen.SetTexture(GetRenderTexture(RT_UI));
	screen.SetPS(PS_2D);
	screen.Draw();

	SetBlendState(BS_NONE);


	// �o�b�N�o�b�t�@�Ɏw��
	SetRenderTarget(RT_BACK);
	screen.SetTexture(GetRenderTexture(m_target));
	screen.SetPS(PS_2D);
	screen.Draw();
}
