#include "shaderList.h"

const char* VetexShaderFile[] = 
{
	"data/shader/AssimpVertex.cso",
	"data/shader/Vertex2D.cso",
	"data/shader/Vertex.cso",
};

const char* PixelShaderFile[] =
{
	"data/shader/AssimpPixel.cso",
	"data/shader/Pixel2D.cso",
	"data/shader/Pixel.cso",
	"data/shader/BillboardPS.cso",
};


VertexShader* g_pVertexShader[VS_MAX];
PixelShader* g_pPixelShader[PS_MAX];
void InitShaderList()
{
	for (int i = 0; i < VS_MAX; ++i)
	{
		g_pVertexShader[i] = new VertexShader;
		if (FAILED(g_pVertexShader[i]->Load(VetexShaderFile[i])))
		{
			PostQuitMessage(0);
		}
	}
	for (int i = 0; i < PS_MAX; ++i)
	{
		g_pPixelShader[i] = new PixelShader;
		if (FAILED(g_pPixelShader[i]->Load(PixelShaderFile[i])))
		{
			PostQuitMessage(0);
		}
	}
}

void UninitShaderList()
{
	for (int i = 0; i < VS_MAX; ++i)
		delete g_pVertexShader[i];
	for (int i = 0; i < PS_MAX; ++i)
		delete g_pPixelShader[i];
}

VertexShader * GetVS(VertexShaderKind kind)
{
	return g_pVertexShader[kind];
}

PixelShader * GetPS(PixelShaderKind kind)
{
	return g_pPixelShader[kind];
}
