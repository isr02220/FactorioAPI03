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
	if (pPlayer != nullptr && pPlayer->GetPickedActor())
		thisIndex = PosToIndex(pPlayer->GetPickedActor()->GetPosition());
	{
		if (rDstVec[thisIndex] == nullptr) {
			if (rDstVec[thisIndex + 1] != nullptr && rDstVec[thisIndex + 1]->GetInfo()->iCX / GRIDCX > 1)
				pointObj->OnCollision(rDstVec[thisIndex + 1]);
			else if (rDstVec[thisIndex + GRIDX] != nullptr && rDstVec[thisIndex + GRIDX]->GetInfo()->iCY / GRIDCY > 1)
				pointObj->OnCollision(rDstVec[thisIndex + GRIDX]);
			else if ((rDstVec[thisIndex + GRIDX + 1] != nullptr && rDstVec[thisIndex + GRIDX + 1]->GetInfo()->iCX / GRIDCX > 1) && rDstVec[thisIndex + GRIDX + 1]->GetInfo()->iCY / GRIDCY > 1)
				pointObj->OnCollision(rDstVec[thisIndex + GRIDX + 1]);
			else
				return;
		}
		else {
			pointObj->OnCollision(rDstVec[thisIndex]);
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
	RECT rc = {};
	INT thisIndex = 0;
	DIRECTION::DIR beltDir;
	DIRECTION::DIR tailDir;
	vector<CObj*>* beltVec = CObjManager::GetInstance()->GetVector(OBJ::BELT);
	for (auto SrcObj : rSrcList) {
		INT thisIndex = ((INT)SrcObj->GetPosition().y / GRIDCY * GRIDX + 1) + ((INT)SrcObj->GetPosition().x / GRIDCX - 1);
		if ((*beltVec)[thisIndex] == nullptr)
			continue;
		beltDir = dynamic_cast<CTransportBelt*>((*beltVec)[thisIndex])->GetWalkingState().direction;
		if(dynamic_cast<CTransportBelt*>((*beltVec)[thisIndex])->tailBelt)
			tailDir = dynamic_cast<CTransportBelt*>((*beltVec)[thisIndex])->tailBelt->GetWalkingState().direction;
		else 
			tailDir = beltDir;

		FLOAT dX;
		FLOAT dY;
		FLOAT dist;
		FLOAT rad;
		switch (beltDir) {
		case DIRECTION::DIR::NORTH:
			switch (tailDir) {
			case DIRECTION::DIR::EAST:
				dX = SrcObj->GetPosition().x - (FLOAT)(*beltVec)[thisIndex]->GetRect()->left + 16;
				dY = SrcObj->GetPosition().y - (FLOAT)(*beltVec)[thisIndex]->GetRect()->top + 16;
				dist = sqrtf(dX * dX + dY * dY);
				rad = atan2f(dY, dX) - 0.05f;
				SrcObj->SetPosition(SrcObj->GetPosition() + POSITION((dist* cosf(rad) - dX), (dist * sinf(rad) - dY)));
				break;
			case DIRECTION::DIR::WEST:
				dX = SrcObj->GetPosition().x - (FLOAT)(*beltVec)[thisIndex]->GetRect()->right - 16;
				dY = SrcObj->GetPosition().y - (FLOAT)(*beltVec)[thisIndex]->GetRect()->top + 16;
				dist = sqrtf(dX * dX + dY * dY);
				rad = atan2f(dY, dX) + 0.05f;
				SrcObj->SetPosition(SrcObj->GetPosition() + POSITION((dist * cosf(rad) - dX), (dist * sinf(rad) - dY)));
				break;
			default:
				SrcObj->SetPosition(SrcObj->GetPosition() + POSITION(0.f, -2.f));
				break;
			}
			break;
		case DIRECTION::DIR::EAST:
			switch (tailDir) {
			case DIRECTION::DIR::SOUTH:
				dX = SrcObj->GetPosition().x - (FLOAT)(*beltVec)[thisIndex]->GetRect()->right - 16;
				dY = SrcObj->GetPosition().y - (FLOAT)(*beltVec)[thisIndex]->GetRect()->top + 16;
				dist = sqrtf(dX * dX + dY * dY);
				rad = atan2f(dY, dX) - 0.05f;
				SrcObj->SetPosition(SrcObj->GetPosition() + POSITION((dist * cosf(rad) - dX), (dist * sinf(rad) - dY)));
				break;
			case DIRECTION::DIR::NORTH:
				dX = SrcObj->GetPosition().x - (FLOAT)(*beltVec)[thisIndex]->GetRect()->right - 16;
				dY = SrcObj->GetPosition().y - (FLOAT)(*beltVec)[thisIndex]->GetRect()->bottom - 16;
				dist = sqrtf(dX * dX + dY * dY);
				rad = atan2f(dY, dX) + 0.05f;
				SrcObj->SetPosition(SrcObj->GetPosition() + POSITION((dist * cosf(rad) - dX), (dist * sinf(rad) - dY)));
				break;
			default:
				SrcObj->SetPosition(SrcObj->GetPosition() + POSITION(2.f, 0.f));
				break;
			}
			break;
		case DIRECTION::DIR::SOUTH:
			switch (tailDir) {
			case DIRECTION::DIR::WEST:
				dX = SrcObj->GetPosition().x - (FLOAT)(*beltVec)[thisIndex]->GetRect()->right - 16;
				dY = SrcObj->GetPosition().y - (FLOAT)(*beltVec)[thisIndex]->GetRect()->bottom - 16;
				dist = sqrtf(dX * dX + dY * dY);
				rad = atan2f(dY, dX) - 0.05f;
				SrcObj->SetPosition(SrcObj->GetPosition() + POSITION((dist * cosf(rad) - dX), (dist * sinf(rad) - dY)));
				break;
			case DIRECTION::DIR::EAST:
				dX = SrcObj->GetPosition().x - (FLOAT)(*beltVec)[thisIndex]->GetRect()->left + 16;
				dY = SrcObj->GetPosition().y - (FLOAT)(*beltVec)[thisIndex]->GetRect()->bottom - 16;
				dist = sqrtf(dX * dX + dY * dY);
				rad = atan2f(dY, dX) + 0.05f;
				SrcObj->SetPosition(SrcObj->GetPosition() + POSITION((dist * cosf(rad) - dX), (dist * sinf(rad) - dY)));
				break;
			default:
				SrcObj->SetPosition(SrcObj->GetPosition() + POSITION(0.f, 2.f));
				break;
			}
			break;
		case DIRECTION::DIR::WEST:
			switch (tailDir) {
			case DIRECTION::DIR::SOUTH:
				dX = SrcObj->GetPosition().x - (FLOAT)(*beltVec)[thisIndex]->GetRect()->left + 16;
				dY = SrcObj->GetPosition().y - (FLOAT)(*beltVec)[thisIndex]->GetRect()->top + 16;
				dist = sqrtf(dX * dX + dY * dY);
				rad = atan2f(dY, dX) + 0.05f;
				SrcObj->SetPosition(SrcObj->GetPosition() + POSITION((dist * cosf(rad) - dX), (dist * sinf(rad) - dY)));
				break;
			case DIRECTION::DIR::NORTH:
				dX = SrcObj->GetPosition().x - (FLOAT)(*beltVec)[thisIndex]->GetRect()->left + 16;
				dY = SrcObj->GetPosition().y - (FLOAT)(*beltVec)[thisIndex]->GetRect()->bottom - 16;
				dist = sqrtf(dX * dX + dY * dY);
				rad = atan2f(dY, dX) - 0.05f;
				SrcObj->SetPosition(SrcObj->GetPosition() + POSITION((dist * cosf(rad) - dX), (dist * sinf(rad) - dY)));
				break;
			default:
				SrcObj->SetPosition(SrcObj->GetPosition() + POSITION(-2.f, 0.f));
				break;
			}
			break;
		default:
			break;
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