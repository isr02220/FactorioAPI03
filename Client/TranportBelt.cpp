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

    GetBeltConnect();

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


        //Rectangle(hDC, rect.left + iScrollX,
        //    rect.top + iScrollY,
        //    rect.right + iScrollX,
        //    rect.bottom + iScrollY);

        //BitBlt(hDC,
        //    cRect.left + iScrollX,
        //    cRect.top + iScrollY,
        //    info.CCX,
        //    info.CCY,
        //    hMemDC,
        //    spriteIndexX / spriteFrameDelay * info.CCX,
        //    spriteIndexY * info.CCY,
        //    SRCCOPY
        //);

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

void CTranportBelt::SetIndexY() {
    GetBeltConnect();
}

void CTranportBelt::GetBeltConnect() {
    POINT pt;
    headBelt = nullptr;
    tailBelt = nullptr;
    portBelt = nullptr;
    starBelt = nullptr;
    CTranportBelt* tempHeadBelt = nullptr;
    CTranportBelt* tempTailBelt = nullptr;
    CTranportBelt* tempPortBelt = nullptr;
    CTranportBelt* tempStarBelt = nullptr;

    pt.x = (LONG)info.position.x;
    pt.y = (LONG)info.position.y;

    pt.y -= 64;
    //pt.y += 64;
    for (auto DstObj : *CObjManager::GetInstance()->GetList(OBJ::ENTITY)) {
        if (PtInRect(DstObj->GetRect(), pt)) {
            tempHeadBelt = dynamic_cast<CTranportBelt*>(DstObj);
            break;
        }
    }
    pt.y += 128;
    for (auto DstObj : *CObjManager::GetInstance()->GetList(OBJ::ENTITY)) {
        if (PtInRect(DstObj->GetRect(), pt)) {
            tempTailBelt = dynamic_cast<CTranportBelt*>(DstObj);
            break;
        }
    }
    pt.y -= 64;
    pt.x -= 64;
    for (auto DstObj : *CObjManager::GetInstance()->GetList(OBJ::ENTITY)) {
        if (PtInRect(DstObj->GetRect(), pt)) {
            tempPortBelt = dynamic_cast<CTranportBelt*>(DstObj);
            break;
        }
    }
    pt.x += 128;
    for (auto DstObj : *CObjManager::GetInstance()->GetList(OBJ::ENTITY)) {
        if (PtInRect(DstObj->GetRect(), pt)) {
            tempStarBelt = dynamic_cast<CTranportBelt*>(DstObj);
            break;
        }
    }

    switch (walkingState.direction) {
    case DIRECTION::DIR::NORTH:
        headBelt = tempHeadBelt;
        tailBelt = tempTailBelt;
        portBelt = tempPortBelt;
        starBelt = tempStarBelt;
        if (portBelt && starBelt) {
            if (portBelt->GetWalkingState().direction == DIRECTION::DIR::EAST &&
                starBelt->GetWalkingState().direction != DIRECTION::DIR::WEST)
                spriteIndexY = 6;
            else if (portBelt->GetWalkingState().direction != DIRECTION::DIR::EAST &&
                starBelt->GetWalkingState().direction == DIRECTION::DIR::WEST) 
                spriteIndexY = 4;
            else 
                spriteIndexY = 2;
        }
        else if (portBelt) {
            if (portBelt->GetWalkingState().direction == DIRECTION::DIR::EAST)
                spriteIndexY = 6;
            else
                spriteIndexY = 2;
        }
        else if (starBelt) {
            if (starBelt->GetWalkingState().direction == DIRECTION::DIR::WEST)
                spriteIndexY = 4;
            else 
                spriteIndexY = 2;
        }
        else {
            spriteIndexY = 2;
        }
        break;
    case DIRECTION::DIR::EAST:
        headBelt = tempStarBelt;
        tailBelt = tempPortBelt;
        portBelt = tempHeadBelt;
        starBelt = tempTailBelt;
        if (portBelt && starBelt) {
            if (portBelt->GetWalkingState().direction == DIRECTION::DIR::SOUTH &&
                starBelt->GetWalkingState().direction != DIRECTION::DIR::NORTH)
                spriteIndexY = 5;
            else if (portBelt->GetWalkingState().direction != DIRECTION::DIR::SOUTH &&
                starBelt->GetWalkingState().direction == DIRECTION::DIR::NORTH)
                spriteIndexY = 8;
            else
                spriteIndexY = 0;
        }
        else if (portBelt) {
            if (portBelt->GetWalkingState().direction == DIRECTION::DIR::SOUTH)
                spriteIndexY = 5;
            else
                spriteIndexY = 0;
        }
        else if (starBelt) {
            if (starBelt->GetWalkingState().direction == DIRECTION::DIR::NORTH)
                spriteIndexY = 8;
            else
                spriteIndexY = 0;
        }
        else {
            spriteIndexY = 0;
        }
        break;     
    case DIRECTION::DIR::SOUTH:
        headBelt = tempTailBelt;
        tailBelt = tempHeadBelt;
        portBelt = tempStarBelt;
        starBelt = tempPortBelt;
        if (portBelt && starBelt) {
            if (portBelt->GetWalkingState().direction == DIRECTION::DIR::WEST &&
                starBelt->GetWalkingState().direction != DIRECTION::DIR::EAST)
                spriteIndexY = 9;
            else if (portBelt->GetWalkingState().direction != DIRECTION::DIR::WEST &&
                starBelt->GetWalkingState().direction == DIRECTION::DIR::EAST)
                spriteIndexY = 11;
            else
                spriteIndexY = 3;
        }
        else if (portBelt) {
            if (portBelt->GetWalkingState().direction == DIRECTION::DIR::WEST)
                spriteIndexY = 9;
            else
                spriteIndexY = 3;
        }
        else if (starBelt) {
            if (starBelt->GetWalkingState().direction == DIRECTION::DIR::EAST)
                spriteIndexY = 11;
            else
                spriteIndexY = 3;
        }
        else {
            spriteIndexY = 3;
        }
        break;
    case DIRECTION::DIR::WEST:
        headBelt = tempPortBelt;
        tailBelt = tempStarBelt;
        portBelt = tempTailBelt;
        starBelt = tempHeadBelt;
        if (portBelt && starBelt) {
            if (portBelt->GetWalkingState().direction == DIRECTION::DIR::NORTH &&
                starBelt->GetWalkingState().direction != DIRECTION::DIR::SOUTH)
                spriteIndexY = 10;
            else if (portBelt->GetWalkingState().direction != DIRECTION::DIR::NORTH &&
                starBelt->GetWalkingState().direction == DIRECTION::DIR::SOUTH)
                spriteIndexY = 7;
            else
                spriteIndexY = 1;
        }
        else if (portBelt) {
            if (portBelt->GetWalkingState().direction == DIRECTION::DIR::NORTH)
                spriteIndexY = 10;
            else
                spriteIndexY = 1;
        }
        else if (starBelt) {
            if (starBelt->GetWalkingState().direction == DIRECTION::DIR::SOUTH)
                spriteIndexY = 7;
            else
                spriteIndexY = 1;
        }
        else {
            spriteIndexY = 1;
        }
        break;
    default:
        headBelt = tempHeadBelt;
        tailBelt = tempTailBelt;
        portBelt = tempPortBelt;
        starBelt = tempStarBelt;
        if (portBelt && starBelt) {
            if (portBelt->GetWalkingState().direction == DIRECTION::DIR::EAST &&
                starBelt->GetWalkingState().direction != DIRECTION::DIR::WEST)
                spriteIndexY = 6;
            else if (portBelt->GetWalkingState().direction != DIRECTION::DIR::EAST &&
                starBelt->GetWalkingState().direction == DIRECTION::DIR::WEST)
                spriteIndexY = 4;
            else
                spriteIndexY = 2;
        }
        else if (portBelt) {
            if (portBelt->GetWalkingState().direction == DIRECTION::DIR::EAST)
                spriteIndexY = 6;
            else
                spriteIndexY = 2;
        }
        else if (starBelt) {
            if (starBelt->GetWalkingState().direction == DIRECTION::DIR::WEST)
                spriteIndexY = 4;
            else
                spriteIndexY = 2;
        }
        else {
            spriteIndexY = 2;
        }
        break;
    }
}