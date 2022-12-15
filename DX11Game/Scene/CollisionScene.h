#pragma once
#include "../Manager/SceneManager.h"
#include "../Test3D.h"
#include "../TestCollision.h"
#include "../TestCamera.h"

// 当たり判定確認用シーン
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