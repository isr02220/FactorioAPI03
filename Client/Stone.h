#pragma once
#include "ResourceOre.h"
class CStone :
    public CResourceOre {
public:
    CStone();
    virtual ~CStone();

    virtual void Ready_Object() override;
    virtual void Render_Object(HDC hDC) override;

    virtual CObj* Gather() override;
};

