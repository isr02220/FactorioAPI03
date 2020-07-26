#pragma once
#include "Entity.h"
class CUI;
class CItem;
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
    virtual CItem* GetNewItem() override;

    void CraftItem(FLOAT _speed);
    
    CUI* craftUI = nullptr;
    CUI* assemUI = nullptr;
    CCraftRecipe* recipe = nullptr;
};

