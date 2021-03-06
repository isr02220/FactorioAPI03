#include "IronOre.h"
#include "ItemIronOre.h"
#include "ResourceOre.h"
CIronOre::CIronOre() : CResourceOre() {

}

CIronOre::~CIronOre() {

}

void CIronOre::Ready_Object() {
	SetName(L"ö����");
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

void CIronOre::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-iron-ore");
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
CObj* CIronOre::Gather() {
	if (storage) {
		storage--;
		spriteIndexY = 7 - (storage / 100);
		if (spriteIndexY < 0) spriteIndexY = 0;
		CObj* tempObj = new CItemIronOre();
		tempObj->Ready_Object();
		return tempObj;
	}
	else {
		SetDead();
		return nullptr;
	}
}

CObj* CIronOre::GetNewActor() {
	return nullptr;
}

CItem* CIronOre::GetNewItem() {
	return nullptr;
}
