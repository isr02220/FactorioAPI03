#include "ItemSolarPanel.h"
//#include "SolarPanel.h"
#include "Actor.h"
#include "Item.h"
CItemSolarPanel::CItemSolarPanel() : CItem() {
	objectType = OBJ::ITEM;
	group = ITEM::GROUP::PRODUCTION;
	subGroup = ITEM::SUBGROUP::PRODUCTION_Electricity;
	lstrcpy(IconName, L"ICON_solar-panel");
	SetName(L"ÅÂ¾ç±¤ ÆÐ³Î");
}

CItemSolarPanel::~CItemSolarPanel() {
	Release_Object();
}

void CItemSolarPanel::LateUpdate_Object() {

}

void CItemSolarPanel::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(IconName);
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


CItem* CItemSolarPanel::GetNewItem() {
	return new CItemSolarPanel();
}

CActor* CItemSolarPanel::GetNewActor() {
	//return dynamic_cast<CActor*>(CAbstractFactory<CSolarPanel>::Create());
	return nullptr;
}