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
    
    spriteIndexY = (INT)walkingState.direction;
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
    switch (walkingState.direction) {
    case DIRECTION::DIR::NORTH: {
        switch (tailBelt->GetWalkingState().direction) {
        case DIRECTION::DIR::NORTH:
            break;
        case DIRECTION::DIR::EAST:
            break;
        case DIRECTION::DIR::SOUTH:
            break;
        case DIRECTION::DIR::WEST:
            break;
        default:
            break;
        }
        break;
    }
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
        break;
    }
    spriteIndexY = (INT)walkingState.direction;

}

void CTranportBelt::GetBeltConnect() {
    POSITION pos;
    headBelt = nullptr;
    tailBelt = nullptr;
    switch (walkingState.direction) {
    case DIRECTION::DIR::NORTH: 
        pos = POSITION(0.f, -64.f);
        break;
    case DIRECTION::DIR::EAST:
        pos = POSITION(64.f, 0.f);
        break;
    case DIRECTION::DIR::SOUTH:
        pos = POSITION(0.f, 64.f);
        break;
    case DIRECTION::DIR::WEST:
        pos = POSITION(-64.f, 0.f);
        break;
    default:
        break;
    }
    pos += info.position;
    for (auto DstObj : *CObjManager::GetInstance()->GetList(OBJ::ENTITY)) {
        if (pos.x >= DstObj->GetInfo()->position.x - (DstObj->GetInfo()->iCX >> 1) &&
            pos.x <= DstObj->GetInfo()->position.x + (DstObj->GetInfo()->iCX >> 1) &&
            pos.y >= DstObj->GetInfo()->position.y - (DstObj->GetInfo()->iCY >> 1) &&
            pos.y <= DstObj->GetInfo()->position.y + (DstObj->GetInfo()->iCY >> 1)) {
            headBelt = dynamic_cast<CTranportBelt*>(DstObj);
            break;
        }
    }

    switch (walkingState.direction) {
    case DIRECTION::DIR::NORTH:
        pos = POSITION(0.f, 64.f);
        break;
    case DIRECTION::DIR::EAST:
        pos = POSITION(-64.f, 0.f);
        break;
    case DIRECTION::DIR::SOUTH:
        pos = POSITION(0.f, -64.f);
        break;
    case DIRECTION::DIR::WEST:
        pos = POSITION(64.f, 0.f);
        break;
    default:
        break;
    }
    pos += info.position;
    for (auto DstObj : *CObjManager::GetInstance()->GetList(OBJ::ENTITY)) {
        if (pos.x >= DstObj->GetInfo()->position.x - (DstObj->GetInfo()->iCX >> 1) &&
            pos.x <= DstObj->GetInfo()->position.x + (DstObj->GetInfo()->iCX >> 1) &&
            pos.y >= DstObj->GetInfo()->position.y - (DstObj->GetInfo()->iCY >> 1) &&
            pos.y <= DstObj->GetInfo()->position.y + (DstObj->GetInfo()->iCY >> 1)) {
            tailBelt = dynamic_cast<CTranportBelt*>(DstObj);
            break;
        }
    }
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

    pt.x = info.position.x;
    pt.y = info.position.y;

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
        break;
    case DIRECTION::DIR::EAST:
        headBelt = tempStarBelt;
        tailBelt = tempPortBelt;
        portBelt = tempHeadBelt;
        starBelt = tempTailBelt;
        break;     
    case DIRECTION::DIR::SOUTH:
        headBelt = tempTailBelt;
        tailBelt = tempHeadBelt;
        portBelt = tempStarBelt;
        starBelt = tempPortBelt;
        break;
    case DIRECTION::DIR::WEST:
        headBelt = tempPortBelt;
        tailBelt = tempStarBelt;
        portBelt = tempTailBelt;
        starBelt = tempHeadBelt;
        break;
    default:
        break;
    }
}