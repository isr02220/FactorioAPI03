#pragma once
#include "framework.h"
class CItem;
class CInventory;
class CItemStack {
public:
	CItemStack(CItem* _item);
	~CItemStack();

	UINT size = 0;
	UINT capacity = 50;
	CItem* item;
	HDC hMemDC;
};

