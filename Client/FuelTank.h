#pragma once
#include "framework.h"
class CItem;
class CItemStack;
class CFuelTank {
public:
	CFuelTank();
	~CFuelTank();

	void PushItem(CItem* _item);
	void PushItem(CObj* _item);
	void PushItemStack(CItemStack* _itemStack);
	void BurnFuel();
	BOOL SpendEnergy(FLOAT _energy);
	CItemStack* PopItemStack();

	CItemStack* fuelStack;
	FLOAT energy = 0.f;
};

