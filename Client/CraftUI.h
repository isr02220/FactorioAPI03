#pragma once
#include "UI.h"
class CActor;
class CItemStack;
class CCraftRecipe;
class CCraftUI :
	public CUI {
public:
	CCraftUI();
	~CCraftUI();
	virtual void Ready_Object() override;
	virtual INT Update_Object() override;
	virtual void LateUpdate_Object() override;
	virtual void Render_Object(HDC hDC) override;
	virtual void Release_Object() override;
	virtual void OnCollision(CObj* _TargetObj) override;
	static list<CCraftRecipe*>* listLogisticsRecipe;
	static list<CCraftRecipe*>* listProductionRecipe;
	static list<CCraftRecipe*>* listIntermediateRecipe;
	static list<CCraftRecipe*>* listCombatRecipe;
	CCraftRecipe* SelectedRecipe = nullptr;
	CActor* targetActor = nullptr;
	list<CCraftRecipe*>* listSelected = nullptr;
	ITEM::GROUP selectedItemGroup = ITEM::GROUP::LOGISTICS;
	INT selectedIndex = 0;
};

