#pragma once
#include "framework.h"
class CCraftRecipe;
class CRecipeManager {
public:
	static CRecipeManager* GetInstance();
	void DestroyInstance();
private:
	CRecipeManager();
	~CRecipeManager();
public:
	CCraftRecipe* FindRecipe(const TCHAR* _IconName);
	void InsertRecipe(CCraftRecipe* _recipe, const TCHAR* _IconName);
	void Release();
private:
	static CRecipeManager* m_pInstance;
	map<const TCHAR*, CCraftRecipe*> mapRecipe;
};