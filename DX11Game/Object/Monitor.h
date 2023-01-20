// レンダーターゲットを描画するクラス
#pragma once
#include "../main.h"

class Monitor
{
public:
	Monitor();
	~Monitor();

	void Update();
	void Draw();

private:
	ERenderTarget m_target;
};