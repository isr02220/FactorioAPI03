#include "ItemStack.h"
#include "Item.h"

CItemStack::CItemStack(CItem* _item) : item(_item), capacity(_item->stackSize){

}

CItemStack::~CItemStack() {
	Safe_Delete(item);
}