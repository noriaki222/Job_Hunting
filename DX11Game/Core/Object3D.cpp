#include "Object3D.h"
#include <time.h>


Object3D::Object3D()
{
	SetModel(CModel::GetModel(EModel::MODEL_TEST));
	m_type = TYPE_3D;
	m_updateOrder = DEFAULT_3D_ORDER;
	m_drawOrder = DEFAULT_3D_ORDER;

	m_isAnim = false;	
	m_animNo = 0;	
	m_animTime = 0.0f;

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
		m_model->SetAnimIndex(m_animNo);
		m_model->SetAnimTime(m_animTime);
	}
	
	ID3D11DeviceContext* pDC = GetDeviceContext();
	// �s�����`��
	SetBlendState(BS_NONE);
	m_model->SetAlpha(m_color.w);
	m_model->Draw(pDC, m_mWorld, eOpacityOnly);

	// �������`��
	SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��
	SetZWrite(false);				// Z�o�b�t�@�X�V���Ȃ�
	m_model->Draw(pDC, m_mWorld, eTransparentOnly);
	SetZWrite(true);				// Z�o�b�t�@�X�V����
	SetBlendState(BS_NONE);			// �A���t�@�u�����h����
	m_model->SetAlpha(1.0f);
}

void Object3D::UpdateMatrix()
{
	if (m_isAnim)
	{
		if (!m_lastTime) { m_lastTime = clock() / double(CLOCKS_PER_SEC); }
		double dNowTime = clock() / double(CLOCKS_PER_SEC);
		double dSlice = dNowTime - m_lastTime;
		m_lastTime = dNowTime;
		m_animTime += dSlice;
		if (m_animTime >= m_model->GetAnimDuration(m_animNo)) {
			m_animTime = 0.0;
		}
	}

	ObjectBase::UpdateMatrix();
}

void Object3D::SetModel(CAssimpModel * model)
{
	m_model = model;
}
