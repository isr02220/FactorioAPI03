#include "Obj.h"

CObj::CObj() {
	ZeroMemory(&m_tInfo, sizeof(INFO));
}
CObj::CObj(FLOAT _positionX, FLOAT _positionY){
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tInfo.position.x = _positionX;
	m_tInfo.position.y = _positionY;
}

CObj::~CObj() {
}

void CObj::Update_Rect_Object() {
	m_tRect.left   = LONG(m_tInfo.position.x - (m_tInfo.iCX >> 1));
	m_tRect.top = LONG(m_tInfo.position.y - (m_tInfo.iCY >> 1));
	m_tRect.right  = LONG(m_tInfo.position.x + (m_tInfo.iCX >> 1));
	m_tRect.bottom = LONG(m_tInfo.position.y + (m_tInfo.iCY >> 1));
}
