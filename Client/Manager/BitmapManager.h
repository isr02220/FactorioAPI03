#pragma once
class CMyBitmap;
class CBitmapManager {
public:
	static CBitmapManager* GetInstance();
	void DestroyInstance();
private:
	CBitmapManager();
	~CBitmapManager();
public:
	HDC FindImage(const TCHAR* pImageKey);
	void InsertTexture(const TCHAR* _filePath, const TCHAR* imageKey);
	void ReleaseBmpMgr();
private:
	static CBitmapManager* m_pInstance;
	map<const TCHAR*, CMyBitmap*> mapBmp;
};

