#include "MainScene.h"
void CMainScene::ReadyScene()
{
	SetActive(true);
	CSoundMgr::Get_Instance()->PlayBGM(L"automation.wav");
}

void CMainScene::UpdateScene()
{
}

void CMainScene::LateUpdateScene()
{
}

void CMainScene::RenderScene(HDC hDC)
{
	BitBlt(hDC,
		0,
		0,
		WINCX,
		WINCY,
		CBitmapManager::GetInstance()->FindImage(L"Title"),
		0,
		0,
		SRCCOPY);
}

void CMainScene::ReleaseScene()
{
	SetActive(false);
}
