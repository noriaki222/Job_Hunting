#pragma once
#include "ObjectBase.h"
#include "../main.h"
#include "../Base/Polygon.h"

class Object2D : public ObjectBase
{
public:
	Object2D();
	Object2D(const LPCWSTR path);
	virtual ~Object2D();

	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	void SetLocalBlendState(EBlendState state) { m_blendState = state; }
	void LoadTexture(const LPCWSTR texPath);
	void ReleseTexture();

protected:
	EBlendState m_blendState;
	ID3D11ShaderResourceView* m_pTex;
};