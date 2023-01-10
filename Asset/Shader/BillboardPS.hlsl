// ピクセルシェーダ

// グローバル
cbuffer global : register(b1) {
	float4	g_vEye;			// 視点座標
	// 光源
	float4	g_vLightDir;	// 光源方向
	float4	g_vLa;			// 環境光
	float4	g_vLd;			// 拡散反射光
	float4	g_vLs;			// 鏡面反射光
	// マテリアル
	float4	g_vKa;			// アンビエント色(+テクスチャ有無)
	float4	g_vKd;			// ディフューズ色
	float4	g_vKs;			// スペキュラ色(+スペキュラ強度)
	float4	g_vKe;			// エミッシブ色
};

// パラメータ
struct VS_OUTPUT {
	float4	Position	: SV_Position;
	float3	Pos4PS		: TEXCOORD0;
	float3	Normal		: TEXCOORD1;
	float2	TexCoord	: TEXCOORD2;
	float4	Diffuse		: COLOR0;
};

Texture2D    g_texture : register(t0);	// テクスチャ
SamplerState g_sampler : register(s0);	// サンプラ

float4 main(VS_OUTPUT input) : SV_Target0
{
	float4 color = input.Diffuse;

	return color;
}
