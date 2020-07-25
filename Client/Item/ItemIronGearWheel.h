#pragma once
#include "Item.h"
class CItemIronGearWheel :
    public CItem {
public:
    CItemIronGearWheel();
    virtual ~CItemIronGearWheel();

    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual CItem* GetNewItem();
    virtual CActor* GetNewActor();

};

