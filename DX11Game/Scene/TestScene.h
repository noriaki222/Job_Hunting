#pragma once
#include "../Manager/SceneManager.h"
#include "../Test2DObj.h"
#include "../Test3D.h"
#include "../TestCamera.h"
#include "../Object/SkyBox.h"
#include "../Object/Land.h"
#include "../TestPlayer.h"
#include "../TestBillBoard.h"
#include "../TestEnemy.h"

// モデルテスト用シーン
class TestScene : public SceneBase
{
public:
	TestScene();
	~TestScene();

private:
	Test2DObj* m_pTest2D;
	TestCamera m_camera;
	SkyBox* m_pSky;
	Land* m_pLand;
	TestPlayer* m_pPlayer;
	TestBillBoard* m_pBillboard;
	TestEnemy* m_pEnemy;
};