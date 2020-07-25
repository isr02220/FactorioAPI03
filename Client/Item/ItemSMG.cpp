#include "ItemSMG.h"
#include "Actor.h"
#include "Item.h"
CItemSMG::CItemSMG() : CItem() {
	objectType = OBJ::ITEM;
	group = ITEM::GROUP::COMBAT;
	subGroup = ITEM::SUBGROUP::COMBAT_Weapon;
	lstrcpy(IconName, L"ICON_submachine-gun");
	SetName(L"±â°ü´ÜÃÑ");
}

CItemSMG::~CItemSMG() {
	Release_Object();
}

void CItemSMG::LateUpdate_Object() {

}

void CItemSMG::Render_Object(HDC hDC) {
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


CItem* CItemSMG::GetNewItem() {
	return new CItemSMG();
}


CActor* CItemSMG::GetNewActor() {
	return nullptr;
}