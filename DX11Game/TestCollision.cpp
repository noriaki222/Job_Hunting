#include "TestCollision.h"

TestCollision::TestCollision()
{
	m_coll.isCollision = true;
	m_transform.rot = DirectX::XMFLOAT3(-45.0f, 45.0f, 0.0f);
	m_transform.pos.z = -10.0f;
	m_tag = TAG_COLLTEST;
}

TestCollision::~TestCollision()
{
}

void TestCollision::Update()
{
#ifdef _DEBUG
	if (Collision(m_target))
	{
		(*debug_collit)->SetRed();
	}
	else
	{
		(*debug_collit)->SetGreen();
	}
#endif // _DEBUG
}
