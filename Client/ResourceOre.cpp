#include "ResourceOre.h"
#include "Entity.h"

CResourceOre::CResourceOre() : CActor() {
	objectType = OBJ::RESOURCEORE;
	strokeColor = RGB(128, 128, 255);
	fillColor = RGB(0, 255, 255);
}

CResourceOre::~CResourceOre() {
	Release_Object();
}

void CResourceOre::Ready_Object() {
	info.iCX = 32;
	info.iCY = 32;
	info.CCX = 128;
	info.CCY = 128;
	speed = 3.f;
	MaxHP = 10;
	HP = MaxHP;
	spriteIndexX = rand() % 8;
}

INT CResourceOre::Update_Object() {
	CObj::Update_Rect_Object();
	if (dead) {
		return STATE_DEAD;
	}
	return STATE_NO_EVENT;
}

void CResourceOre::LateUpdate_Object() {

}

void CResourceOre::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-transport-belt");
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
			spriteIndexX * info.CCX,
			spriteIndexY * info.CCY,
			info.CCX,
			info.CCY,
			RGB(255, 0, 255));
	}

}

void CResourceOre::Release_Object() {

}

void CResourceOre::OnCollision(CObj* _TargetObj) {

}

void CResourceOre::Gather() {
	if (storage) {
		storage--;
		spriteIndexY = 8 - (storage / 100);
		if (spriteIndexY < 0) spriteIndexY = 0;
	}
	else {
		SetDead();
	}
}
