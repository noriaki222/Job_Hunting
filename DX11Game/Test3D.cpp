#include "Test3D.h"

Test3D::Test3D(CScene* pScene) : CModel(pScene)
{
}

Test3D::~Test3D()
{
}

HRESULT Test3D::Init()
{
	HRESULT hr = CModel::Init();
	SetModel(MODEL_PLAYER);
	return hr;
}

void Test3D::Fin()
{
	CModel::Fin();
}

void Test3D::Update()
{
}

void Test3D::Draw()
{
	CModel::Draw();
}

void Test3D::DrawAlpha()
{
	CModel::DrawAlpha();
}
