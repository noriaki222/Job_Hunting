#pragma once
#include "Object\Charactor.h"
#include "Core\Object3D.h"

class TestEnemy : public Charactor
{
public:
	TestEnemy();
	~TestEnemy();

	void Update();

	void SetPlayer(Object3D* obj) { m_player = obj; }
private:
	Object3D* m_player;
};