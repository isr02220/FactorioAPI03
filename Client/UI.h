#pragma once
#include "Obj.h"
class CUI : public CObj {
public:
	CUI();
	~CUI();
	virtual void Ready_Object() override;
	virtual INT Update_Object() override;
	virtual void LateUpdate_Object() override;
	virtual void Render_Object(HDC hDC) override;
	virtual void Release_Object() override;
	virtual void OnCollision(CObj* _TargetObj) override;
	BOOL GetVisible() { return isVisible; }

};

