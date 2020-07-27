#pragma once
#include "UI.h"
class CActor;
class CItemStack;
class CEquipmentUI :
    public CUI {
public:
	CEquipmentUI();
	~CEquipmentUI();
	virtual void Ready_Object() override;
	virtual INT Update_Object() override;
	virtual void LateUpdate_Object() override;
	virtual void Render_Object(HDC hDC) override;
	virtual void Release_Object() override;
	virtual void OnCollision(CObj* _TargetObj) override;
	CActor* targetActor = nullptr;
	CItemStack* armorStack;
	CItemStack* weaponStack;
	CItemStack* magazineStack;
};

