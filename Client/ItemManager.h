#pragma once
#include "framework.h"
#include "ObjManager.h"
class CItemManager {
public:
	CItemManager();
	~CItemManager();
public:
	void ReadyItem();

	void InsterItem(ITEMDATA* _newItem);
	void CreateItem();
private:
	list<ITEMDATA*> m_ListItemData;
	CObjManager* ObjManager = CObjManager::GetInstance();
	DWORD m_Timer = GetTickCount();
};

