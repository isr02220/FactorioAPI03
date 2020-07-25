#include "ItemCoalOre.h"
#include "CoalOre.h"
#include "Actor.h"
#include "Item.h"
CItemCoalOre::CItemCoalOre() : CItem(){
	objectType = OBJ::ITEM;
	group = ITEM::GROUP::INTERMEDIATE;
	subGroup = ITEM::SUBGROUP::INTERMEDIATE_ResourceFluid;
	lstrcpy(IconName, L"ICON_coal");
	SetName(L"¼®Åº");
	isFuel = true;
}

CItemCoalOre::~CItemCoalOre() {
	Release_Object();
}

void CItemCoalOre::LateUpdate_Object() {

}

void CItemCoalOre::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"ICON_coal");
		if (nullptr == hMemDC)
			return;
		INT iScrollX = (INT)CScrollManager::GetInstance()->GetScrollX();
		INT iScrollY = (INT)CScrollManager::GetInstance()->GetScrollY();
		GdiTransparentBlt(hDC,
			cRect.left + iScrollX,
			cRect.top + iScrollY,
			info.CCX,
			info.CCY,
			hMemDC,
			0,
			0,
			info.CCX,
			info.CCY,
			RGB(255, 0, 255));
	}

}


CItem* CItemCoalOre::GetNewItem() {
	return new CItemCoalOre();
}

CActor* CItemCoalOre::GetNewActor() {
	//return dynamic_cast<CActor*>(CAbstractFactory<CCoalOre>::Create());
	return nullptr;
}