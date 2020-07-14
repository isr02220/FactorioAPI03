#pragma once
#include "framework.h"
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
		lstrcpy(info.name, _name);
	}
	void SetPosition(const FLOAT& fX, const FLOAT& fY) {
		info.position.x = fX;
		info.position.y = fY;
	}
	void SetPosition(const POSITION& newPoint) {
		info.position = newPoint;
	}

	TCHAR* GetName() {
		return info.name;
	}
	RECT* GetRect() { return &rect; }
	INFO* GetInfo() { return &info; }
	POSITION GetPosition() { return POSITION(info.position); }
	OBJ::TYPE GetObjectType() { return objectType; }
	TYPEORDER GetOrder() { return order; }


	void Update_Rect_Object();
	void SetVisible(BOOL _val) { isVisible = _val; };
	void SetFillColor(const COLORREF& _FillColor) { fillColor = _FillColor; }
	void SetStrokeColor(const COLORREF& _StrokeColor) { strokeColor = _StrokeColor; }
protected:
	RECT rect;
	RECT cRect;
	INFO info;
	OBJ::TYPE objectType = OBJ::END;
	TYPEORDER order;
	COLORREF fillColor = RGB(255, 255, 255);
	COLORREF strokeColor = RGB(0, 0, 0);
	BOOL isVisible = true;
	
};

