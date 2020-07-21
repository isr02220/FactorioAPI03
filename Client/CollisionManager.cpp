#include "Obj.h"
#include "Item.h"
#include "Player.h"
#include "Mouse.h"
#include "CollisionManager.h"
#include "TransportBelt.h"

CCollisionManager::CCollisionManager() {
}

CCollisionManager::~CCollisionManager() {
}

void CCollisionManager::CollisionPoint(CObj* pointObj, list<CObj*>& rDstList) {
	POSITION pos;
	POINT pt = {};
	for (auto DstObj : rDstList) {
		pos = ToGridPos(pointObj->GetPosition(), DstObj->GetInfo()->iCX);
		pt.x = (INT)pos.x;
		pt.y = (INT)pos.y;
		if (PtInRect(DstObj->GetRect(), pt))
			pointObj->OnCollision(DstObj);
		//if (CheckPoint(pointObj->GetPosition(), DstObj->GetInfo(), &pos)) {
		//	pointObj->OnCollision(DstObj);
		//}
	}
}

void CCollisionManager::CollisionPoint(CObj* pointObj, vector<CObj*>& rDstVec) {
	// 범위 수정할것
	INT thisIndex = PosToIndex(pointObj->GetPosition());
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(CObjManager::GetInstance()->GetPlayer());
	if (pPlayer != nullptr && pPlayer->GetPickedActor()) {
		CActor* pPickedActor = pPlayer->GetPickedActor();
		pPickedActor->Update_Rect_Object();
		INT startX = INT(pPickedActor->GetPosition().x - GRIDCX * 4) / GRIDCX;
		INT startY = INT(pPickedActor->GetPosition().y - GRIDCY * 4) / GRIDCY;
		INT endX   = INT(pPickedActor->GetPosition().x + GRIDCX * 4) / GRIDCX;
		INT endY   = INT(pPickedActor->GetPosition().y + GRIDCY * 4) / GRIDCY;
		for (INT y = startY; y < endY; y++) {
			for (INT x = startX; x < endX; x++) {
				if (rDstVec[(y * GRIDX) + x] == nullptr)
					continue;
				RECT rc = {};
				if (IntersectRect(&rc, pPickedActor->GetRect(), rDstVec[(y * GRIDX) + x]->GetRect()))
					pointObj->OnCollision(rDstVec[(y * GRIDX) + x]);
			}
		}
	}
	else {
		POSITION tPos = ToGridPos(pointObj->GetPosition(), GRIDCX);
		INT startX = INT(tPos.x - GRIDCX * 4) / GRIDCX;
		INT startY = INT(tPos.y - GRIDCY * 4) / GRIDCY;
		INT endX   = INT(tPos.x + GRIDCX * 4) / GRIDCX;
		INT endY   = INT(tPos.y + GRIDCY * 4) / GRIDCY;
		for (INT y = startY; y < endY; y++) {
			for (INT x = startX; x < endX; x++) {
				if (rDstVec[(y * GRIDX) + x] == nullptr)
					continue;
				POINT pt = {};
				pt.x = INT(tPos.x);
				pt.y = INT(tPos.y);
				if (PtInRect(rDstVec[(y * GRIDX) + x]->GetRect(), pt))
					pointObj->OnCollision(rDstVec[(y * GRIDX) + x]);
			}
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

void CCollisionManager::CollisionBelt(list<CObj*>& rSrcList) {
	INT thisIndex = 0;
	vector<CObj*>* beltVec = CObjManager::GetInstance()->GetVector(OBJ::BELT);
	for (auto belt : *beltVec)
		if (dynamic_cast<CTransportBelt*>(belt)) dynamic_cast<CTransportBelt*>(belt)->listItemOnBelt.clear();
	for (auto SrcObj : rSrcList) {
		INT thisIndex = ((INT)SrcObj->GetPosition().y / GRIDCY * GRIDX + 1) + ((INT)SrcObj->GetPosition().x / GRIDCX - 1);
		if ((*beltVec)[thisIndex] == nullptr)
			continue;
		dynamic_cast<CTransportBelt*>((*beltVec)[thisIndex])->listItemOnBelt.emplace_back(SrcObj);
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

	if (point.x >= rDstInfo->position.x - (rDstInfo->iCX >> 1) &&
		point.x <= rDstInfo->position.x + (rDstInfo->iCX >> 1) &&
		point.y >= rDstInfo->position.y - (rDstInfo->iCY >> 1) &&
		point.y <= rDstInfo->position.y + (rDstInfo->iCY >> 1)) {
		*outPosition = rDstInfo->position;
		return true;
	}
	else {
		return false;
	}
}