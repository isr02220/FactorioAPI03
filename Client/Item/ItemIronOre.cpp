#include "ItemIronOre.h"
#include "IronOre.h"
#include "Actor.h"
#include "Item.h"
CItemIronOre::CItemIronOre() : CItem() {
	objectType = OBJ::ITEM;
	group = ITEM::GROUP::INTERMEDIATE;
	subGroup = ITEM::SUBGROUP::INTERMEDIATE_ResourceFluid;
	lstrcpy(IconName, L"ICON_iron-ore");
	SetName(L"ö����");
}

CItemIronOre::~CItemIronOre() {
	Release_Object();
}

void CItemIronOre::LateUpdate_Object() {

}

void CItemIronOre::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"ICON_iron-ore");
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

CItem* CItemIronOre::GetNewItem() {
	return new CItemIronOre();
}

CActor* CItemIronOre::GetNewActor() {
	//return dynamic_cast<CActor*>(CAbstractFactory<CIronOre>::Create());
	return nullptr;
}