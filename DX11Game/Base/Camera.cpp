// カメラクラス
#include "Camera.h"


using namespace DirectX;

// グローバル変数
namespace {
	const float CAM_POS_P_X = 0.0f;					// カメラの視点初期位置(X座標)
	const float CAM_POS_P_Y = 30.0f;				// カメラの視点初期位置(Y座標)
	const float CAM_POS_P_Z = -80.0f;				// カメラの視点初期位置(Z座標)
	const float CAM_POS_R_X = 0.0f;					// カメラの注視点初期位置(X座標)
	const float CAM_POS_R_Y = 0.0f;					// カメラの注視点初期位置(Y座標)
	const float CAM_POS_R_Z = 0.0f;					// カメラの注視点初期位置(Z座標)
	const float VIEW_ANGLE = 30.0f;					// 視野角
	const float VIEW_ASPECT = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;	// アスペクト比
	const float VIEW_NEAR_Z = 1.0f;					// NearZ値
	const float VIEW_FAR_Z = 10000.0f;				// FarZ値

	CCamera g_camera;								// カメラ インスタンス
}

CCamera* CCamera::m_pCamera = &g_camera;			// 現在のカメラ

// コンストラクタ
CCamera::CCamera()
{
	Init();
}

// 初期化
void CCamera::Init()
{
	m_vPos = XMFLOAT3(CAM_POS_P_X, CAM_POS_P_Y, CAM_POS_P_Z);		// 視点
	m_vTarget = XMFLOAT3(CAM_POS_R_X, CAM_POS_R_Y, CAM_POS_R_Z);	// 注視点
	m_vUp = XMFLOAT3(0.0f, 1.0f, 0.0f);		// 上方ベクトル

	m_fAspectRatio = VIEW_ASPECT;			// 縦横比
	m_fFovY = VIEW_ANGLE;					// 視野角(Degree)
	m_fNearZ = VIEW_NEAR_Z;					// 前方クリップ距離
	m_fFarZ = VIEW_FAR_Z;					// 後方クリップ距離

	m_vAngle = XMFLOAT3(0.0f, 0.0f, 0.0f);
	float fVecX, fVecZ;
	fVecX = m_vPos.x - m_vTarget.x;
	fVecZ = m_vPos.z - m_vTarget.z;
	m_fLengthInterval = sqrtf(fVecX * fVecX + fVecZ * fVecZ);

	// 視錐台の初期化
	float fTan = tanf(XMConvertToRadians(m_fFovY * 0.5f));
	m_frus[0].x = 0.0f; m_frus[0].y = -1.0f;
	m_frus[0].z = fTan; m_frus[0].w = 0.0f;
	m_frus[1].x = 0.0f; m_frus[1].y = 1.0f;
	m_frus[1].z = fTan; m_frus[1].w = 0.0f;
	fTan *= m_fAspectRatio;
	m_frus[2].x = 1.0f; m_frus[2].y = 0.0f;
	m_frus[2].z = fTan; m_frus[2].w = 0.0f;
	m_frus[3].x = -1.0f; m_frus[3].y = 0.0f;
	m_frus[3].z = fTan; m_frus[3].w = 0.0f;
	m_frus[4].x = 0.0f; m_frus[4].y = 0.0f;
	m_frus[4].z = 1.0f; m_frus[4].w = -m_fNearZ;
	m_frus[5].x = 0.0f; m_frus[5].y = 0.0f;
	m_frus[5].z = -1.0f; m_frus[5].w = m_fFarZ;

	// 正規化
	for (int i = 0; i < 4; ++i)
		XMStoreFloat4(&m_frus[i], XMPlaneNormalize(XMLoadFloat4(&m_frus[i])));

	CalcWorldMatrix();
}

// 更新
void CCamera::Update()
{
	// マトリックス更新
	UpdateMatrix();
	CalcWorldMatrix();

	XMMATRIX mW = XMLoadFloat4x4(&m_mtxWorld);
	mW = XMMatrixInverse(nullptr, mW);
	mW = XMMatrixTranspose(mW);
	for (int i = 0; i < 6; ++i)
		XMStoreFloat4(&m_frusw[i], XMPlaneTransform(XMLoadFloat4(&m_frus[i]), mW));
}

// 画面クリア
void CCamera::Clear()
{
	// main.cppのリソース参照
	extern ID3D11RenderTargetView* g_pRenderTargetView;
	extern ID3D11DepthStencilView* g_pDepthStencilView;

	float ClearColor[4] = { 0.117647f, 0.254902f, 0.352941f, 1.0f };
	ID3D11DeviceContext* pDC = GetDeviceContext();
	pDC->ClearRenderTargetView(g_pRenderTargetView, ClearColor);
	pDC->ClearDepthStencilView(g_pDepthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	SetZBuffer(true);
	SetBlendState(BS_NONE);
}

// ビュー/プロジェクション マトリックス更新
void CCamera::UpdateMatrix()
{
	XMStoreFloat4x4(&m_mtxView, XMMatrixLookAtLH(
		XMLoadFloat3(&m_vPos), XMLoadFloat3(&m_vTarget), XMLoadFloat3(&m_vUp)));
	XMStoreFloat4x4(&m_mtxProj, XMMatrixPerspectiveFovLH(
		XMConvertToRadians(m_fFovY), m_fAspectRatio, m_fNearZ, m_fFarZ));
}

// ワールド マトリックス設定
void CCamera::SetWorldMatrix(XMFLOAT4X4& mtxWorld)
{
	m_mtxWorld = mtxWorld;
	m_vPos = XMFLOAT3(mtxWorld._41, mtxWorld._42, mtxWorld._43);
	m_vTarget = XMFLOAT3(mtxWorld._41 + mtxWorld._31, mtxWorld._42 + mtxWorld._32, mtxWorld._43 + mtxWorld._33);
	m_vUp = XMFLOAT3(mtxWorld._21, mtxWorld._22, mtxWorld._23);
}

// 視点/注視点/上方ベクトルからワールド マトリックス算出
XMFLOAT4X4& CCamera::CalcWorldMatrix()
{
	XMVECTOR vecZ = XMVectorSet(m_vTarget.x - m_vPos.x, m_vTarget.y - m_vPos.y, m_vTarget.z - m_vPos.z, 0.0f);
	XMFLOAT3 vZ;
	XMStoreFloat3(&vZ, XMVector3Normalize(vecZ));
	XMVECTOR vecY = XMLoadFloat3(&m_vUp);
	XMVECTOR vecX = XMVector3Normalize(XMVector3Cross(vecY, vecZ));
	XMFLOAT3 vX;
	XMStoreFloat3(&vX, vecX);
	vecY = XMVector3Normalize(XMVector3Cross(vecZ, vecX));
	XMFLOAT3 vY;
	XMStoreFloat3(&vY, vecY);

	m_mtxWorld._11 = vX.x;
	m_mtxWorld._12 = vX.y;
	m_mtxWorld._13 = vX.z;
	m_mtxWorld._14 = 0.0f;
	m_mtxWorld._21 = vY.x;
	m_mtxWorld._22 = vY.y;
	m_mtxWorld._23 = vY.z;
	m_mtxWorld._24 = 0.0f;
	m_mtxWorld._31 = vZ.x;
	m_mtxWorld._32 = vZ.y;
	m_mtxWorld._33 = vZ.z;
	m_mtxWorld._34 = 0.0f;
	m_mtxWorld._41 = m_vPos.x;
	m_mtxWorld._42 = m_vPos.y;
	m_mtxWorld._43 = m_vPos.z;
	m_mtxWorld._44 = 1.0f;

	return m_mtxWorld;
}

// 戻り値：0→非表示, -1→部分表示, 1:表示
int CCamera::CollisionViewFrustum(DirectX::XMFLOAT3 * pCenter, float fRadius)
{
	bool bHit = false;
	XMVECTOR frusw, center, dot;
	float fDot;
	center = DirectX::XMLoadFloat3(pCenter);
	for (int i = 0; i < 6; ++i)
	{
		frusw = DirectX::XMLoadFloat4(&m_frusw[i]);
		dot = XMPlaneDotCoord(frusw, center);
		XMStoreFloat(&fDot, dot);
		if (fDot < -fRadius) return 0;	// 完全に外 
		if (fDot <= fRadius) bHit = true;
	}
	if (bHit) return -1;	// 面を跨ぐ
	return 1;
}

// カメラ インスタンス設定
void CCamera::Set(CCamera* pCamera)
{
	m_pCamera = (pCamera) ? pCamera : &g_camera;
}