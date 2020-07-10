#pragma once
#include "Obj.h"
class CBgObj;
class CBackground :
    public CObj {
public:
    virtual void Ready_Object() override;
    virtual INT Update_Object() override;
    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual void Release_Object() override;
    virtual void OnCollision(CObj* _TargetObj) override;
    
protected:
    list<CBgObj*> m_ListBgFar    ;
    list<CBgObj*> m_ListBgMiddle ;
    list<CBgObj*> m_ListBgClose  ;
    FLOAT m_spanX = 0;
    FLOAT m_spanY = 0;
};

class CBgObj {
public:
    CBgObj(LONG _left, LONG _top, LONG _right, LONG _bottom) {
        SetRect((FLOAT)_left, (FLOAT)_top, (FLOAT)_right, (FLOAT)_bottom);
    }
    void SetRect(FLOAT _left, FLOAT _top, FLOAT _right, FLOAT _bottom) {
        fLeft = _left; fTop = _top; fRight = _right; fBottom = _bottom;
    }
    void MoveRect(FLOAT _dx, FLOAT _dy) {
        fLeft += _dx; fTop += _dy; fRight += _dx; fBottom += _dy;
    }
    void Draw(HDC hDC) {
        Rectangle(hDC, (INT)fLeft, (INT)fTop, (INT)fRight, (INT)fBottom);
    }

    FLOAT fLeft;
    FLOAT fTop;
    FLOAT fRight;
    FLOAT fBottom;
    
};
