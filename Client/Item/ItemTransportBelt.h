#pragma once
#include "Item.h"
class CItemTransportBelt :
    public CItem {
public:
    CItemTransportBelt();
    virtual ~CItemTransportBelt();

    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual CItem* GetNewItem();
    virtual CActor* GetNewActor();

};

