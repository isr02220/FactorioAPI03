#include "ProgressBar.h"
#include "Obj.h"
CProgressBar::CProgressBar() {
	objectType = OBJ::UI;
	strokeColor = RGB(255, 128, 255);
	fillColor = RGB(255, 255, 0);
}

CProgressBar::~CProgressBar() {
}

void CProgressBar::Ready_Object() {
	isVisible = false;
	info.iCX = 512;
	info.iCY = 32;
	info.CCX = 512;
	info.CCY = 32;
}

INT CProgressBar::Update_Object() {
	return 0;
}

void CProgressBar::LateUpdate_Object() {
}

void CProgressBar::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDCPanel    = CBitmapManager::GetInstance()->FindImage(L"GUI_ProgressBarPanel");
		HDC hMemDCProgress = CBitmapManager::GetInstance()->FindImage(L"GUI_ProgressBarProgress");

		if (nullptr == hMemDCPanel || nullptr == hMemDCProgress)
			return;

		BitBlt(hDC,
			cRect.left,
			cRect.top,
			info.CCX,
			info.CCY,
			hMemDCPanel,
			0, 0,
			SRCCOPY);

		BitBlt(hDC,
			cRect.left,
			cRect.top,
			INT(info.CCX * progress),
			info.CCY,
			hMemDCProgress,
			0, 0,
			SRCCOPY);

	}
}

void CProgressBar::Release_Object() {
}