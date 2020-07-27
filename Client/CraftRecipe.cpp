#include "CraftRecipe.h"
#include "Item.h"
#include "ItemStack.h"
#include "Inventory.h"

CCraftRecipe::CCraftRecipe(Ingredient** _ingredients, Ingredient* _products, UINT _size, FLOAT _timeToCraft) {
	for (size_t i = 0; i < _size; i++)
		vecIngredients.emplace_back(_ingredients[i]);
	products = _products;
	hMemDC = CBitmapManager::GetInstance()->FindImage(_products->item->IconName);
	timeToCraft = _timeToCraft;
}

CCraftRecipe::~CCraftRecipe() {
	for (auto ingredient : vecIngredients)
		Safe_Delete(ingredient);
	Safe_Delete(products);
}

Ingredient* CCraftRecipe::Craft(CInventory* inventory) {
	if (isCraftable(inventory)) {
		for (auto ingredient : vecIngredients) {
			for (auto itemStack : inventory->listItemStack) {
				if (!lstrcmp(ingredient->item->IconName, itemStack->item->IconName)) {
					itemStack->size -= ingredient->amount;
					//if (itemStack->size == 0) {
					//	auto iter = find_if(inventory->listItemStack.begin(), inventory->listItemStack.end(), [&](CItemStack* is) {
					//		return (is == itemStack);
					//		});
					//	if(iter != inventory->listItemStack.end())
					//		inventory->listItemStack.erase(iter);
					//}
					break;
				}
			}
		}
		return products;
	}
	
	return nullptr;
}

BOOL CCraftRecipe::isCraftable(CInventory* inventory) {
	BOOL filled = false;
	BOOL filleds[4] = {};
	UINT index = 0;
	if (!inventory->listItemStack.empty()) {
		for (auto ingredient : vecIngredients) {
			for (auto itemStack : inventory->listItemStack) {
				if (!lstrcmp(ingredient->item->IconName, itemStack->item->IconName) &&
					ingredient->amount <= itemStack->size) {
					filleds[index] = true;
					break;
				}
			}
			if (filleds[index]) {
				filled = true;
			}
			else {
				filled = false;
				break;
			}
			index++;
		}
	}

	return filled;
}

Ingredient::Ingredient(CItem* _item, const UINT& _amount) {
	item = _item->GetNewItem();
	amount = _amount;
}

Ingredient::~Ingredient() {
	Safe_Delete(item);
}
