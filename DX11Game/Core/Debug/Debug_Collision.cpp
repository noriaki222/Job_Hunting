#include "Debug_Collision.h"

Debug_Collision *Debug_Collision::pInstance = nullptr;

Debug_Collision * Debug_Collision::GetInstance()
{
	return pInstance;
}

Debug_Collision::Debug_Collision()
{
	isShow = false;
}

Debug_Collision::~Debug_Collision()
{
	ListClear();
}

void Debug_Collision::Create()
{
	if (!pInstance)
		pInstance = new Debug_Collision;
}

void Debug_Collision::Destory()
{
	delete pInstance;
	pInstance = nullptr;
}

void Debug_Collision::Draw()
{
	if (!isShow) return;
	Debug_ColIT it = denug_collision.begin();
	while (it != denug_collision.end())
	{
		(*it)->Draw();
		++it;
	}
}

void Debug_Collision::ListClear()
{
	Debug_ColIT it = denug_collision.begin();
	while (it != denug_collision.end())
	{
		SAFE_DELETE(*it);
		++it;
	}
	denug_collision.clear();
}

Debug_ColIT Debug_Collision::AddList(Collider * coll, DirectX::XMFLOAT4X4* world, Transform* tramsform)
{
	denug_collision.push_back(new Box);
	Debug_ColIT it = denug_collision.end();
	--it;
	HRESULT hr = (*it)->Init(coll, world, &tramsform->scale);
	if (FAILED(hr))
	{
		(*it)->Fin();
		SAFE_DELETE(*it);
		return denug_collision.end();
	}

	return it;
}
