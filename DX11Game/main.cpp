// ���C������

// �C���N���[�h
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

// ���C�u���������N
#pragma comment(lib, "winmm")
#pragma comment(lib, "imm32")
#pragma comment(lib, "d3d11")

// �}�N����`
#define CLASS_NAME	_T("AppClass")
#define WINDOW_NAME _T("Base_Program")

// �v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs);
HRESULT Init(HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

// �O���[�o���ϐ�
HWND						g_hWnd;					// ���C�� �E�B���h�E �n���h��
HINSTANCE					g_hInst;				// �C���X�^���X �n���h��

ID3D11Device*				g_pDevice;				// �f�o�C�X
ID3D11DeviceContext*		g_pDeviceContext;		// �f�o�C�X �R���e�L�X�g
IDXGISwapChain*				g_pSwapChain;			// �X���b�v�`�F�[��
ID3D11Texture2D*			g_pRenderTextures[MAX_RENDER];	// �����_�[�e�N�X�`��
ID3D11ShaderResourceView*	g_pRenderShaderResViews[MAX_RENDER];	// �����_�[�e�N�X�`���̃V�F�[�_�[���\�[�X�r���[
ID3D11RenderTargetView*		g_pRenderTargetViews[MAX_RENDER];	// �����_�[�^�[�Q�b�g(0:�o�b�N�o�b�t�@, 1:�Q�[��+UI, 2:UI, 3:�Q�[��
ID3D11Texture2D*			g_pDepthStencilTexture[MAX_DEPTHVIEW];	// Z�o�b�t�@�p������
ID3D11DepthStencilView*		g_pDepthStencilView[MAX_DEPTHVIEW];	// Z�o�b�t�@
ID3D11ShaderResourceView*	g_pDepthShaderResViews[MAX_DEPTHVIEW];	// Z�o�b�t�@�̃V�F�[�_�[���\�[�X�r���[
UINT						g_uSyncInterval = 0;	// �������� (0:��, 1:�L)
ID3D11RasterizerState*		g_pRs[MAX_CULLMODE];	// ���X�^���C�U �X�e�[�g
ID3D11BlendState*			g_pBlendState[MAX_BLENDSTATE];// �u�����h �X�e�[�g
ID3D11DepthStencilState*	g_pDSS[2];				// Z/�X�e���V�� �X�e�[�g

int							g_nCountFPS;			// FPS�J�E���^

static SceneManager* g_pScneManager;


// ���C���֐�
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

	// COM������
	if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) 
	{
		MessageBox(NULL, _T("COM�̏������Ɏ��s���܂����B"), _T("error"), MB_OK);
		return -1;
	}

	// �C���X�^���X �n���h���ۑ�
	g_hInst = hInstance;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E �T�C�Y�Z�o
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX;
	DWORD dwExStyle = 0;
	RECT rc = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRectEx(&rc, dwStyle, FALSE, dwExStyle);

	// �E�B���h�E�̍쐬
	g_hWnd = CreateWindowEx(dwExStyle, CLASS_NAME, WINDOW_NAME, dwStyle, CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top,	nullptr, nullptr, hInstance, nullptr);

	// �t���[���J�E���g������
	timeBeginPeriod(1);				// ����\��ݒ�
	dwExecLastTime = dwFPSLastTime = timeGetTime();
	dwCurrentTime = dwFrameCount = 0;

	// �E�C���h�E�̕\��
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	// DirectX�̏�����
	if (FAILED(Init(g_hWnd, true))) { return -1;}

	// ���b�Z�[�W���[�v
	for (;;) 
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) 
		{
			if (msg.message == WM_QUIT) 
			{
				// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else 
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else 
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500) 
			{	
				// 0.5�b���ƂɎ��s
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60)) 
			{
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				Update();
			}

			// �`�揈��
			Draw();
			dwFrameCount++;
		}
	}

	// �^�C�}�ݒ�����ɖ߂�
	timeEndPeriod(1);

	// �I������
	Uninit();

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, g_hInst);

	// COM�I������
	CoUninitialize();

	return (int)msg.wParam;
}

// �v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:					
		// �E�B���h�E���������ꂽ
		return OnCreate(hWnd, (LPCREATESTRUCT)lParam);
	case WM_DESTROY:				
		// �E�B���h�E�j���w��������
		PostQuitMessage(0);				// �V�X�e���ɃX���b�h�̏I��
		break;
	case WM_KEYDOWN:				
		// �L�[�{�[�h�������ꂽ
		switch (wParam) 
		{
		case VK_ESCAPE:
			// [x]�������ꂽ�悤�ɐU����
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			return 0;
		}
		break;
	case WM_MENUCHAR:
		return MNC_CLOSE << 16;			// [Alt]+[Enter]����BEEP��}�~
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// ���b�Z�[�W�n���h��
int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs)
{
	// �N���C�A���g�̈�T�C�Y���Đݒ�
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

	// IME������
	ImmAssociateContext(hWnd, nullptr);

	return 0;
}

// �o�b�N�o�b�t�@����
HRESULT CreateBackBuffer(void)
{
	// �����_�[�^�[�Q�b�g�e�N�X�`���쐬
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

	// �o�b�N�o�b�t�@���쐬
	ID3D11Texture2D* pBackBuffer = nullptr;
	g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	g_pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_pRenderTargetViews[0]);
	SAFE_RELEASE(pBackBuffer);

	// Z�o�b�t�@�p�e�N�X�`������
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

	// Z�o�b�t�@�^�[�Q�b�g�r���[����
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

	// �e�^�[�Q�b�g�r���[�������_�[�^�[�Q�b�g�ɐݒ�
	g_pDeviceContext->OMSetRenderTargets(1, &g_pRenderTargetViews[0], g_pDepthStencilView[0]);

	// �r���[�|�[�g�ݒ�
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

// ����������
HRESULT Init(HWND hWnd, BOOL bWindow)
{
	HRESULT hr = S_OK;

	// �f�o�C�X�A�X���b�v�`�F�[���̍쐬
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

	// �o�b�N�o�b�t�@����
	hr = CreateBackBuffer();
	if (FAILED(hr)) { return hr; }

	// ���X�^���C�Y�ݒ�
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;	// �J�����O����(���ʕ`��)
	g_pDevice->CreateRasterizerState(&rd, &g_pRs[0]);
	rd.CullMode = D3D11_CULL_FRONT;	// �O�ʃJ�����O(���ʕ`��)
	g_pDevice->CreateRasterizerState(&rd, &g_pRs[1]);
	rd.CullMode = D3D11_CULL_BACK;	// �w�ʃJ�����O(�\�ʕ`��)
	g_pDevice->CreateRasterizerState(&rd, &g_pRs[2]);
	g_pDeviceContext->RSSetState(g_pRs[2]);

	// �u�����h �X�e�[�g����
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
	// �u�����h �X�e�[�g���� (�A���t�@ �u�����h�p)
	//BlendDesc.AlphaToCoverageEnable = TRUE;
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	g_pDevice->CreateBlendState(&BlendDesc, &g_pBlendState[1]);
	// �u�����h �X�e�[�g���� (���Z�����p)
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	g_pDevice->CreateBlendState(&BlendDesc, &g_pBlendState[2]);
	// �u�����h �X�e�[�g���� (���Z�����p)
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	g_pDevice->CreateBlendState(&BlendDesc, &g_pBlendState[3]);
	SetBlendState(BS_ALPHABLEND);
	// �[�x�X�e���V���X�e�[�g����
	CD3D11_DEFAULT def;
	CD3D11_DEPTH_STENCIL_DESC dsd(def);
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	g_pDevice->CreateDepthStencilState(&dsd, &g_pDSS[0]);
	CD3D11_DEPTH_STENCIL_DESC dsd2(def);
	dsd2.DepthEnable = FALSE;
	g_pDevice->CreateDepthStencilState(&dsd2, &g_pDSS[1]);

	// �ȉ��e�N���X�̏���������������
	InitShaderList();

	// �|���S���\��������
	hr = Polygon::Init(g_pDevice);
	if (FAILED(hr))
		return hr;

	// ���͏���������
	hr = InitInput();

	// ���f���ǂݍ���
	hr = CModel::LoadModel();
	if (FAILED(hr))
		return hr;

	hr = CMesh::InitShader();
	if (FAILED(hr))
		return hr;

#ifdef _DEBUG
	Debug_Collision::Create();
#endif // _DEBUG

	// �V�[���}�l�[�W���[������
	SceneManager::Create();
	g_pScneManager = SceneManager::GetInstance();

	return hr;
}

// �o�b�N�o�b�t�@���
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

// �I������
void Uninit(void)
{
	// �ȉ��e�N���X�̏���������������
	SceneManager::Destroy();

#ifdef _DEBUG
	Debug_Collision::Destory();
#endif // _DEBUG

	CMesh::FinShader();

	CModel::ReleseModel();

	UninitInput();

	Polygon::Fin();

	UninitShaderList();

	// �[�x�X�e���V���X�e�[�g���
	for (int i = 0; i < _countof(g_pDSS); ++i) {
		SAFE_RELEASE(g_pDSS[i]);
	}

	// �u�����h �X�e�[�g���
	for (int i = 0; i < MAX_BLENDSTATE; ++i) {
		SAFE_RELEASE(g_pBlendState[i]);
	}

	// ���X�^���C�U �X�e�[�g���
	for (int i = 0; i < MAX_CULLMODE; ++i) {
		SAFE_RELEASE(g_pRs[i]);
	}

	// �o�b�N�o�b�t�@���
	ReleaseBackBuffer();

	// �X���b�v�`�F�[�����
	SAFE_RELEASE(g_pSwapChain);

	// �f�o�C�X �R���e�L�X�g�̊J��
	SAFE_RELEASE(g_pDeviceContext);

	// �f�o�C�X�̊J��
	SAFE_RELEASE(g_pDevice);
}

// �X�V����
void Update(void)
{
	// �e�N���X�̍X�V����������
	UpdateInput();
	CCamera::Get()->Update();
	CCamera::Get()->UpdateMatrix();

	g_pScneManager->Update();
#ifdef _DEBUG
	if (IsKeyRelease('B'))
		Debug_Collision::GetInstance()->GetShow() ? Debug_Collision::GetInstance()->SetShow(false) : Debug_Collision::GetInstance()->SetShow(true);
#endif // _DEBUG

}

// �`�揈��
void Draw(void)
{
	// �e�N���X�̕`�揈��������
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
	// Z�o�b�t�@��`��
	SetRenderTarget(RT_Z);
	screen.SetTexture(GetDepthTexture(DSV_3D));
	screen.SetPS(PS_Z);
	screen.Draw();

	// UI�ƃQ�[�����̂������_�[�^�[�Q�b�g�ɕ`��
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
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pSwapChain->Present(g_uSyncInterval, 0);
}

// ���C���E�B���h�E�n���h���擾
HWND GetMainWnd()
{
	return g_hWnd;
}

// �C���X�^���X�n���h���擾
HINSTANCE GetInstance()
{
	return g_hInst;
}

// �f�o�C�X�擾
ID3D11Device* GetDevice()
{
	return g_pDevice;
}

// �f�o�C�X�R���e�L�X�g�擾
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

// Z�o�b�t�@�L����������
void SetZBuffer(bool bEnable)
{
	g_pDeviceContext->OMSetDepthStencilState((bEnable) ? nullptr : g_pDSS[1], 0);
}

// Z�o�b�t�@�X�V�L����������
void SetZWrite(bool bEnable)
{
	g_pDeviceContext->OMSetDepthStencilState((bEnable) ? nullptr : g_pDSS[0], 0);
}

// �u�����h�X�e�[�g�ݒ�
void SetBlendState(int nBlendState)
{
	if (nBlendState >= 0 && nBlendState < MAX_BLENDSTATE) {
		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		g_pDeviceContext->OMSetBlendState(g_pBlendState[nBlendState], blendFactor, 0xffffffff);
	}
}

// �J�����O�ݒ�
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
