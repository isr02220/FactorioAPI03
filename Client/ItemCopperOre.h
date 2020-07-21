#pragma once
#include "Item.h"
class CItemCopperOre :
    public CItem {
public:
    CItemCopperOre();
    virtual ~CItemCopperOre();

    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual CItem* GetNewItem();

};

