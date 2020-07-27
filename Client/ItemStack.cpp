#include "ItemStack.h"
#include "Item.h"

CItemStack::CItemStack(CItem* _item) : item(_item), capacity(_item->stackSize){
	hMemDC = CBitmapManager::GetInstance()->FindImage(_item->IconName);
}

CItemStack::~CItemStack() {
	Safe_Delete(item);
}