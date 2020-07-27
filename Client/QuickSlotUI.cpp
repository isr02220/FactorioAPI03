#include "QuickSlotUI.h"
#include "Obj.h"
#include "Inventory.h"
#include "ItemStack.h"
#include "Obj.h"
#include "Item.h"
#include "Actor.h"
#include "Mouse.h"

vector<QuickSlot*>* CQuickSlotUI::vecQuickSlot1 = nullptr;
vector<QuickSlot*>* CQuickSlotUI::vecQuickSlot2 = nullptr;

CQuickSlotUI::CQuickSlotUI() {
	if (!vecQuickSlot1) {
		vecQuickSlot1 = new vector<QuickSlot*>;
		vecQuickSlot2 = new vector<QuickSlot*>;
		vecQuickSlot1->resize(10, nullptr);
		vecQuickSlot2->resize(10, nullptr);
	}
	vecSelected = vecQuickSlot1;
	objectType = OBJ::UI;
	strokeColor = RGB(128, 128, 255);
	fillColor = RGB(0, 255, 255);
}

CQuickSlotUI::~CQuickSlotUI() {
	for (auto item : *vecQuickSlot1)
		Safe_Delete(item);
	for (auto item : *vecQuickSlot2)
		Safe_Delete(item);
	vecQuickSlot1->clear();
	vecQuickSlot2->clear();
	vecQuickSlot1->shrink_to_fit();
	vecQuickSlot2->shrink_to_fit();
	Safe_Delete(vecQuickSlot1);
	Safe_Delete(vecQuickSlot2);
}

void CQuickSlotUI::Ready_Object() {
	isVisible = false;
	info.iCX = 512;
	info.iCY = 96;
	info.CCX = 512;
	info.CCY = 96;
}

INT CQuickSlotUI::Update_Object() {
	if (!isVisible) {
		active = false;
		return STATE_NO_EVENT;
	}
	if (!active) {
		active = true;
		return STATE_NO_EVENT;
	}
	POINT pt = {};
	RECT rc = {};
	selectedIndex = 0;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	CMouse* playerMouse = dynamic_cast<CMouse*>(CObjManager::GetInstance()->GetList(OBJ::MOUSE)->front());
	INT indexX = 0;

	for (auto& slot : *vecQuickSlot1) {
		INT cx = rect.left + 59 + indexX * 38;
		INT cy = rect.top + 49;
		SetRect(&rc, cx, cy, cx + 36, cy + 36);
		if (PtInRect(&rc, pt)) {
			selectedIndex = indexX + 1;
			selectedSlot = 0;
			if (CKeyManager::GetInstance()->OnPress(KEY::PrimaryAction)) {
				if (slot) 
					SelectedQuickSlot = slot;
				else 
					if (playerMouse->cursorStack)
						slot = new QuickSlot(playerMouse->cursorStack->item->GetNewItem());
			}
			else if (CKeyManager::GetInstance()->OnPress(KEY::ClearSlot)) {
				if (slot)
					Safe_Delete(slot);
			}
		}
		if (slot) {
			slot->amount = 0;
			for (auto itemStack : targetActor->inventory->listItemStack) {
				if (!lstrcmp(itemStack->item->IconName, slot->item->IconName)) {
					slot->amount += itemStack->size;
				}
			}
			if (playerMouse->cursorStack && !lstrcmp(playerMouse->cursorStack->item->IconName, slot->item->IconName))
				slot->amount += playerMouse->cursorStack->size;
		}
		indexX++;
	}
	indexX = 0;
	for (auto& slot : *vecQuickSlot2) {
		INT cx = rect.left + 59 + indexX * 38;
		INT cy = rect.top + 9;
		SetRect(&rc, cx, cy, cx + 36, cy + 36);
		if (PtInRect(&rc, pt)) {
			selectedIndex = indexX + 1;
			selectedSlot = 1;
			if (CKeyManager::GetInstance()->OnPress(KEY::PrimaryAction)) {
				if (slot) 
					SelectedQuickSlot = slot;
				else 
					if (playerMouse->cursorStack)
						slot = new QuickSlot(playerMouse->cursorStack->item->GetNewItem());
			}
			else if (CKeyManager::GetInstance()->OnPress(KEY::ClearSlot)) {
				if (slot)
					Safe_Delete(slot);
			}
		}
		if (slot) {
			slot->amount = 0;
			for (auto itemStack : targetActor->inventory->listItemStack) {
				if (!lstrcmp(itemStack->item->IconName, slot->item->IconName)) {
					slot->amount += itemStack->size;
				}
			}
			if (playerMouse->cursorStack && !lstrcmp(playerMouse->cursorStack->item->IconName, slot->item->IconName))
				slot->amount += playerMouse->cursorStack->size;
		}
		indexX++;
	}

	return STATE_NO_EVENT;
}

void CQuickSlotUI::LateUpdate_Object() {

}

void CQuickSlotUI::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"GUI_QuickSlot");
		HDC hMemSelectedSlotDC = CBitmapManager::GetInstance()->FindImage(L"GUI_SelectedSlot");

		if (nullptr == hMemDC)
			return;

		BitBlt(hDC,
			cRect.left,
			cRect.top,
			info.CCX,
			info.CCY,
			hMemDC,
			0, 0,
			SRCCOPY);

		INT offsetX;
		if (selectedIndex) {
			offsetX = ((selectedIndex - 1) * 38);
			INT offsetY = 0;
			if (selectedIndex > 5)
				offsetX += 5;
			if (!selectedSlot)
				offsetY = 40;
			BitBlt(hDC,
				cRect.left + 59 + offsetX,
				cRect.top + 9 + offsetY,
				34,
				34,
				hMemSelectedSlotDC,
				0,
				0,
				SRCCOPY);
		}
		if (vecQuickSlot1 && vecQuickSlot2) {
			LOGFONT* logCountFont = CFontManager::GetInstance()->FindFont(L"±¼¸²Ã¼");
			HFONT countFont = CreateFontIndirect(logCountFont);
			HFONT oldFont = (HFONT)SelectObject(hDC, countFont);
			INT index = 0;
			RECT rc = {};
			TCHAR szBuffer[32];
			for (auto slot : *vecQuickSlot1) {
				offsetX = index * 38;
				if (index >= 5)
					offsetX += 5;
				if (slot) {
					GdiTransparentBlt(hDC,
						cRect.left + 61 + offsetX,
						cRect.top + 51,
						32,
						32,
						slot->hMemDC,
						0,
						0,
						32,
						32,
						RGB(255, 0, 255));
					SetTextColor(hDC, RGB(0, 0, 0));
					SetRect(&rc, cRect.left + 61 + offsetX, cRect.top + 71, cRect.left + 91 + offsetX, cRect.top + 91);
					wsprintf(szBuffer, L"%d", slot->amount);
					DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_RIGHT | DT_NOCLIP);
					SetTextColor(hDC, RGB(255, 255, 255));
					OffsetRect(&rc, -1, -1);
					DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_RIGHT | DT_NOCLIP);
					SetTextColor(hDC, RGB(0, 0, 0));
				}
				index++;
			}
			index = 0;
			for (auto slot : *vecQuickSlot2) {
				offsetX = index * 38;
				if (index >= 5)
					offsetX += 5;
				if (slot)
					GdiTransparentBlt(hDC,
						cRect.left + 61 + offsetX,
						cRect.top + 11,
						32,
						32,
						slot->hMemDC,
						0,
						0,
						32,
						32,
						RGB(255, 0, 255));
				index++;
			}

			SelectObject(hDC, oldFont);
			DeleteObject(countFont);
		}
	}
}

void CQuickSlotUI::Release_Object() {
}

void CQuickSlotUI::OnCollision(CObj* _TargetObj) {
}

CItem* CQuickSlotUI::GetQuickSlot(UINT _number) {
	auto iter = vecSelected->begin();
	if (iter[_number] == nullptr)
		return nullptr;
	return iter[_number]->item;
}

QuickSlot::QuickSlot(CItem* _item) {
	item = _item->GetNewItem();
	hMemDC = CBitmapManager::GetInstance()->FindImage(_item->IconName);
}

QuickSlot::~QuickSlot() {
	Safe_Delete(item);
}