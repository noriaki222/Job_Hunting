#pragma once
#include "ObjectBase.h"
#include "../main.h"
#include "../Base/Polygon.h"
#include "../Core/shaderList.h"


class ObjectUI : public ObjectBase
{
public:
	ObjectUI();
	ObjectUI(const LPCWSTR path);
	virtual ~ObjectUI();

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