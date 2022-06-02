// ���C������
// Author:Noriaki Osaki

// �C���N���[�h
#include "main.h"

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
ID3D11RenderTargetView*		g_pRenderTargetView;	// �t���[���o�b�t�@
ID3D11Texture2D*			g_pDepthStencilTexture;	// Z�o�b�t�@�p������
ID3D11DepthStencilView*		g_pDepthStencilView;	// Z�o�b�t�@
UINT						g_uSyncInterval = 0;	// �������� (0:��, 1:�L)
ID3D11RasterizerState*		g_pRs[MAX_CULLMODE];	// ���X�^���C�U �X�e�[�g
ID3D11BlendState*			g_pBlendState[MAX_BLENDSTATE];// �u�����h �X�e�[�g
ID3D11DepthStencilState*	g_pDSS[2];				// Z/�X�e���V�� �X�e�[�g

int							g_nCountFPS;			// FPS�J�E���^


// ���C���֐�
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	return 0;
}