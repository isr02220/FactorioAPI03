#pragma once
#include "Obj.h"
class CPlayer;
class CBullet : public CObj{
	// CObj을(를) 통해 상속됨
public:
	CBullet();
	CBullet(float _degree, float _speed, INT _damage, LONG _bulletSize);
	virtual ~CBullet();
public:
	virtual void Ready_Object() override;
	virtual int Update_Object() override;
	virtual void LateUpdate_Object() override;
	virtual void Render_Object(HDC hDC) override;
	virtual void Release_Object() override;
	virtual void OnCollision(CObj* _TargetObj) override;

public:
	void SetDamage(INT _damage) { m_damage = _damage; };
	void SetPlayer(CPlayer* _pPlayer) { m_pPlayer = _pPlayer; };

	INT  GetDamage()            { return m_damage;    };
	CPlayer* GetPlayer() { return  m_pPlayer; };

public:
	CObjManager* ObjManager = CObjManager::GetInstance();
	INT m_damage = 10;
	CPlayer* m_pPlayer = nullptr;
	FLOAT speed;
	FLOAT angle;
	DWORD timer;
};

