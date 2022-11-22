#include "Object3D.h"

Object3D::Object3D()
{
}

Object3D::~Object3D()
{
}

void Object3D::Init()
{
	SetModel(CModel::GetModel(EModel::MODEL_TEST));
}

void Object3D::Uninit()
{
}

void Object3D::Update()
{
}

void Object3D::Draw()
{
	UpdateMatrix();
	
	ID3D11DeviceContext* pDC = GetDeviceContext();
	// �s�����`��
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
