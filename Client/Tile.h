#pragma once
#include "Obj.h"
class CTile :
    public CObj {
    // CObj을(를) 통해 상속됨
    virtual void Ready_Object() override;
    virtual INT Update_Object() override;
    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual void Release_Object() override;
    virtual void OnCollision(CObj* _TargetObj) override;
};

