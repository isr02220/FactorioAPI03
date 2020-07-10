#pragma once
#include "framework.h"
class CObj;
template<typename T>
class CAbstractFactory {
public:
	static CObj* Create() {
		CObj* pObj = new T;
		pObj->Ready_Object();
		return pObj;
	}
	static CObj* Create(float fX, float fY) {
		CObj* pObj = new T;
		pObj->Ready_Object();
		pObj->SetPos(fX, fY);
		return pObj;
	}
	static CObj* CreateWithForce(float fX, float fY, float forceX, float forceY) {
		CObj* pObj = new T(forceX, forceY);
		pObj->Ready_Object();
		pObj->SetPos(fX, fY);
		return pObj;
	}
};