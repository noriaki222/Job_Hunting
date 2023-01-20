// メイン処理

// インクルード
#include "main.h"
#include "Base\Polygon.h"
#include "Base\Texture.h"
#include "Base\Model.h"
#include "Base\Input.h"
#include "Base\Mesh.h"
#include "Core\shaderList.h"
#include "Core\ScereenObjectBase.h"

#include "Manager\SceneManager.h"
#include "Core\Debug\Debug_Collision.h"

// ライブラリリンク
#pragma comment(lib, "winmm")
#pragma comment(lib, "imm32")
#pragma comment(lib, "d3d11")

// マクロ定義
#define CLASS_NAME	_T("AppClass")
#define WINDOW_NAME _T("Base_Program")

// プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs);
HRESULT Init(HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

// グローバル変数
HWND						g_hWnd;					// メイン ウィンドウ ハンドル
HINSTANCE					g_hInst;				// インスタンス ハンドル

ID3D11Device*				g_pDevice;				// デバイス
ID3D11DeviceContext*		g_pDeviceContext;		// デバイス コンテキスト
IDXGISwapChain*				g_pSwapChain;			// スワップチェーン
ID3D11Texture2D*			g_pRenderTextures[MAX_RENDER];	// レンダーテクスチャ
ID3D11ShaderResourceView*	g_pRenderShaderResViews[MAX_RENDER];	// レンダーテクスチャのシェーダーリソースビュー
ID3D11RenderTargetView*		g_pRenderTargetViews[MAX_RENDER];	// レンダーターゲット(0:バックバッファ, 1:ゲーム+UI, 2:UI, 3:ゲーム
ID3D11Texture2D*			g_pDepthStencilTexture[MAX_DEPTHVIEW];	// Zバッファ用メモリ
ID3D11DepthStencilView*		g_pDepthStencilView[MAX_DEPTHVIEW];	// Zバッファ
ID3D11ShaderResourceView*	g_pDepthShaderResViews[MAX_DEPTHVIEW];	// Zバッファのシェーダーリソースビュー
UINT						g_uSyncInterval = 0;	// 垂直同期 (0:無, 1:有)
ID3D11RasterizerState*		g_pRs[MAX_CULLMODE];	// ラスタライザ ステート
ID3D11BlendState*			g_pBlendState[MAX_BLENDSTATE];// ブレンド ステート
ID3D11DepthStencilState*	g_pDSS[2];				// Z/ステンシル ステート

int							g_nCountFPS;			// FPSカウンタ

static SceneManager* g_pScneManager;


// メイン関数
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	WNDCLASSEX wcex = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0, 0, hInstance, nullptr,
	LoadCursor(nullptr, IDC_ARROW), (HBRUSH)(COLOR_WINDOW + 1), nullptr, CLASS_NAME, nullptr };

	MSG msg;

	// COM初期化
	if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) 
	{
		MessageBox(NULL, _T("COMの初期化に失敗しました。"), _T("error"), MB_OK);
		return -1;
	}

	// インスタンス ハンドル保存
	g_hInst = hInstance;

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウ サイズ算出
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX;
	DWORD dwExStyle = 0;
	RECT rc = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRectEx(&rc, dwStyle, FALSE, dwExStyle);

	// ウィンドウの作成
	g_hWnd = CreateWindowEx(dwExStyle, CLASS_NAME, WINDOW_NAME, dwStyle, CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top,	nullptr, nullptr, hInstance, nullptr);

	// フレームカウント初期化
	timeBeginPeriod(1);				// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();
	dwCurrentTime = dwFrameCount = 0;

	// ウインドウの表示
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	// DirectXの初期化
	if (FAILED(Init(g_hWnd, true))) { return -1;}

	// メッセージループ
	for (;;) 
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) 
		{
			if (msg.message == WM_QUIT) 
			{
				// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else 
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else 
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500) 
			{	
				// 0.5秒ごとに実行
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60)) 
			{
				dwExecLastTime = dwCurrentTime;

				// 更新処理
				Update();
			}

			// 描画処理
			Draw();
			dwFrameCount++;
		}
	}

	// タイマ設定を元に戻す
	timeEndPeriod(1);

	// 終了処理
	Uninit();

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, g_hInst);

	// COM終了処理
	CoUninitialize();

	return (int)msg.wParam;
}

// プロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:					
		// ウィンドウが生成された
		return OnCreate(hWnd, (LPCREATESTRUCT)lParam);
	case WM_DESTROY:				
		// ウィンドウ破棄指示がきた
		PostQuitMessage(0);				// システムにスレッドの終了
		break;
	case WM_KEYDOWN:				
		// キーボードが押された
		switch (wParam) 
		{
		case VK_ESCAPE:
			// [x]が押されたように振舞う
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			return 0;
		}
		break;
	case WM_MENUCHAR:
		return MNC_CLOSE << 16;			// [Alt]+[Enter]時のBEEPを抑止
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// メッセージハンドラ
int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs)
{
	// クライアント領域サイズを再設定
	RECT rcClnt;
	GetClientRect(hWnd, &rcClnt);
	rcClnt.right -= rcClnt.left;
	rcClnt.bottom -= rcClnt.top;
	if (rcClnt.right != SCREEN_WIDTH || rcClnt.bottom != SCREEN_HEIGHT) 
	{
		RECT rcWnd;
		GetWindowRect(hWnd, &rcWnd);
		SIZE sizeWnd;
		sizeWnd.cx = (rcWnd.right - rcWnd.left) - rcClnt.right + SCREEN_WIDTH;
		sizeWnd.cy = (rcWnd.bottom - rcWnd.top) - rcClnt.bottom + SCREEN_HEIGHT;
		SetWindowPos(hWnd, nullptr, 0, 0, sizeWnd.cx, sizeWnd.cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
	}

	// IME無効化
	ImmAssociateContext(hWnd, nullptr);

	return 0;
}

// バックバッファ生成
HRESULT CreateBackBuffer(void)
{
	// レンダーターゲットテクスチャ作成
	D3D11_TEXTURE2D_DESC rtDesc;
	ZeroMemory(&rtDesc, sizeof(rtDesc));
	rtDesc.Width = SCREEN_WIDTH;
	rtDesc.Height = SCREEN_HEIGHT;
	rtDesc.MipLevels = 1;
	rtDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtDesc.SampleDesc.Count = 1;
	rtDesc.Usage = D3D11_USAGE_DEFAULT;
	rtDesc.ArraySize = 1;
	rtDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	rtDesc.CPUAccessFlags = 0;
	for (int i = 1; i < MAX_RENDER; ++i)
	{
		g_pDevice->CreateTexture2D(&rtDesc, 0, &g_pRenderTextures[i]);
		g_pDevice->CreateRenderTargetView(g_pRenderTextures[i], nullptr, &g_pRenderTargetViews[i]);
		g_pDevice->CreateShaderResourceView(g_pRenderTextures[i], 0, &g_pRenderShaderResViews[i]);
	}

	// バックバッファを作成
	ID3D11Texture2D* pBackBuffer = nullptr;
	g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	g_pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_pRenderTargetViews[0]);
	SAFE_RELEASE(pBackBuffer);

	// Zバッファ用テクスチャ生成
	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(td));
	td.Width = SCREEN_WIDTH;
	td.Height = SCREEN_HEIGHT;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format =  DXGI_FORMAT_R32_TYPELESS;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;

	D3D11_SHADER_RESOURCE_VIEW_DESC srvd = {};
	srvd.Format = DXGI_FORMAT_R32_FLOAT;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;

	// Zバッファターゲットビュー生成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = DXGI_FORMAT_D32_FLOAT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;

	for (int i = 0; i < MAX_DEPTHVIEW; ++i)
	{
		HRESULT hr = g_pDevice->CreateTexture2D(&td, nullptr, &g_pDepthStencilTexture[i]);
		if (FAILED(hr)) { return hr; }
		hr = g_pDevice->CreateShaderResourceView(g_pDepthStencilTexture[i], &srvd, &g_pDepthShaderResViews[i]);
		if (FAILED(hr)) { return hr; }
		hr = g_pDevice->CreateDepthStencilView(g_pDepthStencilTexture[i], &dsvd, &g_pDepthStencilView[i]);
		if (FAILED(hr)) { return hr; }
	}

	// 各ターゲットビューをレンダーターゲットに設定
	g_pDeviceContext->OMSetRenderTargets(1, &g_pRenderTargetViews[0], g_pDepthStencilView[0]);

	// ビューポート設定
	D3D11_VIEWPORT vp;
	vp.Width = (float)SCREEN_WIDTH;
	vp.Height = (float)SCREEN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pDeviceContext->RSSetViewports(1, &vp);

	return S_OK;
}

// 初期化処理
HRESULT Init(HWND hWnd, BOOL bWindow)
{
	HRESULT hr = S_OK;

	// デバイス、スワップチェーンの作成
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;
	scd.BufferDesc.Width = SCREEN_WIDTH;
	scd.BufferDesc.Height = SCREEN_HEIGHT;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = bWindow;

	D3D_FEATURE_LEVEL featureLevels[] = 
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
		nullptr, 0, featureLevels, _countof(featureLevels), D3D11_SDK_VERSION, &scd,
		&g_pSwapChain, &g_pDevice, nullptr, &g_pDeviceContext);
	if (FAILED(hr)) { return hr; }

	// バックバッファ生成
	hr = CreateBackBuffer();
	if (FAILED(hr)) { return hr; }

	// ラスタライズ設定
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;	// カリング無し(両面描画)
	g_pDevice->CreateRasterizerState(&rd, &g_pRs[0]);
	rd.CullMode = D3D11_CULL_FRONT;	// 前面カリング(裏面描画)
	g_pDevice->CreateRasterizerState(&rd, &g_pRs[1]);
	rd.CullMode = D3D11_CULL_BACK;	// 背面カリング(表面描画)
	g_pDevice->CreateRasterizerState(&rd, &g_pRs[2]);
	g_pDeviceContext->RSSetState(g_pRs[2]);

	// ブレンド ステート生成
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = FALSE;
	BlendDesc.RenderTarget[0].BlendEnable = FALSE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	g_pDevice->CreateBlendState(&BlendDesc, &g_pBlendState[0]);
	// ブレンド ステート生成 (アルファ ブレンド用)
	//BlendDesc.AlphaToCoverageEnable = TRUE;
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	g_pDevice->CreateBlendState(&BlendDesc, &g_pBlendState[1]);
	// ブレンド ステート生成 (加算合成用)
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	g_pDevice->CreateBlendState(&BlendDesc, &g_pBlendState[2]);
	// ブレンド ステート生成 (減算合成用)
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	g_pDevice->CreateBlendState(&BlendDesc, &g_pBlendState[3]);
	SetBlendState(BS_ALPHABLEND);
	// 深度ステンシルステート生成
	CD3D11_DEFAULT def;
	CD3D11_DEPTH_STENCIL_DESC dsd(def);
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	g_pDevice->CreateDepthStencilState(&dsd, &g_pDSS[0]);
	CD3D11_DEPTH_STENCIL_DESC dsd2(def);
	dsd2.DepthEnable = FALSE;
	g_pDevice->CreateDepthStencilState(&dsd2, &g_pDSS[1]);

	// 以下各クラスの初期化処理を書く
	InitShaderList();

	// ポリゴン表示初期化
	hr = Polygon::Init(g_pDevice);
	if (FAILED(hr))
		return hr;

	// 入力処理初期化
	hr = InitInput();

	// モデル読み込み
	hr = CModel::LoadModel();
	if (FAILED(hr))
		return hr;

	hr = CMesh::InitShader();
	if (FAILED(hr))
		return hr;

#ifdef _DEBUG
	Debug_Collision::Create();
#endif // _DEBUG

	// シーンマネージャー初期化
	SceneManager::Create();
	g_pScneManager = SceneManager::GetInstance();

	return hr;
}

// バックバッファ解放
void ReleaseBackBuffer()
{
	if (g_pDeviceContext) {	g_pDeviceContext->OMSetRenderTargets(0, nullptr, nullptr); }
	for (int i = 0; i < MAX_DEPTHVIEW; ++i)
	{
		SAFE_RELEASE(g_pDepthStencilView[i]);
		SAFE_RELEASE(g_pDepthShaderResViews[i]);
		SAFE_RELEASE(g_pDepthStencilTexture[i]);
	}
	for (int i = 0; i < MAX_RENDER; ++i)
	{
		SAFE_RELEASE(g_pRenderTargetViews[i]);
		SAFE_RELEASE(g_pRenderShaderResViews[i]);
		SAFE_RELEASE(g_pRenderTextures[i]);
	}
}

// 終了処理
void Uninit(void)
{
	// 以下各クラスの初期化処理を書く
	SceneManager::Destroy();

#ifdef _DEBUG
	Debug_Collision::Destory();
#endif // _DEBUG

	CMesh::FinShader();

	CModel::ReleseModel();

	UninitInput();

	Polygon::Fin();

	UninitShaderList();

	// 深度ステンシルステート解放
	for (int i = 0; i < _countof(g_pDSS); ++i) {
		SAFE_RELEASE(g_pDSS[i]);
	}

	// ブレンド ステート解放
	for (int i = 0; i < MAX_BLENDSTATE; ++i) {
		SAFE_RELEASE(g_pBlendState[i]);
	}

	// ラスタライザ ステート解放
	for (int i = 0; i < MAX_CULLMODE; ++i) {
		SAFE_RELEASE(g_pRs[i]);
	}

	// バックバッファ解放
	ReleaseBackBuffer();

	// スワップチェーン解放
	SAFE_RELEASE(g_pSwapChain);

	// デバイス コンテキストの開放
	SAFE_RELEASE(g_pDeviceContext);

	// デバイスの開放
	SAFE_RELEASE(g_pDevice);
}

// 更新処理
void Update(void)
{
	// 各クラスの更新処理を書く
	UpdateInput();
	CCamera::Get()->Update();
	CCamera::Get()->UpdateMatrix();

	g_pScneManager->Update();
#ifdef _DEBUG
	if (IsKeyRelease('B'))
		Debug_Collision::GetInstance()->GetShow() ? Debug_Collision::GetInstance()->SetShow(false) : Debug_Collision::GetInstance()->SetShow(true);
#endif // _DEBUG

}

// 描画処理
void Draw(void)
{
	// 各クラスの描画処理を書く
	CCamera::Get()->Clear();

	g_pScneManager->Draw();

	static ERenderTarget target = RT_GAME_AND_UI;
#ifdef _DEBUG
	if (IsKeyPress(VK_LCONTROL))
	{
		if (IsKeyPress('0'))
			target = RT_BACK;
		if (IsKeyPress('1'))
			target = RT_GAME_AND_UI;
		if (IsKeyPress('2'))
			target = RT_UI;
		if (IsKeyPress('3'))
			target = RT_GAME;
		if (IsKeyPress('4'))
			target = RT_NORMAL;
		if (IsKeyPress('5'))
			target = RT_Z;
		if (IsKeyPress('0'))
			target = RT_DEBUG;
	}
#endif // _DEBUG


	ScereenObjectBase screen;
	// Zバッファを描画
	SetRenderTarget(RT_Z);
	screen.SetTexture(GetDepthTexture(DSV_3D));
	screen.SetPS(PS_Z);
	screen.Draw();

	// UIとゲーム自体をレンダーターゲットに描画
	SetRenderTarget(RT_GAME_AND_UI);
	screen.SetTexture(GetRenderTexture(RT_GAME));
	screen.SetPS(PS_2D);
	screen.Draw();
	SetBlendState(BS_ALPHABLEND);
	screen.SetTexture(GetRenderTexture(RT_UI));
	screen.Draw();
	SetBlendState(BS_NONE);

	SetRenderTarget(RT_BACK);
	screen.SetTexture(GetRenderTexture(target));
	screen.Draw();
	// バックバッファとフロントバッファの入れ替え
	g_pSwapChain->Present(g_uSyncInterval, 0);
}

// メインウィンドウハンドル取得
HWND GetMainWnd()
{
	return g_hWnd;
}

// インスタンスハンドル取得
HINSTANCE GetInstance()
{
	return g_hInst;
}

// デバイス取得
ID3D11Device* GetDevice()
{
	return g_pDevice;
}

// デバイスコンテキスト取得
ID3D11DeviceContext* GetDeviceContext()
{
	return g_pDeviceContext;
}

ID3D11RenderTargetView * GetRenderTargetView(int nTargetNum)
{
	return g_pRenderTargetViews[nTargetNum];
}

ID3D11ShaderResourceView * GetRenderTexture(int nTargetNum)
{
	return g_pRenderShaderResViews[nTargetNum];
}

ID3D11DepthStencilView * GetDepthStencilView(int num)
{
	return g_pDepthStencilView[num];
}

ID3D11ShaderResourceView * GetDepthTexture(int num)
{
	return g_pDepthShaderResViews[num];
}

// Zバッファ有効無効制御
void SetZBuffer(bool bEnable)
{
	g_pDeviceContext->OMSetDepthStencilState((bEnable) ? nullptr : g_pDSS[1], 0);
}

// Zバッファ更新有効無効制御
void SetZWrite(bool bEnable)
{
	g_pDeviceContext->OMSetDepthStencilState((bEnable) ? nullptr : g_pDSS[0], 0);
}

// ブレンドステート設定
void SetBlendState(int nBlendState)
{
	if (nBlendState >= 0 && nBlendState < MAX_BLENDSTATE) {
		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		g_pDeviceContext->OMSetBlendState(g_pBlendState[nBlendState], blendFactor, 0xffffffff);
	}
}

// カリング設定
void SetCullMode(int nCullMode)
{
	if (nCullMode >= 0 && nCullMode < MAX_CULLMODE) {
		g_pDeviceContext->RSSetState(g_pRs[nCullMode]);
	}
}

void SetRenderTarget(int nTargetNum)
{
	g_pDeviceContext->OMSetRenderTargets(1, &g_pRenderTargetViews[nTargetNum], g_pDepthStencilView[0]);
}

void AllRenderTarget()
{
	g_pDeviceContext->OMSetRenderTargets(MAX_RENDER, g_pRenderTargetViews, g_pDepthStencilView[0]);
}

void ClearAllTarget(const FLOAT * color)
{
	for (int i = 0; i < MAX_RENDER; ++i)
	{
		g_pDeviceContext->ClearRenderTargetView(g_pRenderTargetViews[i], color);
	}
}

void ClearAllDepth()
{
	for (int i = 0; i < MAX_DEPTHVIEW; ++i)
	{
		g_pDeviceContext->ClearDepthStencilView(g_pDepthStencilView[i], D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

}
