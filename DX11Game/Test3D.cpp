#include "Test3D.h"
#include "Base\Input.h"

Test3D::Test3D()
{
	SetModel(CModel::GetModel(MODEL_TEST));
	m_transform.scale = DirectX::XMFLOAT3(0.1f, 0.1f, 0.1f);
	m_coll.size = DirectX::XMFLOAT3(40.0f, 80.0f, 50.0f);
	m_coll.center = DirectX::XMFLOAT3(0.0f, 80.0f, 0.0f);
	m_animNo = 2;
	m_isAnim = true;
	m_coll.isCollision = true;
	m_drawOrder = DEFAULT_3D_ORDER + 1;
	m_useRT.push_back(RT_NORMAL);
	m_useRT.push_back(RT_Z);
	m_useRT.push_back(RT_DEBUG);
}

Test3D::~Test3D()
{
}

void Test3D::Update()
{	
	if (IsKeyPress(VK_SPACE))
	{
		m_animNo = 3;
		m_rigidbody.spd.y = 1.0f;
	}
	else
	{
		if (m_transform.pos.y > 0)
		{
			m_rigidbody.spd.y = -1.0f;
		}
	}
	if (IsKeyPress(VK_RIGHT))
	{
		m_rigidbody.spd.x = 1.0f;
	}
	else if (IsKeyPress(VK_LEFT))
	{
		m_rigidbody.spd.x = -1.0f;
	}
	else if (IsKeyPress(VK_UP))
	{
		m_rigidbody.spd.z = 1.0f;
	}
	else if (IsKeyPress(VK_DOWN))
	{
		m_rigidbody.spd.z = -1.0f;
	}
	else
	{
		m_rigidbody = RigidBody::Zero();
	}
}
