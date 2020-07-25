#pragma once
#include "Item.h"
class CItemLightArmor :
    public CItem {
public:
    CItemLightArmor();
    virtual ~CItemLightArmor();

    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual CItem* GetNewItem();
    virtual CActor* GetNewActor();

};

