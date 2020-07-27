#include "framework.h"
#include "ScrollManager.h"

CScrollManager* CScrollManager::m_pInstance = nullptr;
CScrollManager* CScrollManager::GetInstance() {
	if (nullptr == m_pInstance)
		m_pInstance = new CScrollManager();

	return m_pInstance;
}

void CScrollManager::DestroyInstance() {
	if (m_pInstance) {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
CScrollManager::CScrollManager() {
	scrollX = 0;
	scrollY = 0;
}

CScrollManager::~CScrollManager() {

}
