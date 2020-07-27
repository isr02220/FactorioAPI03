#pragma once
#include "Item.h"
class CItemBurnerInserter :
    public CItem {
public:
    CItemBurnerInserter();
    virtual ~CItemBurnerInserter();

    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual CItem* GetNewItem() override;
    virtual CActor* GetNewActor();

};

