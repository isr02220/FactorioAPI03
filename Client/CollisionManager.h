#pragma once
#include "framework.h"
class CObj;
class CCollisionManager {
public:
	CCollisionManager();
	~CCollisionManager();
public:
	static void CollisionRect(list<CObj*>& rDstList, list<CObj*>& rSrcList);
	static void CollisionSphere(list<CObj*>& rDstList, list<CObj*>& rSrcList);
	static bool CheckSphere(CObj* rDstObj, CObj* rSrcObj);
	static void CollisionRectEX(list<CObj*>& rDstList, list<CObj*>& rSrcList);
	static bool CheckRect(CObj* pDstObject, CObj& rSrcObject, float* pMoveX, float* pMoveY);
};