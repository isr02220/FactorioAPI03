#include "Obj.h"
#include "Mouse.h"
CMouse::CMouse() {
	m_ObjectType = OBJ::MOUSE;
}


CMouse::~CMouse() {
}

void CMouse::Ready_Object() {
	m_tInfo.iCX = 20;
	m_tInfo.iCY = 20;
	ShowCursor(false);
}

int CMouse::Update_Object() {
	// 마우스 위치를 얻어오려면!? 
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	m_tInfo.position.x = FLOAT(pt.x);
	m_tInfo.position.y = FLOAT(pt.y);
	return 0;
}

void CMouse::LateUpdate_Object() {
}

void CMouse::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (m_isVisible) {
		POINT pt = {};
		MoveToEx(hDC, m_tRect.left, (m_tRect.top + m_tRect.bottom) / 2, &pt);
		LineTo(hDC, m_tRect.right, (m_tRect.top + m_tRect.bottom) / 2);
		MoveToEx(hDC, (m_tRect.left + m_tRect.right) / 2, m_tRect.top, &pt);
		LineTo(hDC, (m_tRect.left + m_tRect.right) / 2, m_tRect.bottom);
		//Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}

void CMouse::Release_Object() {
}

void CMouse::OnCollision(CObj* _TargetObj) {

}
