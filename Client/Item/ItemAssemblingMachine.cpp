#include "ItemAssemblingMachine.h"
#include "AssemblingMachine.h"
#include "Actor.h"
#include "Item.h"
CItemAssemblingMachine::CItemAssemblingMachine() : CItem() {
	objectType = OBJ::ITEM;
	group = ITEM::GROUP::PRODUCTION;
	subGroup = ITEM::SUBGROUP::PRODUCTION_Production;
	lstrcpy(IconName, L"ICON_assembling-machine");
	SetName(L"조립 기계");
}

CItemAssemblingMachine::~CItemAssemblingMachine() {
	Release_Object();
}

void CItemAssemblingMachine::LateUpdate_Object() {

}

void CItemAssemblingMachine::Render_Object(HDC hDC) {
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


CItem* CItemAssemblingMachine::GetNewItem() {
	return new CItemAssemblingMachine();
}

CActor* CItemAssemblingMachine::GetNewActor() {
	return dynamic_cast<CActor*>(CAbstractFactory<CAssemblingMachine>::Create());
}