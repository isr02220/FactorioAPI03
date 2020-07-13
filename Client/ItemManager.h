#pragma once
#include "framework.h"
#include "ObjManager.h"
class CItem;
class CItemManager {
public:
	CItemManager();
	~CItemManager();
public:
	void ReadyItem();

	void InsterItem(CItem* _newItem);
	void CreateItem();
private:
	list<CItem*> listItemData;
	CObjManager* ObjManager = CObjManager::GetInstance();
	DWORD timer = GetTickCount();
};

