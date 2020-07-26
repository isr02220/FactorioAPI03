#pragma once
#include "framework.h"
class CItem;
class CItemStack;
class Ingredient;
class CInventory {
public:
	CInventory(UINT _capacity);
	~CInventory();

	BOOL   PushItem(CItem* _item);
	BOOL   PushItem(Ingredient* _ingredient);
	BOOL   PushItem(CObj* _item);
	CItemStack*   PushItemStack(CItemStack* _itemStack);
	CItem* PopItem(CItem* _item);
	CItem* PopItem();

	list<CItemStack*> listItemStack;
	UINT capacity = 24;
};

