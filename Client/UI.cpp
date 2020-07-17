#include "UI.h"
#include "Obj.h"
CUI::CUI() {
	objectType = OBJ::UI;
	strokeColor = RGB(128, 128, 255);
	fillColor = RGB(0, 255, 255);
}

CUI::~CUI() {
}

void CUI::Ready_Object() {
	isVisible = false;
	info.iCX = 402;
	info.iCY = 437;
	info.CCX = 402;
	info.CCY = 437;
}

INT CUI::Update_Object() {
	return 0;
}

void CUI::LateUpdate_Object() {
}

void CUI::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
        HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"GUI_Panel");

        if (nullptr == hMemDC)
            return;
		BLENDFUNCTION bf = {};
		bf.AlphaFormat = 0;
		bf.BlendFlags = 0;
		bf.BlendOp = AC_SRC_OVER;
		bf.SourceConstantAlpha = 216;

		GdiAlphaBlend(hDC,
			cRect.left,
			cRect.top,
			info.CCX,
			info.CCY,
			hMemDC,
			0,
			0,
			info.CCX,
			info.CCY,
			bf);
		//BitBlt(hDC, rect.left, rect.top, info.iCX, info.iCY, hMemDC, 0, 0, SRCCOPY);
	}
}

void CUI::Release_Object() {
}

void CUI::OnCollision(CObj* _TargetObj) {
}
