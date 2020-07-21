#include "CoalOre.h"
#include "ItemCoalOre.h"
#include "ResourceOre.h"
CCoalOre::CCoalOre() : CResourceOre() {

}

CCoalOre::~CCoalOre() {

}

void CCoalOre::Ready_Object() {
	SetName(L"¼®Åº");
	info.iCX = 64;
	info.iCY = 64;
	info.CCX = 128;
	info.CCY = 128;
	speed = 3.f;
	MaxHP = 10;
	HP = MaxHP;
	spriteIndexX = rand() % 8;
	storage = 100;
}

void CCoalOre::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-coal");
		if (nullptr == hMemDC)
			return;
		INT iScrollX = (INT)CScrollManager::GetInstance()->GetScrollX();
		INT iScrollY = (INT)CScrollManager::GetInstance()->GetScrollY();
		
		GdiTransparentBlt(hDC,
			cRect.left + iScrollX,
			cRect.top + iScrollY,
			info.CCX,
			info.CCY,
			hMemDC,
			spriteIndexX * info.CCX,
			spriteIndexY * info.CCY,
			info.CCX,
			info.CCY,
			RGB(255, 0, 255));
	}

}
CObj* CCoalOre::Gather() {
	if (storage) {
		storage--;
		spriteIndexY = 7 - (storage / 100);
		if (spriteIndexY < 0) spriteIndexY = 0;
		CObj* tempObj = new CItemCoalOre();
		tempObj->Ready_Object();
		return tempObj;
	}
	else {
		SetDead();
		return nullptr;
	}
}