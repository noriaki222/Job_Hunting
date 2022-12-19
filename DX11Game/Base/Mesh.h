// ���[�U��`���b�V�� [Mesh.h]
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

	void SetWorld(DirectX::XMFLOAT4X4* pWorld) { m_mWorld = *pWorld; }
	void SetMaterial(const CMeshMaterial* pMaterial);
	void GetMaterial(CMeshMaterial* pMaterial) { *pMaterial = m_material; }
	void SetDiffuse(DirectX::XMFLOAT4 vDiffuse) { m_material.m_Diffuse = vDiffuse; }
private:
	ID3D11Buffer* m_pVertexBuffer;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	ID3D11Buffer* m_pIndexBuffer;	// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	VertexShader* m_pVS;
	PixelShader* m_pPS;

	int m_nNumVertex;				// �����_��	
	int m_nNumIndex;				// ���C���f�b�N�X��

	DirectX::XMFLOAT4X4 m_mWorld;

	CMeshMaterial m_material;		// �}�e���A��

	static ID3D11Buffer* m_pConstantBuffer[2];	// �萔�o�b�t�@
	static ID3D11SamplerState* m_pSamplerState;	// �e�N�X�`�� �T���v��
};
