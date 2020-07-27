#include "Inventory.h"
#include "Item.h"
#include "ItemStack.h"
#include "CraftRecipe.h"
CInventory::CInventory(UINT _capacity) : capacity(_capacity) {

}

CInventory::~CInventory() {
	for (auto itemStack : listItemStack)
		Safe_Delete(itemStack);
}

BOOL CInventory::PushItem(CItem* _item) {
	for (auto itemStack : listItemStack) {
		if (!lstrcmp(itemStack->item->GetName(), _item->GetName())) {
			if (itemStack->size < itemStack->capacity) {
				itemStack->size++;
				list<CObj*>* listItem = CObjManager::GetInstance()->GetList(OBJ::ITEM);
				auto iter = find_if(listItem->begin(), listItem->end(), [&](CObj* tObj) { return _item == tObj;	});
				if (iter != listItem->end())
					(*iter)->SetDead();
				return true;
			}
		}
	}
	if (listItemStack.size() >= capacity)
		return false;
	CItemStack* tempItemStack = new CItemStack(_item->GetNewItem());
	tempItemStack->size++;
	listItemStack.emplace_back(tempItemStack);
	list<CObj*>* listItem = CObjManager::GetInstance()->GetList(OBJ::ITEM);
	auto iter = find_if(listItem->begin(), listItem->end(), [&](CObj* tObj) { return _item == tObj;	});
	if(iter != listItem->end())
		(*iter)->SetDead();
	listItemStack.sort([](CItemStack* stack1, CItemStack* stack2) {
		if (!lstrcmp(stack1->item->GetName(), stack2->item->GetName())) {
			return stack1->size > stack2->size;
		}
		else {
			return lstrcmp(stack1->item->GetName(), stack2->item->GetName()) > 0;
		}
		});
	return true;
}

BOOL CInventory::PushItem(Ingredient* _ingredient) {
	if (_ingredient) {
		for (size_t i = 0; i < _ingredient->amount; i++)
			PushItem(_ingredient->item->GetNewItem());
	}
	return true;
}

BOOL CInventory::PushItem(CObj* _item) {
	CItem* tempItem = dynamic_cast<CItem*>(_item);
	if (tempItem)
		return PushItem(tempItem);
	return false;
}

CItemStack* CInventory::PushItemStack(CItemStack* _itemStack) {
	UINT leftItemSize = 0;
	for (size_t i = 0; i < _itemStack->size; i++) {
		if (!PushItem(_itemStack->item->GetNewItem())) {
			leftItemSize = _itemStack->size - i;
			break;
		}
	}
	if (leftItemSize) {
		CItemStack* tempItemStack = new CItemStack(_itemStack->item->GetNewItem());
		tempItemStack->size = leftItemSize;
		Safe_Delete(_itemStack);
		return tempItemStack;
	}
	else {
		Safe_Delete(_itemStack);
		return nullptr;
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
				if (tempItemStack == (*iter)) {
					listItemStack.erase(iter);
					break;
				}
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
