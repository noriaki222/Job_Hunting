// メイン処理
#pragma once

// インクルード
#define NOMINMAX
#include <windows.h>
#include <tchar.h>
#include <math.h>
#include <mmsystem.h>
#include <DirectXMath.h>
#include <d3d11.h>

// マクロ定義
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) {if(x){(x)->Release();x=nullptr;}}
#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(x) {if(x){delete(x);x=nullptr;}}
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) {if(x){delete[](x);x=nullptr;}}
#endif

#define SCREEN_WIDTH	(1280)				// ウインドウの幅
#define SCREEN_HEIGHT	(720)				// ウインドウの高さ
#define SCREEN_CENTER_X	(SCREEN_WIDTH/2)	// ウインドウの中心Ｘ座標
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT/2)	// ウインドウの中心Ｙ座標

#define	NUM_VERTEX		(4)					// 頂点数
#define	NUM_POLYGON		(2)					// ポリゴン数

#define MAX_RENDER		(8)					// 最大レンダーターゲットビューの数

#define SinDeg(degree)	sinf(XMConvertToRadians(degree))
#define CosDeg(degree)	cosf(XMConvertToRadians(degree))

#define GRAVITY	(0.8f)

enum EBlendState {
	BS_NONE = 0,							// 半透明合成無し
	BS_ALPHABLEND,							// 半透明合成
	BS_ADDITIVE,							// 加算合成
	BS_SUBTRACTION,							// 減算合成

	MAX_BLENDSTATE
};

enum ECullMode {
	CULLMODE_NONE = 0,						// カリングしない
	CULLMODE_CW,							// 前面カリング
	CULLMODE_CCW,							// 背面カリング

	MAX_CULLMODE
};

enum ERenderTarget {
	RT_BUCK = 0,							// バックバッファ
	RT_GAME_AND_UI,							// ゲーム+UI
	RT_UI,									// UIのみ
	RT_GAME,								// ゲームのみ
	RT_DEBUG,								// デバック
};

enum EBillbordType
{
	BILLBOARD_NONE,
	BILLBOARD_ALL,
	BILLBOARD_NOT_Y,
};

// 構造体定義
typedef struct
{
	DirectX::XMFLOAT3 vtx;		// 頂点座標
	DirectX::XMFLOAT4 diffuse;	// 拡散反射光
	DirectX::XMFLOAT2 tex;		// テクスチャ座標
} VERTEX_2D;

typedef struct
{
	DirectX::XMFLOAT3 vtx;		// 頂点座標
	DirectX::XMFLOAT3 nor;		// 法線ベクトル
	DirectX::XMFLOAT4 diffuse;	// 拡散反射光
	DirectX::XMFLOAT2 tex;		// テクスチャ座標
} VERTEX_3D;

struct Transform
{
	DirectX::XMFLOAT3 pos;		// 座標
	DirectX::XMFLOAT3 rot;		// 回転 degrees角
	DirectX::XMFLOAT3 scale;	// スケール
	
	static Transform Zero()
	{
		Transform work;
		work.pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		work.rot = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		work.scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
		return work;
	}
};

struct RigidBody
{
	DirectX::XMFLOAT3 spd;	// 速度
	DirectX::XMFLOAT3 acc;	// 加速度
	bool isGravity = false;	// 重力フラグ

	static RigidBody Zero()
	{
		RigidBody work;
		work.spd = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		work.acc = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		work.isGravity = false;
		return work;
	}
};

struct Collider
{
	DirectX::XMFLOAT3 center;	// 当たり判定の中心
	DirectX::XMFLOAT3 size;	// 当たり判定の大きさ(ローカル座標軸
	bool isCollision;	// 当たり判定が有効か

	static Collider Zero()
	{
		Collider work;
		work.center = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		work.size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
		work.isCollision = false;
		return work;
	}
};

// プロトタイプ宣言
HWND GetMainWnd();
HINSTANCE GetInstance();
ID3D11Device* GetDevice();
ID3D11DeviceContext* GetDeviceContext();
ID3D11RenderTargetView* GetRenderTargetView(int nTargetNum = 0);
ID3D11ShaderResourceView* GetRenderTexture(int nTargetNum);
void SetZBuffer(bool bEnable);
void SetZWrite(bool bEnable);
void SetBlendState(int nBlendState);
void SetCullMode(int nCullMode);
void SetRenderTarget(int nTargetNum);
void ClearAllTarget(const FLOAT* color);