#pragma once
#include "../Core/Object3D.h"
#include "Land.h"

class Charactor : public Object3D
{
public:
	Charactor();
	~Charactor();

	void Init();

	void UpdateMatrix();
	void SetLand(Land* land) { m_pLand = land; }

private:
	Land* m_pLand;
};