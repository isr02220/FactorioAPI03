#include "framework.h"
#include "ObjManager.h"
#include "CollisionManager.h"
#include "Obj.h"

CObjManager* CObjManager::m_pInstance = nullptr;

CObjManager::CObjManager() {
}


CObjManager::~CObjManager() {
	ReleaseObjectManager();
}

void CObjManager::AddObject(CObj* pObj, OBJ::ID eID) {
	m_listObj[eID].emplace_back(pObj);
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
}

void CObjManager::LateUpdateObjectManager() {
	for (int i = 0; i < OBJ::END; ++i) {
		for (auto& pObj : m_listObj[i]) {
			pObj->LateUpdate_Object();
		}
	}
	CCollisionManager::CollisionSphere(m_listObj[OBJ::MONSTER], m_listObj[OBJ::BULLET]);
	CCollisionManager::CollisionSphere(m_listObj[OBJ::MONSTER], m_listObj[OBJ::BOMB]);
	CCollisionManager::CollisionSphere(m_listObj[OBJ::PLAYER], m_listObj[OBJ::MONSTERBULLET]);
	CCollisionManager::CollisionSphere(m_listObj[OBJ::PLAYER], m_listObj[OBJ::ITEM]);
	CCollisionManager::CollisionRectEX(m_listObj[OBJ::PLAYER], m_listObj[OBJ::FLOOR]);
	CCollisionManager::CollisionRectEX(m_listObj[OBJ::MONSTER], m_listObj[OBJ::FLOOR]);
	CCollisionManager::CollisionRectEX(m_listObj[OBJ::ITEM], m_listObj[OBJ::FLOOR]);
	
}

void CObjManager::RenderObjectManager(HDC hDC) {
	for (int i = 0; i < OBJ::END; ++i) {
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
	}
}