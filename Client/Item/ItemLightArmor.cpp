#include "ItemLightArmor.h"
#include "Actor.h"
#include "Item.h"
CItemLightArmor::CItemLightArmor() : CItem() {
	objectType = OBJ::ITEM;
	group = ITEM::GROUP::COMBAT;
	subGroup = ITEM::SUBGROUP::COMBAT_Armor;
	lstrcpy(IconName, L"ICON_light-armor");
	SetName(L"라이트 아머");
	stackSize = 1;
}

CItemLightArmor::~CItemLightArmor() {
	Release_Object();
}

void CItemLightArmor::LateUpdate_Object() {

}

void CItemLightArmor::Render_Object(HDC hDC) {
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

CItem* CItemLightArmor::GetNewItem() {
	return new CItemLightArmor();
}

CActor* CItemLightArmor::GetNewActor() {
	return nullptr;
}