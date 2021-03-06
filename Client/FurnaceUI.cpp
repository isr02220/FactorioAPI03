#include "FurnaceUI.h"
#include "FuelTank.h"
#include "Inventory.h"
#include "ItemStack.h"
#include "Obj.h"
#include "Actor.h"
#include "Mouse.h"
#include "ResourceOre.h"

#include "ItemHand.h"

CFurnaceUI::CFurnaceUI() {
	SetName(L"FurnaceUI");
	objectType = OBJ::UI;
	strokeColor = RGB(128, 128, 255);
	fillColor = RGB(0, 255, 255);
}

CFurnaceUI::~CFurnaceUI() {
}

void CFurnaceUI::Ready_Object() {
	isVisible = false;
	info.iCX = 402;
	info.iCY = 150;
	info.CCX = 402;
	info.CCY = 150;
}

INT CFurnaceUI::Update_Object() {
	if (targetActor) {
		if(targetActor->fuelTank)
			fuelStack = targetActor->fuelTank->fuelStack;
		else
			fuelStack = nullptr;

		if (targetActor->inventory && targetActor->inventory->listItemStack.size() != 0)
			inputStack = targetActor->inventory->listItemStack.front();
		else
			inputStack = nullptr;

		if (targetActor->outputInventory && targetActor->outputInventory->listItemStack.size() != 0)
			outputStack = targetActor->outputInventory->listItemStack.front();
		else
			outputStack = nullptr;
	}
	else {
		fuelStack = nullptr;
		inputStack = nullptr;
		outputStack = nullptr;
	}

	if (!isVisible) {
		//ClearIconHand();
		active = false;
		return STATE_NO_EVENT;
	}
	info.position.x = dynamic_cast<CActor*>(CObjManager::GetInstance()->GetPlayer())->GUI->GetPosition().x;
	info.position.y = dynamic_cast<CActor*>(CObjManager::GetInstance()->GetPlayer())->GUI->GetRect()->top - FLOAT(info.iCY >> 1);

	if (!active) {
		active = true;
		return STATE_NO_EVENT;
	}
	POINT pt = {};
	RECT rc = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	if (targetActor && targetActor->fuelTank) {
		SetRect(&rc, rect.left, rect.top, rect.left + 38, rect.top + 38);
		CItemStack* cursorStack = dynamic_cast<CMouse*>(CObjManager::GetInstance()->GetList(OBJ::MOUSE)->front())->cursorStack;
		OffsetRect(&rc, 117, 40);
		if (PtInRect(&rc, pt)) {
			if (CKeyManager::GetInstance()->OnPress(KEY::PrimaryAction)) {
				if (cursorStack && cursorStack->item->isBurnable) {
					if (inputStack) {
						if (!lstrcmp(inputStack->item->IconName, cursorStack->item->IconName)) {
							cursorStack = targetActor->inventory->PushItemStack(cursorStack);
							ClearAllIconHand();
							dynamic_cast<CMouse*>(CObjManager::GetInstance()->GetList(OBJ::MOUSE)->front())->cursorStack = cursorStack;
						}
						else {
							dynamic_cast<CMouse*>(CObjManager::GetInstance()->GetList(OBJ::MOUSE)->front())->cursorStack = targetActor->fuelTank->PopItemStack();
							targetActor->inventory->PushItemStack(cursorStack);
							ClearAllIconHand();
						}
					}
					else {
						cursorStack = targetActor->inventory->PushItemStack(cursorStack);
						ClearAllIconHand();
						dynamic_cast<CMouse*>(CObjManager::GetInstance()->GetList(OBJ::MOUSE)->front())->cursorStack = cursorStack;
					}

				}
			}
		}
		OffsetRect(&rc, 0, 46);
		if (PtInRect(&rc, pt)) {
			if (CKeyManager::GetInstance()->OnPress(KEY::PrimaryAction)) {
				if (cursorStack && cursorStack->item->isFuel) {
					if (fuelStack) {
						if (!lstrcmp(fuelStack->item->IconName, cursorStack->item->IconName)) {
							targetActor->fuelTank->PushItemStack(cursorStack);
							ClearAllIconHand();
							dynamic_cast<CMouse*>(CObjManager::GetInstance()->GetList(OBJ::MOUSE)->front())->cursorStack = nullptr;
						}
						else {
							dynamic_cast<CMouse*>(CObjManager::GetInstance()->GetList(OBJ::MOUSE)->front())->cursorStack = targetActor->fuelTank->PopItemStack();
							targetActor->fuelTank->PushItemStack(cursorStack);
							Safe_Delete(cursorStack);
							ClearAllIconHand();
						}
					}
					else {
						targetActor->fuelTank->PushItemStack(cursorStack);
						Safe_Delete(cursorStack);
						ClearAllIconHand();
						dynamic_cast<CMouse*>(CObjManager::GetInstance()->GetList(OBJ::MOUSE)->front())->cursorStack = nullptr;
					}

				}
			}
		}
		OffsetRect(&rc, 237, -46);
		if (PtInRect(&rc, pt)) {
			if (CKeyManager::GetInstance()->OnPress(KEY::PrimaryAction)) {
				if (outputStack) {
					if (cursorStack) {
						dynamic_cast<CActor*>(CObjManager::GetInstance()->GetPlayer())->inventory->PushItemStack(cursorStack);
						ClearAllIconHand();
					}
					dynamic_cast<CMouse*>(CObjManager::GetInstance()->GetList(OBJ::MOUSE)->front())->cursorStack = outputStack;
					targetActor->outputInventory->listItemStack.pop_front();
				}
			}
		}
	}
	return STATE_NO_EVENT;
}

void CFurnaceUI::LateUpdate_Object() {

}

void CFurnaceUI::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible && targetActor) {
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"GUI_furnace");
		HDC hMemSelectedSlotDC = CBitmapManager::GetInstance()->FindImage(L"GUI_SelectedSlot");
		HDC hMemDCEnergy = CBitmapManager::GetInstance()->FindImage(L"GUI_BurnerEnergy");
		HDC hMemDCProgress = CBitmapManager::GetInstance()->FindImage(L"GUI_FurnaceProgress");

		if (nullptr == hMemDC || nullptr == hMemSelectedSlotDC || nullptr == hMemDCEnergy || nullptr == hMemDCProgress)
			return;



		BitBlt(hDC,
			cRect.left,
			cRect.top,
			info.CCX,
			info.CCY,
			hMemDC,
			0, 0,
			SRCCOPY);

		BitBlt(hDC,
			cRect.left + 157,
			cRect.top + 54,
			INT(193 * targetActor->progress / 100.f),
			7,
			hMemDCProgress,
			0, 0,
			SRCCOPY);

		BitBlt(hDC,
			cRect.left + 157,
			cRect.top + 98,
			INT(233 * targetActor->fuelTank->energy / 100.f),
			7,
			hMemDCEnergy,
			0, 0,
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
		if (targetActor && targetActor->fuelTank) {

			RECT rc = {};
			POINT pt = {};
			GetCursorPos(&pt);
			ScreenToClient(g_hWnd, &pt);
			CItemStack* cursorStack = dynamic_cast<CMouse*>(CObjManager::GetInstance()->GetList(OBJ::MOUSE)->front())->cursorStack;
			SetRect(&rc, rect.left, rect.top, rect.left + 38, rect.top + 38);
			OffsetRect(&rc, 117, 40);
			if (targetActor && targetActor->inventory && inputStack) {
				GdiTransparentBlt(hDC,
					cRect.left + 119,
					cRect.top + 42,
					32,
					32,
					inputStack->hMemDC,
					0,
					0,
					32,
					32,
					RGB(255, 0, 255));
				SetTextColor(hDC, RGB(0, 0, 0));
				OffsetRect(&rc, -4, 24);
				wsprintf(szBuffer, L"%d", inputStack->size);
				DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_RIGHT | DT_NOCLIP);
				SetTextColor(hDC, RGB(255, 255, 255));
				OffsetRect(&rc, -1, -1);
				DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_RIGHT | DT_NOCLIP);
				SetTextColor(hDC, RGB(0, 0, 0));
			}
			SetRect(&rc, rect.left, rect.top, rect.left + 38, rect.top + 38);
			OffsetRect(&rc, 117, 86);
			if (targetActor && targetActor->fuelTank && fuelStack) {
				GdiTransparentBlt(hDC,
					cRect.left + 119,
					cRect.top + 88,
					32,
					32,
					fuelStack->hMemDC,
					0,
					0,
					32,
					32,
					RGB(255, 0, 255));
				SetTextColor(hDC, RGB(0, 0, 0));
				OffsetRect(&rc, -4, 24);
				wsprintf(szBuffer, L"%d", fuelStack->size);
				DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_RIGHT | DT_NOCLIP);
				SetTextColor(hDC, RGB(255, 255, 255));
				OffsetRect(&rc, -1, -1);
				DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_RIGHT | DT_NOCLIP);
				SetTextColor(hDC, RGB(0, 0, 0));
			}
			SetRect(&rc, rect.left, rect.top, rect.left + 38, rect.top + 38);
			OffsetRect(&rc, 354, 40);
			if (targetActor && targetActor->outputInventory && outputStack) {
				GdiTransparentBlt(hDC,
					cRect.left + 356,
					cRect.top + 42,
					32,
					32,
					outputStack->hMemDC,
					0,
					0,
					32,
					32,
					RGB(255, 0, 255));
				SetTextColor(hDC, RGB(0, 0, 0));
				OffsetRect(&rc, -4, 24);
				wsprintf(szBuffer, L"%d", outputStack->size);
				DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_RIGHT | DT_NOCLIP);
				SetTextColor(hDC, RGB(255, 255, 255));
				OffsetRect(&rc, -1, -1);
				DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_RIGHT | DT_NOCLIP);
				SetTextColor(hDC, RGB(0, 0, 0));
			}
		}

		SelectObject(hDC, oldFont);
		DeleteObject(titleFont);
		DeleteObject(countFont);
	}
}

void CFurnaceUI::Release_Object() {
}

void CFurnaceUI::OnCollision(CObj* _TargetObj) {
}

