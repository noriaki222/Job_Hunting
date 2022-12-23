#pragma once
#include "ObjectBase.h"
#include "../main.h"
#include "../Base/Polygon.h"
#include "../Core/shaderList.h"

enum EBillbordType
{
	BILLBOARD_NONE,
	BILLBOARD_ALL,
	BILLBOARD_NOT_Y,
};

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

	void SetVS(VertexShaderKind kind) { m_VS = kind; }
	void SetPS(PixelShaderKind kind) { m_PS = kind; }

protected:
	EBlendState m_blendState;
	ID3D11ShaderResourceView* m_pTex;
	EBillbordType m_billboard;

	DirectX::XMFLOAT2 m_uv;

private:
	VertexShaderKind m_VS;
	PixelShaderKind m_PS;

};