// ユーザ定義メッシュ [Mesh.h]
#pragma once
#include "../main.h"
#include "../Core/shaderList.h"

class CMeshMaterial {
public:
	DirectX::XMFLOAT4	m_Diffuse;		// Diffuse color RGBA
	DirectX::XMFLOAT4	m_Ambient;		// Ambient color RGB
	DirectX::XMFLOAT4	m_Specular;		// Specular 'shininess'
	DirectX::XMFLOAT4	m_Emissive;		// Emissive color RGB
	float		m_Power;		// Sharpness if specular highlight
};

class CMesh
{
public:
	CMesh();
	virtual ~CMesh();

	static HRESULT InitShader();
	static void FinShader();

	HRESULT Init(const VERTEX_3D vertexWk[], int nVertex, const int indexWk[], int nIndex);
	virtual void Fin();
	virtual void Draw();

	HRESULT MakeMeshVertex(VERTEX_3D vertexWk[], int indexWk[]);

	DirectX::XMFLOAT4X4* GetWorld() { return &m_mWorld; }
	void SetWorld(DirectX::XMFLOAT4X4* pWorld) { m_mWorld = *pWorld; }
	void SetMaterial(const CMeshMaterial* pMaterial);
	void GetMaterial(CMeshMaterial* pMaterial) { *pMaterial = m_material; }
	void SetDiffuse(DirectX::XMFLOAT4 vDiffuse) { m_material.m_Diffuse = vDiffuse; }
	ID3D11ShaderResourceView* GetTexture() { return m_pTexture; }
	void SetTexture(ID3D11ShaderResourceView* tex) { m_pTexture = tex; }

	int m_nNumVertex;				// 総頂点数	
	int m_nNumIndex;				// 総インデックス数

	void SetVS(VertexShaderKind kind) { m_pVS = GetVS(kind); }
	void SetPS(PixelShaderKind kind) { m_pPS = GetPS(kind); }
private:
	ID3D11Buffer* m_pVertexBuffer;	// 頂点バッファインターフェースへのポインタ
	ID3D11Buffer* m_pIndexBuffer;	// インデックスバッファインターフェースへのポインタ
	ID3D11ShaderResourceView* m_pTexture;
	VertexShader* m_pVS;
	PixelShader* m_pPS;


	DirectX::XMFLOAT4X4 m_mWorld;

	CMeshMaterial m_material;		// マテリアル

	static ID3D11Buffer* m_pConstantBuffer[2];	// 定数バッファ
	static ID3D11SamplerState* m_pSamplerState;	// テクスチャ サンプラ
};
