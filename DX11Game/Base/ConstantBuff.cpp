#include "ConstantBuff.h"

ConstantBuff::ConstantBuff() : m_pBuff(nullptr)
{
}

ConstantBuff::~ConstantBuff()
{
	SAFE_RELEASE(m_pBuff);
}

void ConstantBuff::Init()
{
	// CreateObj‚ðŽg—p‚·‚é‚½‚ß
}

HRESULT ConstantBuff::Create(UINT size)
{
	HRESULT hr;

	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = size;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	ID3D11Device* pDevice = GetDevice();
	hr = pDevice->CreateBuffer(&desc, nullptr, &m_pBuff);
	return hr;
}

void ConstantBuff::Write(const void * data)
{
	ID3D11DeviceContext* pDC = GetDeviceContext();
	pDC->UpdateSubresource(m_pBuff, 0, nullptr, data, 0, 0);
}

void ConstantBuff::BindVS(int num)
{
	ID3D11DeviceContext* pDC = GetDeviceContext();
	pDC->VSSetConstantBuffers(num, 1, &m_pBuff);
}

void ConstantBuff::BindPS(int num)
{
	ID3D11DeviceContext* pDC = GetDeviceContext();
	pDC->PSSetConstantBuffers(num, 1, &m_pBuff);
}
