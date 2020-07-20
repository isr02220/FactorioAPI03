#include "BurnerDrill.h"
#include "Entity.h"

CBurnerDrill::CBurnerDrill() : CEntity() {
	objectType = OBJ::ENTITY;
	lstrcpy(info.name, L"BurnerDrill");
	strokeColor = RGB(128, 128, 255);
	fillColor = RGB(0, 255, 255);
}

CBurnerDrill::~CBurnerDrill() {
	Release_Object();
}

void CBurnerDrill::Ready_Object() {
	info.iCX = 128;
	info.iCY = 128;
	info.CCX = 200;
	info.CCY = 200;
	speed = 3.f;
	MaxHP = 10;
	HP = MaxHP;
	spriteFrameDelay = 2;
}

INT CBurnerDrill::Update_Object() {
	info.position += (info.force * speed);

	CObj::Update_Rect_Object();
	if (dead) {
		return STATE_DEAD;
	}
	if (miningState.mining && ++spriteIndexX >= 8) spriteIndexX = 0;

	switch (walkingState.direction) {
	case DIRECTION::DIR::NORTH:
		spriteIndexY = 2;
		break;
	case DIRECTION::DIR::EAST:
		spriteIndexY = 0;
		break;
	case DIRECTION::DIR::SOUTH:
		spriteIndexY = 3;
		break;
	case DIRECTION::DIR::WEST:
		spriteIndexY = 1;
		break;
	default:
		spriteIndexY = 2;
		break;
	}
	return STATE_NO_EVENT;
}

void CBurnerDrill::LateUpdate_Object() {

}

void CBurnerDrill::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-burner-mining-drill");
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

void CBurnerDrill::Render_Placable(HDC hDC, BOOL placable) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC;
		if (placable)
			hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-burner-mining-drill-placable");
		else
			hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-burner-mining-drill-unplacable");
		if (nullptr == hMemDC)
			return;
		switch (walkingState.direction) {
		case DIRECTION::DIR::NORTH:
			spriteIndexY = 2;
			break;
		case DIRECTION::DIR::EAST:
			spriteIndexY = 0;
			break;
		case DIRECTION::DIR::SOUTH:
			spriteIndexY = 3;
			break;
		case DIRECTION::DIR::WEST:
			spriteIndexY = 1;
			break;
		default:
			spriteIndexY = 2;
			break;
		}
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

void CBurnerDrill::Release_Object() {

}

void CBurnerDrill::OnCollision(CObj* _TargetObj) {

}

CObj* CBurnerDrill::GetNewActor() {
	CObj* tempObj = new CBurnerDrill();
	tempObj->Ready_Object();
	return tempObj;
}
