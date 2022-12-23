#pragma once
#include "../Core/Object3D.h"

class SkyBox : public Object3D
{
public:
	SkyBox();
	~SkyBox();

	void Draw();

	void SetPos(DirectX::XMFLOAT3 pos) { m_transform.pos = pos; }
};