#pragma once
#include "Entity.h"
class CItem;
class CActor;
class CBurnerInserter :
    public CEntity {
public:
    CBurnerInserter();
    virtual ~CBurnerInserter();
public:
    virtual void Ready_Object() override;
    virtual INT  Update_Object() override;
    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual void Render_Placable(HDC hDC, BOOL placable) override;
    virtual void Release_Object() override;
    virtual void OnCollision(CObj* _TargetObj) override;
    virtual CObj* GetNewActor() override;
    virtual void SetSpriteDir() override;

    void TransportItem();

public:
    CObj* pickedItem = nullptr;
    vector<CItem*> vecFilter;
    RECT inputRect;
    CActor* outputActor = nullptr;
    POSITION outputPos = { 0.f,0.f };
protected:

};

