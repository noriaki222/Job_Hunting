#pragma once
#include "../main.h"
#include "../Base/Shader.h"

enum VertexShaderKind
{
	VS_ASSIMP,
	VS_MAX
};

enum PixelShaderKind
{
	PS_ASSIMP,
	PS_MAX
};

void InitShaderList();
void UninitShaderList();
ID3D11VertexShader* GetVS(VertexShaderKind kind);
ID3D11PixelShader* GetPS(PixelShaderKind kind);