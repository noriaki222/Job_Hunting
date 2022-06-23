// フェード イン/アウト [Fade.cpp]
#include "Fade.h"
#include "../Base/Polygon.h"

using namespace DirectX;

// 静的メンバ
EFade CFade::m_fade = FADE_NONE;
EScene CFade::m_sceneNext = SCENE_TITLE;
XMFLOAT4 CFade::m_vColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
float CFade::m_fRate = 1.0f / (60.0f * 0.5f);

// 初期化
void CFade::Init()
{
	m_vColor.w = 1.0f;			// 不透明度
	m_fade = FADE_IN;			// 状態
	m_sceneNext = SCENE_TITLE;	// 次のシーン
}

// 更新
void CFade::Update()
{
	// 何もしていない
	if (m_fade == FADE_NONE) {
		return;
	}
	// フェードアウト処理
	if (m_fade == FADE_OUT) {
		m_vColor.w += m_fRate;	// 不透明度を増加
		if (m_vColor.w >= 1.0f) {
			// フェードイン処理に切替
			m_vColor.w = 1.0f;
			m_fade = FADE_IN;
			// シーン切替
			CScene::Change(m_sceneNext);
		}
		// 音もフェードアウト
		return;
	}
	// フェードイン処理
	m_vColor.w -= m_fRate;	// 不透明度を下げる
	if (m_vColor.w <= 0.0f) {
		// フェード処理終了
		m_vColor.w = 0.0f;
		m_fade = FADE_NONE;
	}
	// 音もフェードイン
}

// 描画
void CFade::Draw()
{
	ID3D11DeviceContext* pDC = GetDeviceContext();

	SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);

	Polygon::SetColor(m_vColor);
	Polygon::SetTexture(nullptr);
	Polygon::SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	Polygon::SetUV(0.0f, 0.0f);
	Polygon::SetFrameSize(1.0f, 1.0f);
	Polygon::SetPos(0.0f, 0.0f);
	Polygon::Draw(pDC);

	Polygon::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// フェードアウト開始
void CFade::Out(EScene scene, float fSecond)
{
	if (m_fade != FADE_OUT) {
		m_fade = FADE_OUT;
		m_sceneNext = scene;
		m_fRate = 1.0f / (60.0f * fSecond);
	}
}

// フェードイン アウト カラー設定
void CFade::SetColor(XMFLOAT3 vColor)
{
	m_vColor.x = vColor.x;
	m_vColor.y = vColor.y;
	m_vColor.z = vColor.z;
}
