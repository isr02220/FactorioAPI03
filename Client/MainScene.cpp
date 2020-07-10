#include "MainScene.h"
#include "KeyManager.h"
void CMainScene::ReadyScene()
{
	SetActive(true);
}

void CMainScene::UpdateScene()
{
	key1 = CKeyManager::GetInstance()->KeyDown(KEY::ATTACK);
	key2 = CKeyManager::GetInstance()->KeyUp(KEY::ATTACK);
	key3 = CKeyManager::GetInstance()->KeyOnDown(KEY::ATTACK);
	key4 = CKeyManager::GetInstance()->KeyOnUp(KEY::ATTACK);
	CKeyManager::GetInstance()->UpdateKeyManager();
}

void CMainScene::LateUpdateScene()
{
}

void CMainScene::RenderScene(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	TCHAR szBuffer[32];
	RECT rc = { (WINCX >> 1) - 50, (WINCY >> 1) - 50, (WINCX >> 1) + 50, (WINCY >> 1) + 50 };
	wsprintf(szBuffer, L"METAL SLUG");
	DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_CENTER | DT_NOCLIP);
	rc.top += 50;
	rc.bottom += 50;
	if (key1) {
		wsprintf(szBuffer, L"KeyDown(KEY::ATTACK)");
		DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_CENTER | DT_NOCLIP);
	}
	rc.top += 50;
	rc.bottom += 50;
	if(key2) {
		wsprintf(szBuffer, L"KeyUp(KEY::ATTACK)");
		DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_CENTER | DT_NOCLIP);
	}
	rc.top += 50;
	rc.bottom += 50;
	if(key3) {
		wsprintf(szBuffer, L"KeyOnDown(KEY::ATTACK)");
		DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_CENTER | DT_NOCLIP);
	}
	rc.top += 50;
	rc.bottom += 50;
	if(key4) {
		wsprintf(szBuffer, L"KeyOnUp(KEY::ATTACK)");
		DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_CENTER | DT_NOCLIP);
	}

	wsprintf(szBuffer, L"ENTER 를 눌러 시작하시오");
	DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_CENTER | DT_NOCLIP);
}

void CMainScene::ReleaseScene()
{
	SetActive(false);
}
