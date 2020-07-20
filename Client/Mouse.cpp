#include "Obj.h"
#include "Mouse.h"
#include "Player.h"
#include "UI.h"
CMouse::CMouse() {
	objectType = OBJ::MOUSE;
}


CMouse::~CMouse() {
}

void CMouse::Ready_Object() {
	info.iCX = 64;
	info.iCY = 64;
	//ShowCursor(false);
}

int CMouse::Update_Object() {
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	pt.x -= (LONG)CScrollManager::GetInstance()->GetScrollX();
	pt.y -= (LONG)CScrollManager::GetInstance()->GetScrollY();
	info.position.x = FLOAT(pt.x);
	info.position.y = FLOAT(pt.y);
	selectedActor = nullptr;
	selectedUI = nullptr;
	dynamic_cast<CPlayer*>(CObjManager::GetInstance()->GetPlayer())->UpdateSelected(selectedActor);
	dynamic_cast<CPlayer*>(CObjManager::GetInstance()->GetPlayer())->UpdateSelectedUI(selectedUI);
	return 0;
}

void CMouse::LateUpdate_Object() {
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	for (auto ui : *CObjManager::GetInstance()->GetList(OBJ::UI)) {
		if (PtInRect(ui->GetRect(), pt) && dynamic_cast<CUI*>(ui)->GetVisible()) {
			selectedUI = dynamic_cast<CUI*>(ui);
			selectedActor = nullptr;
			dynamic_cast<CPlayer*>(CObjManager::GetInstance()->GetPlayer())->UpdateSelected(selectedActor);
			dynamic_cast<CPlayer*>(CObjManager::GetInstance()->GetPlayer())->UpdateSelectedUI(selectedUI);
		}
	}
}

void CMouse::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		POINT pt = {};
		//MoveToEx(hDC, rect.left, (rect.top + rect.bottom) / 2, &pt);
		//LineTo(hDC, rect.right, (rect.top + rect.bottom) / 2);
		//MoveToEx(hDC, (rect.left + rect.right) / 2, rect.top, &pt);
		//LineTo(hDC, (rect.left + rect.right) / 2, rect.bottom);
		//Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
	HPEN   hPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 0));
	HPEN   oldPen = (HPEN)SelectObject(hDC, hPen);

	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	if (selectedActor) {
		INT ScrollX = CScrollManager::GetInstance()->GetScrollX();
		INT ScrollY = CScrollManager::GetInstance()->GetScrollY();
		RECT* tRect = selectedActor->GetRect();
		Rectangle(hDC, tRect->left + ScrollX, tRect->top + ScrollY, tRect->right + ScrollX, tRect->bottom + ScrollY);
	}
	else if (selectedUI) {
		RECT * tRect = selectedUI->GetRect();
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
	if (selectedActor && selectedUI == nullptr) {
		dynamic_cast<CPlayer*>(CObjManager::GetInstance()->GetPlayer())->UpdateSelected(selectedActor);
	}
}
