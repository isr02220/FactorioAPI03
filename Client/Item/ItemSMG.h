#pragma once
#include "Item.h"
class CItemSMG :
    public CItem {
public:
    CItemSMG();
    virtual ~CItemSMG();

    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual CItem* GetNewItem();
    virtual CActor* GetNewActor();

};

