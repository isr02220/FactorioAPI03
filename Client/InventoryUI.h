#pragma once
#include "UI.h"
class CActor;
class CItemStack;
class CInventoryUI :
    public CUI {
public:
	CInventoryUI();
	~CInventoryUI();
	virtual void Ready_Object() override;
	virtual INT Update_Object() override;
	virtual void LateUpdate_Object() override;
	virtual void Render_Object(HDC hDC) override;
	virtual void Release_Object() override;
	virtual void OnCollision(CObj* _TargetObj) override;
	void ClearIconHand();
	void ClearAllIconHand();
	void SortItemStack();
	CActor* targetActor = nullptr;
	list<CItemStack*>* listItemStack = nullptr;
	INT selectedIndex = 0;
};

