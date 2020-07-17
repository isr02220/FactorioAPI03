#pragma once
#include "Actor.h"
class CResourceOre :
    public CActor {
public:
    CResourceOre();
    virtual ~CResourceOre();

    virtual void Ready_Object() override;
    virtual INT  Update_Object() override;
    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual void Release_Object() override;
    virtual void OnCollision(CObj* _TargetObj) override;

    void Gather();
public:
    INT storage;
};

