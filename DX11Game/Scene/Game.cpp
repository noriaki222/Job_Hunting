//=============================================================================
//
// ゲーム クラス実装 [Game.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "Game.h"
#include "../Core/GameObj.h"
#include "../Core/Fade.h"
#include "../Base/Texture.h"
#include "../Base/Polygon.h"

using namespace DirectX;

// コンストラクタ
CGame::CGame() : CScene()
{
	m_id = SCENE_GAME;
	m_p3D = nullptr;
}

// デストラクタ
CGame::~CGame()
{
}

// 初期化
bool CGame::Init()
{
	m_bResult = false;

	m_cam.Init();
	CCamera::Set(&m_cam);
	m_p3D = new Test3D(this);

	// 全オブジェクト初期化
	if (FAILED(CGameObj::InitAll(m_pObj))) {
		return false;
	}


	// BGM再生開始


	return true;
}

// 終了処理
void CGame::Fin()
{
	// BGM再生停止

	// 全オブジェクト終了処理
	CGameObj::FinAll(m_pObj);
}

// 更新
void CGame::Update()
{
	// 全キャラ更新
	CGameObj::UpdateAll(m_pObj);

}

// 描画
void CGame::Draw()
{
	// 全キャラ描画
	CGameObj::DrawAll(m_pObj);

	/*SetZBuffer(false);
	SetBlendState(BS_ALPHABLEND);
	CPolygon::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	CPolygon::SetTexture(m_pTex);
	CPolygon::SetPos(0.0f, 0.0f);
	CPolygon::SetSize(800.0f, 200.0f);
	CPolygon::Draw(GetDeviceContext());*/
}