#pragma once
#include "UI.h"
class CActor;
class CItemStack;
class CFurnaceUI :
	public CUI {
public:
	CFurnaceUI();
	~CFurnaceUI();
	virtual void Ready_Object() override;
	virtual INT Update_Object() override;
	virtual void LateUpdate_Object() override;
	virtual void Render_Object(HDC hDC) override;
	virtual void Release_Object() override;
	virtual void OnCollision(CObj* _TargetObj) override;
	void SortItemStack();
	CActor* targetActor = nullptr;
	list<CItemStack*>* listItemStack = nullptr;
	INT selectedIndex = 0;
};

