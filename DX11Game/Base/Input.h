// キー入力
#pragma once
#include <Windows.h>
#include "../main.h"

#define A	(0)
#define B	(1)
#define X	(2)
#define Y	(3)
#define LB	(4)
#define RB	(5)
#define VIEW	(6)	// 戻るボタン
#define MENUE	(7)	// スタートボタン

// コントローラーのスティック
enum JOYSTIC
{
	LEFT,
	RIGHT,
};

HRESULT InitInput();
void UninitInput();
void UpdateInput();

bool IsKeyPress(BYTE key);
bool IsKeyTrigger(BYTE key);
bool IsKeyRelease(BYTE key);

JOYINFOEX *GetJoyState(DWORD joy);
bool IsButtonPress(DWORD dwBtn);
bool IsButtonTrigger(DWORD dwBtn);
bool IsButtonRelease(DWORD dwBtn);

DirectX::XMFLOAT2 GetStick(JOYSTIC stick);
float StickNormalize(float input);