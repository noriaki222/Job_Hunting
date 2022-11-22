#include "Test3D.h"

Test3D::Test3D()
{
	SetModel(CModel::GetModel(EModel::MODEL_TEST));
	m_transform.scale = DirectX::XMFLOAT3(10000.0f, 10000.0f, 10000.0f);
}

Test3D::~Test3D()
{
}
