#pragma once
#include "framework.h"
class CItem;
class CItemStack;
class Ingredient;
class CInventory {
public:
	CInventory(UINT _capacity);
	~CInventory();

	void   PushItem(CItem* _item);
	void   PushItem(Ingredient* _ingredient);
	void   PushItem(CObj* _item);
	void   PushItemStack(CItemStack* _itemStack);
	CItem* PopItem(CItem* _item);
	CItem* PopItem();

	list<CItemStack*> listItemStack;
	UINT capacity = 24;
};

