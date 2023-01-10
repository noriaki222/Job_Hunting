#pragma once
#include "../Core/Object3D.h"

class Land : public Object3D
{
public:
	Land();
	~Land();

	void Init();

	void InitVertex();
	void FInVertex();

	bool CollisionRay(DirectX::XMFLOAT3 vP0, DirectX::XMFLOAT3 vW, DirectX::XMFLOAT3* pX = nullptr, DirectX::XMFLOAT3* pN = nullptr);

private:
	UINT m_nVertex;
	TAssimpVertex* m_pVertex;
	UINT m_nIndex;
	UINT* m_pIndex;
};