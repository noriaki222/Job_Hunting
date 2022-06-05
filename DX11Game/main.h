// ���C������
#pragma once

// �C���N���[�h
#define NOMINMAX
#include <windows.h>
#include <tchar.h>
#include <math.h>
#include <mmsystem.h>
#include <DirectXMath.h>
#include <d3d11.h>

// �}�N����`
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) {if(x){(x)->Release();x=nullptr;}}
#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(x) {if(x){delete(x);x=nullptr;}}
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) {if(x){delete[](x);x=nullptr;}}
#endif

#define SCREEN_WIDTH	(1280)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)				// �E�C���h�E�̍���
#define SCREEN_CENTER_X	(SCREEN_WIDTH/2)	// �E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT/2)	// �E�C���h�E�̒��S�x���W

#define	NUM_VERTEX		(4)					// ���_��
#define	NUM_POLYGON		(2)					// �|���S����

#define SinDeg(degree)	sinf(XMConvertToRadians(degree))
#define CosDeg(degree)	cosf(XMConvertToRadians(degree))

enum EBlendState {
	BS_NONE = 0,							// ��������������
	BS_ALPHABLEND,							// ����������
	BS_ADDITIVE,							// ���Z����
	BS_SUBTRACTION,							// ���Z����

	MAX_BLENDSTATE
};

enum ECullMode {
	CULLMODE_NONE = 0,						// �J�����O���Ȃ�
	CULLMODE_CW,							// �O�ʃJ�����O
	CULLMODE_CCW,							// �w�ʃJ�����O

	MAX_CULLMODE
};

// �\���̒�`
typedef struct
{
	DirectX::XMFLOAT3 vtx;		// ���_���W
	DirectX::XMFLOAT4 diffuse;	// �g�U���ˌ�
	DirectX::XMFLOAT2 tex;		// �e�N�X�`�����W
} VERTEX_2D;

typedef struct
{
	DirectX::XMFLOAT3 vtx;		// ���_���W
	DirectX::XMFLOAT3 nor;		// �@���x�N�g��
	DirectX::XMFLOAT4 diffuse;	// �g�U���ˌ�
	DirectX::XMFLOAT2 tex;		// �e�N�X�`�����W
} VERTEX_3D;

// �v���g�^�C�v�錾
HWND GetMainWnd();
HINSTANCE GetInstance();
ID3D11Device* GetDevice();
ID3D11DeviceContext* GetDeviceContext();
ID3D11RenderTargetView* GetRenderTargetView();
void SetZBuffer(bool bEnable);
void SetZWrite(bool bEnable);
void SetBlendState(int nBlendState);
void SetCullMode(int nCullMode);