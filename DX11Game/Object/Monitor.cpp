#include "Monitor.h"
#include "../Base/Input.h"
#include "../Core/ScereenObjectBase.h"

Monitor::Monitor()
{
	m_target = RT_GAME_AND_UI;
}

Monitor::~Monitor()
{
}

void Monitor::Update()
{
#ifdef _DEBUG
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
		if (IsKeyPress('0'))
			m_target = RT_DEBUG;
	}
#endif // _DEBUG
}

void Monitor::Draw()
{
	ScereenObjectBase screen;
	// Zバッファを描画
	SetRenderTarget(RT_Z);
	screen.SetTexture(GetDepthTexture(DSV_3D));
	screen.SetPS(PS_Z);
	screen.Draw();

	// エッジ描画
	SetRenderTarget(RT_EDGE);
	screen.SetTexture(GetRenderTexture(RT_NORMAL));
	screen.SetPS(PS_2D);
	screen.Draw();

	// UIとゲーム自体をレンダーターゲットに描画
	SetRenderTarget(RT_GAME_AND_UI);
	screen.SetTexture(GetRenderTexture(RT_GAME));
	screen.SetPS(PS_2D);
	screen.Draw();
	SetBlendState(BS_ALPHABLEND);
	screen.SetTexture(GetRenderTexture(RT_UI));
	screen.Draw();
	SetBlendState(BS_NONE);


	// バックバッファに指定
	SetRenderTarget(RT_BACK);
	screen.SetTexture(GetRenderTexture(m_target));
	screen.Draw();
}
