#pragma once
#include "../Manager/SceneManager.h"
#include "../Test3D.h"
#include "../TestCollision.h"
#include "../TestCamera.h"

// �����蔻��m�F�p�V�[��
class CollisionScene : public SceneBase
{
public:
	CollisionScene();
	~CollisionScene();

private:
	Test3D* m_p3D;
	TestCollision* m_p3D2;
	TestCamera m_cam;
};