#include "framework.h"
#include "UIManager.h"
#include "Obj.h"
CUIManager* CUIManager::m_pInstance = nullptr;
CObjManager* CUIManager::objMgr = nullptr;
CUIManager::CUIManager() {
}


CUIManager::~CUIManager() {
	Release();
}

void CUIManager::Ready() {

}

void CUIManager::Update() {

}

void CUIManager::Render(HDC hDC) {

}

void CUIManager::Release() {
}
