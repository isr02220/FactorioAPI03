#pragma once
#include "Item.h"
class CItemAssemblingMachine :
    public CItem {
public:
    CItemAssemblingMachine();
    virtual ~CItemAssemblingMachine();

    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual CItem* GetNewItem();
    virtual CActor* GetNewActor();

};

