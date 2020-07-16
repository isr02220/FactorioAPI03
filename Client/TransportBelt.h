#pragma once
#include "Entity.h"
class CTransportBelt :
    public CEntity {
public:
    CTransportBelt();
    virtual ~CTransportBelt();

    static INT beltSpriteIndexX;
    static INT beltSpriteFrameDelay;
public:
    virtual void Ready_Object() override;
    virtual INT  Update_Object() override;
    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual void Release_Object() override;
    virtual void OnCollision(CObj* _TargetObj) override;

    void SetIndexY();
    void GetBeltConnect();

public:
    CTransportBelt* headBelt = nullptr;
    CTransportBelt* tailBelt = nullptr;
    CTransportBelt* portBelt = nullptr;
    CTransportBelt* starBelt = nullptr;
protected:
    INT headSpriteIndex = 0;
    INT tailSpriteIndex = 0;
    INT HeadTailDistX = 0;
    INT HeadTailDistY = 0;
};

