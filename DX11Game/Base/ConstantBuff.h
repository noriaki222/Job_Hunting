#pragma once
#include "../main.h"

class ConstantBuff
{
public:
	ConstantBuff();
	~ConstantBuff();

	void Init();
	// 注意：定数バッファは4バイト区切りでないと作成出来ない
	HRESULT Create(UINT size);
	void Write(const void* data);
	void BindVS(int num);
	void BindPS(int num);

private:
	ID3D11Buffer* m_pBuff;
};