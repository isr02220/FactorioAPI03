#pragma once
#include "Entity.h"
class CActor;
class CItem;
class CWorm :
    public CEntity {
public:
    CWorm();
    virtual ~CWorm();

    static INT beltSpriteIndexX;
    static INT beltSpriteFrameDelay;
public:
    virtual void Ready_Object() override;
    virtual INT  Update_Object() override;
    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual void Release_Object() override;
    virtual void OnCollision(CObj* _TargetObj) override;
    virtual CObj* GetNewActor() override;
    virtual CItem* GetNewItem() override;
    void Shoot();

public:
    CActor* targetActor;

};

