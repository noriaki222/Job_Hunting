//=============================================================================
//
// タイトル画面クラス実装 [Title.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "Title.h"
#include "../Base/Texture.h"
#include "../Base/Polygon.h"
#include "../Core/Fade.h"

// 定数定義
namespace {
	const LPCWSTR g_pszPathTexTitle = L"data/texture/title_logo.png";
	const float g_fTexTitleWidth = 800.0f;
	const float g_fTexTitleHeight = 200.0f;

	const LPCWSTR g_pszPathTexStart = L"data/texture/press_enter.png";
	const float g_fTexStartWidth = 480.0f;
	const float g_fTexStartHeight = 120.0f;
	const float g_fTexStartY = SCREEN_HEIGHT / -2.5f;

	const LPCWSTR g_pszPathTexBG = L"data/texture/title_bg.png";
}

// コンストラクタ
CTitle::CTitle() : CScene()
{
	m_id = SCENE_TITLE;

	m_bStart = false;
	m_pTexTitle = nullptr;
	m_pTexStart = nullptr;
	m_pTexBG = nullptr;
	m_nTimer = 0;
}

// デストラクタ
CTitle::~CTitle()
{
}

// 初期化
bool CTitle::Init()
{
	if (!CScene::Init()) {
		return false;
	}

	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	m_bStart = false;
	// テクスチャの読み込み
	hr = CreateTextureFromFile(pDevice, g_pszPathTexTitle, &m_pTexTitle);
	if (FAILED(hr)) {
		return false;
	}
	hr = CreateTextureFromFile(pDevice, g_pszPathTexStart, &m_pTexStart);
	if (FAILED(hr)) {
		Fin();
		return false;
	}
	hr = CreateTextureFromFile(pDevice, g_pszPathTexBG, &m_pTexBG);
	if (FAILED(hr)) {
		Fin();
		return false;
	}

	m_nTimer = 0;


	return true;
}

// 終了処理
void CTitle::Fin()
{

	SAFE_RELEASE(m_pTexBG);
	SAFE_RELEASE(m_pTexStart);
	SAFE_RELEASE(m_pTexTitle);

	CScene::Fin();
}

// 更新
void CTitle::Update()
{
	++m_nTimer;
	if (m_nTimer > 120) {
		m_nTimer = 0;
	}
}

// 描画
void CTitle::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);

	Polygon::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	Polygon::SetTexture(m_pTexBG);
	Polygon::SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	Polygon::SetUV(0.0f, 0.0f);
	Polygon::SetFrameSize(1.0f, 1.0f);
	Polygon::SetPos(0.0f, 0.0f);
	Polygon::Draw(pDC);

	Polygon::SetTexture(m_pTexTitle);
	Polygon::SetSize(g_fTexTitleWidth, g_fTexTitleHeight);
	Polygon::Draw(pDC);

	Polygon::SetAlpha((m_nTimer <= 60) ? m_nTimer / 60.0f : (120 - m_nTimer) / 60.0f);
	Polygon::SetTexture(m_pTexStart);
	Polygon::SetSize(g_fTexStartWidth, g_fTexStartHeight);
	Polygon::SetPos(0.0f, g_fTexStartY);
	Polygon::Draw(pDC);
}
