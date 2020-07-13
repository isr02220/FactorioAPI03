#include "Obj.h"
#include "Mouse.h"
#include "Player.h"
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
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	info.position.x = FLOAT(pt.x);
	info.position.y = FLOAT(pt.y);
	selectedActor = nullptr;
	dynamic_cast<CPlayer*>(CObjManager::GetInstance()->GetPlayer())->UpdateSelected(selectedActor);
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
	HPEN   hPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 0));
	HPEN   oldPen = (HPEN)SelectObject(hDC, hPen);

	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	if (selectedActor) {
		RECT* tRect = selectedActor->GetRect();
		Rectangle(hDC, tRect->left, tRect->top, tRect->right, tRect->bottom);
	}

	SelectObject(hDC, oldPen);
	SelectObject(hDC, oldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void CMouse::Release_Object() {
}

void CMouse::OnCollision(CObj* _TargetObj) {
	selectedActor = dynamic_cast<CActor*>(_TargetObj);
	if (selectedActor) {
		dynamic_cast<CPlayer*>(CObjManager::GetInstance()->GetPlayer())->UpdateSelected(selectedActor);
	}
}
