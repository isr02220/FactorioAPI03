#include "ItemHand.h"
#include "Item.h"
CItemHand::CItemHand() : CItem() {
	objectType = OBJ::ITEM;
	group = ITEM::GROUP::INTERMEDIATE;
	subGroup = ITEM::SUBGROUP::INTERMEDIATE_ResourceFluid;
	lstrcpy(IconName, L"ICON_hand");
	SetName(L"¼±ÅÃ");
}

CItemHand::~CItemHand() {
	Release_Object();
}

void CItemHand::LateUpdate_Object() {

}

void CItemHand::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"ICON_hand");
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


CItem* CItemHand::GetNewItem() {
	return new CItemHand();
}