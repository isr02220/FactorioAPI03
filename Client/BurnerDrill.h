#pragma once
#include "Entity.h"
class CBurnerDrill :
    public CEntity {
public:
    CBurnerDrill();
    virtual ~CBurnerDrill();

    static INT beltSpriteIndexX;
    static INT beltSpriteFrameDelay;
public:
    virtual void Ready_Object() override;
    virtual INT  Update_Object() override;
    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual void Render_Placable(HDC hDC, BOOL placable) override;
    virtual void Release_Object() override;
    virtual void OnCollision(CObj* _TargetObj) override;
    virtual CObj* GetNewActor() override;

    void GatherResourceOre(FLOAT speed);

    POSITION GetOutputPos() { return outputPos; }
    void SetOutputPos(POSITION _Pos) { outputPos = _Pos; }
    void SetOutputPos();
protected:
    POSITION outputPos;
};

