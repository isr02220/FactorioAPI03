#pragma once
#include "framework.h"
#include "Obj.h"
class CItem :
    public CObj {
public:
	CItem();
	virtual ~CItem();

    virtual void Ready_Object() override;
    virtual INT  Update_Object() override;
    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual void Release_Object() override;
    virtual void OnCollision(CObj* _TargetObj) override;

public:

	ITEM::GROUP group;
	ITEM::SUBGROUP subGroup;
protected:
	DWORD timer = GetTickCount();
};