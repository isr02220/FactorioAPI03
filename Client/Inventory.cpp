#include "Inventory.h"
#include "Item.h"
#include "ItemStack.h"
CInventory::CInventory(UINT _capacity) : capacity(_capacity) {

}

CInventory::~CInventory() {
	for (auto itemStack : listItemStack)
		Safe_Delete(itemStack);
}

void CInventory::PushItem(CItem* _item) {
	for (auto itemStack : listItemStack) {
		if (!lstrcmp(itemStack->item->GetName(), _item->GetName())) {
			if (itemStack->size < itemStack->capacity) {
				itemStack->size++;
				Safe_Delete(_item);
				return;
			}
		}
	}
	CItemStack* tempItemStack = new CItemStack(_item->GetNewItem());
	tempItemStack->size++;
	listItemStack.emplace_back(tempItemStack);
	Safe_Delete(_item);
	listItemStack.sort([](CItemStack* stack1, CItemStack* stack2) {
		if (!lstrcmp(stack1->item->GetName(), stack2->item->GetName())) {
			return stack1->size > stack2->size;
		}
		else {
			return lstrcmp(stack1->item->GetName(), stack2->item->GetName()) > 0;
		}
		});
}

void CInventory::PushItemStack(CItemStack* _itemStack) {
	for (size_t i = 0; i < _itemStack->size; i++) {
		PushItem(_itemStack->item->GetNewItem());
	}
}

CItem* CInventory::PopItem(CItem* _item) {
	CItemStack* tempItemStack = nullptr;
	for (auto itemStack : listItemStack) {
		if (!lstrcmp(itemStack->item->GetName(), _item->GetName())) {
			if (itemStack->size > 0) {
				if (tempItemStack) {
					if (tempItemStack->size > itemStack->size)
						tempItemStack = itemStack;
				}
				else {
					tempItemStack = itemStack;
				}
			}
		}
	}
	if (tempItemStack) {
		if (--(tempItemStack->size) == 0)
			for (auto iter = listItemStack.begin(); iter != listItemStack.end(); iter++) {
				if (tempItemStack == (*iter))
					listItemStack.erase(iter);
			}
		CItem* tItem = _item->GetNewItem();
		tItem->Ready_Object();
		return tItem;
	}
	else {
		return nullptr;
	}
}

CItem* CInventory::PopItem() {
	CItemStack* tempItemStack = nullptr;
	for (auto itemStack : listItemStack) {
		if (itemStack->size > 0) {
			if (tempItemStack) {
				if (tempItemStack->size > itemStack->size)
					tempItemStack = itemStack;
			}
			else {
				tempItemStack = itemStack;
			}
		}
	}
	if (tempItemStack) {
		if (--(tempItemStack->size) == 0)
			for (auto iter = listItemStack.begin(); iter != listItemStack.end(); iter++) {
				if (tempItemStack == (*iter)) {
					listItemStack.erase(iter);
					break;
				}
			}
		CItem* tItem = tempItemStack->item->GetNewItem();
		tItem->Ready_Object();
		return tItem;
	}
	else {
		return nullptr;
	}
}
