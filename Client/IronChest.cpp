#include "Inventory.h"
#include "IronChest.h"

CIronChest::CIronChest() {
    SetName(L"IronChest");
    objectType = OBJ::ENTITY;
	inventory = new CInventory(24);
}

CIronChest::~CIronChest() {
	Safe_Delete(inventory);
}
void CIronChest::Ready_Object() {
    info.iCX = 64;
    info.iCY = 64;
    info.CCX = 66;
    info.CCY = 76;
    speed = 3.f;
    MaxHP = 10;
    HP = MaxHP;
}

INT CIronChest::Update_Object() {
    info.position += (info.force * speed);
    CObj::Update_Rect_Object();
    if (dead) {
        return STATE_DEAD;
    }

    return STATE_NO_EVENT;
}

void CIronChest::LateUpdate_Object() {

}

void CIronChest::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-iron-chest");
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
			0,
			0,
			info.CCX,
			info.CCY,
			RGB(255, 0, 255));
	}
}

void CIronChest::Render_Placable(HDC hDC, BOOL placable) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC;
		if (placable)
			hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-iron-chest-placable");
		else
			hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-iron-chest-unplacable");
		if (nullptr == hMemDC)
			return;
		SetSpriteDir();
		INT iScrollX = (INT)CScrollManager::GetInstance()->GetScrollX();
		INT iScrollY = (INT)CScrollManager::GetInstance()->GetScrollY();

		GdiTransparentBlt(hDC,
			cRect.left + iScrollX,
			cRect.top + iScrollY,
			info.CCX,
			info.CCY,
			hMemDC,
			0,
			0,
			info.CCX,
			info.CCY,
			RGB(255, 0, 255));
	}
}

void CIronChest::Release_Object() {

}

void CIronChest::OnCollision(CObj* _TargetObj) {

}

CObj* CIronChest::GetNewActor() {
    CObj* tempObj = new CIronChest();
    tempObj->Ready_Object();
    return tempObj;
}
