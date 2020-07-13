#include "ItemManager.h"
#include "Item.h"
CItemManager::CItemManager() {
	
}

CItemManager::~CItemManager() {

}

void CItemManager::ReadyItem() {
	timer = GetTickCount();
}
void CItemManager::InsterItem(CItem* _newItem) {
	listItemData.emplace_back(_newItem);
}

void CItemManager::CreateItem() {
	auto iterList = listItemData.begin();
	CObj* tempItem = nullptr;
	ObjManager->AddObject(tempItem, OBJ::ITEM);
	listItemData.erase(iterList);
}
