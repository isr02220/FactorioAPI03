#pragma once
#include "Entity.h"
class CInventory;
class CCraftRecipe;
class CAssemblingMachine :
    public CEntity {
public:
    CAssemblingMachine();
    virtual ~CAssemblingMachine();
public:
    virtual void Ready_Object() override;
    virtual INT  Update_Object() override;
    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual void Render_Placable(HDC hDC, BOOL placable) override;
    virtual void Release_Object() override;
    virtual void OnCollision(CObj* _TargetObj) override;
    virtual CObj* GetNewActor() override;

    void CraftItem(FLOAT _speed);

    CCraftRecipe* recipe = nullptr;
};

