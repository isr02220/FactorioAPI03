#include "Obj.h"
#include "Item.h"
#include "Player.h"
#include "CollisionManager.h"

CCollisionManager::CCollisionManager() {
}

CCollisionManager::~CCollisionManager() {
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
	float fX = rDstObj->GetInfo()->fX - rSrcObj->GetInfo()->fX;
	float fY = rDstObj->GetInfo()->fY - rSrcObj->GetInfo()->fY;
	float fDist = sqrtf(fX * fX + fY * fY);
	return fDist < fRadiusSum;
}
void CCollisionManager::CollisionRectEX(list<CObj*>& rDstList, list<CObj*>& rSrcList) {
	float fMoveX = 0.f, fMoveY = 0.f;
	for (auto& rDstObject : rDstList) {
		for (auto& rSrcObject : rSrcList) {
			if (CheckRect(rDstObject, *rSrcObject, &fMoveX, &fMoveY)) {
				float fX = rDstObject->GetInfo()->fX;
				float fY = rDstObject->GetInfo()->fY;
				if (fMoveX > fMoveY) {
					if (fY < rSrcObject->GetInfo()->fY)
						fMoveY *= -1.f;
					rDstObject->SetPos(fX, fY + fMoveY);
				}
				else {
					if (fX < rSrcObject->GetInfo()->fX)
						fMoveX *= -1.f;
					rDstObject->SetPos(fX + fMoveX, fY);
				}

			}
		}
	}

}

bool CCollisionManager::CheckRect(CObj* pDstObject, CObj& rSrcObject, float* pMoveX, float* pMoveY) {
	float fRadiusSumX = static_cast<float>((pDstObject->GetInfo()->iCX >> 1) + (rSrcObject.GetInfo()->iCX >> 1));
	float fRadiusSumY = static_cast<float>((pDstObject->GetInfo()->iCY >> 1) + (rSrcObject.GetInfo()->iCY >> 1));

	float fDistX = fabsf(pDstObject->GetInfo()->fX - rSrcObject.GetInfo()->fX);
	float fDistY = fabsf(pDstObject->GetInfo()->fY - rSrcObject.GetInfo()->fY);

	if (fDistX <= fRadiusSumX && fDistY <= fRadiusSumY) {
		*pMoveX = fRadiusSumX - fDistX;
		*pMoveY = fRadiusSumY - fDistY;
		return true;
	}
	return false;
}