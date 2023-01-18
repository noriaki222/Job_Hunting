#include "TestEnemy.h"

TestEnemy::TestEnemy()
{
	m_tag = TAG_ENEMY;
	SetModel(CModel::GetModel(MODEL_ENEMY0));
	m_transform.scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_transform.pos = DirectX::XMFLOAT3(5.0f, 5.0f, 0.0f);
	m_coll.center = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_coll.size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_rigidbody.isGravity = false;
	m_drawOrder = DEFAULT_3D_ORDER + 1;
}

TestEnemy::~TestEnemy()
{
}

void TestEnemy::Update()
{
}
