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
    virtual void Render_Placable(HDC hDC , BOOL placable);
    virtual void Release_Object() override;
    virtual void OnCollision(CObj* _TargetObj) override;
    virtual CObj* GetNewActor();

public:
    virtual void UpdateSelected(CActor* _Target);

    CActor*       GetSelectedActor()  { return selectedActor; }
    WALKINGSTATE  GetWalkingState()   { return walkingState ; }
    MININGSTATE   GetMiningState()    { return miningState  ; }
    SHOOTINGSTATE GetShootingState()  { return shootingState; }
    CActor*       GetPickedActor()    { return pickedActor  ; }
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
    void SetWalkingState  (const DIRECTION::DIR & _direction  ) { walkingState.direction  = _direction; }
    void SetMiningState   (const MININGSTATE  & _miningState  ) { miningState   = _miningState  ; }
    void SetShootingState (const SHOOTINGSTATE& _shootingState) { shootingState = _shootingState; }
    void SetRepairingState(const REPAIRSTATE  & _repairState  ) { repairState   = _repairState  ; }
    void SetOrientation   (const ORIENTATION  & _orientation  ) { orientation   = _orientation  ; }
    void SetControllable  (const BOOL         & _controllable ) { controllable  = _controllable ; }
    void SetInvincible    (const BOOL         & _invincible   ) { invincible    = _invincible   ; }
    void SetActive        (const BOOL         & _active       ) { active        = _active       ; }
    void SetSpeed         (const FLOAT        & _speed        ) { speed         = _speed        ; }
    void SetScore         (const INT          & _score        ) { score         = _score        ; }
    void SetHP            (const INT          & _HP           ) { HP            = _HP           ; }
    void SetMaxHP         (const INT          & _MaxHP        ) { MaxHP         = _MaxHP        ; }
    void SetSpriteIndexX  (const INT          & _index        ) { spriteIndexX  = _index        ; }
    void SetSpriteIndexY  (const INT          & _index        ) { spriteIndexY  = _index        ; }

    void SetDead() { dead = true; }
    void IncreaseScore(const INT& _score) { score += _score; }
protected:
    CActor* selectedActor = nullptr;
    CActor* pickedActor = nullptr;
    WALKINGSTATE walkingState;
    MININGSTATE miningState;
    SHOOTINGSTATE shootingState;
    PICKINGSTATE pickingState;
    REPAIRSTATE repairState;
    ORIENTATION orientation;

    BOOL controllable = false;
    BOOL invincible = false;
    BOOL active = false;
    BOOL dead = false;
    FLOAT speed = 1.f;
    INT  score = 0;
    INT  HP = 1;
    INT  MaxHP = 1;

    DWORD Timer = GetTickCount();

    INT spriteFrameDelay = 1;
    INT spriteIndexX = 0;
    INT spriteIndexY = 0;
};