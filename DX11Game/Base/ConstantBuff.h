#pragma once
#include "../main.h"

class ConstantBuff
{
public:
	ConstantBuff();
	~ConstantBuff();

	void Init();
	// ���ӁF�萔�o�b�t�@��4�o�C�g��؂�łȂ��ƍ쐬�o���Ȃ�
	HRESULT Create(UINT size);
	void Write(const void* data);
	void BindVS(int num);
	void BindPS(int num);

private:
	ID3D11Buffer* m_pBuff;
};