#pragma once
#include "../../Base/Mesh.h"

class Box : public CMesh
{
public:
	Box();
	virtual ~Box();

	void Draw();

	HRESULT Init(DirectX::XMFLOAT3* box, DirectX::XMFLOAT3* center, DirectX::XMFLOAT4X4* world, DirectX::XMFLOAT3* scale);
	void SetRed();
	void SetGreen();

private:
	DirectX::XMFLOAT3* m_center;
	DirectX::XMFLOAT4X4* m_world;
};