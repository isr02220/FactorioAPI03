#pragma once
#include "Item.h"
class CItemCoalOre :
    public CItem {
public:
    CItemCoalOre();
    virtual ~CItemCoalOre();

    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;

};

