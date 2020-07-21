#pragma once
#include "Entity.h"
class CInventory;
class CIronChest :
    public CEntity {
public:
    CIronChest();
    virtual ~CIronChest();
    virtual void Ready_Object() override;
    virtual INT  Update_Object() override;
    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual void Render_Placable(HDC hDC, BOOL placable) override;
    virtual void Release_Object() override;
    virtual void OnCollision(CObj* _TargetObj) override;
    virtual CObj* GetNewActor() override;

public:
    CInventory* inventory;
};

