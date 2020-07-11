#include "Player.h"

CPlayer::CPlayer() : CObj() {
    m_ObjectType = OBJ::PLAYER;
}

CPlayer::CPlayer(FLOAT _positionX, FLOAT _positionY) : CObj(_positionX, _positionY) {
    m_ObjectType = OBJ::PLAYER;
}

CPlayer::~CPlayer() {
    Release_Object();
}

void CPlayer::Ready_Object() {
    m_tInfo.position.x = -100.f;
    m_tInfo.position.y = 700.f;
    m_tInfo.iCX = 60;
    m_tInfo.iCY = 100;
    //m_fSpeed = 7.f;
    m_tInfo.force.y = 0.f;
	m_HP = m_MaxHP = 200;
    m_isJump = true;
}

int CPlayer::Update_Object() {
    //m_tInfo.position.y += m_fSpeed * forceY;
    m_tInfo.position.y += m_tInfo.force.y;
    //if (m_isDead)
    //    return STATE_DEAD;

    CObj::Update_Rect_Object();
      
    if (m_ShootDelay > 0) m_ShootDelay -= 1;

    return STATE_NO_EVENT;
}

void CPlayer::LateUpdate_Object() {
    m_BarrelEndPt.x = LONG(m_tInfo.position.x + (cosf(m_BarrelAngle * pi / 180.f) * m_BarrelSize));
    m_BarrelEndPt.y = LONG(m_tInfo.position.y - (sinf(m_BarrelAngle * pi / 180.f) * m_BarrelSize));
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

        MoveToEx(hDC, int(m_tInfo.position.x), int(m_tInfo.position.y), nullptr);
        LineTo(hDC, INT(m_BarrelEndPt.x + spanX), INT(m_BarrelEndPt.y + spanY));
    }

}

void CPlayer::Release_Object() {

}

void CPlayer::OnCollision(CObj* _TargetObj) {

}