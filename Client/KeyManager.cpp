#include "framework.h"
#include "KeyManager.h"

CKeyManager* CKeyManager::m_pInstance = nullptr;

CKeyManager::CKeyManager() {

}


CKeyManager::~CKeyManager() {
	DestroyInstance();
}