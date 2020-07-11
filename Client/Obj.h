#pragma once
#include"ObjManager.h"
class CObj abstract{
public:
	CObj();
	CObj(FLOAT _positionX, FLOAT _positionY);
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
		lstrcpy(m_tInfo.name, _name);
	}
	void SetPosition(FLOAT& fX, FLOAT& fY) {
		m_tInfo.position.x = fX;
		m_tInfo.position.y = fY;
	}
	void SetPosition(POSITION newPoint) {
		m_tInfo.position = newPoint;
	}

	TCHAR* GetName() {
		return m_tInfo.name;
	}
	POSITION GetPosition() { return POSITION(m_tInfo.position); }
	RECT* GetRect() { return &m_tRect; }
	OBJ::TYPE GetObjectType() { return m_ObjectType; }
	INFO* GetInfo() { return &m_tInfo; }


	void Update_Rect_Object();
	void SetDead() { m_isDead = true; };
	void SetFillColor(COLORREF _FillColor) { m_FillColor = _FillColor; }
	void SetStrokeColor(COLORREF _StrokeColor) { m_StrokeColor = _StrokeColor; }
protected:
	RECT m_tRect;
	INFO m_tInfo;
	OBJ::TYPE m_ObjectType = OBJ::END;
	COLORREF m_FillColor = RGB(255, 255, 255);
	COLORREF m_StrokeColor = RGB(0, 0, 0);
	BOOL m_isDead = false;
	BOOL m_isVisible = true;
	
};

