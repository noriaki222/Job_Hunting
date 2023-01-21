// レンダーターゲットを描画するクラス
#pragma once
#include "../main.h"
#include <vector>

enum PostEffect
{
	PE_EDGE,

	MAX_PE
};

class Monitor
{
public:
	Monitor();
	~Monitor();

	void Update();
	void Draw();

private:
	ERenderTarget m_target;
	bool m_useEffect;	// ポストエフェクトを使用するか
	std::vector<PostEffect> m_postEffects;
};