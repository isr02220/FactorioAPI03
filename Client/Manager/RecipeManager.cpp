#include "RecipeManager.h"
#include "framework.h"
#include "ItemHeaders.h"
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
	{
		//ȭ�� ���Ա�
		tempIngreds[0] = new Ingredient(new CItemIronGearWheel(), 1);
		tempIngreds[1] = new Ingredient(new CItemIronPlate(), 1);
		tempIngreds[2] = nullptr;
		tempProducts = new Ingredient(new CItemBurnerInserter(), 1);
		InsertRecipe(new CCraftRecipe(tempIngreds, tempProducts, 2, 0.5f), tempProducts->item->IconName);

		//ö ����
		tempIngreds[0] = new Ingredient(new CItemIronPlate(), 8);
		tempIngreds[1] = nullptr;
		tempIngreds[2] = nullptr;
		tempProducts = new Ingredient(new CItemIronChest(), 1);
		InsertRecipe(new CCraftRecipe(tempIngreds, tempProducts, 1, 0.5f), tempProducts->item->IconName);

		//��� ��Ʈ
		tempIngreds[0] = new Ingredient(new CItemIronGearWheel(), 1);
		tempIngreds[1] = new Ingredient(new CItemIronPlate(), 1);
		tempIngreds[2] = nullptr;
		tempProducts = new Ingredient(new CItemTransportBelt(), 1);
		InsertRecipe(new CCraftRecipe(tempIngreds, tempProducts, 2, 0.5f), tempProducts->item->IconName);
	}
	{
		//���� ���
		tempIngreds[0] = new Ingredient(new CItemElectronicCircuit(), 3);
		tempIngreds[1] = new Ingredient(new CItemIronGearWheel(), 5);
		tempIngreds[2] = new Ingredient(new CItemIronPlate(), 9);
		tempProducts = new Ingredient(new CItemAssemblingMachine(), 1);
		InsertRecipe(new CCraftRecipe(tempIngreds, tempProducts, 3, 0.5f), tempProducts->item->IconName);

		//ȭ�� ä����
		tempIngreds[0] = new Ingredient(new CItemIronGearWheel(), 3);
		tempIngreds[1] = new Ingredient(new CItemIronPlate(), 3);
		tempIngreds[2] = new Ingredient(new CItemFurnace(), 1);
		tempProducts = new Ingredient(new CItemBurnerDrill(), 1);
		InsertRecipe(new CCraftRecipe(tempIngreds, tempProducts, 3, 2.f), tempProducts->item->IconName);

		//�� �뱤��
		tempIngreds[0] = new Ingredient(new CItemStone(), 5);
		tempIngreds[1] = nullptr;
		tempIngreds[2] = nullptr;
		tempProducts = new Ingredient(new CItemFurnace(), 1);
		InsertRecipe(new CCraftRecipe(tempIngreds, tempProducts, 1, 0.5), tempProducts->item->IconName);

		//�¾籤 �г�
		tempIngreds[0] = new Ingredient(new CItemCopperPlate(), 5);
		tempIngreds[1] = new Ingredient(new CItemElectronicCircuit(), 15);
		tempIngreds[2] = new Ingredient(new CItemIronPlate(), 5);
		tempProducts = new Ingredient(new CItemSolarPanel(), 1);
		InsertRecipe(new CCraftRecipe(tempIngreds, tempProducts, 3, 10.f), tempProducts->item->IconName);

	}

	{
		//ö ��
		tempIngreds[0] = new Ingredient(new CItemIronOre(), 1);
		tempIngreds[1] = nullptr;
		tempIngreds[2] = nullptr;
		tempProducts = new Ingredient(new CItemIronPlate(), 1);
		InsertRecipe(new CCraftRecipe(tempIngreds, tempProducts, 1, 3.2f), tempProducts->item->IconName);

		//���� ��
		tempIngreds[0] = new Ingredient(new CItemCopperOre(), 1);
		tempIngreds[1] = nullptr;
		tempIngreds[2] = nullptr;
		tempProducts = new Ingredient(new CItemCopperPlate(), 1);
		InsertRecipe(new CCraftRecipe(tempIngreds, tempProducts, 1, 3.2f), tempProducts->item->IconName);

		//���� ���̺�
		tempIngreds[0] = new Ingredient(new CItemCopperPlate(), 1);
		tempIngreds[1] = nullptr;
		tempIngreds[2] = nullptr;
		tempProducts = new Ingredient(new CItemCopperCable(), 2);
		InsertRecipe(new CCraftRecipe(tempIngreds, tempProducts, 1, 0.5f), tempProducts->item->IconName);

		//���� ȸ��
		tempIngreds[0] = new Ingredient(new CItemCopperCable(), 3);
		tempIngreds[1] = new Ingredient(new CItemIronPlate(), 1);
		tempIngreds[2] = nullptr;
		tempProducts = new Ingredient(new CItemElectronicCircuit(), 1);
		InsertRecipe(new CCraftRecipe(tempIngreds, tempProducts, 2, 0.5f), tempProducts->item->IconName);

		//ö ��Ϲ���
		tempIngreds[0] = new Ingredient(new CItemIronPlate(), 2);
		tempIngreds[1] = nullptr;
		tempIngreds[2] = nullptr;
		tempProducts = new Ingredient(new CItemIronGearWheel(), 1);
		InsertRecipe(new CCraftRecipe(tempIngreds, tempProducts, 1, 0.5f), tempProducts->item->IconName);
	}

	{
		//����Ʈ �Ƹ�
		tempIngreds[0] = new Ingredient(new CItemIronPlate(), 40);
		tempIngreds[1] = nullptr;
		tempIngreds[2] = nullptr;
		tempProducts = new Ingredient(new CItemLightArmor(), 1);
		InsertRecipe(new CCraftRecipe(tempIngreds, tempProducts, 1, 3.f), tempProducts->item->IconName);
		
		//ȭ��� źâ
		tempIngreds[0] = new Ingredient(new CItemIronPlate(), 4);
		tempIngreds[1] = nullptr;
		tempIngreds[2] = nullptr;
		tempProducts = new Ingredient(new CItemMagazine(), 1);
		InsertRecipe(new CCraftRecipe(tempIngreds, tempProducts, 1, 1.f), tempProducts->item->IconName);

		//�������
		tempIngreds[0] = new Ingredient(new CItemCopperPlate(), 5);
		tempIngreds[1] = new Ingredient(new CItemIronGearWheel(), 10);
		tempIngreds[2] = new Ingredient(new CItemIronPlate(), 10);

		tempProducts = new Ingredient(new CItemSMG(), 1);
		InsertRecipe(new CCraftRecipe(tempIngreds, tempProducts, 3, 10.f), tempProducts->item->IconName);
	}

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
