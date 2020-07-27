#include "ItemElectronicCircuit.h"
#include "Actor.h"
#include "Item.h"
CItemElectronicCircuit::CItemElectronicCircuit() : CItem() {
	objectType = OBJ::ITEM;
	group = ITEM::GROUP::INTERMEDIATE;
	subGroup = ITEM::SUBGROUP::INTERMEDIATE_CraftingComponents;
	lstrcpy(IconName, L"ICON_electronic-circuit");
	SetName(L"전자 회로");
	stackSize = 200;
}

CItemElectronicCircuit::~CItemElectronicCircuit() {
	Release_Object();
}

void CItemElectronicCircuit::LateUpdate_Object() {

}

void CItemElectronicCircuit::Render_Object(HDC hDC) {
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

CItem* CItemElectronicCircuit::GetNewItem() {
	return new CItemElectronicCircuit();
}

CActor* CItemElectronicCircuit::GetNewActor() {
	return nullptr;
}