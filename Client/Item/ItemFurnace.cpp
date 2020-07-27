#include "ItemFurnace.h"
#include "Furnace.h"
#include "Actor.h"
#include "Item.h"
CItemFurnace::CItemFurnace() : CItem() {
	objectType = OBJ::ITEM;
	group = ITEM::GROUP::PRODUCTION;
	subGroup = ITEM::SUBGROUP::PRODUCTION_Furnace;
	lstrcpy(IconName, L"ICON_stone-furnace");
	SetName(L"µ¹ ¿ë±¤·Î");
}

CItemFurnace::~CItemFurnace() {
	Release_Object();
}

void CItemFurnace::LateUpdate_Object() {

}

void CItemFurnace::Render_Object(HDC hDC) {
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


CItem* CItemFurnace::GetNewItem() {
	return new CItemFurnace();
}

CActor* CItemFurnace::GetNewActor() {
	return dynamic_cast<CActor*>(CAbstractFactory<CFurnace>::Create());
}