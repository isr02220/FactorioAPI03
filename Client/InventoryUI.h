#pragma once
#include "UI.h"
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
};

