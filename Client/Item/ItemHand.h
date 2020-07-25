#pragma once
#include "Item.h"
class CItemHand :
    public CItem {
public:
    CItemHand();
    virtual ~CItemHand();

    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual CItem* GetNewItem();

};

