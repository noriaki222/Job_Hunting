// 2D�|���S������
#pragma once
#include "../main.h"

class Polygon
{
private:
	static ID3D11ShaderResourceView* m_pTexture;	// �e�N�X�`���ւ̃|�C���^

	static VERTEX_2D m_vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	static DirectX::XMFLOAT4 m_vColor;						// �|���S���̒��_�J���[
	static bool m_bInvalidate;						// ���_�f�[�^�X�V�t���O

	static DirectX::XMFLOAT2 m_vPosTexFrame;					// UV���W
	static DirectX::XMFLOAT2 m_vSizeTexFrame;				// �e�N�X�`�����o�T�C�Y

	static ID3D11Buffer* m_pConstantBuffer;			// �萔�o�b�t�@
	static ID3D11Buffer* m_pVertexBuffer;			// ���_�o�b�t�@
	static ID3D11SamplerState* m_pSamplerState;		// �e�N�X�`�� �T���v��
	static ID3D11VertexShader* m_pVertexShader;		// ���_�V�F�[�_
	static ID3D11InputLayout* m_pInputLayout;		// ���_�t�H�[�}�b�g
	static ID3D11PixelShader* m_pPixelShader;		// �s�N�Z���V�F�[�_

	static DirectX::XMFLOAT4X4 m_mProj;						// �ˉe�ϊ��s��
	static DirectX::XMFLOAT4X4 m_mView;						// �r���[�ϊ��s��
	static DirectX::XMFLOAT4X4 m_mWorld;						// ���[���h�ϊ��s��
	static DirectX::XMFLOAT4X4 m_mTex;						// �e�N�X�`���ϊ��s��

private:
	static HRESULT MakeVertex(ID3D11Device* pDevice);
	static void SetVertex(void);

public:
	static HRESULT Init(ID3D11Device* pDevice);
	static void Fin();
	static void Draw(ID3D11DeviceContext* pDeviceContext);
	static void Draw(ID3D11DeviceContext* pDeviceContext, DirectX::XMFLOAT4X4 mWorld);
	static void SetTexture(ID3D11ShaderResourceView* pTexture);
	static void SetUV(float fU, float fV);
	static void SetFrameSize(float fWidth, float fHeight);
	static void SetColor(float fRed, float fGreen, float fBlue);
	static void SetColor(DirectX::XMFLOAT3 vColor);
	static void SetAlpha(float fAlpha);
	static void SetColor(float fRed, float fGreen, float fBlue, float fAlpha);
	static void SetColor(DirectX::XMFLOAT4 vColor);
};
