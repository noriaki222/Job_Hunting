#pragma once
#include "../main.h"
#include "../Core/SceneBase.h"
#include "../Core/SceneData.h"
#include "../Object/SceneFade.h"


class SceneManager
{
public:
	static SceneManager* GetInstance();

	static HRESULT Create();
	static void Destroy();

	void Update();
	void Draw();

	void SetSecne(EScene scene);
	EScene GetScene() { return m_eScene; }

	SceneBase* GetActiveScene() { return m_pActiceScene; }

protected:
	SceneManager();
	~SceneManager();

	static SceneManager* pInstance;

	EScene m_eScene;
	EScene m_eNextScene;
	SceneBase* m_pActiceScene;
	bool m_isChange;
	SceneFade* m_pSceneFade;

};