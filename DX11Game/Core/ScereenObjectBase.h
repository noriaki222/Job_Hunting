#pragma once
#include "../main.h"
#include "../Base/Texture.h"
#include "../Base/Polygon.h"

class ScereenObjectBase
{
public:
	ScereenObjectBase();
	ScereenObjectBase(const char* texPath);
	virtual ~ScereenObjectBase();

	virtual void Update();
	virtual void Draw();

	void LoadTexture(const char* texPath);
	void SetTexture(ID3D11ShaderResourceView* tex) { m_pTexture = tex; }

	void SetVS(VertexShaderKind num) { m_VSkind = num; }
	void SetPS(PixelShaderKind num) { m_PSkind = num; }
	
private:
	ID3D11ShaderResourceView* m_pTexture;
	VertexShaderKind m_VSkind;
	PixelShaderKind m_PSkind;

protected:
	DirectX::XMFLOAT4 m_color;
	DirectX::XMFLOAT2 m_uv;
	Transform m_transform;
};
