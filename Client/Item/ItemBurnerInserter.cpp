#include "ItemBurnerInserter.h"
#include "BurnerInserter.h"
#include "Actor.h"
#include "Item.h"
CItemBurnerInserter::CItemBurnerInserter() : CItem() {
	objectType = OBJ::ITEM;
	group = ITEM::GROUP::LOGISTICS;
	subGroup = ITEM::SUBGROUP::LOGISTICS_Inserter;
	lstrcpy(IconName, L"ICON_inserter");
	SetName(L"화력 투입기");
}

CItemBurnerInserter::~CItemBurnerInserter() {
	Release_Object();
}

void CItemBurnerInserter::LateUpdate_Object() {

}

void CItemBurnerInserter::Render_Object(HDC hDC) {
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


CItem* CItemBurnerInserter::GetNewItem() {
	return new CItemBurnerInserter();
}

CActor* CItemBurnerInserter::GetNewActor() {
	return dynamic_cast<CActor*>(CAbstractFactory<CBurnerInserter>::Create());
}