#pragma once
#include "Item.h"
class CItemCopperCable :
    public CItem {
public:
    CItemCopperCable();
    virtual ~CItemCopperCable();

    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual CItem* GetNewItem();
    virtual CActor* GetNewActor();

};

