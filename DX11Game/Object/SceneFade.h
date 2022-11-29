#pragma once
#include "../Core/ScereenObjectBase.h"

enum EFadeState
{
	FADESTATE_NONE,
	FADESTATE_FADEIN,
	FADESTATE_FADEOUT,
	MAX_FADESTATE,
};

class SceneFade : public ScereenObjectBase
{
public:
	static SceneFade* GetInstance();

	static void Create();
	static void Destroy();

	void Update();

	void FadeInScene();
	void FadeOutScene();

	EFadeState GetFadeScene() { return fadeState; }

protected:
	SceneFade();
	~SceneFade();

	static SceneFade* pInstance;
	bool foutbuf;
	EFadeState fadeState;
};