#include "Obj.h"
#include "Mouse.h"
CMouse::CMouse() {
	objectType = OBJ::MOUSE;
}


CMouse::~CMouse() {
}

void CMouse::Ready_Object() {
	info.iCX = 20;
	info.iCY = 20;
	ShowCursor(false);
}

int CMouse::Update_Object() {
	// 마우스 위치를 얻어오려면!? 
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	info.position.x = FLOAT(pt.x);
	info.position.y = FLOAT(pt.y);
	return 0;
}

void CMouse::LateUpdate_Object() {
}

void CMouse::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		POINT pt = {};
		MoveToEx(hDC, rect.left, (rect.top + rect.bottom) / 2, &pt);
		LineTo(hDC, rect.right, (rect.top + rect.bottom) / 2);
		MoveToEx(hDC, (rect.left + rect.right) / 2, rect.top, &pt);
		LineTo(hDC, (rect.left + rect.right) / 2, rect.bottom);
		//Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}

void CMouse::Release_Object() {
}

void CMouse::OnCollision(CObj* _TargetObj) {

}
