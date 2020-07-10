#include "ItemManager.h"
CItemManager::CItemManager() {
	
}

CItemManager::~CItemManager() {

}

void CItemManager::ReadyItem() {
	m_Timer = GetTickCount();
}
void CItemManager::InsterItem(ITEMDATA* _newItem) {
	m_ListItemData.emplace_back(_newItem);
}

void CItemManager::CreateItem() {
	if (m_ListItemData.size()) {
		auto iterList = m_ListItemData.begin();
		if ((*iterList)->timer + m_Timer < GetTickCount()) {

			CObj* tempItem = nullptr;

			ObjManager->AddObject(tempItem, OBJ::ITEM);
			m_ListItemData.erase(iterList);
		}
	}
}
