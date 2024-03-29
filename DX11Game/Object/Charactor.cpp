#include "Charactor.h"

using namespace DirectX;

Charactor::Charactor()
{
	m_pLand = nullptr;

	// デフォルトキャラの設定
	SetModel(CModel::GetModel(MODEL_TEST));
	m_transform.scale = DirectX::XMFLOAT3(0.1f, 0.1f, 0.1f);
	m_coll.size = DirectX::XMFLOAT3(40.0f, 80.0f, 50.0f);
	m_coll.center = DirectX::XMFLOAT3(0.0f, 80.0f, 0.0f);
	m_rigidbody.isGravity = true;
	m_coll.isCollision = true;
	isGround = false;


	m_life = 1;
	m_attack = 1;
	m_isAttack = false;
	m_useRT.push_back(RT_NORMAL);
}

Charactor::~Charactor()
{
}

void Charactor::Init()
{
	startGravity = m_rigidbody.isGravity;
	Object3D::Init();
}

void Charactor::UpdateMatrix()
{
	Object3D::UpdateMatrix();
	// 地面との当たり判定
	XMFLOAT3 vP0;
	vP0.x = m_transform.pos.x;
	vP0.y = m_transform.pos.y + m_coll.size.y * m_transform.scale.y;
	vP0.z = m_transform.pos.z;
	
	XMFLOAT3 vX, vY;
	if (m_pLand && m_pLand->CollisionRay(vP0, XMFLOAT3(0.0f, -1.0f, 0.0f), &vX, &vY))
	{
		if (vX.y > m_transform.pos.y)
		{
			m_transform.pos.y = vX.y;
			isGround = true;
		}
		else
		{
			isGround = false;
		}
	}
	else
	{
		if (0.0f > m_transform.pos.y)
		{
			m_transform.pos.y = 0.0f;
			isGround = true;
		}
	}
	
	// ワールド行列更新
	XMFLOAT4X4 mW = GetWorld();
	mW._42 = m_transform.pos.y;
	SetWorld(mW);

	if (startGravity)
	{
		m_rigidbody.isGravity = isGround ? false : true;
	}
}
