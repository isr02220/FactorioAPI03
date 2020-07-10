#include "Player.h"

CPlayer::CPlayer() : CObj() {
    m_ObjId = OBJ::PLAYER;
}

CPlayer::CPlayer(float _forceX, float _forceY) : CObj(_forceX, forceY) {
    m_ObjId = OBJ::PLAYER;
}

CPlayer::~CPlayer() {
    Release_Object();
}

void CPlayer::Ready_Object() {
    m_tInfo.fX = -100.f;
    m_tInfo.fY = 700.f;
    m_tInfo.iCX = 60;
    m_tInfo.iCY = 100;
    m_fSpeed = 7.f;
    forceY = 0.f;
	m_HP = m_MaxHP = 200;
    m_isJump = true;
}

int CPlayer::Update_Object() {
    m_tInfo.fY += m_fSpeed * forceY;
    //if (m_isDead)
    //    return STATE_DEAD;

    CObj::Update_Rect_Object();
      
    if (m_ShootDelay > 0) m_ShootDelay -= 1;

    return STATE_NO_EVENT;
}

void CPlayer::LateUpdate_Object() {
    m_BarrelEndPt.x = LONG(m_tInfo.fX + (cosf(m_BarrelAngle * pi / 180.f) * m_BarrelSize));
    m_BarrelEndPt.y = LONG(m_tInfo.fY - (sinf(m_BarrelAngle * pi / 180.f) * m_BarrelSize));
}

void CPlayer::Render_Object(HDC hDC) {
    CObj::Update_Rect_Object();
    if (m_isVisible) {
		COLORREF bColor = RGB(250, 128, 64);	// 브러쉬 색
		HBRUSH hBrush = CreateSolidBrush(bColor);
		HBRUSH  oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		
        Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);

        MoveToEx(hDC, int(m_tInfo.fX), int(m_tInfo.fY), nullptr);
        LineTo(hDC, INT(m_BarrelEndPt.x + spanX), INT(m_BarrelEndPt.y + spanY));
    }

}

void CPlayer::Release_Object() {

}

void CPlayer::OnCollision(CObj* _TargetObj) {

}