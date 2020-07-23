#include "Item.h"

CItem::CItem() : CObj(),
	group(ITEM::GROUP::INTERMEDIATE),
	subGroup(ITEM::SUBGROUP::INTERMEDIATE_ResourceFluid){
	objectType = OBJ::ITEM;
}

CItem::~CItem() {
	Release_Object();
}

void CItem::Ready_Object() {
	info.iCX = 32;
	info.iCY = 32;
	info.CCX = 32;
	info.CCY = 32;
}

INT CItem::Update_Object() {
	if (dead)
		return STATE_DEAD;
	CObj::Update_Rect_Object();
	if (info.position.x > -CScrollManager::GetInstance()->GetScrollX() &&
		info.position.x < -CScrollManager::GetInstance()->GetScrollX() + WINCX &&
		info.position.y > -CScrollManager::GetInstance()->GetScrollY() &&
		info.position.y < -CScrollManager::GetInstance()->GetScrollY() + WINCY)
		isVisible = true;
	else
		isVisible = false;
	return STATE_NO_EVENT;
}

void CItem::LateUpdate_Object() {

}

void CItem::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"ICON_coal");
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
			0,
			0,
			info.CCX,
			info.CCY,
			RGB(255, 0, 255));
	}

}

void CItem::Release_Object() {

}

void CItem::OnCollision(CObj* _TargetObj) {

}

CItem* CItem::GetNewItem() {
	return new CItem();
}
