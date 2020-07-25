#include "ItemCopperCable.h"
#include "Actor.h"
#include "Item.h"
CItemCopperCable::CItemCopperCable() : CItem() {
	objectType = OBJ::ITEM;
	group = ITEM::GROUP::INTERMEDIATE;
	subGroup = ITEM::SUBGROUP::INTERMEDIATE_CraftingComponents;
	lstrcpy(IconName, L"ICON_copper-cable");
	SetName(L"구리 전선");
}

CItemCopperCable::~CItemCopperCable() {
	Release_Object();
}

void CItemCopperCable::LateUpdate_Object() {

}

void CItemCopperCable::Render_Object(HDC hDC) {
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

CItem* CItemCopperCable::GetNewItem() {
	return new CItemCopperCable();
}

CActor* CItemCopperCable::GetNewActor() {
	return nullptr;
}