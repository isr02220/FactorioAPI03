#include "framework.h"
#include "ObjManager.h"
#include "TransportBelt.h"
#include "Obj.h"

CObjManager* CObjManager::m_pInstance = nullptr;

CObjManager::CObjManager() {
	for (int i = 0; i < OBJ::END; ++i) {
		vecObj[i].resize(GRIDX * GRIDY, nullptr);
	}
}


CObjManager::~CObjManager() {
	ReleaseObjectManager();
}

void CObjManager::AddObject(CObj* pObj, OBJ::TYPE eID) {
	m_listObj[eID].emplace_back(pObj);
}

void CObjManager::InsertObject(CObj* pObj, OBJ::TYPE eID) {
	vecObj[eID][((INT)pObj->GetPosition().y / GRIDCY * GRIDY) + ((INT)pObj->GetPosition().x / GRIDCX)] = pObj;
}

void CObjManager::UpdateObjectManager() {
	// �ֽ� �ڵ� ! 
	for (size_t i = 0; i < OBJ::END; ++i) {
		auto iter_end = m_listObj[i].end();
		for (auto iter = m_listObj[i].begin(); iter != iter_end; ) {
			int iEvent = (*iter)->Update_Object();
			if (STATE_DEAD == iEvent) {
				Safe_Delete(*iter);
				iter = m_listObj[i].erase(iter);
			}
			else
				++iter;
		}
	}

	for (size_t i = 0; i < OBJ::END; ++i) {
		for (auto& Object : vecObj[i]) {
			if (Object == nullptr)
				continue;
			int iEvent = Object->Update_Object();
			if (STATE_DEAD == iEvent) {
				Safe_Delete(Object);
			}
		}
	}
}

void CObjManager::LateUpdateObjectManager() {
	CCollisionManager::CollisionBelt(m_listObj[OBJ::PLAYER]);
	CCollisionManager::CollisionBelt(m_listObj[OBJ::ITEM]);
	CCollisionManager::CollisionSphere(m_listObj[OBJ::PLAYER], m_listObj[OBJ::ITEM]);
	CCollisionManager::CollisionSphere(m_listObj[OBJ::MONSTER], m_listObj[OBJ::BULLET]);
	CCollisionManager::CollisionSphere(m_listObj[OBJ::PLAYER], m_listObj[OBJ::MONSTERBULLET]);
	CCollisionManager::CollisionRectEX(m_listObj[OBJ::PLAYER], m_listObj[OBJ::BELT]);
	CCollisionManager::CollisionPoint(m_listObj[OBJ::MOUSE].front(), m_listObj[OBJ::PLAYER]);
	CCollisionManager::CollisionPoint(m_listObj[OBJ::MOUSE].front(), vecObj[OBJ::RESOURCEORE]);
	CCollisionManager::CollisionPoint(m_listObj[OBJ::MOUSE].front(), vecObj[OBJ::BELT]);
	CCollisionManager::CollisionPoint(m_listObj[OBJ::MOUSE].front(), vecObj[OBJ::ENTITY]);

	for (int i = 0; i < OBJ::END; ++i) {
		for (auto& pObj : m_listObj[i]) {
			pObj->LateUpdate_Object();
		}
		for (auto& pObj : vecObj[i]) {
			if (pObj == nullptr)
				continue;
			pObj->LateUpdate_Object();
		}
	}
}

void CObjManager::RenderObjectManager(HDC hDC) {

	INT scrollX = -CScrollManager::GetInstance()->GetScrollX();
	INT scrollY = -CScrollManager::GetInstance()->GetScrollY();
	INT startX = scrollX / GRIDCX;
	INT startY = scrollY / GRIDCY;
	INT endX = (scrollX + WINCX) / GRIDCX;
	INT endY = (scrollY + WINCY) / GRIDCY;
	if (startX < 0) startX = 0;
	if (startY < 0) startY = 0;
	if (endX > GRIDX) endX = GRIDX;
	if (endY > GRIDY) endY = GRIDY;
	for (int i = 0; i < OBJ::END; ++i) {

		for (INT y = startY; y < endY; y++) {
			for (INT x = startX; x < endX; x++) {
				if (i == OBJ::BELTEND) {
					if (vecObj[i-1][(y * (INT)GRIDX) + x] == nullptr)
						continue;
					CTransportBelt* tempBelt = dynamic_cast<CTransportBelt*>(vecObj[i - 1][INT(INT(y * GRIDX) + x)]);
					if ((tempBelt->headBelt == nullptr || tempBelt->headBelt->tailBelt != tempBelt) &&
						(tempBelt->headBelt == nullptr || tempBelt->headBelt->headBelt == nullptr || tempBelt->headBelt->headBelt != tempBelt)) {
							HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"hr-transport-belt");
							GdiTransparentBlt(hDC,
								tempBelt->GetCRect()->left - scrollX + tempBelt->HeadTailDistX,
								tempBelt->GetCRect()->top - scrollY + tempBelt->HeadTailDistY,
								tempBelt->GetInfo()->CCX,
								tempBelt->GetInfo()->CCY,
								hMemDC,
								CTransportBelt::beltSpriteIndexX / CTransportBelt::beltSpriteFrameDelay * tempBelt->GetInfo()->CCX,
								tempBelt->headSpriteIndex * tempBelt->GetInfo()->CCY,
								tempBelt->GetInfo()->CCX,
								tempBelt->GetInfo()->CCY,
								RGB(255, 0, 255));
						
					}
				}
				else {
					if (vecObj[i][(y * GRIDX) + x] == nullptr)
						continue;
					vecObj[i][(y * GRIDX) + x]->Render_Object(hDC);
				}
			}
		}

		for (auto& pObj : m_listObj[i]) {
			pObj->Render_Object(hDC);
		}
	}
}

void CObjManager::ReleaseObjectManager() {
	for (int i = 0; i < OBJ::END; ++i) {
		for (auto& pObj : m_listObj[i])
			Safe_Delete(pObj);
		m_listObj[i].clear();

		for (auto& pObj : vecObj[i])
			Safe_Delete(pObj);
		vecObj[i].clear();
		vecObj[i].shrink_to_fit();
	}
}
