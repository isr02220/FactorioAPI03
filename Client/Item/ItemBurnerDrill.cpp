#include "ItemBurnerDrill.h"
#include "BurnerDrill.h"
#include "Actor.h"
#include "Item.h"
CItemBurnerDrill::CItemBurnerDrill() : CItem() {
	objectType = OBJ::ITEM;
	group = ITEM::GROUP::PRODUCTION;
	subGroup = ITEM::SUBGROUP::PRODUCTION_ResourceExtraction;
	lstrcpy(IconName, L"ICON_burner-mining-drill");
	SetName(L"È­·Â Ã¤±¤±â");
}

CItemBurnerDrill::~CItemBurnerDrill() {
	Release_Object();
}

void CItemBurnerDrill::LateUpdate_Object() {

}

void CItemBurnerDrill::Render_Object(HDC hDC) {
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


CItem* CItemBurnerDrill::GetNewItem() {
	return new CItemBurnerDrill();
}


CActor* CItemBurnerDrill::GetNewActor() {
	return dynamic_cast<CActor*>(CAbstractFactory<CBurnerDrill>::Create());
}