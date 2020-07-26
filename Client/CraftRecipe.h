#pragma once
#include "framework.h"
class CItem;
class Ingredient;
class Products;
class CInventory;
class CCraftRecipe {
public:
	CCraftRecipe(Ingredient** _ingredients, Ingredient* _products, UINT _size, FLOAT _timeToCraft);
	~CCraftRecipe();
	Ingredient* Craft(CInventory* inventory);
	BOOL isCraftable(CInventory* inventory);

public:
	vector<Ingredient*> vecIngredients;
	Ingredient* products = nullptr;
	HDC hMemDC;
	FLOAT timeToCraft = 100.f;
};

class Ingredient {
public:
	Ingredient(CItem* _item, const UINT& _amount);
	~Ingredient();
	CItem* item = nullptr;
	UINT amount = 0;
};