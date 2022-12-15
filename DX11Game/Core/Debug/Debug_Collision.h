#pragma once
#include "../../main.h"
#include "Box.h"
#include <list>

using Debug_ColIT = std::list<Box*>::iterator;

class Debug_Collision
{
public:
	static Debug_Collision* GetInstance();

	Debug_Collision();
	~Debug_Collision();

	static void Create();
	static void Destory();
	void Draw();
	
	void ListClear();

	Debug_ColIT AddList(Collider* col, DirectX::XMFLOAT4X4* world, Transform* transform);

	bool GetShow() { return isShow; }
	void SetShow(bool flg) { isShow = flg; }
private:
	static Debug_Collision* pInstance;
	bool isShow;
	std::list<Box*> denug_collision;
};