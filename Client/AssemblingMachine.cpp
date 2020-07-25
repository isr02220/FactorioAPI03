#include "AssemblingMachine.h"
#include "Entity.h"
#include "ItemStack.h"
#include "Inventory.h"
#include "Item.h"
#include "AssemblingMachineUI.h"
#include "CraftRecipe.h"
#include "RecipeManager.h"

CAssemblingMachine::CAssemblingMachine() : CEntity() {
	objectType = OBJ::ENTITY;
	lstrcpy(info.name, L"조립 기계");
	inventory = new CInventory(3);
	outputInventory = new CInventory(1);
	rotatAble = false;
}

CAssemblingMachine::~CAssemblingMachine() {
	Release_Object();
}

void CAssemblingMachine::Ready_Object() {
	CObj* tempUi = CAbstractFactory<CAssemblingMachineUI>::Create(WINCX >> 1, WINCY >> 2);
	CObjManager::GetInstance()->AddObject(tempUi, OBJ::UI);
	GUI = dynamic_cast<CUI*>(tempUi);
	dynamic_cast<CAssemblingMachineUI*>(GUI)->targetActor = this;
	info.iCX = 128;
	info.iCY = 128;
	info.CCX = 214;
	info.CCY = 226;
	speed = 3.f;
	MaxHP = 10;
	HP = MaxHP;
	spriteFrameDelay = 2;
}

INT CAssemblingMachine::Update_Object() {
	info.position += (info.force * speed);

	CObj::Update_Rect_Object();
	if (dead) {
		return STATE_DEAD;
	}
	CraftItem(speed);
	return STATE_NO_EVENT;
}

void CAssemblingMachine::LateUpdate_Object() {

}

void CAssemblingMachine::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-assembling-machine");
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

void CAssemblingMachine::Render_Placable(HDC hDC, BOOL placable) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC;
		if (placable)
			hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-assembling-machine-placable");
		else
			hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-assembling-machine-unplacable");
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

void CAssemblingMachine::Release_Object() {
	Safe_Delete(fuelTank);
	dynamic_cast<CAssemblingMachineUI*>(GUI)->targetActor = nullptr;
	GUI->SetDead();
}

void CAssemblingMachine::OnCollision(CObj* _TargetObj) {

}

CObj* CAssemblingMachine::GetNewActor() {
	CObj* tempObj = new CAssemblingMachine();
	tempObj->Ready_Object();
	return tempObj;
}

void CAssemblingMachine::CraftItem(FLOAT _speed) {
	recipe = CRecipeManager::GetInstance()->FindRecipe(L"ICON_copper-cable");
	
	BOOL Crafting = (recipe && recipe->isCraftable(inventory));

	if (Crafting) {
		if (++spriteIndexX >= 16 * spriteFrameDelay)
			spriteIndexX = 0;
		progress++;
		if (progress >= 100.f) {
			outputInventory->PushItem(recipe->Craft(inventory));
			progress = 0.f;
		}
	}
}
