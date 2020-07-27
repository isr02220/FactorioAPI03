#pragma once
#include "Item.h"
class CItemMagazine :
    public CItem {
public:
    CItemMagazine();
    virtual ~CItemMagazine();

    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual CItem* GetNewItem();
    virtual CActor* GetNewActor();

};

