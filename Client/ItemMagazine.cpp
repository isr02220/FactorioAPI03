#include "ItemMagazine.h"
#include "Actor.h"
#include "Item.h"
CItemMagazine::CItemMagazine() : CItem() {
	objectType = OBJ::ITEM;
	group = ITEM::GROUP::COMBAT;
	subGroup = ITEM::SUBGROUP::COMBAT_Ammo;
	lstrcpy(IconName, L"ICON_firearm-magazine");
	SetName(L"È­±â¿ë ÅºÃ¢");
}

CItemMagazine::~CItemMagazine() {
	Release_Object();
}

void CItemMagazine::LateUpdate_Object() {

}

void CItemMagazine::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(IconName);
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


CItem* CItemMagazine::GetNewItem() {
	return new CItemMagazine();
}

CActor* CItemMagazine::GetNewActor() {
	return nullptr;
}