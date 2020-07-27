#pragma once
#include "Item.h"
class CItemFurnace :
    public CItem {
public:
    CItemFurnace();
    virtual ~CItemFurnace();

    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual CItem* GetNewItem();
    virtual CActor* GetNewActor();

};

