// �G�b�W�\���p�s�N�Z���V�F�[�_

// �O���[�o��
cbuffer global : register(b0) {
	matrix g_mWorld;
	matrix g_mView;
	matrix g_mProjection;
	matrix g_mTexture;
};

// �p�����[�^
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

Texture2D    normalTex : register(t0);	// �@���}�b�v
Texture2D	 depthTex  : register(t1);	// �[�x�}�b�v
SamplerState g_sampler : register(s0);	// �T���v��

PS_EdgeInput VSXEdge(VS_OUTPUT In)
{
	float2 texSize;
	float level;

	normalTex.GetDimensions(0, texSize.x, texSize.y, level);

	PS_EdgeInput Out;
	Out.pos = In.Position;
	float2 tex = In.TexCoord;

	float offset = 0.2f;

	// �@��
	Out.tex0.xy = tex + float2(-offset / texSize.x, -offset / texSize.y);	// ����
	Out.tex1.xy = tex + float2(               0.0f, -offset / texSize.y);	// ��
	Out.tex2.xy = tex + float2( offset / texSize.x, -offset / texSize.y);	// �E��
	Out.tex3.xy = tex + float2(-offset / texSize.x, 0.0f);					// ��
	Out.tex4    = tex + float2(               0.0f, 0.0f);					// �^��
	Out.tex5.xy = tex + float2( offset / texSize.x, 0.0f);					// �E
	Out.tex6.xy = tex + float2(-offset / texSize.x, offset / texSize.y);	// ����
	Out.tex7.xy = tex + float2(               0.0f, offset / texSize.y);	// ��
	Out.tex8.xy = tex + float2( offset / texSize.x, offset / texSize.y);	// �E��

	// �[�x
	offset = 1.0f;
	Out.tex0.zw = tex + float2(-offset / texSize.x, -offset / texSize.y);	// ����
	Out.tex1.zw = tex + float2(               0.0f, -offset / texSize.y);	// ��
	Out.tex2.zw = tex + float2( offset / texSize.x, -offset / texSize.y);	// �E��
	Out.tex3.zw = tex + float2(-offset / texSize.x, 0.0f);					// ��
	Out.tex5.zw = tex + float2( offset / texSize.x, 0.0f);					// �E
	Out.tex6.zw = tex + float2(-offset / texSize.x, offset / texSize.y);	// ����
	Out.tex7.zw = tex + float2(               0.0f, offset / texSize.y);	// ��
	Out.tex8.zw = tex + float2( offset / texSize.x, offset / texSize.y);	// �E��
	
	return Out;
}

float4 main(VS_OUTPUT In) : SV_Target0
{
	PS_EdgeInput input = VSXEdge(In);

	// ���͂̃s�N�Z���̖@���̒l�̕��όv�Z
	float3 Normal = normalTex.Sample(g_sampler, input.tex4).xyz * -8.0f;
	Normal += normalTex.Sample(g_sampler, input.tex0.xy).xyz;
	Normal += normalTex.Sample(g_sampler, input.tex1.xy).xyz;
	Normal += normalTex.Sample(g_sampler, input.tex2.xy).xyz;
	Normal += normalTex.Sample(g_sampler, input.tex3.xy).xyz;
	Normal += normalTex.Sample(g_sampler, input.tex5.xy).xyz;
	Normal += normalTex.Sample(g_sampler, input.tex6.xy).xyz;
	Normal += normalTex.Sample(g_sampler, input.tex7.xy).xyz;
	Normal += normalTex.Sample(g_sampler, input.tex8.xy).xyz;

	// ���͂̃s�N�Z���̐[�x�l�̕��ς��v�Z����
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

	// �@���̌���or�[�x�̌��ʂ����ȏ�̏ꍇ�G�b�W�Ƃ݂Ȃ�
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