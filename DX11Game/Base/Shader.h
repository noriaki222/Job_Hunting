#pragma once

// �x����\��
//#pragma warning(disable : 4996)

#include <d3d11.h>
#include <string>
#include <map>

HRESULT LoadVertexShader(LPCWSTR pwszVSFName, ID3D11VertexShader** ppVertexShader,
	ID3D11InputLayout** ppVertexLayout,
	const D3D11_INPUT_ELEMENT_DESC* pInpElemDesc = nullptr, UINT uNumElem = 0);
HRESULT LoadPixelShader(LPCWSTR pwszPSFName, ID3D11PixelShader** ppPixelShader);
HRESULT LoadShader(LPCWSTR pwszVSFName, LPCWSTR pwszPSFName,
	ID3D11VertexShader** ppVertexShader, ID3D11InputLayout** ppVertexLayout, ID3D11PixelShader** ppPixelShader,
	const D3D11_INPUT_ELEMENT_DESC* pInpElemDesc = nullptr, UINT uNumElem = 0);
HRESULT LoadVertexShader(LPCSTR pszVSFName, ID3D11VertexShader** ppVertexShader,
	ID3D11InputLayout** ppVertexLayout,
	const D3D11_INPUT_ELEMENT_DESC* pInpElemDesc = nullptr, UINT uNumElem = 0);
HRESULT LoadPixelShader(LPCSTR pszPSFName, ID3D11PixelShader** ppPixelShader);
HRESULT LoadShader(LPCSTR pszVSFName, LPCSTR pszPSFName,
	ID3D11VertexShader** ppVertexShader, ID3D11InputLayout** ppVertexLayout,
	ID3D11PixelShader** ppPixelShader,
	const D3D11_INPUT_ELEMENT_DESC* pInpElemDesc = nullptr, UINT uNumElem = 0);

class Shader
{
protected:
	enum Kind
	{
		VertexShader,
		PixelShader
	};
protected:
	Shader(Kind kind);

public:
	virtual ~Shader();

	HRESULT Load(const char *pFileName);
	HRESULT Compile(const char *pCode);

	virtual void Bind() = 0;

protected:
	virtual HRESULT MakeShader(void* pData, UINT size) = 0;

private:
	Kind m_kind;
};

class VertexShader : public Shader
{
private:
	using ILkey = std::pair<std::string, ID3D11InputLayout*>;
	using ILList = std::map<std::string, ID3D11InputLayout*>;

public:
	static void ReleaseInputLayout();

	VertexShader();
	~VertexShader();
	void Bind();

protected:
	HRESULT MakeShader(void* pData, UINT size);

private:
	static ILList m_list;
	ID3D11VertexShader* m_pVS;
	ID3D11InputLayout* m_pInputLayout;
};

class PixelShader : public Shader
{
public:
	PixelShader();
	~PixelShader();
	void Bind();

protected:
	HRESULT MakeShader(void* pData, UINT size);

private:
	ID3D11PixelShader* m_pPS;
};

void SetTextureVS(ID3D11ShaderResourceView* pTex, UINT slot = 0);
void SetTexturePS(ID3D11ShaderResourceView* pTex, UINT slot = 0);