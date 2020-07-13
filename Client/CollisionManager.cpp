#include "Obj.h"
#include "Item.h"
#include "Player.h"
#include "CollisionManager.h"

CCollisionManager::CCollisionManager() {
}

CCollisionManager::~CCollisionManager() {
}

void CCollisionManager::CollisionPoint(CObj* pointObj, list<CObj*>& rDstList) {
	POSITION pos;
	for (auto DstObj : rDstList) {
		if (CheckPoint(pointObj->GetPosition(), DstObj->GetInfo(), &pos)) {
			pointObj->OnCollision(DstObj);
		}
	}
}

void CCollisionManager::CollisionRect(list<CObj*>& rDstList, list<CObj*>& rSrcList) {
	RECT rc = {};
	for (auto DstObj : rDstList) {
		for (auto SrcObj : rSrcList) {
			if (IntersectRect(&rc, DstObj->GetRect(), SrcObj->GetRect())) {
				DstObj->OnCollision(SrcObj);
				SrcObj->OnCollision(DstObj);
			}
		}
	}
}

void CCollisionManager::CollisionSphere(list<CObj*>& rDstList, list<CObj*>& rSrcList) {

	for (auto DstObj : rDstList) {
		for (auto SrcObj : rSrcList) {
			if (CheckSphere(DstObj, SrcObj)) {
				DstObj->OnCollision(SrcObj);
				SrcObj->OnCollision(DstObj);
			}
		}
	}
}

bool CCollisionManager::CheckSphere(CObj* rDstObj, CObj* rSrcObj) {
	float fRadiusSum = static_cast<float>((rDstObj->GetInfo()->iCX >> 1) + (rSrcObj->GetInfo()->iCX >> 1));
	POSITION tempPos = rDstObj->GetInfo()->position - rSrcObj->GetInfo()->position;
	float fDist = sqrtf(tempPos.x * tempPos.x + tempPos.y * tempPos.y);
	return fDist < fRadiusSum;
}
void CCollisionManager::CollisionRectEX(list<CObj*>& rDstList, list<CObj*>& rSrcList) {
	FLOAT fMoveX = 0.f, fMoveY = 0.f;
	for (auto& rDstObject : rDstList) {
		for (auto& rSrcObject : rSrcList) {
			if (CheckRect(rDstObject, *rSrcObject, &fMoveX, &fMoveY)) {
				POSITION dstPos = rDstObject->GetInfo()->position;
				if (fMoveX > fMoveY) {
					if (dstPos.y < rSrcObject->GetInfo()->position.y)
						fMoveY *= -1.f;
					rDstObject->SetPosition(dstPos + POSITION(0, fMoveY));
				}
				else {
					if (dstPos.x < rSrcObject->GetInfo()->position.x)
						fMoveX *= -1.f;
					rDstObject->SetPosition(dstPos + POSITION(fMoveX, 0));
				}

			}
		}
	}

}

bool CCollisionManager::CheckRect(CObj* pDstObject, CObj& rSrcObject, float* pMoveX, float* pMoveY) {
	float fRadiusSumX = static_cast<float>((pDstObject->GetInfo()->iCX >> 1) + (rSrcObject.GetInfo()->iCX >> 1));
	float fRadiusSumY = static_cast<float>((pDstObject->GetInfo()->iCY >> 1) + (rSrcObject.GetInfo()->iCY >> 1));

	float fDistX = fabsf(pDstObject->GetInfo()->position.x - rSrcObject.GetInfo()->position.x);
	float fDistY = fabsf(pDstObject->GetInfo()->position.y - rSrcObject.GetInfo()->position.y);

	if (fDistX <= fRadiusSumX && fDistY <= fRadiusSumY) {
		*pMoveX = fRadiusSumX - fDistX;
		*pMoveY = fRadiusSumY - fDistY;
		return true;
	}
	return false;
}

bool CCollisionManager::CheckPoint(const POSITION& point, INFO* rDstInfo, POSITION* outPosition) {

	if (point.x > rDstInfo->position.x - (rDstInfo->iCX >> 1) &&
		point.x < rDstInfo->position.x + (rDstInfo->iCX >> 1) &&
		point.y > rDstInfo->position.y - (rDstInfo->iCY >> 1) &&
		point.y < rDstInfo->position.y + (rDstInfo->iCY >> 1)) {
		*outPosition = rDstInfo->position;
		return true;
	}
	else {
		return false;
	}
}