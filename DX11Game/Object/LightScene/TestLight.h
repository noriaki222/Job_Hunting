#pragma once
#include "../../Base/Light.h"

class TestLight : public CLight
{
public:
	TestLight();
	~TestLight();

	void Update();

private:
	float m_rad;
};