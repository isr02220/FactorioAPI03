#pragma once
#include "UI.h"
class CFloatingText :
    public CUI {
public:
	CFloatingText();
	~CFloatingText();
	virtual void Ready_Object() override;
	virtual INT Update_Object() override;
	virtual void LateUpdate_Object() override;
	virtual void Render_Object(HDC hDC) override;
	virtual void Release_Object() override;

private:
	DWORD timer = GetTickCount();
};

