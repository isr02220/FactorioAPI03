#pragma once
#include "Obj.h"
class CPlayer;
class CItem :
	public CObj {
public:
	CItem();
	CItem(float _forceX, float _forceY);
	virtual ~CItem();
public:
	BOOL GetAngleGunType() { return AngleGunType; }
	INT GetBullets() { return m_Bullets; }
	INT GetBombCount() { return m_BombCount; }
	ITEM::ID GetItemType() { return m_ItemType; }
	// CObj을(를) 통해 상속됨
	virtual void Ready_Object()             override;
	virtual int Update_Object()             override;
	virtual void LateUpdate_Object()        override;
	virtual void Render_Object(HDC hDC)     override;
	virtual void Release_Object()           override;
	virtual void OnCollision(CObj* _TargetObj) override;
public:
	BOOL GetIsJump() { return m_isJump; }
	void SetIsJump(BOOL _value) { m_isJump = _value; }
protected:
	CObjManager* ObjManager = CObjManager::GetInstance();
	INT  m_Score = 10;
	INT  m_HP = 1;
	INT  m_MaxHP = 1;
	INT m_Bullets = 0;
	INT m_BombCount= 0 ;
	ITEM::ID m_ItemType = ITEM::END;
	BOOL m_isJump = true;
	BOOL AngleGunType = true;
	DWORD m_Timer = GetTickCount();
};

