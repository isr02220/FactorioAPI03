#pragma once
#include "Monster.h"
class CHelicopter :
	public CMonster
{
public:
	CHelicopter();
	virtual ~CHelicopter();
public:
	// CObj을(를) 통해 상속됨
	virtual void Ready_Object()             override;
	virtual int Update_Object()             override;
	virtual void LateUpdate_Object()        override;
	virtual void Render_Object(HDC hDC)     override;
	virtual void Release_Object()           override;

private:
	void Update_TailAngle();
	void Move();
	void Render_Tail(HDC hDC);
	void Update_Barrel();
private:
	int m_iMoveAngle{ 0 };
	int m_iTailAngle{ 0 };
	int m_iTailSpeed{ 5 };
	float m_fTempX{ 100 };
	float m_fTempY;

	float m_fBarrelX{ 0.f };
	float m_fBarrelY{ 0.f };
	int m_iCenterBarrelX{ 0 };
	int m_iCenterBarrelY{ 0 };
};

