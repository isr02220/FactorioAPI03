#pragma once
#include "ResourceOre.h"
class CCopperOre :
    public CResourceOre {
public:
    CCopperOre();
    virtual ~CCopperOre();

    virtual void Ready_Object() override;
    virtual void Render_Object(HDC hDC) override;

    virtual CObj* Gather() override;
};

