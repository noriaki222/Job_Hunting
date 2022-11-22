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
	// 不透明描画
	m_model->SetAlpha(m_color.w);
	m_model->Draw(pDC, m_mWorld, eOpacityOnly);

	// 半透明描画
	SetBlendState(BS_ALPHABLEND);	// アルファブレンド有効
	SetZWrite(false);				// Zバッファ更新しない
	m_model->Draw(pDC, m_mWorld, eTransparentOnly);
	SetZWrite(true);				// Zバッファ更新する
	SetBlendState(BS_NONE);			// アルファブレンド無効
	m_model->SetAlpha(1.0f);
}

void Object3D::SetModel(CAssimpModel * model)
{
	m_model = model;
}
