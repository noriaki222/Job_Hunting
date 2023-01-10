#pragma once
#include "../main.h"

enum EScene
{
	SCENE_TEST = -10,		// テストシーン
	SCENE_COLLISION = -1,	// 当たり判定
	SCENE_NONE = 0,		// 未設定
	SCENE_TITLE = 1,	// タイトルシーン

	MAX_SCENE	// シーン数
};