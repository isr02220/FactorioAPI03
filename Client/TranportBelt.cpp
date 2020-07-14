#include "TranportBelt.h"
#include "Entity.h"

CTranportBelt::CTranportBelt() : CEntity() {
    objectType = OBJ::ENTITY;
    strokeColor = RGB(128, 128, 255);
    fillColor = RGB(0, 255, 255);
}

CTranportBelt::~CTranportBelt() {
    Release_Object();
}

void CTranportBelt::Ready_Object() {
    info.iCX = 64;
    info.iCY = 64;
    info.CCX = 128;
    info.CCY = 128;
    speed = 3.f;
    MaxHP = 10;
    HP = MaxHP;
}

INT CTranportBelt::Update_Object() {
    info.position += (info.force * speed);
    CObj::Update_Rect_Object();
    if (dead) {
        return STATE_DEAD;
    }

    return STATE_NO_EVENT;
}

void CTranportBelt::LateUpdate_Object() {

}

void CTranportBelt::Render_Object(HDC hDC) {
    CObj::Update_Rect_Object();
    if (isVisible) {
        INT spriteFrameDelay = 2;
        HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-transport-belt");

        if (++spriteIndexX >= 16 * spriteFrameDelay) spriteIndexX = 0;

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

void CTranportBelt::Release_Object() {

}

void CTranportBelt::OnCollision(CObj* _TargetObj) {

}
