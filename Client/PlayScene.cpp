#include "framework.h"
#include "Player.h"
#include "Worm.h"
#include "Entity.h"
#include "EntityHeaders.h"
#include "TransportBelt.h"
#include "ResourceOre.h"
#include "CoalOre.h"
#include "CopperOre.h"
#include "IronOre.h"
#include "Stone.h"

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
		ObjManager->GetPlayer()->SetName(L"플레이어");
		POSITION playerPos = ToGridPos(ObjManager->GetPlayer()->GetPosition(), GRIDCX);
		
		CObj* tempObj = CAbstractFactory<CWorm>::Create(playerPos + POSITION(3000, 0));
		ObjManager->AddObject(tempObj, OBJ::MONSTER);

		tempObj = CAbstractFactory<CCrashSite>::Create(playerPos + POSITION(3200, 0));
		ObjManager->AddObject(tempObj, OBJ::ENTITY);

		tempObj = CAbstractFactory<CTeacher>::Create(playerPos + POSITION(3000, 0));
		tempObj->SetVisible(false);
		ObjManager->AddObject(tempObj, OBJ::ENTITY);
		
		const INT oreSizeX = 2;
		const INT oreSizeY = 2;
		for (INT i = 0; i < oreSizeY; i++)
			for (INT j = 0; j < oreSizeX; j++)
				ObjManager->InsertObject(CAbstractFactory<CCoalOre>::Create(playerPos.x + GRIDCX * j, playerPos.y + GRIDCX * i), OBJ::RESOURCEORE);
		
		for (INT i = -oreSizeY * 2; i < -oreSizeY; i++)
			for (INT j = -oreSizeX * 2; j < -oreSizeX; j++)
				ObjManager->InsertObject(CAbstractFactory<CCopperOre>::Create(playerPos.x + GRIDCX * j, playerPos.y + GRIDCX * i), OBJ::RESOURCEORE);
		
		for (INT i = -oreSizeY * 2; i < -oreSizeY; i++)
			for (INT j = 0; j < oreSizeX; j++)
				ObjManager->InsertObject(CAbstractFactory<CIronOre>::Create(playerPos.x + GRIDCX * j, playerPos.y + GRIDCX * i), OBJ::RESOURCEORE);
		
		for (INT i = 0; i < oreSizeY; i++)
			for (INT j = -oreSizeX * 2; j < -oreSizeX; j++)
				ObjManager->InsertObject(CAbstractFactory<CStone>::Create(playerPos.x + GRIDCX * j, playerPos.y + GRIDCX * i), OBJ::RESOURCEORE);


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
	//TCHAR szBuffer[32];
	//SetBkMode(hMemDC, OPAQUE);
	//wsprintf(szBuffer, L"1번 : 운송벨트", playerScore);
	//TextOut(hMemDC, 100, 50, szBuffer, lstrlen(szBuffer));
	//wsprintf(szBuffer, L"2번 : 화력 채광드릴", playerScore);
	//TextOut(hMemDC, 100, 100, szBuffer, lstrlen(szBuffer));
	//wsprintf(szBuffer, L"좌클릭 : 설치", playerScore);
	//TextOut(hMemDC, 100, 150, szBuffer, lstrlen(szBuffer));
	//wsprintf(szBuffer, L"우클릭 : 채집, 수거", playerScore);
	//TextOut(hMemDC, 100, 200, szBuffer, lstrlen(szBuffer));
	//wsprintf(szBuffer, L"Q : 선택해제", playerScore);
	//TextOut(hMemDC, 100, 250, szBuffer, lstrlen(szBuffer));
	//wsprintf(szBuffer, L"R : 회전", playerScore);
	//TextOut(hMemDC, 100, 300, szBuffer, lstrlen(szBuffer));
	//wsprintf(szBuffer, L"E : 인벤토리", playerScore);
	//TextOut(hMemDC, 100, 350, szBuffer, lstrlen(szBuffer));

	m_iFPS++;
	SetTextColor(hMemDC, RGB(255, 255, 255));
	if (m_dwOldTime + 1000 < GetTickCount()) {
		wsprintf(m_szFPS, L"FPS : %d", m_iFPS);
		m_iFPS = 0;
		m_dwOldTime = GetTickCount();
	}
	TextOut(hMemDC, WINCX - 200, 50, m_szFPS, lstrlen(m_szFPS));
	SetTextColor(hMemDC, RGB(0, 0, 0));
	/////////////////////
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	DeleteObject(SelectObject(hMemDC, oldBitmap));
	DeleteDC(hMemDC);
	/////////////////////
}

void CPlayScene::ReleaseScene() {
	ObjManager->ReleaseObjectManager();

}
