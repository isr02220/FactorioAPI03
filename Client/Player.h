#pragma once
#include "Obj.h"
#include "Item.h"
class CPlayer : public CObj {
public:
	CPlayer();
	CPlayer(float _forceX, float _forceY);
	virtual ~CPlayer();
public:
	// CObj을(를) 통해 상속됨
	virtual void Ready_Object();
	virtual int Update_Object();
	virtual void LateUpdate_Object();
	virtual void Render_Object(HDC hDC);
	virtual void Release_Object();
	virtual void OnCollision(CObj* _TargetObj) override;
public:

	void IncreaseScore() { m_score++; }
	void IncreaseScore(INT _score) { m_score += _score; }
	INT  GetHP() { return m_HP; };
	INT  GetMAXHP() { return m_HP; };
	INT GetScore() { return m_score; }
	INT GetBomb() { return m_bombCount; }
	INT GetBullets() { return m_Bullets; }
	ITEM::ID GetItemType() { return m_ItemType; }
	void SetItem(CItem* pItem);
	BOOL GetIsJump() { return m_isJump; }
	void SetIsJump(BOOL _value) { m_isJump = _value; }

	CObj* CreateBullet(float _degree, float _speed, INT _damage, LONG _bulletSize);
	CObj* CreateGuidedBullet(float _degree, float _speed, INT _damage, LONG _bulletSize);
	CObj* CreateBomb(float _degree, float _speed, INT _damage, LONG _bombSize);
	CObj* CreateHeavyBullet(float _degree, float _speed, INT _damage, LONG _bulletSize);
	CObj* CreateShotBullet(float _degree, float _speed, INT _damage, LONG _bulletSize);
	BOOL MonsterInRange();
	BOOL IsMonsterInRange();
private:
	CObjManager* ObjManager = CObjManager::GetInstance();
	BOOL m_controlAble = false;
	BOOL m_Invincible = true;
	BOOL m_AngleGun = true;
	INT m_Bullets = 0;
	INT m_score = 0;
	INT m_bombCount = 10;
	INT m_powerCount = 1;
	INT m_ShootDegree = 0;
	INT m_ShootSpeed = 10;
	INT m_ShootDelay = 0;
	BOOL m_isJump = false;
	INT m_BarrelSize = 100;
	INT m_BarrelAngleSpeed = 10;
	ITEM::ID m_ItemType = ITEM::NORMAL;
	FLOAT m_BarrelAngle = 0.f;
	POINT m_BarrelEndPt = {};
	DWORD m_Timer = GetTickCount();
	CItem* m_pItem = nullptr;

	INT  m_HP = 1;
	INT  m_MaxHP = 1;
};

