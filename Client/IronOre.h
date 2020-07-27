#pragma once
#include "ResourceOre.h"
class CIronOre :
    public CResourceOre {
public:
    CIronOre();
    virtual ~CIronOre();

    virtual void Ready_Object() override;
    virtual void Render_Object(HDC hDC) override;

    virtual CObj* Gather() override;

    virtual CObj* GetNewActor() override;
    virtual CItem* GetNewItem() override;
};

