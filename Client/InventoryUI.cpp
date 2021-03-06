#include "InventoryUI.h"
#include "Inventory.h"
#include "ItemStack.h"
#include "Obj.h"
#include "Actor.h"
#include "Mouse.h"

#include "ItemHand.h"

CInventoryUI::CInventoryUI() {
	SetName(L"InventoryUI");
	objectType = OBJ::UI;
	strokeColor = RGB(128, 128, 255);
	fillColor = RGB(0, 255, 255);
}

CInventoryUI::~CInventoryUI() {
}

void CInventoryUI::Ready_Object() {
	isVisible = false;
	info.iCX = 402;
	info.iCY = 437;
	info.CCX = 402;
	info.CCY = 437;
}

INT CInventoryUI::Update_Object() {
	if (targetActor && targetActor->inventory) {
		listItemStack = &(targetActor->inventory->listItemStack);
	}
	else {
		listItemStack = nullptr;
	}
	
	if (!isVisible) {
		ClearIconHand();
		active = false;
		return STATE_NO_EVENT;
	}
	if (!active) {
		active = true;
		return STATE_NO_EVENT;
	}
	if (CKeyManager::GetInstance()->OnPress(KEY::ClearCursor)) {
		ClearIconHand();
		SortItemStack();
	}
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	if (listItemStack) {
		INT index = 0;
		RECT rc = {};
		SetRect(&rc, rect.left, rect.top, rect.left + 38, rect.top + 38);
		CItemStack* cursorStack = dynamic_cast<CMouse*>(CObjManager::GetInstance()->GetList(OBJ::MOUSE)->front())->cursorStack;
		OffsetRect(&rc, 14, 47);
		selectedIndex = 0;
		for (auto itemStack : *listItemStack) {
			INT cx = rect.left + 14 + (index % 10 * 38);
			INT cy = rect.top + 47 + (index / 10 * 38);
			SetRect(&rc, cx, cy, cx + 38, cy + 38);
			if (PtInRect(&rc, pt)) {
				if (CKeyManager::GetInstance()->OnPress(KEY::PrimaryAction)) {
					if (cursorStack) {
						if (!lstrcmp(itemStack->item->IconName, L"ICON_hand")) {
							cursorStack = targetActor->inventory->PushItemStack(cursorStack);
							ClearIconHand();
							SortItemStack();
							dynamic_cast<CMouse*>(CObjManager::GetInstance()->GetList(OBJ::MOUSE)->front())->cursorStack = cursorStack;
						}
						else {
							targetActor->inventory->PushItemStack(cursorStack);
							dynamic_cast<CMouse*>(CObjManager::GetInstance()->GetList(OBJ::MOUSE)->front())->cursorStack = itemStack;
							for (auto iter = listItemStack->begin(); iter != listItemStack->end(); iter++) {
								if (*iter == itemStack) {
									listItemStack->erase(iter);
									break;
								}
							}
						}
						
					}
					else {
						dynamic_cast<CMouse*>(CObjManager::GetInstance()->GetList(OBJ::MOUSE)->front())->cursorStack = itemStack;
						for (auto iter = listItemStack->begin(); iter != listItemStack->end(); iter++) {
							if (*iter == itemStack) {
								iter = listItemStack->erase(iter);
								listItemStack->emplace(iter, new CItemStack(new CItemHand()));
								break;
							}
						}
					}

				}
				selectedIndex = index + 1;
				break;
			}
			index++;
		}
		if (selectedIndex == 0 && PtInRect(&rect, pt) && cursorStack &&
			CKeyManager::GetInstance()->OnPress(KEY::PrimaryAction)) {
			ClearAllIconHand();
			cursorStack = targetActor->inventory->PushItemStack(cursorStack);
			dynamic_cast<CMouse*>(CObjManager::GetInstance()->GetList(OBJ::MOUSE)->front())->cursorStack = cursorStack;
		}
	}

	return STATE_NO_EVENT;
}

void CInventoryUI::LateUpdate_Object() {
}

void CInventoryUI::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible && targetActor) {

		if (targetActor != CObjManager::GetInstance()->GetPlayer()) {
			POSITION pos = {};
			pos.x = (FLOAT)dynamic_cast<CActor*>(CObjManager::GetInstance()->GetPlayer())->GUI->GetRect()->right + (info.iCX >> 1);
			pos.y = (FLOAT)dynamic_cast<CActor*>(CObjManager::GetInstance()->GetPlayer())->GUI->GetPosition().y;
			SetPosition(pos);
			CObj::Update_Rect_Object();
		}

		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"GUI_InventoryMerged");
		HDC hMemSelectedSlotDC = CBitmapManager::GetInstance()->FindImage(L"GUI_SelectedSlot");

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
		if(selectedIndex)
			BitBlt(hDC,
				cRect.left + 12 + ((selectedIndex - 1) % 10 * 38),
				cRect.top + 45 + ((selectedIndex - 1) / 10 * 38),
				36,
				36,
				hMemSelectedSlotDC,
				0,
				0,
				SRCCOPY);

		TCHAR szBuffer[32];
		RECT rc = {};
		SetRect(&rc, cRect.left + 14, cRect.top + 14, cRect.left + 128, cRect.top + 64);
		wsprintf(szBuffer, L"%s", targetActor->GetName());
		SetTextColor(hDC, RGB(255, 255, 255));

		LOGFONT* logTitleFont = CFontManager::GetInstance()->FindFont(L"HY�߰���");
		LOGFONT* logCountFont = CFontManager::GetInstance()->FindFont(L"����ü");
		HFONT titleFont = CreateFontIndirect(logTitleFont);
		HFONT countFont = CreateFontIndirect(logCountFont);
		HFONT oldFont = (HFONT)SelectObject(hDC, titleFont);
		DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_LEFT | DT_NOCLIP);
		SelectObject(hDC, countFont);
		if (listItemStack) {
			INT index = 0;
			for (auto itemStack : *listItemStack) {
				GdiTransparentBlt(hDC,
					cRect.left + 14 + (index % 10 * 38),
					cRect.top + 47 + (index / 10 * 38),
					32,
					32,
					itemStack->hMemDC,
					0,
					0,
					32,
					32,
					RGB(255, 0, 255));
				if (lstrcmp(itemStack->item->IconName, L"ICON_hand")) {
					SetRect(&rc, cRect.left, cRect.top + 22, cRect.left + 32, cRect.top + 32);
					OffsetRect(&rc, 14 + (index % 10 * 38), 47 + (index / 10 * 38));
					SetTextColor(hDC, RGB(0, 0, 0));
					wsprintf(szBuffer, L"%d", itemStack->size);
					DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_RIGHT | DT_NOCLIP);
					SetTextColor(hDC, RGB(255, 255, 255));
					OffsetRect(&rc, -1, -1);
					DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_RIGHT | DT_NOCLIP);
					SetTextColor(hDC, RGB(0, 0, 0));
				}
				index++;
			}
		}

		SelectObject(hDC, oldFont);
		DeleteObject(titleFont);
		DeleteObject(countFont);
	}
}

void CInventoryUI::Release_Object() {
}

void CInventoryUI::OnCollision(CObj* _TargetObj) {
}

void CInventoryUI::ClearIconHand() {
	if(listItemStack)
	for (auto iter = listItemStack->begin(); iter != listItemStack->end(); iter++)
		if (!lstrcmp((*iter)->item->IconName, L"ICON_hand")) {
			listItemStack->erase(iter);
			break;
		}
	
}

void CInventoryUI::SortItemStack() {
	if (listItemStack) {
		listItemStack->sort([](CItemStack* stack1, CItemStack* stack2) {
			if (!lstrcmp(stack1->item->GetName(), stack2->item->GetName())) {
				return stack1->size > stack2->size;
			}
			else {
				return lstrcmp(stack1->item->GetName(), stack2->item->GetName()) > 0;
			}
			});
	}
	
}
