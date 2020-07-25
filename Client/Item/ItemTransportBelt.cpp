#include "ItemTransportBelt.h"
#include "TransportBelt.h"
#include "Actor.h"
#include "Item.h"
CItemTransportBelt::CItemTransportBelt() : CItem() {
	objectType = OBJ::ITEM;
	group = ITEM::GROUP::LOGISTICS;
	subGroup = ITEM::SUBGROUP::LOGISTICS_BeltTransport;
	lstrcpy(IconName, L"ICON_transport-belt");
	SetName(L"운송 벨트");
}

CItemTransportBelt::~CItemTransportBelt() {
	Release_Object();
}

void CItemTransportBelt::LateUpdate_Object() {

}

void CItemTransportBelt::Render_Object(HDC hDC) {
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


CItem* CItemTransportBelt::GetNewItem() {
	return new CItemTransportBelt();
}

CActor* CItemTransportBelt::GetNewActor() {
	return dynamic_cast<CActor*>(CAbstractFactory<CTransportBelt>::Create());
}