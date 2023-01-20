// Zバッファ表示用ピクセルシェーダ
// 遠いものが黒く、近いものを赤く表示

// グローバル
cbuffer global : register(b0) {
	matrix g_mWorld;
	matrix g_mView;
	matrix g_mProjection;
	matrix g_mTexture;
};

// パラメータ
struct VS_OUTPUT {
	float4	Position	: SV_Position;
	float2	TexCoord	: TEXCOORD0;
	float4	Diffuse		: COLOR0;
};

Texture2D    g_texture : register(t0);	// テクスチャ
SamplerState g_sampler : register(s0);	// サンプラ

float4 main(VS_OUTPUT input) : SV_Target0
{
	float4 Color = input.Diffuse;
	if (g_mTexture._44 > 0.0f) {
		Color = g_texture.Sample(g_sampler, input.TexCoord);
	}

	// 勉強不足:データが多く書き込まれている範囲でエルミート補完する方法
	Color.r = smoothstep(0.9964f, 1.0f, Color.r);

	Color.r = 1.0f - Color.r;

	return float4(Color.r, 0.0f, 0.0f, 1.0f);
}
