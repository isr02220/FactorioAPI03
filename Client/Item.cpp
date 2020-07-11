#include "CollisionManager.h"
#include "Item.h"
#include "Player.h"
CItem::CItem() : CObj() {
	m_ObjectType = OBJ::ITEM;
}

CItem::CItem(FLOAT _positionX, FLOAT _positionY) : CObj(_positionX, _positionY) {
	m_ObjectType = OBJ::ITEM;
}

CItem::~CItem() {
}



void CItem::Ready_Object() {

	m_tInfo.iCX = 100;
	m_tInfo.iCY = 100;
	m_tInfo.force = FORCE(0,0);
}

int CItem::Update_Object() {
	CObj::Update_Rect_Object();

	if (m_isDead)
		return STATE_DEAD;

	if (m_isJump)
		m_tInfo.force.y += 0.4f;
	else
		m_tInfo.force.y = 0.f;
	m_tInfo.position.y += m_tInfo.force.y;

	return STATE_NO_EVENT;
}

void CItem::LateUpdate_Object() {
	CObj::Update_Rect_Object();
	if (m_tRect.left < 50 || m_tRect.right > WINCX - 50)
		m_tInfo.force.x *= -1.f;
	if (m_tRect.top < 50 || m_tRect.bottom > WINCY - 50)
		m_tInfo.force.y *= -1.f;

}

void CItem::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (m_isVisible) {
		//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		TCHAR szBuffer[32];
		swprintf_s(szBuffer, L"%s \nHP : %d / %d", m_tInfo.name, m_HP, m_MaxHP);
		RECT rc = m_tRect;
		rc.top = m_tRect.bottom;
		rc.bottom = rc.top + 40;
		DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_VCENTER);
	}
}

void CItem::Release_Object() {

}


void CItem::OnCollision(CObj* _TargetObj) {
	switch (_TargetObj->GetObjectType()) {
	case OBJ::BULLET: {
		break;
	case OBJ::MONSTER:
		break;
	case OBJ::PLAYER: {
		CPlayer* tempPlayer = dynamic_cast<CPlayer*>(_TargetObj);
		RECT rc = {};
		if (IntersectRect(&rc, tempPlayer->GetRect(), GetRect())) {
			//tempPlayer->SetItem(this);
			SetDead();

		}
	}
					break;
	default:
		break;
	}
	}
}

