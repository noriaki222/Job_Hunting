// Assimp用ピクセルシェーダ (AssimpPixel.hlsl)

// グローバル
cbuffer global : register(b0) {
	matrix	g_mtxWVP;			// ワールド×ビュー×射影行列
	matrix	g_mtxWorld;			// ワールド行列
	matrix	g_mtxTexture;		// テクスチャ行列
	float4	g_vCameraPos;		// 視点座標(ワールド空間)
	float4	g_vLightDir;		// 光源方向(ワールド空間)
	float4	g_vLightAmbient;	// 環境光
	float4	g_vLightDiffuse;	// 拡散光
	float4	g_vLightSpecular;	// 鏡面反射光
	float4	g_vCameraDir;		// 視点方向
};

// マテリアル
cbuffer global2 : register(b1) {
	float4	g_Ambient;			// 環境色
	float4	g_Diffuse;			// 拡散色+アルファ
	float4	g_Specular;			// 鏡面反射色+強度
	float4	g_Emissive;			// 発光色
	float4	g_Flags;			// 拡散色テクスチャ有無, 発光色テクスチャ有無, 透過テクスチャ有無
};

Texture2D    g_texture			: register(t0);	// テクスチャ
Texture2D    g_texEmissive		: register(t1);	// 発光テクスチャ
Texture2D    g_texTransparent	: register(t2);	// 透過テクスチャ
Texture2D    g_texSpecular		: register(t3);	// 鏡面反射テクスチャ
SamplerState g_sampler			: register(s0);	// サンプラ

// パラメータ
struct VS_OUTPUT {
	float4	Pos			: SV_Position;
	float2	Tex			: TEXCOORD0;
	float3	Normal		: TEXCOORD1;
	float3	PosForPS	: TEXCOORD2;
	float3  NormalPS	: TEXCOORD3;
	float3  wPos		: TEXCOORD4;
};

struct PS_OUT {
	float4 target0 : SV_Target0;	// RT_GAME
};

//
// ピクセルシェーダ
//
PS_OUT main(VS_OUTPUT input)
{
	PS_OUT Out;
	float t = dot(input.NormalPS, g_vLightDir.xyz);
	t *= -1.0f;
	if (t < 0)
	{
		t = 0.0f;
	}

	float3 diffuseLig = g_Ambient * t;
	
	float3 refVec = reflect(diffuseLig, input.NormalPS);
	float3 toEye = g_vCameraPos.xyz - input.wPos;
	toEye = normalize(toEye);

	t = dot(refVec, toEye);

	if (t < 0.0f)
	{
		t = 0.0f;
	}

	t = pow(t, 5.0f);
	float3 specularLig = g_Specular * t;


	float3 lig = diffuseLig + specularLig;

	Out.target0 = float4(lig, 1.0f);
	return Out;
}
