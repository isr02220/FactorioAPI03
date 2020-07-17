#include "InventoryUI.h"
#include "Obj.h"
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
	return 0;
}

void CInventoryUI::LateUpdate_Object() {
}

void CInventoryUI::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"GUI_InventoryMerged");

		if (nullptr == hMemDC)
			return;
		BLENDFUNCTION bf = {};
		bf.AlphaFormat = 0;
		bf.BlendFlags = 0;
		bf.BlendOp = AC_SRC_OVER;
		bf.SourceConstantAlpha = 216;

		BitBlt(hDC,
			cRect.left,
			cRect.top,
			info.CCX,
			info.CCY,
			hMemDC,
			0,0,
			SRCCOPY);
	}
}

void CInventoryUI::Release_Object() {
}

void CInventoryUI::OnCollision(CObj* _TargetObj) {
}