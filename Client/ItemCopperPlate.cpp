#include "ItemCopperPlate.h"
#include "Item.h"
CItemCopperPlate::CItemCopperPlate() : CItem() {
	objectType = OBJ::ITEM;
	group = ITEM::GROUP::INTERMEDIATE;
	subGroup = ITEM::SUBGROUP::INTERMEDIATE_ResourceFluid;
	lstrcpy(IconName, L"ICON_copper-plate");
	SetName(L"±¸¸®ÆÇ");
	isBurnable = true;
}

CItemCopperPlate::~CItemCopperPlate() {
	Release_Object();
}

void CItemCopperPlate::LateUpdate_Object() {

}

void CItemCopperPlate::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"ICON_copper-plate");
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

CItem* CItemCopperPlate::GetNewItem() {
	return new CItemCopperPlate();
}