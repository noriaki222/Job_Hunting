// エッジ表示用ピクセルシェーダ

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

struct PS_EdgeInput
{
	float4 pos  : SV_Position;
	float4 tex0 : TEXCOORD0;
	float4 tex1 : TEXCOORD1;
	float4 tex2 : TEXCOORD2;
	float4 tex3 : TEXCOORD3;
	float2 tex4 : TEXCOORD4;
	float4 tex5 : TEXCOORD5;
	float4 tex6 : TEXCOORD6;
	float4 tex7 : TEXCOORD7;
	float4 tex8 : TEXCOORD8;
};

Texture2D    normalTex : register(t0);	// 法線マップ
Texture2D	 depthTex  : register(t1);	// 深度マップ
SamplerState g_sampler : register(s0);	// サンプラ

PS_EdgeInput VSXEdge(VS_OUTPUT In)
{
	float2 texSize;
	float level;

	normalTex.GetDimensions(0, texSize.x, texSize.y, level);

	PS_EdgeInput Out;
	Out.pos = In.Position;
	float2 tex = In.TexCoord;

	float offset = 0.2f;

	// 法線
	Out.tex0.xy = tex + float2(-offset / texSize.x, -offset / texSize.y);	// 左上
	Out.tex1.xy = tex + float2(               0.0f, -offset / texSize.y);	// 上
	Out.tex2.xy = tex + float2( offset / texSize.x, -offset / texSize.y);	// 右上
	Out.tex3.xy = tex + float2(-offset / texSize.x, 0.0f);					// 左
	Out.tex4    = tex + float2(               0.0f, 0.0f);					// 真ん中
	Out.tex5.xy = tex + float2( offset / texSize.x, 0.0f);					// 右
	Out.tex6.xy = tex + float2(-offset / texSize.x, offset / texSize.y);	// 左下
	Out.tex7.xy = tex + float2(               0.0f, offset / texSize.y);	// 下
	Out.tex8.xy = tex + float2( offset / texSize.x, offset / texSize.y);	// 右下

	// 深度
	offset = 1.0f;
	Out.tex0.zw = tex + float2(-offset / texSize.x, -offset / texSize.y);	// 左上
	Out.tex1.zw = tex + float2(               0.0f, -offset / texSize.y);	// 上
	Out.tex2.zw = tex + float2( offset / texSize.x, -offset / texSize.y);	// 右上
	Out.tex3.zw = tex + float2(-offset / texSize.x, 0.0f);					// 左
	Out.tex5.zw = tex + float2( offset / texSize.x, 0.0f);					// 右
	Out.tex6.zw = tex + float2(-offset / texSize.x, offset / texSize.y);	// 左下
	Out.tex7.zw = tex + float2(               0.0f, offset / texSize.y);	// 下
	Out.tex8.zw = tex + float2( offset / texSize.x, offset / texSize.y);	// 右下
	
	return Out;
}

float4 main(VS_OUTPUT In) : SV_Target0
{
	PS_EdgeInput input = VSXEdge(In);

	// 周囲のピクセルの法線の値の平均計算
	float3 Normal = normalTex.Sample(g_sampler, input.tex4).xyz * -8.0f;
	Normal += normalTex.Sample(g_sampler, input.tex0.xy).xyz;
	Normal += normalTex.Sample(g_sampler, input.tex1.xy).xyz;
	Normal += normalTex.Sample(g_sampler, input.tex2.xy).xyz;
	Normal += normalTex.Sample(g_sampler, input.tex3.xy).xyz;
	Normal += normalTex.Sample(g_sampler, input.tex5.xy).xyz;
	Normal += normalTex.Sample(g_sampler, input.tex6.xy).xyz;
	Normal += normalTex.Sample(g_sampler, input.tex7.xy).xyz;
	Normal += normalTex.Sample(g_sampler, input.tex8.xy).xyz;

	// 周囲のピクセルの深度値の平均を計算する
	float depth = depthTex.Sample(g_sampler, input.tex4).x;
	float depth2 = depthTex.Sample(g_sampler, input.tex0.zw).x;
	depth2 += depthTex.Sample(g_sampler, input.tex1.zw).x;
	depth2 += depthTex.Sample(g_sampler, input.tex2.zw).x;
	depth2 += depthTex.Sample(g_sampler, input.tex3.zw).x;
	depth2 += depthTex.Sample(g_sampler, input.tex5.zw).x;
	depth2 += depthTex.Sample(g_sampler, input.tex6.zw).x;
	depth2 += depthTex.Sample(g_sampler, input.tex7.zw).x;
	depth2 += depthTex.Sample(g_sampler, input.tex8.zw).x;
	depth2 /= 8.0f;

	// 法線の結果or深度の結果が一定以上の場合エッジとみなす
	float4 Color;
	if (length(Normal) >= 0.1f || abs(depth2 - depth) > 0.005f)
	{
		Color = float4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	else
	{
		Color = float4(1.0f, 1.0f, 1.0f, 0.0f);
	}

	return Color;
}