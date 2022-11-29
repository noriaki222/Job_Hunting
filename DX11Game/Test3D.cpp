#include "Test3D.h"
#include <time.h>
#include "Base\Input.h"

Test3D::Test3D()
{
	SetModel(CModel::GetModel(EModel::MODEL_TEST));
	m_transform.scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_animNo = 2;
	m_isAnim = true;
}

Test3D::~Test3D()
{
}

void Test3D::Update()
{
	if (IsKeyPress(VK_SPACE))
	{
		m_animNo = 3;
	}

	Object3D::Update();
}
