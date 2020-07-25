#include "framework.h"
#include "BeltManager.h"
#include "TransportBelt.h"

CBeltManager* CBeltManager::m_pInstance = nullptr;
CBeltManager::CBeltManager() {
}


CBeltManager::~CBeltManager() {
	Release();
}

void CBeltManager::Ready() {
	vecBelt.resize(GRIDX * GRIDY, nullptr);
}

void CBeltManager::Update() {

}

void CBeltManager::Render(HDC hDC) {
	for (auto& Belt : vecBelt) {
		if (Belt == nullptr)
			continue;
		POINT pt = {};
		RECT rc = {};
		rc.left = -TILECX;
		rc.right = WINCX + TILECX;
		rc.top = -TILECY;
		rc.bottom = WINCX + TILECY;
		pt.x = (INT)Belt->GetPosition().x - CScrollManager::GetInstance()->GetScrollX();
		pt.y = (INT)Belt->GetPosition().y - CScrollManager::GetInstance()->GetScrollY();

		if (PtInRect(&rc, pt))
			Belt->Render_Object(hDC);
	}
}

void CBeltManager::Release() {
	for (auto& pTile : vecBelt)
		Safe_Delete(pTile);
	vecBelt.clear();
	vecBelt.shrink_to_fit();

}
