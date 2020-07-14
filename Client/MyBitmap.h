#pragma once
#include "framework.h"
class CMyBitmap {
public:
	CMyBitmap();
	~CMyBitmap();
public:
	HDC GetMemDC() { return hMemDC; }
	void LoadBmp(const TCHAR* pFilePath);
	void Release();
private:
	HDC hMemDC;
	HBITMAP OldBitmap;
	HBITMAP hBitmap;
};

