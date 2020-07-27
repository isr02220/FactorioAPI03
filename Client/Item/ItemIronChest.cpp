#include "ItemIronChest.h"
#include "IronChest.h"
#include "Actor.h"
#include "Item.h"
CItemIronChest::CItemIronChest() : CItem() {
	objectType = OBJ::ITEM;
	group = ITEM::GROUP::LOGISTICS;
	subGroup = ITEM::SUBGROUP::LOGISTICS_Storage;
	lstrcpy(IconName, L"ICON_iron-chest");
	SetName(L"Ã¶ »óÀÚ");
}

CItemIronChest::~CItemIronChest() {
	Release_Object();
}

void CItemIronChest::LateUpdate_Object() {

}

void CItemIronChest::Render_Object(HDC hDC) {
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


CItem* CItemIronChest::GetNewItem() {
	return new CItemIronChest();
}

CActor* CItemIronChest::GetNewActor() {
	return dynamic_cast<CActor*>(CAbstractFactory<CIronChest>::Create());
}