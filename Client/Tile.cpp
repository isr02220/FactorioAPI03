#include "Tile.h"

void CTile::Ready_Object() {
    info.iCX = TILECX;
    info.iCY = TILECY;
    info.CCX = TILECX;
    info.CCY = TILECY;
}

INT CTile::Update_Object() {

    return 0;
}

void CTile::LateUpdate_Object() {

}

void CTile::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"dirt");
	if (nullptr == hMemDC)
		return;
	int iScrollX = CScrollManager::GetInstance()->GetScrollX();
	int iScrollY = CScrollManager::GetInstance()->GetScrollY();
	BitBlt(hDC, rect.left + iScrollX, rect.top + iScrollY, info.iCX, info.iCY, hMemDC, 0, 0, SRCCOPY);
}

void CTile::Release_Object() {

}

void CTile::OnCollision(CObj* _TargetObj) {

}
