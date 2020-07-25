#pragma once
class CFontManager {
public:
	static CFontManager* GetInstance();
	void DestroyInstance();
private:
	CFontManager();
	~CFontManager();
public:
	LOGFONT* FindFont(const TCHAR* pFontKey);
	void InsertFont(LOGFONT* _font, const TCHAR* pFontKey);
	void Release();
private:
	static CFontManager* m_pInstance;
	map<const TCHAR*,LOGFONT*> mapFont;
};

