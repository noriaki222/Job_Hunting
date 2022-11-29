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
}

Object3D::~Object3D()
{
}

void Object3D::Init()
{
}

void Object3D::Uninit()
{
}

void Object3D::Update()
{
	if (m_isAnim)
	{
		static double dLastTime = clock() / double(CLOCKS_PER_SEC);
		double dNowTime = clock() / double(CLOCKS_PER_SEC);
		double dSlice = dNowTime - dLastTime;
		dLastTime = dNowTime;
		m_animTime += dSlice;
		if (m_animTime >= m_model->GetAnimDuration(m_animNo)) {
			m_animTime = 0.0;
		}
	}
}

void Object3D::Draw()
{
	if (m_isAnim)
	{
		m_model->SetAnimIndex(m_animNo);
		m_model->SetAnimTime(m_animTime);
	}
	UpdateMatrix();
	
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

void Object3D::SetModel(CAssimpModel * model)
{
	m_model = model;
}
