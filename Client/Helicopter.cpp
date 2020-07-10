#include "Helicopter.h"

CHelicopter::CHelicopter()
{
}

CHelicopter::~CHelicopter()
{
}

void CHelicopter::Ready_Object()
{
	m_fSpeed = 2.f;
	forceX = -1.f;
	m_tInfo.iCX = 200;
	m_tInfo.iCY = 100;
	m_iTailAngle = 0;
	m_MaxHP = m_HP = 200;
	m_fTempX = m_tInfo.fX;
	m_fTempY = m_tInfo.fY;
	m_iTailSpeed = 5;
	m_MonsterType = MONSTER::HELICOPTER;
}

int CHelicopter::Update_Object()
{
	CObj::Update_Rect_Object();
	if (m_tRect.left < DeadLineLeft) return STATE_DEAD;
	if (m_HP <= 0)
	{
		m_isVisible = false;
		m_tInfo.fX += m_fSpeed * forceX;
		forceY += 1.f;
		m_tInfo.fY += forceY;
		if (!m_isJump)
			return STATE_DEAD;

		return NO_EVENT;
	}
	else {
		forceY = -10.f;
	}
	Update_TailAngle();
	Move();
	Update_Barrel();

	if (m_Timer + 1000 < GetTickCount()) {
		ShootTo(ObjManager->GetPlayer(), LONG(m_fBarrelX), LONG(m_fBarrelY));
		m_Timer = GetTickCount();
	}
	
		//return STATE_DEAD;
	return NO_EVENT;
}

void CHelicopter::LateUpdate_Object()
{
	if (m_fTempX - (m_tInfo.iCX >> 1) < 50 || m_fTempX + (m_tInfo.iCX >> 1) > WINCX - 50)
		forceX *= -1.f;
}

void CHelicopter::Render_Object(HDC hDC)
{
	CMonster::Render_Object(hDC);

	// ÇÁ·ÎÆç·¯
	Ellipse(hDC, m_tRect.left-20, m_tRect.top, m_tRect.right + 20 - (m_tInfo.iCX >> 1), m_tRect.top + 20);

	// Body
	Rectangle(hDC, m_tRect.left, m_tRect.top + 20, m_tRect.right - (m_tInfo.iCX >> 1), m_tRect.bottom);

	// Tail
	Rectangle(hDC, m_tRect.left + (m_tInfo.iCX >> 1), m_tRect.bottom - 20, m_tRect.right, m_tRect.bottom);

	// Tail ÇÁ·ÎÆç·¯
	Render_Tail(hDC);

	if (m_isVisible) {
		// Æ÷½Å
		MoveToEx(hDC, m_iCenterBarrelX + spanX, m_iCenterBarrelY + spanY, nullptr);
		LineTo(hDC, int(m_fBarrelX + spanX), int(m_fBarrelY + spanY));
	}
}

void CHelicopter::Release_Object()
{
}

void CHelicopter::Update_TailAngle()
{
	m_iTailAngle = m_iTailAngle + int(m_iTailSpeed*forceX) % 360;
}

void CHelicopter::Move()
{
	m_fTempX += m_fSpeed * forceX;
	
	// Move
	m_iMoveAngle = static_cast<int>(m_iMoveAngle + m_fSpeed) % 360;
	float radian = DEGREE_RADIAN(static_cast<float>(m_iMoveAngle));
	m_tInfo.fX = cosf(radian) * 20 + m_fTempX;

	m_tInfo.fY = sinf(radian) * 20 + m_fTempY;
}

void CHelicopter::Render_Tail(HDC hDC)
{
	int r = 30;
	const float fixAngle = 90.f;
	for (int i = 0; i < 2; ++i)
	{
		float radian = DEGREE_RADIAN(static_cast<float>(i * fixAngle + m_iTailAngle));
		int rCos = static_cast<int>(r * cosf(radian));
		int rSin = static_cast<int>(r * sinf(radian));
		int tailX = m_tRect.right - 10;
		int tailY = m_tRect.bottom - 10;
		MoveToEx(hDC, tailX - rCos, tailY - rSin, nullptr);
		LineTo(hDC, tailX + rCos, tailY + rSin);
	}
	
}

void CHelicopter::Update_Barrel()
{
	m_iCenterBarrelX = m_tRect.left + 30;
	m_iCenterBarrelY = m_tRect.bottom - 20;
	float r = 100.f;
	FLOAT dx = ObjManager->GetPlayer()->GetInfo()->fX - m_tInfo.fX;
	FLOAT dy = ObjManager->GetPlayer()->GetInfo()->fY - m_tInfo.fY;
	FLOAT degree = atan2f(dy, dx) * radian;
	m_fBarrelX = r * cosf(DEGREE_RADIAN(degree)) + float(m_iCenterBarrelX);
	m_fBarrelY = r * sinf(DEGREE_RADIAN(degree)) + float(m_iCenterBarrelY);
}
