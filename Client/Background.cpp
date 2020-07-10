#include "framework.h"
#include "Background.h"

void CBackground::Ready_Object() {
	for (size_t i = 0; i < 50; i++) {
		m_ListBgFar.emplace_back(new CBgObj(i * 100 + (rand() % 50), 400 + (rand() % 200), (i + 1) * 100, WINCY));
		m_ListBgMiddle.emplace_back(new CBgObj(i * 200 + (rand() % 100), 500 + (rand() % 100), (i + 1) * 200, WINCY));
		m_ListBgClose.emplace_back(new CBgObj(i * 300 + (rand() % 200), 600 + (rand() % 100), (i + 1) * 300, WINCY));
	}
}

INT CBackground::Update_Object() {

	for (auto bgObj : m_ListBgFar) {
		bgObj->MoveRect(0.25f * (spanX - m_spanX), 0.25f * (spanY - m_spanY));
		if (bgObj->fRight < 0.f)
			bgObj->MoveRect(5100.f, 0.f);
		else if (bgObj->fRight > 5100.f)
			bgObj->MoveRect(-5100.f, 0.f);
	}
	for (auto bgObj : m_ListBgMiddle){
		bgObj->MoveRect(0.5f * (spanX - m_spanX), 0.5f * (spanY - m_spanY));
		if (bgObj->fRight < 0.f) 
			bgObj->MoveRect(10200.f, 0.f);
		else if (bgObj->fRight > 10200.f)
			bgObj->MoveRect(-10200.f, 0.f);
		
	}
	for (auto bgObj : m_ListBgClose){
		bgObj->MoveRect(1.f * (spanX - m_spanX), 1.f * (spanY - m_spanY));
		if (bgObj->fRight < 0.f) 
			bgObj->MoveRect(15300.f, 0.f);
		else if (bgObj->fRight > 15300.f)
			bgObj->MoveRect(-15300.f, 0.f);
		
	}

	m_spanX = spanX;
	m_spanY = spanY;
	return 0;
}

void CBackground::LateUpdate_Object() {

}

void CBackground::Render_Object(HDC hDC) {
	HPEN   hPen1 = CreatePen(PS_SOLID, 1, RGB(26, 26, 26));
	HBRUSH hBrush1 = CreateSolidBrush((26, 26, 26));
	HPEN   hPen2 = CreatePen(PS_SOLID, 1, RGB(64, 64, 64));
	HBRUSH hBrush2 = CreateSolidBrush(RGB(64, 64, 64));
	HPEN   hPen3 = CreatePen(PS_SOLID, 1, RGB(92, 92, 92));
	HBRUSH hBrush3 = CreateSolidBrush(RGB(92, 92, 92));

	HPEN   oldPen   = (HPEN)SelectObject(hDC, hPen1);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush1);

	for (auto bgObj : m_ListBgFar)
		bgObj->Draw(hDC);
	(HPEN)SelectObject(hDC, hPen2);
	(HBRUSH)SelectObject(hDC, hBrush2);
	for (auto bgObj : m_ListBgMiddle)
		bgObj->Draw(hDC);
	(HPEN)SelectObject(hDC, hPen3);
	(HBRUSH)SelectObject(hDC, hBrush3);
	for (auto bgObj : m_ListBgClose)
		bgObj->Draw(hDC);

	SelectObject(hDC, oldPen);
	SelectObject(hDC, oldBrush);
	DeleteObject(hPen1);
	DeleteObject(hBrush1);
	DeleteObject(hPen2);
	DeleteObject(hBrush2);
	DeleteObject(hPen3);
	DeleteObject(hBrush3);
}

void CBackground::Release_Object() {

}

void CBackground::OnCollision(CObj* _TargetObj) {

}
