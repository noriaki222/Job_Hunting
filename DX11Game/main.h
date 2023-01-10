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

#define MAX_RENDER		(8)					// �ő僌���_�[�^�[�Q�b�g�r���[�̐�

#define SinDeg(degree)	sinf(XMConvertToRadians(degree))
#define CosDeg(degree)	cosf(XMConvertToRadians(degree))

#define GRAVITY	(0.8f)

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

enum ERenderTarget {
	RT_BUCK = 0,							// �o�b�N�o�b�t�@
	RT_GAME_AND_UI,							// �Q�[��+UI
	RT_UI,									// UI�̂�
	RT_GAME,								// �Q�[���̂�
	RT_DEBUG,								// �f�o�b�N
};

enum EBillbordType
{
	BILLBOARD_NONE,
	BILLBOARD_ALL,
	BILLBOARD_NOT_Y,
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

struct Transform
{
	DirectX::XMFLOAT3 pos;		// ���W
	DirectX::XMFLOAT3 rot;		// ��] degrees�p
	DirectX::XMFLOAT3 scale;	// �X�P�[��
	
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
	DirectX::XMFLOAT3 spd;	// ���x
	DirectX::XMFLOAT3 acc;	// �����x
	bool isGravity = false;	// �d�̓t���O

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
	DirectX::XMFLOAT3 center;	// �����蔻��̒��S
	DirectX::XMFLOAT3 size;	// �����蔻��̑傫��(���[�J�����W��
	bool isCollision;	// �����蔻�肪�L����

	static Collider Zero()
	{
		Collider work;
		work.center = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		work.size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
		work.isCollision = false;
		return work;
	}
};

// �v���g�^�C�v�錾
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