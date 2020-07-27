#pragma once
#include "Item.h"
class CItemSolarPanel :
    public CItem {
public:
    CItemSolarPanel();
    virtual ~CItemSolarPanel();

    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual CItem* GetNewItem();
    virtual CActor* GetNewActor();

};

