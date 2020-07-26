#include "BurnerInserter.h"
#include "ItemBurnerInserter.h"
#include "Entity.h"
#include "Item.h"
#include "IronChest.h"
#include "FuelTank.h"
#include "Inventory.h"
CBurnerInserter::CBurnerInserter() : CEntity() {
    objectType = OBJ::ENTITY;
	SetName(L"ÅõÀÔ±â");
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
        CActor* tActor = dynamic_cast<CActor*>((*CObjManager::GetInstance()->GetVector(OBJ::ENTITY))[PosToIndex((info.position * 2.f) - outputPos)]);
        INT startX = INT(((info.position * 2.f) - outputPos).x - GRIDCX * 4) / GRIDCX;
        INT startY = INT(((info.position * 2.f) - outputPos).y - GRIDCY * 4) / GRIDCY;
        INT endX   = INT(((info.position * 2.f) - outputPos).x + GRIDCX * 4) / GRIDCX;
        INT endY   = INT(((info.position * 2.f) - outputPos).y + GRIDCY * 4) / GRIDCY;
        POINT pt = {};
        pt.x = (INT)((info.position * 2.f) - outputPos).x;
        pt.y = (INT)((info.position * 2.f) - outputPos).y;
        vector<CObj*>* vecEntity = CObjManager::GetInstance()->GetVector(OBJ::ENTITY);
        for (INT y = startY; y < endY; y++) {
            for (INT x = startX; x < endX; x++) {
                if ((*vecEntity)[(y * GRIDX) + x] == nullptr)
                    continue;
                RECT rc = {};
                if (PtInRect((*vecEntity)[(y * GRIDX) + x]->GetRect(), pt)) {
                    tActor = dynamic_cast<CActor*>((*vecEntity)[(y * GRIDX) + x]);
                    break;
                }

            }
        }
        if(tActor) {
            if(tActor->outputInventory)
                pickedItem = tActor->outputInventory->PopItem();
            else if (tActor->inventory)
                pickedItem = tActor->inventory->PopItem();
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
        tActor = nullptr;
        startX = INT(outputPos.x - GRIDCX * 4) / GRIDCX;
        startY = INT(outputPos.y - GRIDCY * 4) / GRIDCY;
        endX   = INT(outputPos.x + GRIDCX * 4) / GRIDCX;
        endY   = INT(outputPos.y + GRIDCY * 4) / GRIDCY;
        pt.x = (INT)outputPos.x;
        pt.y = (INT)outputPos.y;
        for (INT y = startY; y < endY; y++) {
            for (INT x = startX; x < endX; x++) {
                if ((*vecEntity)[(y * GRIDX) + x] == nullptr)
                    continue;
                RECT rc = {};
                if (PtInRect((*vecEntity)[(y * GRIDX) + x]->GetRect(), pt)) {
                    tActor = dynamic_cast<CActor*>((*vecEntity)[(y * GRIDX) + x]);
                    break;
                }

            }
        }
        if (tActor && (tActor->inventory || tActor->fuelTank)) {
                outputActor = tActor;
        }
        else {
            outputActor = nullptr;
        }
    }
    else if (pickedItem) {
        if (Timer + 600 < GetTickCount()) {

            if (outputActor) {
                if (outputActor->fuelTank && dynamic_cast<CItem*>(pickedItem)->isFuel) {
                    outputActor->fuelTank->PushItem(dynamic_cast<CItem*>(pickedItem));
                        pickingState = false;
                        pickedItem = nullptr;
                        Timer = GetTickCount();
                }
                else if (outputActor->inventory) {
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

CItem* CBurnerInserter::GetNewItem() {
	CItem* tempItem = new CItemBurnerInserter();
	return tempItem;
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
