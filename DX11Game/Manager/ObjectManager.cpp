#include "ObjectManager.h"

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
			SetBlendState(BS_ALPHABLEND);
		if ((*it)->GetType() == TYPE_3D)
			SetBlendState(BS_NONE);
		(*it)->Draw();
		++it;
		SetBlendState(BS_NONE);
	}
}

OBJiterator ObjectManager::AddManager(ObjectBase * obj)
{
	OBJiterator retit = m_pObjlist.begin();
	while (retit != m_pObjlist.end())
	{
		if (m_pObjlist.size() > 0)
		{
			// ˆ—‡‚Ì•À‚Ñ‘Ö‚¦
			if ((*retit)->GetDrawOrder() > obj->GetDrawOrder())
			{
				// ƒŠƒXƒg‚Ì—v‘f‚ª1‚Â‚¾‚Á‚½ê‡æ“ª‚É“ü‚ê‚é
				if (m_pObjlist.size() == 1)
				{
					m_pObjlist.push_front(obj);
					return m_pObjlist.begin();
				}
				--retit;
				m_pObjlist.insert(retit, obj);
				++retit;
				return retit;
			}
		}
		++retit;
	}

	m_pObjlist.push_back(obj);
	retit = m_pObjlist.end();
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
