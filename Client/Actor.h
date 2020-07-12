#pragma once
#include "Obj.h"
class CActor :
    public CObj {
public:
    CActor();
    CActor(FLOAT _positionX, FLOAT _positionY);
    virtual ~CActor();
    // CObj을(를) 통해 상속됨
    virtual void Ready_Object() override;
    virtual INT Update_Object() override;
    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual void Release_Object() override;
    virtual void OnCollision(CObj* _TargetObj) override;

public:
    virtual void UpdateSelected();

    WALKINGSTATE  GetWalkingState()   { return walkingState ; }
    MININGSTATE   GetMiningState()    { return miningState  ; }
    SHOOTINGSTATE GetShootingState()  { return shootingState; }
    PICKINGSTATE  GetPickingState()   { return pickingState ; }
    REPAIRSTATE   GetRepairingState() { return repairState  ; }
    ORIENTATION   GetOrientation()    { return orientation  ; }
    BOOL          GetControllable()   { return controllable ; }
    BOOL          GetInvincible()     { return invincible   ; }
    BOOL          GetActive()         { return active       ; }
    FLOAT         GetSpeed()          { return speed        ; }
    INT           GetScore()          { return score        ; }
    INT           GetHP()             { return HP           ; }
    INT           GetMaxHp()          { return MaxHP        ; }
    
    void SetWalkingState  (const WALKINGSTATE & _walkingState ) { walkingState  = _walkingState ; }
    void SetMiningState   (const MININGSTATE  & _miningState  ) { miningState   = _miningState  ; }
    void SetShootingState (const SHOOTINGSTATE& _shootingState) { shootingState = _shootingState; }
    void SetPickingState  (const PICKINGSTATE & _pickingState ) { pickingState  = _pickingState ; }
    void SetRepairingState(const REPAIRSTATE  & _repairState  ) { repairState   = _repairState  ; }
    void SetOrientation   (const ORIENTATION  & _orientation  ) { orientation   = _orientation  ; }
    void SetControllable  (const BOOL         & _controllable ) { controllable  = _controllable ; }
    void SetInvincible    (const BOOL         & _invincible   ) { invincible    = _invincible   ; }
    void SetActive        (const BOOL         & _active       ) { active        = _active       ; }
    void SetSpeed         (const FLOAT        & _speed        ) { speed         = _speed        ; }
    void SetScore         (const INT          & _score        ) { score         = _score        ; }
    void SetHP            (const INT          & _HP           ) { HP            = _HP           ; }
    void SetMaxHP         (const INT          & _MaxHP        ) { MaxHP         = _MaxHP        ; }
    
    void IncreaseScore(const INT& _score) { score += _score; }
protected:
    CActor* selectedActor;
    WALKINGSTATE walkingState;
    MININGSTATE miningState;
    SHOOTINGSTATE shootingState;
    PICKINGSTATE pickingState;
    REPAIRSTATE repairState;
    ORIENTATION orientation;

    BOOL controllable = false;
    BOOL invincible = false;
    BOOL active = false;
    FLOAT speed = 1.f;
    INT  score = 0;
    INT  HP = 1;
    INT  MaxHP = 1;

    DWORD Timer = GetTickCount();

};