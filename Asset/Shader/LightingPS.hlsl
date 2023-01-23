// Assimp�p�s�N�Z���V�F�[�_ (AssimpPixel.hlsl)

// �O���[�o��
cbuffer global : register(b0) {
	matrix	g_mtxWVP;			// ���[���h�~�r���[�~�ˉe�s��
	matrix	g_mtxWorld;			// ���[���h�s��
	matrix	g_mtxTexture;		// �e�N�X�`���s��
	float4	g_vCameraPos;		// ���_���W(���[���h���)
	float4	g_vLightDir;		// ��������(���[���h���)
	float4	g_vLightAmbient;	// ����
	float4	g_vLightDiffuse;	// �g�U��
	float4	g_vLightSpecular;	// ���ʔ��ˌ�
	float4	g_vCameraDir;		// ���_����
};

// �}�e���A��
cbuffer global2 : register(b1) {
	float4	g_Ambient;			// ���F
	float4	g_Diffuse;			// �g�U�F+�A���t�@
	float4	g_Specular;			// ���ʔ��ːF+���x
	float4	g_Emissive;			// �����F
	float4	g_Flags;			// �g�U�F�e�N�X�`���L��, �����F�e�N�X�`���L��, ���߃e�N�X�`���L��
};

Texture2D    g_texture			: register(t0);	// �e�N�X�`��
Texture2D    g_texEmissive		: register(t1);	// �����e�N�X�`��
Texture2D    g_texTransparent	: register(t2);	// ���߃e�N�X�`��
Texture2D    g_texSpecular		: register(t3);	// ���ʔ��˃e�N�X�`��
SamplerState g_sampler			: register(s0);	// �T���v��

// �p�����[�^
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
// �s�N�Z���V�F�[�_
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
