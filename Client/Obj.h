#pragma once
#include"ObjManager.h"
class CObj abstract{
public:
	CObj();
	CObj(FLOAT _forceX, FLOAT _forceY);
	virtual ~CObj();

public:
	virtual void Ready_Object()			    = 0;
	virtual INT  Update_Object()		    = 0;
	virtual void LateUpdate_Object()	    = 0;
	virtual void Render_Object(HDC hDC)	    = 0;
	virtual void Release_Object()		    = 0; 
	virtual void OnCollision(CObj* _TargetObj) = 0;

public:
	void SetName(const TCHAR* _name) {
		lstrcpy(m_tInfo.chName, _name);
	}
	void SetPos(FLOAT fX, FLOAT fY) {
		m_tInfo.fX = fX;
		m_tInfo.fY = fY;
	}
	void SetPos(POINT& newPoint) {
		m_tInfo.fX = FLOAT(newPoint.x);
		m_tInfo.fY = FLOAT(newPoint.y);
	}
	
	void IncreasePos(FLOAT fX, FLOAT fY) {
		m_tInfo.fX += fX;
		m_tInfo.fY += fY;
	}
	TCHAR* GetName() {
		return m_tInfo.chName;
	}
	POINT GetPos() {
		POINT tempPoint;
		tempPoint.x = LONG(m_tInfo.fX);
		tempPoint.y = LONG(m_tInfo.fY);
		return tempPoint;
	}
	RECT* GetRect() { return &m_tRect; }
	OBJ::ID GetObjId() { return m_ObjId; }
	INFO* GetInfo() { return &m_tInfo; }


	void Update_Rect_Object();
	void SetDead() { m_isDead = true; };
	void SetFillColor(COLORREF _FillColor) { m_FillColor = _FillColor; }
	void SetStrokeColor(COLORREF _StrokeColor) { m_StrokeColor = _StrokeColor; }
protected:
	RECT m_tRect;
	INFO m_tInfo;
	OBJ::ID m_ObjId = OBJ::END;
	FLOAT forceX;
	FLOAT forceY;
	FLOAT m_fSpeed;
	FLOAT m_fAngle;
	COLORREF m_FillColor = RGB(255, 255, 255);
	COLORREF m_StrokeColor = RGB(0, 0, 0);
	BOOL m_isDead = false;
	BOOL m_isVisible = true;
	
};

