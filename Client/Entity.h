#pragma once
#include "Actor.h"
class CEntity :
    public CActor {
public:
    CEntity();
    CEntity(FLOAT _positionX, FLOAT _positionY);
    virtual ~CEntity();

    virtual void Ready_Object() override;
    virtual INT  Update_Object() override;
    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual void Release_Object() override;
    virtual void OnCollision(CObj* _TargetObj) override;
    virtual void SetSpriteDir();
};

