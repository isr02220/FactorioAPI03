#include "MainScene.h"
#include "KeyManager.h"
void CMainScene::ReadyScene()
{
	SetActive(true);
}

void CMainScene::UpdateScene()
{
}

void CMainScene::LateUpdateScene()
{
}

void CMainScene::RenderScene(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	TCHAR szBuffer[32];
	RECT rc = { (WINCX >> 1) - 50, (WINCY >> 1) - 50, (WINCX >> 1) + 50, (WINCY >> 1) + 50 };
	wsprintf(szBuffer, L"Factorio");
	DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_CENTER | DT_NOCLIP);

	rc.top += 30;
	rc.bottom += 30;
	wsprintf(szBuffer, L"ENTER 를 눌러 시작하시오");
	DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_CENTER | DT_NOCLIP);
}

void CMainScene::ReleaseScene()
{
	SetActive(false);
}
