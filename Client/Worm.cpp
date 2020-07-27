#include "Worm.h"
#include "Entity.h"
#include "Item.h"
#include "bullet.h"
#include "BurnerUI.h"

CWorm::CWorm() : CEntity() {
	objectType = OBJ::ENTITY;
	lstrcpy(info.name, L"¶¥±¼ ¹ú·¹");
}

CWorm::~CWorm() {
	Release_Object();
}

void CWorm::Ready_Object() {
	info.iCX = 320;
	info.iCY = 280;
	info.CCX = 480;
	info.CCY = 440;
	speed = 3.f;
	MaxHP = 200;
	HP = MaxHP;
	spriteFrameDelay = 4;
}

INT CWorm::Update_Object() {
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
			if (++spriteIndexX >= 12 * spriteFrameDelay) {
				Shoot();
				spriteIndexX = 0;
			}
		}
		else {
			spriteIndexX = 0;
		}
	}

	return STATE_NO_EVENT;
}

void CWorm::LateUpdate_Object() {
	
}

void CWorm::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC;
		if(HP <= 0)
			hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-worm-die");
		else {
			hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-worm-attack");
		}
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


void CWorm::Release_Object() {
}

void CWorm::OnCollision(CObj* _TargetObj) {
	if (_TargetObj->GetObjectType() == OBJ::BULLET) {
		HP -= dynamic_cast<CBullet*>(_TargetObj)->m_damage;
	}
}

CObj* CWorm::GetNewActor() {
	CObj* tempObj = new CWorm();
	tempObj->Ready_Object();
	return tempObj;
}

CItem* CWorm::GetNewItem() {
	CItem* tempItem = new CItem();
	return tempItem;
}

void CWorm::Shoot() {
	shootingState.shooting = true;
	shootingState.position = CObjManager::GetInstance()->GetPlayer()->GetPosition();

	FLOAT dx = shootingState.position.x - info.position.x;
	FLOAT dy = shootingState.position.y - info.position.y;
	FLOAT rad = atan2f(dy, dx);
	POSITION gunPos = info.position;
	if (rad < 0) rad += 2.f * pi;

	if (rad > 0 && rad <= pi / 8.f) {
		walkingState.direction = DIRECTION::DIR::EAST;
		gunPos += POSITION(51, -41);
	}
	else if (rad > pi / 8.f && rad <= pi / 8.f * 3.f) {
		walkingState.direction = DIRECTION::DIR::SOUTHEAST;
		gunPos += POSITION(30, -17);
	}
	else if (rad > pi / 8.f * 3.f && rad <= pi / 8.f * 5.f) {
		walkingState.direction = DIRECTION::DIR::SOUTH;
		gunPos += POSITION(0, -27);
	}
	else if (rad > pi / 8.f * 5.f && rad <= pi / 8.f * 7.f) {
		walkingState.direction = DIRECTION::DIR::SOUTHWEST;
		gunPos += POSITION(-35, -35);
	}
	else if (rad > pi / 8.f * 7.f && rad <= pi / 8.f * 9.f) {
		walkingState.direction = DIRECTION::DIR::WEST;
		gunPos += POSITION(-43, -52);
	}
	else if (rad > pi / 8.f * 9.f && rad <= pi / 8.f * 11.f) {
		walkingState.direction = DIRECTION::DIR::NORTHWEST;
		gunPos += POSITION(-38, -83);
	}
	else if (rad > pi / 8.f * 11.f && rad <= pi / 8.f * 13.f) {
		walkingState.direction = DIRECTION::DIR::NORTH;
		gunPos += POSITION(0, -86);
	}
	else if (rad > pi / 8.f * 13.f && rad <= pi / 8.f * 15.f) {
		walkingState.direction = DIRECTION::DIR::NORTHEAST;
		gunPos += POSITION(46, -47);
	}
	else {
		walkingState.direction = DIRECTION::DIR::EAST;
		gunPos += POSITION(51, -41);
	}
	if (shootingState.delay == 0) {
		shootingState.delay = 10;
		CObj* pBullet = new CBullet(ToDegree(rad), 10.f, 20, 10);
		pBullet->Ready_Object();
		pBullet->SetPosition(gunPos);
		CObjManager::GetInstance()->AddObject(pBullet, OBJ::MONSTERBULLET);
	}
}
