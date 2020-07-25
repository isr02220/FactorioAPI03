#pragma once
#include "TransportBelt.h"

class CBeltManager {
public:
	static CBeltManager* GetInstance() {
		if (nullptr == m_pInstance)
			m_pInstance = new CBeltManager;
		return m_pInstance;
	}
	static void DestroyInstance() {
		if (m_pInstance) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	CBeltManager();
	~CBeltManager();
public:
	void Ready();
	void Update();
	void Render(HDC hDC);
	void Release();
public:

private:
	static CBeltManager* m_pInstance;
	vector<CObj*> vecBelt;
};

