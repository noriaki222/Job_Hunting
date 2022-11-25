// 2Dポリゴン処理
#pragma once
#include "../main.h"

class Polygon
{
private:
	static ID3D11ShaderResourceView* m_pTexture;	// テクスチャへのポインタ

	static VERTEX_2D m_vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	static DirectX::XMFLOAT4 m_vColor;						// ポリゴンの頂点カラー
	static bool m_bInvalidate;						// 頂点データ更新フラグ

	static DirectX::XMFLOAT2 m_vPosTexFrame;					// UV座標
	static DirectX::XMFLOAT2 m_vSizeTexFrame;				// テクスチャ抽出サイズ

	static ID3D11Buffer* m_pConstantBuffer;			// 定数バッファ
	static ID3D11Buffer* m_pVertexBuffer;			// 頂点バッファ
	static ID3D11SamplerState* m_pSamplerState;		// テクスチャ サンプラ
	static ID3D11VertexShader* m_pVertexShader;		// 頂点シェーダ
	static ID3D11InputLayout* m_pInputLayout;		// 頂点フォーマット
	static ID3D11PixelShader* m_pPixelShader;		// ピクセルシェーダ

	static DirectX::XMFLOAT4X4 m_mProj;						// 射影変換行列
	static DirectX::XMFLOAT4X4 m_mView;						// ビュー変換行列
	static DirectX::XMFLOAT4X4 m_mWorld;						// ワールド変換行列
	static DirectX::XMFLOAT4X4 m_mTex;						// テクスチャ変換行列

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
