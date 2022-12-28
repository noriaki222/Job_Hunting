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
	
private:
	ID3D11ShaderResourceView* m_pTexture;

protected:
	DirectX::XMFLOAT4 m_color;
	DirectX::XMFLOAT2 m_uv;
	Transform m_transform;
};
