#include "ItemIronGearWheel.h"
#include "Actor.h"
#include "Item.h"
CItemIronGearWheel::CItemIronGearWheel() : CItem() {
	objectType = OBJ::ITEM;
	group = ITEM::GROUP::INTERMEDIATE;
	subGroup = ITEM::SUBGROUP::INTERMEDIATE_CraftingComponents;
	lstrcpy(IconName, L"ICON_iron-gear-wheel");
	SetName(L"Ã¶ Åé´Ï¹ÙÄû");
}

CItemIronGearWheel::~CItemIronGearWheel() {
	Release_Object();
}

void CItemIronGearWheel::LateUpdate_Object() {

}

void CItemIronGearWheel::Render_Object(HDC hDC) {
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


CItem* CItemIronGearWheel::GetNewItem() {
	return new CItemIronGearWheel();
}

CActor* CItemIronGearWheel::GetNewActor() {
	return nullptr;
}