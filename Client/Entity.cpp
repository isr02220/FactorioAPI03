#include "Actor.h"
#include "Entity.h"

CEntity::CEntity() : CActor(){
	objectType = OBJ::ENTITY;
    strokeColor = RGB(128, 128, 255);
    fillColor = RGB(0, 255, 255);
}

CEntity::CEntity(FLOAT _positionX, FLOAT _positionY) : CActor(_positionX, _positionY) {
	objectType = OBJ::ENTITY;
}

CEntity::~CEntity() {
	Release_Object();
}

void CEntity::Ready_Object() {
    info.iCX = 50;
    info.iCY = 50;
    speed = 3.f;
    MaxHP = 10;
    HP = MaxHP;
}

INT CEntity::Update_Object() {
    info.position += (info.force * speed);
    CObj::Update_Rect_Object();
    if (dead) {
        return STATE_DEAD;
    }

    return STATE_NO_EVENT;
}

void CEntity::LateUpdate_Object() {

}

void CEntity::Render_Object(HDC hDC) {
    CObj::Update_Rect_Object();
    if (isVisible) {
        HPEN   hPen = CreatePen(PS_SOLID, 1, strokeColor);
        HBRUSH hBrush = CreateSolidBrush(fillColor);

        HPEN   oldPen = (HPEN)SelectObject(hDC, hPen);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
        CScrollManager* scrollMgr =  CScrollManager::GetInstance();
        Rectangle(hDC, rect.left + scrollMgr->GetScrollX(),
            rect.top + scrollMgr->GetScrollY(),
            rect.right + scrollMgr->GetScrollX(),
            rect.bottom + scrollMgr->GetScrollY());

        SelectObject(hDC, oldPen);
        SelectObject(hDC, oldBrush);
        DeleteObject(hPen);
        DeleteObject(hBrush);

    }
}

void CEntity::Release_Object() {

}

void CEntity::OnCollision(CObj* _TargetObj) {

}
