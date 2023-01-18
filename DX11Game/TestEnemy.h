#pragma once
#include "Object\Charactor.h"

class TestEnemy : public Charactor
{
public:
	TestEnemy();
	~TestEnemy();

	void Update();

	void SetPlayer(Charactor* obj) { m_player = obj; }
private:
	Charactor* m_player;
};