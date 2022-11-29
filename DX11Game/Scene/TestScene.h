#pragma once
#include "../Manager/SceneManager.h"
#include "../Test2DObj.h"
#include "../Test3D.h"

class TestScene : public SceneBase
{
public:
	TestScene();
	~TestScene();

	void Update();

private:
	Test2DObj* m_pTest2D;
	Test3D* m_pTest3D;
};