#include "TestEnemy.h"

TestEnemy::TestEnemy()
{
	m_tag = TAG_ENEMY;
	SetModel(CModel::GetModel(MODEL_ENEMY0));
	m_transform.scale = DirectX::XMFLOAT3(0.1f, 0.1f, 0.1f);
	m_transform.pos = DirectX::XMFLOAT3(10.0f, 0.0f, 15.0f);
	m_coll.center = DirectX::XMFLOAT3(0.0f, 80.0f, 0.0f);
	m_coll.size = DirectX::XMFLOAT3(40.0f, 100.0f, 50.0f);
	m_drawOrder = DEFAULT_3D_ORDER + 1;

	m_visible = false;
}

TestEnemy::~TestEnemy()
{
}

void TestEnemy::Update()
{
}
