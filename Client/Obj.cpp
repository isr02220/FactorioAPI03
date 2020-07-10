#include "Obj.h"

CObj::CObj() {
	ZeroMemory(&m_tInfo, sizeof(INFO));
}
CObj::CObj(FLOAT _forceX, FLOAT _forceY) : forceX(_forceX), forceY(_forceY) {
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tInfo, sizeof(INFO));
}

CObj::~CObj() {
}

void CObj::Update_Rect_Object() {
	m_tRect.left   = LONG(m_tInfo.fX - (m_tInfo.iCX >> 1));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.iCY >> 1));
	m_tRect.right  = LONG(m_tInfo.fX + (m_tInfo.iCX >> 1));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.iCY >> 1));
}
