#pragma once
#include "framework.h"
class CItem;
class CItemStack;
class CInventory {
public:
	CInventory(UINT _capacity);
	~CInventory();

	void   PushItem(CItem* _item);
	CItem* PopItem(CItem* _item);
	CItem* PopItem();

	list<CItemStack*> listItemStack;
	UINT capacity = 24;
};
