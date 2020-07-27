#pragma once
#include "UI.h"
class CItem;
class CActor;
class QuickSlot;
class CQuickSlotUI :
    public CUI {
public:
	CQuickSlotUI();
	~CQuickSlotUI();
	virtual void Ready_Object() override;
	virtual INT Update_Object() override;
	virtual void LateUpdate_Object() override;
	virtual void Render_Object(HDC hDC) override;
	virtual void Release_Object() override;
	virtual void OnCollision(CObj* _TargetObj) override;
	
	CItem* GetQuickSlot(UINT _number);

	static vector<QuickSlot*>* vecQuickSlot1;
	static vector<QuickSlot*>* vecQuickSlot2;
	QuickSlot* SelectedQuickSlot = nullptr;
	CActor* targetActor = nullptr;
	vector<QuickSlot*>* vecSelected = vecQuickSlot1;
	INT selectedIndex = 0;
	INT selectedSlot  = 0;
};

class QuickSlot {
public:
	QuickSlot(CItem* _item);
	~QuickSlot();

	HDC hMemDC;
	CItem* item = nullptr;
	UINT amount = 0;
};