// シーン
#pragma once
#include "../main.h"
#include <vector>
#include "../Manager/ObjectManager.h"
#include "../Base/Camera.h"

class DeleterBase
{
public:
	virtual ~DeleterBase() {}
};
template<class T>
class Deleter : public DeleterBase
{
public:
	Deleter(T* ptr) : m_obj(ptr){}
	virtual ~Deleter() 
	{ 
		delete m_obj; 
		m_obj = nullptr;
	}

	T* m_obj;
};

class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase();

	virtual void Update();
	void ConstUpdate();
	// オブジェクトの描画直前
	virtual void LateUodate();
	virtual void Draw();

	template <class T>T* CreateObj();

private:
	ObjectManager* m_pObjMng;
	CCamera m_camera;
protected:
	std::vector<DeleterBase*> m_pDeleter;
};

template<class T>
inline T * SceneBase::CreateObj()
{
	T* pObj = new T;
	m_pDeleter.push_back(new Deleter<T>(pObj));
	pObj->Init();
	return pObj;
}
