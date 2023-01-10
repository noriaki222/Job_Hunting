#pragma once
#include "../main.h"
#include "../Base/Shader.h"

enum VertexShaderKind
{
	VS_ASSIMP,
	VS_2D,
	VS_3D,
	VS_MAX
};

enum PixelShaderKind
{
	PS_ASSIMP,
	PS_2D,
	PS_3D,
	PS_BILLBOARD,
	PS_MAX
};

void InitShaderList();
void UninitShaderList();
VertexShader* GetVS(VertexShaderKind kind);
PixelShader* GetPS(PixelShaderKind kind);