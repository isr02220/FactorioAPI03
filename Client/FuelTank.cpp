#include "FuelTank.h"
#include "Item.h"
#include "ItemStack.h"
CFuelTank::CFuelTank() {

}

CFuelTank::~CFuelTank() {
	Safe_Delete(fuelStack);
}

void CFuelTank::PushItem(CItem* _item) {
	if (fuelStack) {
		if (!lstrcmp(fuelStack->item->IconName, _item->IconName))
			fuelStack->size++;
	}
	else {
		fuelStack = new CItemStack(_item->GetNewItem());
		fuelStack->size++;
	}
	list<CObj*>* listItem = CObjManager::GetInstance()->GetList(OBJ::ITEM);
	if (listItem->size() > 0) {
		auto iter = find_if(listItem->begin(), listItem->end(), [&](CObj* tObj) { return _item == tObj;	});
		if (iter != listItem->end())
			(*iter)->SetDead();
	}

}

void CFuelTank::PushItem(CObj* _item) {
	CItem* tempItem = dynamic_cast<CItem*>(_item);
	if (tempItem)
		PushItem(tempItem);
}

void CFuelTank::PushItemStack(CItemStack* _itemStack) {
	for (size_t i = 0; i < _itemStack->size; i++) {
		PushItem(_itemStack->item->GetNewItem());
	}
}

void CFuelTank::BurnFuel() {
	if (fuelStack) {
		fuelStack->size--;
		if (fuelStack->size == 0) 
			Safe_Delete(fuelStack);
		energy += 100.f;
		
	}
}

BOOL CFuelTank::SpendEnergy(FLOAT _energy) {
	if (energy > 0.f) {
		energy -= _energy;
		return true;
	}
	else {
		BurnFuel();
		if (energy <= 0.f)
			energy = 0.f;
		return false;
	}
}

CItemStack* CFuelTank::PopItemStack() {
	if (fuelStack) {
		CItemStack* tempFuelStack = new CItemStack(fuelStack->item->GetNewItem());
		for (size_t i = 0; i < fuelStack->size; i++) {
			tempFuelStack->size++;
		}
		Safe_Delete(fuelStack);
		return tempFuelStack;
	}
	return nullptr;
}
