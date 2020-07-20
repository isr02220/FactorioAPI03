#include "framework.h"
#include "FontManager.h"
CFontManager* CFontManager::m_pInstance = nullptr;
CFontManager* CFontManager::GetInstance() {
	if (nullptr == m_pInstance)
		m_pInstance = new CFontManager();

	return m_pInstance;
}

void CFontManager::DestroyInstance() {
	if (m_pInstance) {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
CFontManager::CFontManager() {
}

CFontManager::~CFontManager() {

}

LOGFONT* CFontManager::FindFont(const TCHAR* pFontKey) {
	auto iter_find = mapFont.find(pFontKey);
	if (iter_find == mapFont.end())
		return nullptr;
	return iter_find->second;
}

void CFontManager::InsertFont(LOGFONT* _font, const TCHAR* pFontKey) {
	auto iter_find = mapFont.find(pFontKey);
	if (iter_find != mapFont.end())
		return;
	mapFont.emplace(map<const TCHAR*,LOGFONT*>::value_type(pFontKey, _font));
}

void CFontManager::Release() {
	for (auto& pair : mapFont) 
		Safe_Delete(pair.second);
	mapFont.clear();
}