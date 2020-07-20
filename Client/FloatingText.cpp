#include "FloatingText.h"
#include "Obj.h"
CFloatingText::CFloatingText() {
	objectType = OBJ::UI;
	strokeColor = RGB(0, 0, 0);
	fillColor = RGB(255, 255, 255);
}

CFloatingText::~CFloatingText() {
}

void CFloatingText::Ready_Object() {
	isVisible = true;
	info.iCX = 10;
	info.iCY = 10;
	info.CCX = 10;
	info.CCY = 10;
}

INT CFloatingText::Update_Object() {
	if (timer + 500 < GetTickCount())
		return STATE_DEAD;
	info.position.y -= 1.f;
	return STATE_NO_EVENT;
}

void CFloatingText::LateUpdate_Object() {
}

void CFloatingText::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {

		SetTextColor(hDC, RGB(0, 0, 0));
		SetBkMode(hDC, TRANSPARENT);

		LOGFONT* logFont = CFontManager::GetInstance()->FindFont(L"±Ã¼­Ã¼");
		HFONT myFont = CreateFontIndirect(logFont);
		HFONT oldFont = (HFONT)SelectObject(hDC, myFont);

		RECT rc = {};
		rc.left   = rect.left   + CScrollManager::GetInstance()->GetScrollX();
		rc.top    = rect.top    + CScrollManager::GetInstance()->GetScrollY();
		rc.right  = rect.right  + CScrollManager::GetInstance()->GetScrollX();
		rc.bottom = rect.bottom + CScrollManager::GetInstance()->GetScrollY();
		
		rc.left   += 1;
		rc.right  += 1;
		DrawText(hDC, info.name, lstrlen(info.name), &rc, DT_VCENTER | DT_NOCLIP);
		rc.top    += 1;
		rc.bottom += 1;
		DrawText(hDC, info.name, lstrlen(info.name), &rc, DT_VCENTER | DT_NOCLIP);
		rc.left   -= 1;
		rc.right  -= 1;
		DrawText(hDC, info.name, lstrlen(info.name), &rc, DT_VCENTER | DT_NOCLIP);
		rc.left   -= 1;
		rc.right  -= 1;
		DrawText(hDC, info.name, lstrlen(info.name), &rc, DT_VCENTER | DT_NOCLIP);
		rc.top    -= 1;
		rc.bottom -= 1;
		DrawText(hDC, info.name, lstrlen(info.name), &rc, DT_VCENTER | DT_NOCLIP);
		rc.left   -= 1;
		rc.right  -= 1;
		DrawText(hDC, info.name, lstrlen(info.name), &rc, DT_VCENTER | DT_NOCLIP);
		rc.left   += 1;
		rc.right  += 1;
		DrawText(hDC, info.name, lstrlen(info.name), &rc, DT_VCENTER | DT_NOCLIP);
		rc.top    += 1;
		rc.bottom += 1;

		SetTextColor(hDC, RGB(255, 255, 255));

		DrawText(hDC, info.name, lstrlen(info.name), &rc, DT_VCENTER | DT_NOCLIP);

		SetTextColor(hDC, RGB(0, 0, 0));
		SelectObject(hDC, oldFont);
		DeleteObject(myFont);
	}
}

void CFloatingText::Release_Object() {
}