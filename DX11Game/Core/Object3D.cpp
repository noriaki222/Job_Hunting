#include "Object3D.h"
#include <time.h>


Object3D::Object3D()
{
	SetModel(CModel::GetModel(EModel::MODEL_TEST));
	m_type = TYPE_3D;
	m_updateOrder = DEFAULT_3D_ORDER;
	m_drawOrder = DEFAULT_3D_ORDER;

	m_isAnim = false;	
	m_anim.Set(0, 0);
	m_nextAnim.Set(0, 0);
	m_animTime = 0.0f;
	m_changeAnim = true;

	m_useRT.push_back(RT_GAME);
}

Object3D::~Object3D()
{
}

void Object3D::Init()
{
#ifdef _DEBUG
	debug_collit = Debug_Collision::GetInstance()->AddList(&m_coll, &m_mWorld, &m_transform);
#endif // DEBUG
}

void Object3D::Uninit()
{
}

void Object3D::Update()
{
}

void Object3D::Draw()
{
	if (m_isAnim)
	{
		m_model->SetAnimIndex(m_anim.AnimNo);
		m_model->SetAnimTime(m_animTime);
	}
	
	ID3D11DeviceContext* pDC = GetDeviceContext();
	// 不透明描画
	SetBlendState(BS_NONE);
	m_model->SetAlpha(m_color.w);
	DirectX::XMFLOAT4X4 mW;
	DirectX::XMStoreFloat4x4(&mW, DirectX::XMMatrixMultiply(DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_startRot.x)), XMLoadFloat4x4(&GetWorld())));
	DirectX::XMStoreFloat4x4(&mW, DirectX::XMMatrixMultiply(DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_startRot.y)),XMLoadFloat4x4(&mW)));
	DirectX::XMStoreFloat4x4(&mW, DirectX::XMMatrixMultiply(DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_startRot.z)),XMLoadFloat4x4(&mW)));
	m_model->Draw(pDC, mW, eOpacityOnly);

	// 半透明描画
	SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効
	SetZWrite(false);				// Zバッファ更新しない
	m_model->Draw(pDC, mW, eTransparentOnly);
	SetZWrite(true);				// Zバッファ更新する
	SetBlendState(BS_NONE);			// アルファブレンド無効
	m_model->SetAlpha(1.0f);
}

void Object3D::UpdateMatrix()
{
	if (m_isAnim)
	{
		if (m_anim.Priority <= m_nextAnim.Priority) 
		{
			m_anim = m_nextAnim; 
			m_changeAnim = true; 
		}
		else 
		{ 
			m_changeAnim = false; 
		}
		if (!m_lastTime) { m_lastTime = clock() / double(CLOCKS_PER_SEC); }
		double dNowTime = clock() / double(CLOCKS_PER_SEC);
		double dSlice = dNowTime - m_lastTime;
		m_lastTime = dNowTime;
		m_animTime += dSlice;
		if (m_animTime >= m_model->GetAnimDuration(m_anim.AnimNo)) {
			m_animTime = 0.0;
			m_anim = m_nextAnim;
			m_changeAnim = true;
		}
	}

	ObjectBase::UpdateMatrix();
}

void Object3D::SetModel(CAssimpModel * model)
{
	m_model = model;
}
