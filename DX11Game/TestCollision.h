#pragma once
#include "Test3D.h"

class TestCollision : public Test3D
{
public:
	TestCollision();
	~TestCollision();

	void Update();
	void SetTarget(ObjectBase* target) { m_target = target; }

private:
	ObjectBase* m_target; // “–‚½‚è”»’è‚Ì‘ŠŽè
};