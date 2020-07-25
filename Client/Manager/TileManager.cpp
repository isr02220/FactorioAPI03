#include "framework.h"
#include "TileManager.h"
#include "Tile.h"

CTileManager* CTileManager::m_pInstance = nullptr;
CTileManager::CTileManager()
{
}


CTileManager::~CTileManager()
{
	Release(); 
}

void CTileManager::Ready()
{
	float fX = 0.f, fY = 0.f; 
	m_vecTile.reserve(TILEX * TILEY); 
	for (int i = 0 ; i < TILEY; ++i)
	{
		for (int j = 0 ; j < TILEX; ++j)
		{
			fX = float((TILECX * j) + (TILECX >> 1));
			fY = float((TILECY * i) + (TILECY >> 1));
			CObj* pObj = CAbstractFactory<CTile>::Create(fX, fY); 
			m_vecTile.emplace_back(pObj);
		}
	}
}

void CTileManager::Update()
{
	
}

void CTileManager::Render(HDC hDC)
{
	POINT pt = {};
	RECT rc = {};
	rc.left = -TILECX;
	rc.right = WINCX + TILECX;
	rc.top = -TILECY;
	rc.bottom = WINCX + TILECY;
	for (auto& pTile : m_vecTile) {
		pt.x = (INT)pTile->GetPosition().x + CScrollManager::GetInstance()->GetScrollX();
		pt.y = (INT)pTile->GetPosition().y + CScrollManager::GetInstance()->GetScrollY();

		if (PtInRect(&rc, pt))
			pTile->Render_Object(hDC);
	}
}

void CTileManager::Release()
{
	for (auto& pTile : m_vecTile)
		Safe_Delete(pTile); 
	m_vecTile.clear(); 
	m_vecTile.shrink_to_fit(); 

}
