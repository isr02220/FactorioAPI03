#include "CrashSite.h"
#include "Entity.h"
#include "Item.h"
#include "bullet.h"
#include "BurnerUI.h"

CCrashSite::CCrashSite() : CEntity() {
	objectType = OBJ::ENTITY;
	lstrcpy(info.name, L"ºÎ¼­Áø ÀÜÇØ");
}

CCrashSite::~CCrashSite() {
	Release_Object();
}

void CCrashSite::Ready_Object() {
	info.iCX = 128;
	info.iCY = 128;
	info.CCX = 282;
	info.CCY = 182;
	speed = 3.f;
	MaxHP = 200;
	HP = MaxHP;
	spriteFrameDelay = 2;
}

INT CCrashSite::Update_Object() {
	info.position += (info.force * speed);

	CObj::Update_Rect_Object();
	if (dead) {
		return STATE_DEAD;
	}
	if (HP <= 0 && MaxHP) {
		Timer = GetTickCount();
		MaxHP = 0;
		spriteIndexX = 0;
	}
	if (HP <= 0) {
		if (Timer + 8000 < GetTickCount()) {
			SetDead();
		}
     	if (spriteIndexX < 7 * spriteFrameDelay) spriteIndexX++;
	}
	else {
		if (shootingState.delay > 0) shootingState.delay--;
		POSITION playerPos = CObjManager::GetInstance()->GetPlayer()->GetPosition();
		if (info.position.x - playerPos.x < 800) {
			if (++spriteIndexX >= 20 * spriteFrameDelay) {
				spriteIndexX = 0;
			}
		}
		else {
			spriteIndexX = 0;
		}
	}

	return STATE_NO_EVENT;
}

void CCrashSite::LateUpdate_Object() {
	
}

void CCrashSite::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-crash-site");
		if (nullptr == hMemDC)
			return;
		INT iScrollX = (INT)CScrollManager::GetInstance()->GetScrollX();
		INT iScrollY = (INT)CScrollManager::GetInstance()->GetScrollY();

		GdiTransparentBlt(hDC,
			cRect.left + iScrollX,
			cRect.top + iScrollY,
			info.CCX,
			info.CCY,
			hMemDC,
			spriteIndexX / spriteFrameDelay * info.CCX,
			0,
			info.CCX,
			info.CCY,
			RGB(255, 0, 255));
	}

}


void CCrashSite::Release_Object() {
}

void CCrashSite::OnCollision(CObj* _TargetObj) {
	if (_TargetObj->GetObjectType() == OBJ::BULLET) {
		HP -= dynamic_cast<CBullet*>(_TargetObj)->m_damage;
	}
}

CObj* CCrashSite::GetNewActor() {
	CObj* tempObj = new CCrashSite();
	tempObj->Ready_Object();
	return tempObj;
}

CItem* CCrashSite::GetNewItem() {
	CItem* tempItem = new CItem();
	return tempItem;
}
