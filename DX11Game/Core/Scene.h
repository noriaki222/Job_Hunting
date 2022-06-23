//=============================================================================
//
// �V�[�� �N���X��` [Scene.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once
#include "../main.h"
#include "../Base/Camera.h"

// �萔��`
enum EScene {
	SCENE_NONE = 0,		// (�V�[����)
	SCENE_TITLE,		// �^�C�g�����
	SCENE_GAME,			// �Q�[�����

	MAX_SCENE
};

// �N���X��`
class CGameObj;
class CScene {
protected:
	EScene m_id;
	CGameObj* m_pObj;

private:
	static CScene* m_pScene;
	static CScene* m_pTop;
	CScene* m_pBack;
	CScene* m_pNext;

public:
	CScene();
	virtual ~CScene();

	virtual bool Init();
	virtual void Fin();
	virtual void Update() = 0;
	virtual void Draw() = 0;

	static bool InitAll();
	static void FinAll();
	static void UpdateAll();
	static void DrawAll();

	static void Change(EScene scene);

	CGameObj* GetObj() { return m_pObj; }
	void SetObj(CGameObj* pObj) { m_pObj = pObj; }
	CGameObj* Find(int id, CGameObj* pStart = nullptr);
};
