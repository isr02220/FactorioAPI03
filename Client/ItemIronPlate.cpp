#include "ItemIronPlate.h"
#include "Item.h"
CItemIronPlate::CItemIronPlate() : CItem() {
	objectType = OBJ::ITEM;
	group = ITEM::GROUP::INTERMEDIATE;
	subGroup = ITEM::SUBGROUP::INTERMEDIATE_ResourceFluid;
	lstrcpy(IconName, L"ICON_iron-plate");
	SetName(L"ö��");
	isBurnable = true;
}

CItemIronPlate::~CItemIronPlate() {
	Release_Object();
}

void CItemIronPlate::LateUpdate_Object() {

}

void CItemIronPlate::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"ICON_iron-plate");
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

CItem* CItemIronPlate::GetNewItem() {
	return new CItemIronPlate();
}