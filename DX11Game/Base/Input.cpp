#include "Input.h"
#include <Xinput.h>

// グローバル変数
BYTE g_keyTable[256];
BYTE g_oldTable[256];

JOYINFOEX g_joyState;
JOYINFOEX g_joyOldState;

HRESULT InitInput()
{
	HRESULT hr;
	GetKeyboardState(g_keyTable);
	hr = joyGetPosEx(0, &g_joyState);
	return hr;
}

void UninitInput()
{
}

void UpdateInput()
{
	// 古い入力を更新
	memcpy_s(g_oldTable, sizeof(g_oldTable), g_keyTable, sizeof(g_keyTable));
	g_joyOldState = g_joyState;
	// 現在の入力を所存
	GetKeyboardState(g_keyTable);
	joyGetPosEx(0, &g_joyState);
}

bool IsKeyPress(BYTE key)
{
	return g_keyTable[key] & 0x80;
}

bool IsKeyTrigger(BYTE key)
{
	return (g_keyTable[key] ^ g_oldTable[key]) & g_keyTable[key] & 0x80;
}

bool IsKeyRelease(BYTE key)
{
	return (g_keyTable[key] ^ g_oldTable[key]) & g_oldTable[key] & 0x80;
}

JOYINFOEX * GetJoyState(DWORD joy)
{
	return &g_joyState;
}

bool IsButtonPress(DWORD dwBtn)
{
	return (g_joyState.dwButtons & (1 << dwBtn)) ? true : false;
}

bool IsButtonTrigger(DWORD dwBtn)
{
	bool old = (g_joyOldState.dwButtons & (1 << dwBtn)) ? true : false;
	bool now = (g_joyState.dwButtons & (1 << dwBtn)) ? true : false;
	return (now && !old) ? true : false;
}

bool IsButtonRelease(DWORD dwBtn)
{
	bool old = (g_joyOldState.dwButtons & (1 << dwBtn)) ? true : false;
	bool now = (g_joyState.dwButtons & (1 << dwBtn)) ? true : false;
	return (!now && old) ? true : false;
}

DirectX::XMFLOAT2 GetStick(JOYSTIC stick)
{
	DirectX::XMFLOAT2 val = DirectX::XMFLOAT2(0.0f, 0.0f);
	switch (stick)
	{
	case LEFT:
		val.x = (LONG)g_joyState.dwXpos - 0x08000;
		val.y = (LONG)g_joyState.dwYpos - 0x08000;
		break;
	case RIGHT:
		val.x = (LONG)g_joyState.dwUpos - 0x08000;
		val.y = (LONG)g_joyState.dwRpos - 0x08000;
		break;
	}

	val.x = StickNormalize(val.x);
	val.y = StickNormalize(val.y);
	return val;
}

float StickNormalize(float input)
{
	input /= 32768;
	input *= 100;
	input = (int)input / 100.0f;
	return input;
}
