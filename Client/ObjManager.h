#pragma once
#include "framework.h"
class CObj;
class CObjManager {
public:
	static CObjManager* GetInstance() {
		if (nullptr == m_pInstance)
			m_pInstance = new CObjManager;

		return m_pInstance;
	}
	static void Destroy_Instance() {
		if (m_pInstance) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	CObjManager();
	~CObjManager();
public:
	CObj* GetPlayer() { return m_listObj[OBJ::PLAYER].front(); }
	list<CObj*>* GetList(OBJ::ID eID) { return &m_listObj[eID]; }
public:
	void AddObject(CObj* pObj, OBJ::ID eID);

public:
	void UpdateObjectManager();
	void LateUpdateObjectManager();
	void RenderObjectManager(HDC hDC);
	void ReleaseObjectManager();
private:
	static CObjManager* m_pInstance;
private:
	list<CObj*> m_listObj[OBJ::END];
};
