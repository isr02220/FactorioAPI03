#include "InventoryUI.h"
#include "Inventory.h"
#include "ItemStack.h"
#include "Obj.h"
#include "Actor.h"
CInventoryUI::CInventoryUI() {
	objectType = OBJ::UI;
	strokeColor = RGB(128, 128, 255);
	fillColor = RGB(0, 255, 255);
}

CInventoryUI::~CInventoryUI() {
}

void CInventoryUI::Ready_Object() {
	isVisible = false;
	info.iCX = 402;
	info.iCY = 437;
	info.CCX = 402;
	info.CCY = 437;
}

INT CInventoryUI::Update_Object() {
	if (targetActor && targetActor->inventory) {
		listItemStack = &(targetActor->inventory->listItemStack);
	}
	else {
		listItemStack = nullptr;
	}

	return STATE_NO_EVENT;
}

void CInventoryUI::LateUpdate_Object() {
}

void CInventoryUI::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"GUI_InventoryMerged");

		if (nullptr == hMemDC)
			return;

		BitBlt(hDC,
			cRect.left,
			cRect.top,
			info.CCX,
			info.CCY,
			hMemDC,
			0,0,
			SRCCOPY);

		for (auto itemStack : *listItemStack) {

		}
	}
}

void CInventoryUI::Release_Object() {
}

void CInventoryUI::OnCollision(CObj* _TargetObj) {
}