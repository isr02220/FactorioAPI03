#include "EquipmentUI.h"
#include "Inventory.h"
#include "ItemStack.h"
#include "Obj.h"
#include "Actor.h"
#include "Mouse.h"

#include "ItemHand.h"

CEquipmentUI::CEquipmentUI() {
	SetName(L"EquipmentUI");
	objectType = OBJ::UI;
	strokeColor = RGB(128, 128, 255);
	fillColor = RGB(0, 255, 255);
}

CEquipmentUI::~CEquipmentUI() {
}

void CEquipmentUI::Ready_Object() {
	isVisible = false;
	info.iCX = 86;
	info.iCY = 82;
	info.CCX = 86;
	info.CCY = 82;
}

INT CEquipmentUI::Update_Object() {
	
	if (!isVisible) {
		active = false;
		return STATE_NO_EVENT;
	}
	if (!active) {
		active = true;
		return STATE_NO_EVENT;
	}
	if (armorStack == nullptr && targetActor->inventory) {
		for (auto itemStack : targetActor->inventory->listItemStack) {
			if (!lstrcmp(itemStack->item->IconName, L"ICON_light-armor")) {
				armorStack = itemStack;
				auto iter = find_if(targetActor->inventory->listItemStack.begin(),
					targetActor->inventory->listItemStack.end(),
					[&](CItemStack* tItemStack) { return itemStack == tItemStack; });

				if (iter != targetActor->inventory->listItemStack.end())
					targetActor->inventory->listItemStack.erase(iter);
				break;
			}
		}
	}
	if (weaponStack == nullptr && targetActor->inventory) {
		for (auto itemStack : targetActor->inventory->listItemStack) {
			if (!lstrcmp(itemStack->item->IconName, L"ICON_submachine-gun")) {
				weaponStack = itemStack;
				auto iter = find_if(targetActor->inventory->listItemStack.begin(),
					targetActor->inventory->listItemStack.end(),
					[&](CItemStack* tItemStack) { return itemStack == tItemStack; });

				if (iter != targetActor->inventory->listItemStack.end())
					targetActor->inventory->listItemStack.erase(iter);
				break;
			}
		}
	}
	if (magazineStack == nullptr && targetActor->inventory) {
		for (auto itemStack : targetActor->inventory->listItemStack) {
			if (!lstrcmp(itemStack->item->IconName, L"ICON_firearm-magazine")) {
				magazineStack = new CItemStack(itemStack->item->GetNewItem());
				break;
			}
		}
	}

	return STATE_NO_EVENT;
}

void CEquipmentUI::LateUpdate_Object() {
}

void CEquipmentUI::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible && targetActor) {

		if (targetActor != CObjManager::GetInstance()->GetPlayer()) {
			POSITION pos = {};
			pos.x = (FLOAT)dynamic_cast<CActor*>(CObjManager::GetInstance()->GetPlayer())->GUI->GetRect()->right + (info.iCX >> 1);
			pos.y = (FLOAT)dynamic_cast<CActor*>(CObjManager::GetInstance()->GetPlayer())->GUI->GetPosition().y;
			SetPosition(pos);
			CObj::Update_Rect_Object();
		}

		HDC hMemDC                = CBitmapManager::GetInstance()->FindImage(L"GUI_Equipment"      );
		HDC hMemEquipedArmorDC    = CBitmapManager::GetInstance()->FindImage(L"GUI_EquipedArmor"   );
		HDC hMemEquipedMagazineDC = CBitmapManager::GetInstance()->FindImage(L"GUI_EquipedMagazine");
		HDC hMemEquipedSMGDC      = CBitmapManager::GetInstance()->FindImage(L"GUI_EquipedSMG"     );

		if (nullptr == hMemDC)
			return;

		BitBlt(hDC,
			cRect.left,
			cRect.top,
			info.CCX,
			info.CCY,
			hMemDC,
			0,0,
			SRCCOPY);
		if(armorStack)
			BitBlt(hDC, cRect.left + 8, cRect.top + 42, 36, 36, hMemEquipedArmorDC, 0, 0, SRCCOPY);
		if(weaponStack)
			BitBlt(hDC, cRect.left + 46, cRect.top + 4, 36, 36, hMemEquipedSMGDC, 0, 0, SRCCOPY);
		if(magazineStack)
			BitBlt(hDC, cRect.left + 46, cRect.top + 42, 36, 36, hMemEquipedMagazineDC, 0, 0, SRCCOPY);

		TCHAR szBuffer[32];
		RECT rc = {};
		LOGFONT* logCountFont = CFontManager::GetInstance()->FindFont(L"±¼¸²Ã¼");
		HFONT countFont = CreateFontIndirect(logCountFont);
		HFONT oldFont = (HFONT)SelectObject(hDC, countFont);
		if (magazineStack) {
			UINT amount = 0;
			for (auto itemStack : targetActor->inventory->listItemStack) {
				if (!lstrcmp(itemStack->item->IconName, L"ICON_firearm-magazine")) {
					amount += itemStack->size;
				}
			}
			SetRect(&rc, cRect.left + 46, cRect.top +64, cRect.left +80, cRect.top + 80);
			SetTextColor(hDC, RGB(0, 0, 0));
			wsprintf(szBuffer, L"%d", amount);
			DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_RIGHT | DT_NOCLIP);
			SetTextColor(hDC, RGB(255, 255, 255));
			OffsetRect(&rc, -1, -1);
			DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_RIGHT | DT_NOCLIP);
			SetTextColor(hDC, RGB(0, 0, 0));
			
			
		}

		SelectObject(hDC, oldFont);
		DeleteObject(countFont);
	}
}

void CEquipmentUI::Release_Object() {
}

void CEquipmentUI::OnCollision(CObj* _TargetObj) {
}
