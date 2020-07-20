#pragma once
#include "ResourceOre.h"
class CCoalOre :
    public CResourceOre {
public:
    CCoalOre();
    virtual ~CCoalOre();

    virtual void Ready_Object() override;
    virtual void Render_Object(HDC hDC) override;

    virtual CObj* Gather() override;
};

