#include "RecipeManager.h"
#include "framework.h"
#include "ItemIronOre.h"
#include "ItemCopperOre.h"
#include "ItemIronPlate.h"
#include "ItemCopperPlate.h"
#include "CraftRecipe.h"
CRecipeManager* CRecipeManager::m_pInstance = nullptr;
CRecipeManager* CRecipeManager::GetInstance() {
	if (nullptr == m_pInstance)
		m_pInstance = new CRecipeManager();

	return m_pInstance;
}

void CRecipeManager::DestroyInstance() {
	if (m_pInstance) {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
CRecipeManager::CRecipeManager() {
	Ingredient** tempIngreds = new Ingredient*[3];
	Ingredient* tempProducts = nullptr;

	tempIngreds[0] = new Ingredient(new CItemIronOre(), 1);
	tempIngreds[1] = nullptr;
	tempIngreds[2] = nullptr;
	tempProducts = new Ingredient(new CItemIronPlate(), 1);
	InsertRecipe(new CCraftRecipe(tempIngreds, tempProducts, 1), tempProducts->item->IconName);

	tempIngreds[0] = new Ingredient(new CItemCopperOre(), 1);
	tempIngreds[1] = nullptr;
	tempIngreds[2] = nullptr;
	tempProducts = new Ingredient(new CItemCopperPlate(), 1);
	InsertRecipe(new CCraftRecipe(tempIngreds, tempProducts, 1), tempProducts->item->IconName);
}

CRecipeManager::~CRecipeManager() {

}

CCraftRecipe* CRecipeManager::FindRecipe(const TCHAR* _IconName) {
	auto iter_find = find_if(mapRecipe.begin(), mapRecipe.end(), [&](auto& rPair) {
		return !lstrcmp(_IconName, rPair.first);
		});
	if (iter_find == mapRecipe.end())
		return nullptr;
	return iter_find->second;
}

void CRecipeManager::InsertRecipe(CCraftRecipe* _recipe, const TCHAR* _IconName) {

	auto iter_find = mapRecipe.find(_IconName);
	if (iter_find != mapRecipe.end())
		return;;
	mapRecipe.emplace(_IconName, _recipe);
}

void CRecipeManager::Release() {
	for (auto& pair : mapRecipe)
		Safe_Delete(pair.second);
	mapRecipe.clear();
}
