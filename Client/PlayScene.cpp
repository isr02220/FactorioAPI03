#include "framework.h"
#include "Player.h"
#include "Entity.h"
#include "TransportBelt.h"
#include "ResourceOre.h"
#include "CoalOre.h"
#include "Mouse.h"
#include "CollisionManager.h"
#include "ObjManager.h"
#include "AbstractFactory.h"
#include "PlayScene.h"
#include "Tile.h"
#include "TileManager.h"

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
		m_dwOldTime = GetTickCount();
		CTileManager::GetInstance()->Ready();
		ObjManager->AddObject(CAbstractFactory<CMouse>::Create(), OBJ::MOUSE);

		ObjManager->AddObject(CAbstractFactory<CPlayer>::Create(), OBJ::PLAYER);
		ObjManager->GetPlayer()->SetName(L"사막여우");
		POSITION playerPos = ToGridPos(ObjManager->GetPlayer()->GetPosition(), GRIDCX);
		
		for (size_t i = 0; i < 8; i++) 
			for (size_t j = 0; j < 8; j++)
				ObjManager->AddObject(CAbstractFactory<CCoalOre>::Create(playerPos.x + GRIDCX * j, playerPos.y + GRIDCX * i), OBJ::RESOURCEORE);


		SetActive(true);
	}
}

void CPlayScene::UpdateScene() {
	DeadLineTop    = FLOAT(DeadLineMargin) - spanY;
	DeadLineLeft   = FLOAT(DeadLineMargin) - spanX;
	DeadLineBottom = FLOAT(WINCY - DeadLineMargin) - spanY;
	DeadLineRight  = FLOAT(WINCX - DeadLineMargin) - spanX;

	if (++CTransportBelt::beltSpriteIndexX >= 16 * CTransportBelt::beltSpriteFrameDelay) CTransportBelt::beltSpriteIndexX = 0;

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
	SetBkMode(hMemDC, TRANSPARENT);
	////////////////
	CTileManager::GetInstance()->Render(hMemDC);
	ObjManager->RenderObjectManager(hMemDC);
	INT playerScore = dynamic_cast<CPlayer*>(ObjManager->GetPlayer())->GetScore();
	TCHAR szBuffer[32];
	wsprintf(szBuffer, L"Player Score : %d", playerScore);
	TextOut(hMemDC, (WINCX >> 1) - 50, 50, szBuffer, lstrlen(szBuffer));

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
