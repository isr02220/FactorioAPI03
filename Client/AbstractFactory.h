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
	static CObj* Create(const FLOAT& fX, const FLOAT& fY) {
		CObj* pObj = new T;
		pObj->Ready_Object();
		pObj->SetPosition(fX, fY);
		return pObj;
	}
	static CObj* Create(const POSITION& pos) {
		CObj* pObj = new T;
		pObj->Ready_Object();
		pObj->SetPosition(pos);
		return pObj;
	}
};