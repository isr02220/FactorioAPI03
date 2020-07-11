#include "framework.h"
#include "Player.h"
#include "Mouse.h"
#include "CollisionManager.h"
#include "ObjManager.h"
#include "AbstractFactory.h"
#include "PlayScene.h"

extern FLOAT spanX = 0.f;
extern FLOAT spanY = 0.f;
extern FLOAT DeadLineTop    = 0;
extern FLOAT DeadLineLeft   = 0;
extern FLOAT DeadLineBottom = 0;
extern FLOAT DeadLineRight  = 0;
CPlayScene::CPlayScene() {
}


CPlayScene::~CPlayScene() {
	ReleaseScene();
}

void CPlayScene::ReadyScene() {
	if (!GetActive()) {
		m_dwOldTime = GetTickCount();
		ObjManager->AddObject(CAbstractFactory<CPlayer>::Create(), OBJ::PLAYER);
		ObjManager->GetPlayer()->SetName(L"사막여우");
		m_bg = new CBackground;
		m_bg->Ready_Object();
		SetActive(true);
	}
}

void CPlayScene::UpdateScene() {
	DeadLineTop    = FLOAT(DeadLineMargin) - spanY;
	DeadLineLeft   = FLOAT(DeadLineMargin) - spanX;
	DeadLineBottom = FLOAT(WINCY - DeadLineMargin) - spanY;
	DeadLineRight  = FLOAT(WINCX - DeadLineMargin) - spanX;

	if (GetAsyncKeyState('R') & 0x8000) {
		DebugRectDraw = true;
	}
	if (GetAsyncKeyState('T') & 0x8000) {
		DebugRectDraw = false;
	}

	if (GetAsyncKeyState('1') & 0x8000) {
		spanX -= 4.f;
	}
	if (GetAsyncKeyState('2') & 0x8000) {
		spanX += 4.f;
	}
	if (GetAsyncKeyState('3') & 0x8000) {
		spanY -= 4.f;
	}
	if (GetAsyncKeyState('4') & 0x8000) {
		spanY += 4.f;
	}
	itemManager.CreateItem();
	m_bg->Update_Object();
	ObjManager->UpdateObjectManager();
}

void CPlayScene::LateUpdateScene() {

	ObjManager->LateUpdateObjectManager();

	if (ObjManager->GetList(OBJ::ITEM)->size() == 0) {


	}
}

void CPlayScene::RenderScene(HDC hDC) {
	/////////////////
	//HDC hMemDC = m_hDC;
	HDC hMemDC;
	HBITMAP hBitmap, oldBitmap;
	hMemDC = CreateCompatibleDC(hDC);
	hBitmap = CreateCompatibleBitmap(hDC, WINCX, WINCY);
	oldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	////////////////

	Rectangle(hMemDC, 0, 0, WINCX, WINCY);
	Rectangle(hMemDC, DeadLineMargin, DeadLineMargin, WINCX - DeadLineMargin, WINCY - DeadLineMargin);
	m_bg->Render_Object(hMemDC);
	for (size_t i = 0; i < OBJ::END; i++) {
		for (auto pObj : *ObjManager->GetList((OBJ::TYPE)i)) {
			//pObj->IncreasePos(spanX, -spanY);
			pObj->Render_Object(hMemDC);
			//pObj->IncreasePos(-spanX, spanY);
		}
	}
	size_t bulletCount = ObjManager->GetList(OBJ::BULLET)->size();
	INT playerScore = dynamic_cast<CPlayer*>(ObjManager->GetPlayer())->GetScore();
	INT HaveBullet = dynamic_cast<CPlayer*>(ObjManager->GetPlayer())->GetBullets();
	TCHAR szBuffer[32];
	wsprintf(szBuffer, L"Player Score : %d", playerScore);
	TextOut(hMemDC, (WINCX >> 1) - 50, 50, szBuffer, lstrlen(szBuffer));

	/*wsprintf(szBuffer, L"목숨");
	for (INT i = 0; i < dynamic_cast<CPlayer*>(ObjManager->GetPlayer())->GetLife(); i++) {
		RECT rc = {};
		rc.left = 100 + i * 70;
		rc.right = 150 + i * 70;
		rc.top = 100;
		rc.bottom = 150;
		Rectangle(hMemDC, rc.left, rc.top, rc.right, rc.bottom);
		rc.top = 115;
		DrawText(hMemDC, szBuffer, lstrlen(szBuffer), &rc, DT_VCENTER | DT_CENTER | DT_NOCLIP);
	}*/

	// Player HP bar
	{
		COLORREF bColor = RGB(250, 250, 0);	// 브러쉬 색
		HBRUSH hBrush = CreateSolidBrush(bColor);
		HBRUSH  oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
		RECT rcMaxHp = { 10,100, 10 + dynamic_cast<CPlayer*>(ObjManager->GetPlayer())->GetMAXHP(),130 };
		Rectangle(hMemDC, rcMaxHp.left, rcMaxHp.top, rcMaxHp.right, rcMaxHp.bottom);
		SelectObject(hMemDC, oldBrush);
		DeleteObject(hBrush);
	}
	{
		COLORREF bColor = RGB(250, 0, 0);	// 브러쉬 색
		HBRUSH hBrush = CreateSolidBrush(bColor);
		HBRUSH  oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
		RECT rcHp = { 10,100, 10 + dynamic_cast<CPlayer*>(ObjManager->GetPlayer())->GetHP(),130 };
		Rectangle(hMemDC, rcHp.left, rcHp.top, rcHp.right, rcHp.bottom);
		SelectObject(hMemDC, oldBrush);
		DeleteObject(hBrush);
	}

	//
	//wsprintf(szBuffer, L"폭탄");
	//for (INT i = 0; i < dynamic_cast<CPlayer*>(ObjManager->GetPlayer())->GetBomb(); i++) {
	//	RECT rc = {};
	//	rc.left = (WINCX >> 1) + 100 + i * 70;
	//	rc.right = (WINCX >> 1) + 150 + i * 70;
	//	rc.top = 100;
	//	rc.bottom = 150;
	//	Rectangle(hMemDC, rc.left, rc.top, rc.right, rc.bottom);
	//	rc.top = 120;
	//	DrawText(hMemDC, szBuffer, lstrlen(szBuffer), &rc, DT_VCENTER | DT_CENTER | DT_NOCLIP);
	//}


	m_iFPS++;

	if (m_dwOldTime + 1000 < GetTickCount()) {
		wsprintf(m_szFPS, L"FPS : %d", m_iFPS);
		m_iFPS = 0;
		m_dwOldTime = GetTickCount();
	}
	TextOut(hMemDC, WINCX - 200, 50, m_szFPS, lstrlen(m_szFPS));

	/////////////////////
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	DeleteObject(SelectObject(hMemDC, oldBitmap));
	DeleteDC(hMemDC);
	/////////////////////
}

void CPlayScene::ReleaseScene() {
	ObjManager->ReleaseObjectManager();

}
