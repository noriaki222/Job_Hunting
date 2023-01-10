#include "ObjectManager.h"
#include "../Base/Camera.h"
#include "../Core/ScereenObjectBase.h"

ObjectManager *ObjectManager::pInstance = nullptr;

ObjectManager * ObjectManager::GetInstance()
{
	return pInstance;
}

void ObjectManager::Create()
{
	if (!pInstance)
		pInstance = new ObjectManager;
}

void ObjectManager::Destory()
{
	delete pInstance;
	pInstance = nullptr;
}

void ObjectManager::Update()
{
	OBJiterator it;
	it = m_pObjlist.begin();
	while (it != m_pObjlist.end())
	{
		if (!(*it)->GetEnable())
		{
			++it;
			continue;
		}
		(*it)->UpdateMatrix();
		(*it)->Update();
		++it;
	}
}

void ObjectManager::Draw()
{
	// UIリスト
	std::list<ObjectBase*> ui_list;

	OBJiterator it;
	it = m_pObjlist.begin();
	while (it != m_pObjlist.end())
	{
		if (!(*it)->GetEnable() || !(*it)->GetVisible())
		{
			++it;
			continue;
		}
		if ((*it)->GetType() == TYPE_2D)
		{
			SetBlendState(BS_ALPHABLEND);
			SetRenderTarget(RT_GAME);
		}
		if ((*it)->GetType() == TYPE_3D)
		{
			if (CCamera::Get()->CollisionViewFrustum(&(*it)->GetPos(), 0.0f) == 0 && (*it)->GetTag() != TAG_SKY && (*it)->GetTag() != TAG_LAND)
			{
				++it;
				continue;
			}
			SetBlendState(BS_NONE);
			SetRenderTarget(RT_GAME);
		}
		if ((*it)->GetType() == TYPE_UI)
		{
			SetBlendState(BS_ALPHABLEND);
			SetRenderTarget(RT_UI);
			ui_list.push_back((*it));
		}
		(*it)->Draw();
		++it;
		SetBlendState(BS_NONE);
	}

	// UIとゲーム自体をレンダーターゲットに描画
	ScereenObjectBase screen;
	SetRenderTarget(RT_GAME_AND_UI);
	screen.SetTexture(GetRenderTexture(RT_GAME));
	screen.Draw();
	it = ui_list.begin();
	while (it != ui_list.end())
	{
		SetBlendState(BS_ALPHABLEND);
		(*it)->Draw();
		++it;
	}
}

OBJiterator ObjectManager::AddManager(ObjectBase * obj)
{
	m_pObjlist.push_back(obj);
	OBJiterator retit = m_pObjlist.end();
	--retit;
	return retit;
}

void ObjectManager::Release(OBJiterator it)
{
	m_pObjlist.erase(it);
}

ObjectBase * ObjectManager::FindObj(EObjTag tag, ObjectBase* base = nullptr)
{
	OBJiterator it = m_pObjlist.begin();
	if (base)
	{
		it = base->GetIt();
		++it;
	}
	while (it != m_pObjlist.end())
	{
		if ((*it)->GetTag() == tag)
		{
			return (*it);
		}
		++it;
	}
	return nullptr;
}

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}
