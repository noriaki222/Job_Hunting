#include "SceneFade.h"

#define FADETEX_NORMAL ("data/texture/transition000.png")
#define FADEWIDTHBUFFER (1.3f)
#define FRAMERATE (62.5f)

SceneFade* SceneFade::pInstance = nullptr;

SceneFade* SceneFade::GetInstance()
{
	return pInstance;
}

void SceneFade::Create()
{
	if (!pInstance)
	{
		pInstance = new SceneFade;
	}
}

void SceneFade::Destroy()
{
	delete pInstance;
	pInstance = nullptr;
}

void SceneFade::Update()
{
	static int tick = 0;
	if (fadeState == FADESTATE_FADEIN)
	{
		m_transform.pos.x = 0.0f + (-(SCREEN_WIDTH * FADEWIDTHBUFFER) + 0.0f) / (int)(0.5 * FRAMERATE) * tick;
		++tick;
		if (m_transform.pos.x == -(SCREEN_WIDTH * FADEWIDTHBUFFER))
		{
			fadeState = FADESTATE_NONE;
			tick = 0;
		}
	}
	if (fadeState == FADESTATE_FADEOUT)
	{
		m_transform.pos.x = (SCREEN_WIDTH * FADEWIDTHBUFFER) + (0.0f + -(SCREEN_WIDTH * FADEWIDTHBUFFER)) / (int)(0.5 * FRAMERATE) * tick;
		++tick;
		if (m_transform.pos.x == 0.0f)
		{
			if (foutbuf)
			{
				foutbuf = false;
			}
			else
			{
				fadeState = FADESTATE_NONE;
				tick = 0;
			}
		}
	}
}

void SceneFade::FadeInScene()
{
	if (fadeState != FADESTATE_NONE)
	{
		return;
	}
	fadeState = FADESTATE_FADEIN;
	m_transform.pos.x = 0.0f;
}

void SceneFade::FadeOutScene()
{
	if (fadeState != FADESTATE_NONE)
	{
		return;
	}
	fadeState = FADESTATE_FADEOUT;
	m_transform.pos.x = SCREEN_WIDTH * FADEWIDTHBUFFER;
}

SceneFade::SceneFade()
{
	foutbuf = false;
	LoadTexture(FADETEX_NORMAL);
	m_transform.scale.x *= FADEWIDTHBUFFER; m_transform.scale.y *= FADEWIDTHBUFFER; m_transform.scale.z *= FADEWIDTHBUFFER;
	m_color = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	fadeState = FADESTATE_FADEIN;
}

SceneFade::~SceneFade()
{
}
