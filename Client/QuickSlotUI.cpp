#include "QuickSlotUI.h"
#include "Obj.h"
CQuickSlotUI::CQuickSlotUI() {
	objectType = OBJ::UI;
	strokeColor = RGB(128, 128, 255);
	fillColor = RGB(0, 255, 255);
}

CQuickSlotUI::~CQuickSlotUI() {
}

void CQuickSlotUI::Ready_Object() {
	isVisible = false;
	info.iCX = 512;
	info.iCY = 96;
	info.CCX = 512;
	info.CCY = 96;
}

INT CQuickSlotUI::Update_Object() {
	return 0;
}

void CQuickSlotUI::LateUpdate_Object() {
}

void CQuickSlotUI::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"GUI_QuickSlot");

		if (nullptr == hMemDC)
			return;

		BitBlt(hDC,
			cRect.left,
			cRect.top,
			info.CCX,
			info.CCY,
			hMemDC,
			0, 0,
			SRCCOPY);
	}
}

void CQuickSlotUI::Release_Object() {
}

void CQuickSlotUI::OnCollision(CObj* _TargetObj) {
}