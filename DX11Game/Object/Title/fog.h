#pragma once
#include "../../Core/Object2D.h"

class Fog : public Object2D
{
public:
	Fog();
	~Fog();

	void Update();

	float spd = 0.01f;
};