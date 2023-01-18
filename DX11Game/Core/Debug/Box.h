#pragma once
#include "../../Base/Mesh.h"

class Box : public CMesh
{
public:
	Box();
	virtual ~Box();

	void Draw();

	HRESULT Init(Collider* coll, DirectX::XMFLOAT4X4* world, DirectX::XMFLOAT3* scale);
	void SetRed();
	void SetGreen();
	void SetBlue();

private:
	CMesh m_mesh;
	Collider* m_coll;
	DirectX::XMFLOAT4X4* m_world;
};