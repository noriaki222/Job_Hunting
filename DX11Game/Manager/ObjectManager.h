// �I�u�W�F�N�g�Ǘ��N���X
#pragma once
#include "../Core/ObjectBase.h"

#include <list>

using OBJiterator = std::list<ObjectBase*>::iterator;

class ObjectManager
{
public:
	static ObjectManager* GetInstance();

	static void Create();
	static void Destory();

	void Update();
	void Draw();

	OBJiterator AddManager(ObjectBase* obj);
	void Release(OBJiterator it);
	void Clear() { m_pObjlist.clear(); }
	void Sort(){ m_pObjlist.sort(comp); }

	// tag:�T������I�u�W�F�N�g��Tag, base:�z���base�ȍ~�̃I�u�W�F�N�g��T��
	ObjectBase* FindObj(EObjTag tag, ObjectBase* base);

private:
	static ObjectManager *pInstance;
	ObjectManager();
	~ObjectManager();

	std::list<ObjectBase*> m_pObjlist;
};