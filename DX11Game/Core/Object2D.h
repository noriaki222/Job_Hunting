#pragma once
#include "ObjectBase.h"
#include "../main.h"
#include "../Base/Mesh.h"
#include "../Core/shaderList.h"


class Object2D : public ObjectBase
{
public:
	Object2D();
	Object2D(const LPCWSTR path, DirectX::XMFLOAT2 size);
	virtual ~Object2D();

	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	void SetLocalBlendState(EBlendState state) { m_blendState = state; }
	void LoadTexture(const LPCWSTR texPath);

	void SetVS(VertexShaderKind kind) { m_VS = kind; }
	void SetPS(PixelShaderKind kind) { m_PS = kind; }

protected:
	EBlendState m_blendState;
	EBillbordType m_billboard;

	DirectX::XMFLOAT2 m_defaultsize;

	DirectX::XMFLOAT2 m_uv;

private:
	void MakeVertex();

	CMesh m_mesh;
	CMeshMaterial m_material;

	ID3D11ShaderResourceView* m_pTex;

	VertexShaderKind m_VS;
	PixelShaderKind m_PS;

};