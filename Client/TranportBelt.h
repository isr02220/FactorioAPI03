#pragma once
#include "Entity.h"
class CTranportBelt :
    public CEntity {
public:
    CTranportBelt();
    virtual ~CTranportBelt();

public:
    virtual void Ready_Object() override;
    virtual INT  Update_Object() override;
    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual void Release_Object() override;
    virtual void OnCollision(CObj* _TargetObj) override;

    void SetIndexY();
    void GetBeltConnect();

private:
    CTranportBelt* headBelt = nullptr;
    CTranportBelt* tailBelt = nullptr;
    CTranportBelt* portBelt = nullptr;
    CTranportBelt* starBelt = nullptr;
};

