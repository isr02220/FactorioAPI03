#include "BurnerInserter.h"
#include "Entity.h"
#include "Item.h"
#include "IronChest.h"
#include "Inventory.h"
CBurnerInserter::CBurnerInserter() : CEntity() {
    objectType = OBJ::ENTITY;
	SetName(L"BurnerInserter");
}

CBurnerInserter::~CBurnerInserter() {
    Release_Object();
}

void CBurnerInserter::Ready_Object() {
    info.iCX = 64;
    info.iCY = 64;
    info.CCX = 192;
    info.CCY = 192;
    speed = 3.f;
    MaxHP = 10;
    HP = MaxHP;
    spriteFrameDelay = 4;
}

INT CBurnerInserter::Update_Object() {
    info.position += (info.force * speed);

    CObj::Update_Rect_Object();
    if (dead) {
        return STATE_DEAD;
    }
    SetSpriteDir();
	TransportItem();
    return STATE_NO_EVENT;
}

void CBurnerInserter::LateUpdate_Object() {

}

void CBurnerInserter::Render_Object(HDC hDC) {
    CObj::Update_Rect_Object();
    if (isVisible) {
        HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-inserter");
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

void CBurnerInserter::Render_Placable(HDC hDC, BOOL placable) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC;
		if(placable)
			hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-inserter-placable");
		else
			hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-inserter-unplacable");
		if (nullptr == hMemDC)
			return;
		
        SetSpriteDir();
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

void CBurnerInserter::Release_Object() {

}

void CBurnerInserter::OnCollision(CObj* _TargetObj) {

}

void CBurnerInserter::TransportItem() {
    if (pickedItem == nullptr && spriteIndexX == 0) {
        if ((*CObjManager::GetInstance()->GetVector(OBJ::ENTITY))[PosToIndex((info.position * 2.f) - outputPos)] &&
            !lstrcmp((*CObjManager::GetInstance()->GetVector(OBJ::ENTITY))[PosToIndex((info.position * 2.f) - outputPos)]->GetName(), L"IronChest")) {
            pickedItem = dynamic_cast<CIronChest*>((*CObjManager::GetInstance()->GetVector(OBJ::ENTITY))[PosToIndex((info.position * 2.f) - outputPos)])->inventory->PopItem();
            if (pickedItem) {
                pickingState = true;
                Timer = GetTickCount();
            }
        }
        else {
            list<CObj*>* itemList = CObjManager::GetInstance()->GetList(OBJ::ITEM);
            POINT pt = {};
            for (auto iter = itemList->begin(); iter != itemList->end();) {
                pt.x = (INT)(*iter)->GetPosition().x;
                pt.y = (INT)(*iter)->GetPosition().y;
                if (PtInRect(&inputRect, pt)) {
                    pickedItem = *iter;
                    itemList->erase(iter);
                    pickedItem->SetPosition(info.position);
                    Timer = GetTickCount();
                    pickingState = true;
                    break;
                }
                iter++;
            }
        }
    }
    else if (pickedItem) {
        if (Timer + 600 < GetTickCount()) {

            if ((*CObjManager::GetInstance()->GetVector(OBJ::ENTITY))[PosToIndex(outputPos)] && 
                !lstrcmp((*CObjManager::GetInstance()->GetVector(OBJ::ENTITY))[PosToIndex(outputPos)]->GetName(), L"IronChest")) {
                CActor* outputActor = dynamic_cast<CActor*>((*CObjManager::GetInstance()->GetVector(OBJ::ENTITY))[PosToIndex(outputPos)]);
                if (outputActor->inventory) {
                    outputActor->inventory->PushItem(dynamic_cast<CItem*>(pickedItem));
                    pickingState = false;
                    pickedItem = nullptr;
                    Timer = GetTickCount();
                }
            }
            else {
                list<CObj*>* itemList = CObjManager::GetInstance()->GetList(OBJ::ITEM);
                POINT pt = {};
                pt.x = (INT)outputPos.x;
                pt.y = (INT)outputPos.y;
                BOOL dropable = true;
                for (auto iter = itemList->begin(); iter != itemList->end();) {
                    if (PtInRect((*iter)->GetRect(), pt)) {
                        dropable = false;
                        break;
                    }
                    iter++;
                }
                if (dropable) {
                    pickedItem->SetPosition(outputPos);
                    CObjManager::GetInstance()->AddObject(pickedItem, OBJ::ITEM);
                    pickingState = false;
                    pickedItem = nullptr;
                    Timer = GetTickCount();
                }
            }
        }
    }

    if (pickingState) {
        if (spriteIndexX < 8 * spriteFrameDelay) spriteIndexX++;
    }
    else {
        if (spriteIndexX > 0) spriteIndexX--;
    }
}

CObj* CBurnerInserter::GetNewActor() {
	CObj* tempObj = new CBurnerInserter();
	tempObj->Ready_Object();
	return tempObj;
}

void CBurnerInserter::SetSpriteDir() {
    switch (walkingState.direction) {
    case DIRECTION::DIR::NORTH:
        CopyRect(&inputRect, &rect);
        OffsetRect(&inputRect, 0, 64);
        outputPos = info.position + POSITION(0, -84);
        spriteIndexY = 2;
        break;
    case DIRECTION::DIR::EAST:
        CopyRect(&inputRect, &rect);
        OffsetRect(&inputRect, -64, 0);
        outputPos = info.position + POSITION(84, 0);
        spriteIndexY = 0;
        break;
    case DIRECTION::DIR::SOUTH:
        CopyRect(&inputRect, &rect);
        OffsetRect(&inputRect, 0, -64);
        outputPos = info.position + POSITION(0, 84);
        spriteIndexY = 3;
        break;
    case DIRECTION::DIR::WEST:
        CopyRect(&inputRect, &rect);
        OffsetRect(&inputRect, 64, 0);
        outputPos = info.position + POSITION(-84, 0);
        spriteIndexY = 1;
        break;
    default:
        CopyRect(&inputRect, &rect);
        OffsetRect(&inputRect, 0, 64);
        outputPos = info.position + POSITION(0, -84);
        spriteIndexY = 2;
        break;
    }
}
