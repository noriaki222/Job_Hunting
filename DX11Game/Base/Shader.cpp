#include <stdio.h>
#include "Shader.h"
#include "../main.h"
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler")

void SetTextureVS(ID3D11ShaderResourceView * pTex, UINT slot)
{
	GetDeviceContext()->VSSetShaderResources(slot, 1, &pTex);
}

void SetTexturePS(ID3D11ShaderResourceView * pTex, UINT slot)
{
	GetDeviceContext()->PSSetShaderResources(slot, 1, &pTex);
}

Shader::Shader(Kind kind) : m_kind(kind)
{
}

Shader::~Shader()
{
}

HRESULT Shader::Load(const char * pFileName)
{
	HRESULT hr = E_FAIL;

	// ファイル読み込み
	FILE* fp;
	fopen_s(&fp, pFileName, "rb");
	if (!fp) { return hr; }

	// ファイルサイズ
	int fileSize = 0;
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);

	// メモリ読み込み
	fseek(fp, 0, SEEK_SET);
	char* pData = new char[fileSize];
	fread(pData, fileSize, 1, fp);
	fclose(fp);

	// シェーダー作成
	hr = MakeShader(pData, fileSize);

	// 終了処理
	if (pData) { delete[] pData; }
	return hr;
}

HRESULT Shader::Compile(const char * pCode)
{
	static const char *pTargetList[] =
	{
		"vs_5_0",
		"ps_5_0"
	};

	HRESULT hr;
	ID3DBlob *pBlob;
	ID3DBlob *error;
	UINT compileFlg = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	hr = D3DCompile(pCode, strlen(pCode), nullptr, nullptr, nullptr, "main", pTargetList[m_kind], compileFlg, 0, &pBlob, &error);
	if (FAILED(hr)) { return hr; }

	// シェーダー作成
	hr = MakeShader(pBlob->GetBufferPointer(), (UINT)pBlob->GetBufferSize());
	SAFE_RELEASE(pBlob);
	SAFE_RELEASE(error);

	return hr;
}


VertexShader::ILList VertexShader::m_list;
void VertexShader::ReleaseInputLayout()
{
	ILList::iterator it = m_list.begin();
	while (it != m_list.end())
	{
		SAFE_RELEASE((it->second));
		++it;
	}
}

VertexShader::VertexShader() : Shader(Shader::VertexShader), m_pVS(nullptr), m_pInputLayout(nullptr)
{
}

VertexShader::~VertexShader()
{
	SAFE_RELEASE(m_pVS);
}

void VertexShader::Bind()
{
	ID3D11DeviceContext* pContext = GetDeviceContext();
	pContext->VSSetShader(m_pVS, NULL, 0);
	pContext->IASetInputLayout(m_pInputLayout);
}

HRESULT VertexShader::MakeShader(void * pData, UINT size)
{
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();

	// シェーダー作成
	hr = pDevice->CreateVertexShader(pData, size, NULL, &m_pVS);
	if (FAILED(hr)) { return hr; }
	
	// 動的に入力レイアウトを取得
	ID3D11ShaderReflection *pReflection;
	D3D11_SHADER_DESC shaderDesc;
	D3D11_INPUT_ELEMENT_DESC* pInputDesc;
	D3D11_SIGNATURE_PARAMETER_DESC sigDesc;
	std::string key = "";

	DXGI_FORMAT formats[][4] =
	{
		{ DXGI_FORMAT_R32_UINT, DXGI_FORMAT_R32G32_UINT, DXGI_FORMAT_R32G32B32_UINT, DXGI_FORMAT_R32G32B32A32_UINT,},
		{ DXGI_FORMAT_R32_SINT,	DXGI_FORMAT_R32G32_SINT, DXGI_FORMAT_R32G32B32_SINT, DXGI_FORMAT_R32G32B32A32_SINT,},
		{ DXGI_FORMAT_R32_FLOAT, DXGI_FORMAT_R32G32_FLOAT, DXGI_FORMAT_R32G32B32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT,},
	};

	hr = D3DReflect(pData, size, IID_PPV_ARGS(&pReflection));
	if (FAILED(hr)) { return hr; }

	pReflection->GetDesc(&shaderDesc);
	pInputDesc = new D3D11_INPUT_ELEMENT_DESC[shaderDesc.InputParameters];
	for (UINT i = 0; i < shaderDesc.InputParameters; ++i)
	{
		pReflection->GetInputParameterDesc(i, &sigDesc);
		pInputDesc[i].SemanticName = sigDesc.SemanticName;
		pInputDesc[i].SemanticIndex = sigDesc.SemanticIndex;

		// 立っているビットの数を数える
		BYTE elementCount = sigDesc.Mask;
		elementCount = (elementCount & 0x05) + ((elementCount >> 1) & 0x05);
		elementCount = (elementCount & 0x03) + ((elementCount >> 2) & 0x03);

		switch (sigDesc.ComponentType)
		{
		case D3D_REGISTER_COMPONENT_UINT32:
			pInputDesc[i].Format = formats[0][elementCount - 1];
			break;
		case D3D_REGISTER_COMPONENT_SINT32:
			pInputDesc[i].Format = formats[1][elementCount - 1];
			break;
		case D3D_REGISTER_COMPONENT_FLOAT32:
			pInputDesc[i].Format = formats[2][elementCount - 1];
			break;
		}
		pInputDesc[i].InputSlot = 0;
		pInputDesc[i].AlignedByteOffset = i == 0 ? 0 : D3D11_APPEND_ALIGNED_ELEMENT;
		pInputDesc[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		pInputDesc[i].InstanceDataStepRate = 0;

		key += sigDesc.SemanticName;
		key += '0' + sigDesc.SemanticIndex;
	}

	ILList::iterator it = m_list.begin();
	while (it != m_list.end())
	{
		if (it->first == key)
		{
			m_pInputLayout = it->second;
			break;
		}
		++it;
	}
	if (it == m_list.end())
	{
		hr = pDevice->CreateInputLayout(pInputDesc, shaderDesc.InputParameters, pData, size, &m_pInputLayout);
		if (SUCCEEDED(hr)) 
		{ 
			m_list.insert(ILkey(key, m_pInputLayout)); 
		}
	}

	delete[] pInputDesc;
	pReflection->Release();
	return hr;
}

PixelShader::PixelShader() : Shader(Shader::PixelShader), m_pPS(nullptr)
{
}

PixelShader::~PixelShader()
{
	SAFE_RELEASE(m_pPS);
}

void PixelShader::Bind()
{
	ID3D11DeviceContext* pContext = GetDeviceContext();
	pContext->PSSetShader(m_pPS, nullptr, 0);
}

HRESULT PixelShader::MakeShader(void * pData, UINT size)
{
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();
	hr = pDevice->CreatePixelShader(pData, size, NULL, &m_pPS);

	return hr;
}
