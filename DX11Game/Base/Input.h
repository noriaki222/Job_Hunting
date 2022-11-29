// ƒL[“ü—Í
#pragma once
#include <Windows.h>

HRESULT InitInput();
void UninitInput();
void UpdateInput();

bool IsKeyPress(BYTE key);
bool IsKeyTrigger(BYTE key);
bool IsKeyRelease(BYTE key);