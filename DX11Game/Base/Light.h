// 光源クラス
#pragma once
#include "../main.h"

class CLight
{
protected:
	DirectX::XMFLOAT4 m_diffuse;
	DirectX::XMFLOAT4 m_ambient;
	DirectX::XMFLOAT4 m_specular;
	DirectX::XMFLOAT3 m_direction;
	bool m_bEnable;			// ライティング有効/無効

	static CLight* m_pLight;

public:
	CLight();

	void Init();
	DirectX::XMFLOAT4& GetDiffuse() { return m_diffuse; }
	DirectX::XMFLOAT4& GetAmbient() { return m_ambient; }
	DirectX::XMFLOAT4& GetSpecular() { return m_specular; }
	DirectX::XMFLOAT3& GetDir();
	void SetEnable(bool bEnable = true) { m_bEnable = bEnable; }
	void SetDisable(bool bDisable = true) { m_bEnable = !bDisable; }

	static CLight* Get();
	static void Set(CLight* pLight = nullptr);
};