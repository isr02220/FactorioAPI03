#pragma once
#include "framework.h"
class CItem;
class CCraftRecipe {
public:
	CCraftRecipe();
	~CCraftRecipe();
	CItem* Craft(CItem* _mat);

public:
	FLOAT time = 1.f;
};

