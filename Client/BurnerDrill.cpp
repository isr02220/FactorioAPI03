#include "BurnerDrill.h"
#include "ResourceOre.h"
#include "Entity.h"
#include "IronChest.h"
#include "Inventory.h"
#include "Item.h"
#include "BurnerUI.h"
#include "FloatingText.h"

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
	CObj* tempUi = CAbstractFactory<CBurnerUI>::Create(WINCX >> 1, WINCY >> 2);
	CObjManager::GetInstance()->AddObject(tempUi, OBJ::UI);
	GUI = dynamic_cast<CUI*>(tempUi);
	dynamic_cast<CBurnerUI*>(GUI)->targetActor = this;
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

	SetSpriteDir();
	SetOutputPos();
	GatherResourceOre(speed);
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

void CBurnerDrill::Release_Object() {

}

void CBurnerDrill::OnCollision(CObj* _TargetObj) {

}

CObj* CBurnerDrill::GetNewActor() {
	CObj* tempObj = new CBurnerDrill();
	tempObj->Ready_Object();
	return tempObj;
}

void CBurnerDrill::GatherResourceOre(FLOAT speed) {
	INT startX = INT(info.position.x - GRIDCX * 4) / GRIDCX;
	INT startY = INT(info.position.y - GRIDCY * 4) / GRIDCY;
	INT endX   = INT(info.position.x + GRIDCX * 4) / GRIDCX;
	INT endY   = INT(info.position.y + GRIDCY * 4) / GRIDCY;
	if (miningState.target == nullptr || miningState.target->storage < 0) {
		vector<CObj*>* vecResourceOre = CObjManager::GetInstance()->GetVector(OBJ::RESOURCEORE);
		for (INT y = startY; y < endY; y++) {
			for (INT x = startX; x < endX; x++) {
				if ((*vecResourceOre)[(y * GRIDX) + x] == nullptr)
					continue;
				RECT rc = {};
				if (IntersectRect(&rc, &rect, (*vecResourceOre)[(y * GRIDX) + x]->GetRect())) {
					miningState.mining = true;
					miningState.target = dynamic_cast<CResourceOre*>((*vecResourceOre)[(y * GRIDX) + x]);
				}

			}
		}
	}
	else {
		if (miningState.mining && ++spriteIndexX >= 8) spriteIndexX = 0;
		if (Timer + 1500 < GetTickCount()) {
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
				miningState.mining = true;
				CObj* tempObj = dynamic_cast<CResourceOre*>(miningState.target)->Gather();
				if (tempObj == nullptr)
					return;

				if ((*CObjManager::GetInstance()->GetVector(OBJ::ENTITY))[PosToIndex(outputPos)] &&
					!lstrcmp((*CObjManager::GetInstance()->GetVector(OBJ::ENTITY))[PosToIndex(outputPos)]->GetName(), L"IronChest")) {
					CActor* outputActor = dynamic_cast<CActor*>((*CObjManager::GetInstance()->GetVector(OBJ::ENTITY))[PosToIndex(outputPos)]);
					if (outputActor->inventory) {
						outputActor->inventory->PushItem(dynamic_cast<CItem*>(tempObj));
					}
				}
				else {
					tempObj->SetPosition(outputPos);
					CObjManager::GetInstance()->AddObject(tempObj, OBJ::ITEM);
				}
				Timer = GetTickCount();
			}
		}
	}

}

void CBurnerDrill::SetOutputPos() {
	switch (walkingState.direction) {
	case DIRECTION::DIR::NORTH:
		outputPos = info.position + POSITION(-16.f, -80.f);
		break;
	case DIRECTION::DIR::EAST:
		outputPos = info.position + POSITION(80.f, -16.f);
		break;
	case DIRECTION::DIR::SOUTH:
		outputPos = info.position + POSITION(16.f, 80.f);
		break;
	case DIRECTION::DIR::WEST:
		outputPos = info.position + POSITION(-80.f, 16.f);
		break;
	default:
		outputPos = info.position + POSITION(-16.f, -80.f);
		break;
	}
}
