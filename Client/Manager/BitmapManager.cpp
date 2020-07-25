#include "framework.h"
#include "BitmapManager.h"
#include "MyBitmap.h"
CBitmapManager* CBitmapManager::m_pInstance = nullptr;
CBitmapManager* CBitmapManager::GetInstance() {
	if (nullptr == m_pInstance)
		m_pInstance = new CBitmapManager();

	return m_pInstance;
}

void CBitmapManager::DestroyInstance() {
	if (m_pInstance) {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
CBitmapManager::CBitmapManager() {
}

CBitmapManager::~CBitmapManager() {

}

HDC CBitmapManager::FindImage(const TCHAR* imageKey) {
	auto iter_find = find_if(mapBmp.begin(), mapBmp.end(), [&](auto& rPair) {
		return !lstrcmp(imageKey, rPair.first);
		});
	if (iter_find == mapBmp.end())
		return nullptr;
	return iter_find->second->GetMemDC();
}

void CBitmapManager::InsertTexture(const TCHAR* _filePath, const TCHAR* imageKey) {
	auto iter_find = mapBmp.find(imageKey); 
	if (iter_find != mapBmp.end())
		return;
	CMyBitmap* pBitmap = new CMyBitmap;
	pBitmap->LoadBmp(_filePath);
	mapBmp.emplace(imageKey, pBitmap);
}

void CBitmapManager::ReleaseBmpMgr() {
	for (auto& pair : mapBmp) 
		Safe_Delete(pair.second);
	
	mapBmp.clear();
}