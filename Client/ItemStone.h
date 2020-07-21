#pragma once
#include "Item.h"
class CItemStone :
    public CItem {
public:
    CItemStone();
    virtual ~CItemStone();

    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual CItem* GetNewItem();

};

