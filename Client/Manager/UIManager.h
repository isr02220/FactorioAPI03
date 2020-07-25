#pragma once
#include "framework.h"
class CObj;
class CUIManager {
public:
	static CUIManager* GetInstance() {
		if (nullptr == m_pInstance) {
			m_pInstance = new CUIManager;
			objMgr = CObjManager::GetInstance();
		}
		return m_pInstance;
	}
	static void DestroyInstance() {
		if (m_pInstance) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	CUIManager();
	~CUIManager();
public:
	void Ready();
	void Update();
	void Render(HDC hDC);
	void Release();
public:

private:
	static CUIManager* m_pInstance;
	static CObjManager* objMgr;
};

