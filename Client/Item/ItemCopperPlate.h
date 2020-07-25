#pragma once
#include "Item.h"
class CItemCopperPlate :
    public CItem {
public:
    CItemCopperPlate();
    virtual ~CItemCopperPlate();

    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual CItem* GetNewItem();
    virtual CActor* GetNewActor();

};

