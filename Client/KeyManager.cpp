#include "framework.h"
#include "KeyManager.h"

CKeyManager* CKeyManager::m_pInstance = nullptr;

CKeyManager::CKeyManager() {
	ZeroMemory(&m_dwKeyUp, sizeof(DWORD));
	ZeroMemory(&m_dwKeyDown, sizeof(DWORD));
	m_dwKeyDown = ~m_dwKeyDown;
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::ATTACK, VK_LBUTTON));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::JUMP, VK_RBUTTON));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::LEFT, VK_LEFT));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::RIGHT, VK_RIGHT));
}


CKeyManager::~CKeyManager() {
	DestroyInstance();
}