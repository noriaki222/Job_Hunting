#include "TestPlayer.h"
#include "Base\Input.h"

using namespace DirectX;

TestPlayer::TestPlayer()
{
	m_anim.Set(0, 0);
	m_isAnim = true;
	m_startRot.y = 180.0f;
}

TestPlayer::~TestPlayer()
{
}

void TestPlayer::Update()
{
	static XMFLOAT2 input = XMFLOAT2(0.0f, 0.0f);

	// ÉvÉåÉCÉÑÅ[ÇÃëÄçÏ
	if (IsKeyPress(VK_RIGHT) && m_changeAnim)
	{
		m_nextAnim.Set(3, 0);
		m_rigidbody.spd.x = 1.0f;
		input.x = 1.0f;
		input.y = 0.0f;
		if (IsKeyPress(VK_UP) && m_changeAnim)
		{
			m_rigidbody.spd.z = 1.0f;
			input.y = 1.0f;
		}
		else if (IsKeyPress(VK_DOWN) && m_changeAnim)
		{
			m_rigidbody.spd.z = -1.0f;
			input.y = -1.0f;
		}
	}
	else if (IsKeyPress(VK_LEFT) && m_changeAnim)
	{
		m_nextAnim.Set(3, 0);
		m_rigidbody.spd.x = -1.0f;
		input.x = -1.0f;
		input.y = 0.0f;
		if (IsKeyPress(VK_UP) && m_changeAnim)
		{
			m_rigidbody.spd.z = 1.0f;
			input.y = 1.0f;
		}
		else if (IsKeyPress(VK_DOWN) && m_changeAnim)
		{
			m_rigidbody.spd.z = -1.0f;
			input.y = -1.0f;
		}
	}
	else if (IsKeyPress(VK_UP) && m_changeAnim)
	{
		m_nextAnim.Set(3, 0);
		m_rigidbody.spd.x = 0.0f;
		m_rigidbody.spd.z = 1.0f;
		input.x = 0.0f;
		input.y = 1.0f;
	}
	else if (IsKeyPress(VK_DOWN) && m_changeAnim)
	{
		m_nextAnim.Set(3, 0);
		m_rigidbody.spd.x = 0.0f;
		m_rigidbody.spd.z = -1.0f;
		input.x = 0.0f;
		input.y = -1.0f;
	}
	else
	{
		m_rigidbody = RigidBody::Zero();
		m_nextAnim.Set(0, 0);
	}

	if (IsKeyPress(VK_SPACE))
	{
		m_nextAnim.Set(4, 2);
	}


	// å¸Ç¢ÇƒÇ¢ÇÈï˚å¸Ç÷à⁄ìÆ
	RotAxisY(XMConvertToDegrees(atan2f(input.x, input.y)));
	XMFLOAT3 pos = GetPos();
	pos.x += GetLocalZ().x * m_rigidbody.spd.x;
	pos.y += GetLocalZ().y * m_rigidbody.spd.y;
	pos.z += GetLocalZ().z * m_rigidbody.spd.z;
	m_mWorld._41 = pos.x;
	m_mWorld._42 = pos.y;
	m_mWorld._43 = pos.z;
	m_transform.pos = pos;
}
