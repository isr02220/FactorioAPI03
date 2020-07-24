#pragma once
#include "framework.h"
class CItem;
class Ingredient;
class Products;
class CInventory;
class CCraftRecipe {
public:
	CCraftRecipe(Ingredient** _ingredients, Ingredient* _products, UINT _size);
	~CCraftRecipe();
	Ingredient* Craft(CInventory* inventory);

public:
	FLOAT time = 1.f;
	vector<Ingredient*> vecIngredients;
	Ingredient* products = nullptr;
};

class Ingredient {
public:
	Ingredient(CItem* _item, const UINT& _amount);
	~Ingredient();
	CItem* item = nullptr;
	UINT amount = 0;
};