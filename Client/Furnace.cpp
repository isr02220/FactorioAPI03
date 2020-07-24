#include "Furnace.h"
#include "ResourceOre.h"
#include "Entity.h"
#include "FuelTank.h"
#include "ItemStack.h"
#include "Inventory.h"
#include "Item.h"
#include "FurnaceUI.h"
#include "FloatingText.h"
#include "CraftRecipe.h"
#include "RecipeManager.h"

CFurnace::CFurnace() : CEntity() {
	objectType = OBJ::ENTITY;
	lstrcpy(info.name, L"Furnace");
	fuelTank = new CFuelTank();
	inventory = new CInventory(1);
	outputInventory = new CInventory(1);
	rotatAble = false;
}

CFurnace::~CFurnace() {
	Release_Object();
}

void CFurnace::Ready_Object() {
	CObj* tempUi = CAbstractFactory<CFurnaceUI>::Create(WINCX >> 1, WINCY >> 2);
	CObjManager::GetInstance()->AddObject(tempUi, OBJ::UI);
	GUI = dynamic_cast<CUI*>(tempUi);
	dynamic_cast<CFurnaceUI*>(GUI)->targetActor = this;
	info.iCX = 128;
	info.iCY = 128;
	info.CCX = 192;
	info.CCY = 192;
	speed = 3.f;
	MaxHP = 10;
	HP = MaxHP;
	spriteFrameDelay = 1;
}

INT CFurnace::Update_Object() {
	info.position += (info.force * speed);

	CObj::Update_Rect_Object();
	if (dead) {
		return STATE_DEAD;
	}
	BurnItem(speed);
	return STATE_NO_EVENT;
}

void CFurnace::LateUpdate_Object() {

}

void CFurnace::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-stone-furnace");
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

void CFurnace::Render_Placable(HDC hDC, BOOL placable) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC;
		if (placable)
			hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-stone-furnace-placable");
		else
			hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-stone-furnace-unplacable");
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

void CFurnace::Release_Object() {
	Safe_Delete(fuelTank);
	dynamic_cast<CFurnaceUI*>(GUI)->targetActor = nullptr;
	GUI->SetDead();
}

void CFurnace::OnCollision(CObj* _TargetObj) {

}

CObj* CFurnace::GetNewActor() {
	CObj* tempObj = new CFurnace();
	tempObj->Ready_Object();
	return tempObj;
}

void CFurnace::BurnItem(FLOAT _speed) {
	BOOL burning = (fuelTank->SpendEnergy(0.05f) > 0.f && inventory->listItemStack.size() != 0);
	if (burning) {
		spriteIndexX = 1;
		progress++;
		if (progress >= 100.f) {
			CCraftRecipe* tempRecipe = CRecipeManager::GetInstance()->FindRecipe(L"ICON_copper-ore");
			outputInventory->PushItem(tempRecipe->Craft(inventory));
			progress = 0.f;
		}
	}
	else {
		spriteIndexX = 0;
		fuelTank->energy += 0.05f;
	}
}
