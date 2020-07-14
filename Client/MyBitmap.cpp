#include "framework.h"
#include "MyBitmap.h"


CMyBitmap::CMyBitmap() {
}


CMyBitmap::~CMyBitmap() {
}

void CMyBitmap::LoadBmp(const TCHAR* pFilePath) {
	HDC hDC = GetDC(g_hWnd);
	hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(g_hWnd, hDC);
	hBitmap = (HBITMAP)LoadImage(nullptr, pFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	OldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
}

void CMyBitmap::Release() {
	SelectObject(hMemDC, OldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
}
