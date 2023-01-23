#include "TestLight.h"
#include "../../Base/Input.h"

TestLight::TestLight()
{
	m_rad = 0.0f;
}

TestLight::~TestLight()
{
}

void TestLight::Update()
{
	using namespace DirectX;
	if (IsKeyPress(VK_LEFT)) { m_rad -= 0.01f; }
	if (IsKeyPress(VK_RIGHT)) { m_rad += 0.01f; }
	m_direction = XMFLOAT3(cosf(m_rad), -1.0f, sinf(m_rad));
}
