#pragma once
#include "Item.h"
class CItemIronPlate :
    public CItem {
public:
    CItemIronPlate();
    virtual ~CItemIronPlate();

    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual CItem* GetNewItem();
    virtual CActor* GetNewActor();

};

