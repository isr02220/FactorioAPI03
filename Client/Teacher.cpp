#include "Teacher.h"
#include "Entity.h"
#include "Item.h"
#include "bullet.h"
#include "BurnerUI.h"
#include "FloatingText.h"

CTeacher::CTeacher() : CEntity() {
	objectType = OBJ::ENTITY;
	lstrcpy(info.name, L"¼±»ý´Ô");
}

CTeacher::~CTeacher() {
	Release_Object();
}

void CTeacher::Ready_Object() {
	info.iCX = 64;
	info.iCY = 64;
	info.CCX = 110;
	info.CCY = 128;
	speed = 3.f;
	MaxHP = 200;
	HP = MaxHP;
	spriteFrameDelay = 2;
	spriteIndexY = 6;
}

INT CTeacher::Update_Object() {
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

void CTeacher::LateUpdate_Object() {
	
}

void CTeacher::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		spriteFrameDelay = 4;
		spriteIndexX = 0;
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-level1_idle_gun");
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
			spriteIndexY * info.CCY,
			info.CCX,
			info.CCY,
			RGB(255, 0, 255));
	}

}


void CTeacher::Release_Object() {
}

void CTeacher::OnCollision(CObj* _TargetObj) {
	if (_TargetObj->GetObjectType() == OBJ::BULLET) {
		HP -= dynamic_cast<CBullet*>(_TargetObj)->m_damage;
	}
}

CObj* CTeacher::GetNewActor() {
	CObj* tempObj = new CTeacher();
	tempObj->Ready_Object();
	return tempObj;
}

CItem* CTeacher::GetNewItem() {
	CItem* tempItem = new CItem();
	return tempItem;
}
