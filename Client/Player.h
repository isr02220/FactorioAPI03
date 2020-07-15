#pragma once
#include "Actor.h"
class CMouse;
class CPlayer : public CActor {
public:
	CPlayer();
	CPlayer(FLOAT _positionX, FLOAT _positionY);
	virtual ~CPlayer();
public:
	virtual void Ready_Object() override;
	virtual int Update_Object() override;
	virtual void LateUpdate_Object() override;
	virtual void Render_Object(HDC hDC) override;
	virtual void Release_Object() override;
	virtual void OnCollision(CObj* _TargetObj) override;

public:
	void Move();
private:
	CMouse* playerMouse;
	
};

