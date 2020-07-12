#include "CollisionManager.h"
#include "Item.h"
#include "Player.h"
CItem::CItem() : CObj() {
	objectType = OBJ::ITEM;
}

CItem::CItem(FLOAT _positionX, FLOAT _positionY) : CObj(_positionX, _positionY) {
	objectType = OBJ::ITEM;
}

CItem::~CItem() {
}



void CItem::Ready_Object() {

	info.iCX = 100;
	info.iCY = 100;
	info.force = FORCE(0,0);
}

int CItem::Update_Object() {
	CObj::Update_Rect_Object();

	if (isDead)
		return STATE_DEAD;

	if (m_isJump)
		info.force.y += 0.4f;
	else
		info.force.y = 0.f;
	info.position.y += info.force.y;

	return STATE_NO_EVENT;
}

void CItem::LateUpdate_Object() {
	CObj::Update_Rect_Object();
	if (rect.left < 50 || rect.right > WINCX - 50)
		info.force.x *= -1.f;
	if (rect.top < 50 || rect.bottom > WINCY - 50)
		info.force.y *= -1.f;

}

void CItem::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		TCHAR szBuffer[32];
		swprintf_s(szBuffer, L"%s \nHP : %d / %d", info.name, m_HP, m_MaxHP);
		RECT rc = rect;
		rc.top = rect.bottom;
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

