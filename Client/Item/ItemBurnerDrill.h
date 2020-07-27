#pragma once
#include "Item.h"
class CItemBurnerDrill :
    public CItem {
public:
    CItemBurnerDrill();
    virtual ~CItemBurnerDrill();

    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual CItem* GetNewItem();
    virtual CActor* GetNewActor();

};

