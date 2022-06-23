//=============================================================================
//
// ゲーム クラス定義 [Game.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once
#include "../Core/Scene.h"
#include "../TestCamera.h"
#include "../Test3D.h";

// クラス定義
class CEnemy;
class CGame : public CScene
{
private:
	bool m_bResult;
	TestCam m_cam;
	Test3D* m_p3D;

public:
	CGame();
	virtual ~CGame();

	virtual bool Init();
	virtual void Fin();
	virtual void Update();
	virtual void Draw();


private:
};
