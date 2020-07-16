#include "framework.h"
#include "ObjManager.h"
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
	// 최신 코드 ! 
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
	CCollisionManager::CollisionBelt(m_listObj[OBJ::PLAYER]);
	CCollisionManager::CollisionSphere(m_listObj[OBJ::PLAYER], m_listObj[OBJ::ITEM]);
	CCollisionManager::CollisionRectEX(m_listObj[OBJ::PLAYER], m_listObj[OBJ::ENTITY]);
	CCollisionManager::CollisionPoint(m_listObj[OBJ::MOUSE].front(), m_listObj[OBJ::PLAYER]);
	CCollisionManager::CollisionPoint(m_listObj[OBJ::MOUSE].front(), m_listObj[OBJ::ENTITY]);
	CCollisionManager::CollisionPoint(m_listObj[OBJ::MOUSE].front(), vecObj[OBJ::ENTITY]);
	
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
				if (vecObj[i][(y * GRIDX) + x] == nullptr)
					continue;
				vecObj[i][(y * GRIDX) + x]->Render_Object(hDC);
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
