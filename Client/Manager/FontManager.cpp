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
	LOGFONT* tempFont = new LOGFONT();
	tempFont->lfHeight         = _font->lfHeight        ;
	tempFont->lfWidth          = _font->lfWidth         ;
	tempFont->lfEscapement     = _font->lfEscapement    ;
	tempFont->lfOrientation    = _font->lfOrientation   ;
	tempFont->lfWeight         = _font->lfWeight        ;
	tempFont->lfItalic         = _font->lfItalic        ;
	tempFont->lfUnderline      = _font->lfUnderline     ;
	tempFont->lfStrikeOut      = _font->lfStrikeOut     ;
	tempFont->lfCharSet        = _font->lfCharSet       ;
	tempFont->lfOutPrecision   = _font->lfOutPrecision  ;
	tempFont->lfClipPrecision  = _font->lfClipPrecision ;
	tempFont->lfQuality        = _font->lfQuality       ;
	tempFont->lfPitchAndFamily = _font->lfPitchAndFamily;
	lstrcpy(tempFont->lfFaceName, _font->lfFaceName);
	mapFont.emplace(map<const TCHAR*,LOGFONT*>::value_type(pFontKey, tempFont));
}

void CFontManager::Release() {
	for (auto& pair : mapFont) 
		Safe_Delete(pair.second);
	mapFont.clear();
}