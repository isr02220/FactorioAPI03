#pragma once
#include "Item.h"
class CItemIronOre :
    public CItem {
public:
    CItemIronOre();
    virtual ~CItemIronOre();

    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual CItem* GetNewItem();
    virtual CActor* GetNewActor();

};

