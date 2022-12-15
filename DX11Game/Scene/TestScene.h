#pragma once
#include "../Manager/SceneManager.h"
#include "../Test2DObj.h"
#include "../Test3D.h"
#include "../TestCamera.h"

// ���f���e�X�g�p�V�[��
class TestScene : public SceneBase
{
public:
	TestScene();
	~TestScene();

private:
	Test2DObj* m_pTest2D;
	Test3D* m_pTest3D;
	TestCamera m_camera;
};