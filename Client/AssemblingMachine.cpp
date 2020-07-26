#include "AssemblingMachine.h"
#include "ItemAssemblingMachine.h"
#include "Entity.h"
#include "Player.h"
#include "ItemStack.h"
#include "Inventory.h"
#include "Item.h"
#include "AssemblingMachineUI.h"
#include "CraftUI.h"
#include "CraftRecipe.h"
#include "RecipeManager.h"
FLOAT CAssemblingMachine::craftSpeed = 0.8f;
CAssemblingMachine::CAssemblingMachine() : CEntity() {
	objectType = OBJ::ENTITY;
	lstrcpy(info.name, L"조립 기계");
	inventory = new CInventory(0);
	outputInventory = new CInventory(1);
	rotatAble = false;
}

CAssemblingMachine::~CAssemblingMachine() {
	Release_Object();
}

void CAssemblingMachine::Ready_Object() {
	CObj* tempUi = CAbstractFactory<CAssemblingMachineUI>::Create(WINCX >> 1, WINCY >> 2);
	CObjManager::GetInstance()->AddObject(tempUi, OBJ::UI);
	assemUI = dynamic_cast<CUI*>(tempUi);
	dynamic_cast<CAssemblingMachineUI*>(assemUI)->targetActor = this;

	tempUi = CAbstractFactory<CCraftUI>::Create(WINCX >> 1, WINCY >> 1);
	CObjManager::GetInstance()->AddObject(tempUi, OBJ::UI);
	craftUI = dynamic_cast<CUI*>(tempUi);
	dynamic_cast<CCraftUI*>(craftUI)->targetActor = this;

	GUI = craftUI;

	info.iCX = 192;
	info.iCY = 192;
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
	recipe = dynamic_cast<CCraftUI*>(craftUI)->SelectedRecipe;

	if (recipe) {
		GUI = assemUI;
		if (craftUI->GetVisible()) {
			craftUI->SetVisible(false);
			assemUI->SetVisible(true);
			dynamic_cast<CPlayer*>(CObjManager::GetInstance()->GetPlayer())->GUI->SetVisible(true);
			dynamic_cast<CPlayer*>(CObjManager::GetInstance()->GetPlayer())->focusedUI = assemUI;
			if (!inventory->listItemStack.empty()) {
				for (auto itemStack : inventory->listItemStack)
					Safe_Delete(itemStack);
				inventory->listItemStack.clear();
			}
			inventory->capacity = recipe->vecIngredients.size();
			for (size_t i = 0; i < recipe->vecIngredients.size(); i++)
				inventory->listItemStack.emplace_back(new CItemStack(recipe->vecIngredients[i]->item));
		}
	}
	else {
		GUI = craftUI;
		if (craftUI->GetVisible()) {
			assemUI->SetVisible(false);
			craftUI->SetVisible(true);
			dynamic_cast<CPlayer*>(CObjManager::GetInstance()->GetPlayer())->focusedUI = craftUI;
		}
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
	Safe_Delete(inventory);
	Safe_Delete(outputInventory);
	dynamic_cast<CAssemblingMachineUI*>(assemUI)->targetActor = nullptr;
	dynamic_cast<CCraftUI*>(craftUI)->targetActor = nullptr;
	assemUI->SetDead();
	craftUI->SetDead();

}

void CAssemblingMachine::OnCollision(CObj* _TargetObj) {

}

CObj* CAssemblingMachine::GetNewActor() {
	CObj* tempObj = new CAssemblingMachine();
	tempObj->Ready_Object();
	return tempObj;
}

CItem* CAssemblingMachine::GetNewItem() {
	CItem* tempItem = new CItemAssemblingMachine();
	return tempItem;
}

void CAssemblingMachine::CraftItem(FLOAT _speed) {
	
	BOOL Crafting = (recipe && recipe->isCraftable(inventory));

	if (Crafting) {
		if (++spriteIndexX >= 16 * spriteFrameDelay)
			spriteIndexX = 0;
		progress += craftSpeed / recipe->timeToCraft;
		if (progress >= 100.f) {
			outputInventory->PushItem(recipe->Craft(inventory));
			progress = 0.f;
		}
	}
}
