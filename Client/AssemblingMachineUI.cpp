#include "AssemblingMachineUI.h"
#include "Inventory.h"
#include "ItemStack.h"
#include "Obj.h"
#include "Actor.h"
#include "Mouse.h"

#include "ItemHand.h"

CAssemblingMachineUI::CAssemblingMachineUI() {
	SetName(L"AssemblingMachineUI");
	objectType = OBJ::UI;
	strokeColor = RGB(128, 128, 255);
	fillColor = RGB(0, 255, 255);
}

CAssemblingMachineUI::~CAssemblingMachineUI() {
}

void CAssemblingMachineUI::Ready_Object() {
	isVisible = false;
	info.iCX = 402;
	info.iCY = 150;
	info.CCX = 402;
	info.CCY = 150;
}

INT CAssemblingMachineUI::Update_Object() {
	if (targetActor) {
		if (targetActor->inventory && targetActor->inventory->listItemStack.size() != 0) {
			auto iter = targetActor->inventory->listItemStack.begin();
			inputStacks[0] = *iter++;
			inputStacks[1] = *iter++;
			inputStacks[2] = *iter;
		}
		else {
			inputStacks[0] = nullptr;
			inputStacks[1] = nullptr;
			inputStacks[2] = nullptr;
		}

		if (targetActor->outputInventory && targetActor->outputInventory->listItemStack.size() != 0)
			outputStack = targetActor->outputInventory->listItemStack.front();
		else
			outputStack = nullptr;
	}
	else {
		inputStacks[0] = nullptr;
		inputStacks[1] = nullptr;
		inputStacks[2] = nullptr;
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
	if (targetActor) {
		SetRect(&rc, rect.left, rect.top, rect.left + 38, rect.top + 38);
		CItemStack* cursorStack = dynamic_cast<CMouse*>(CObjManager::GetInstance()->GetList(OBJ::MOUSE)->front())->cursorStack;
		for (size_t i = 0; i < 3; i++) {
			SetRect(&rc, rect.left, rect.top, rect.left + 38, rect.top + 38);
			OffsetRect(&rc, 117 + i * 38, 40);
			if (PtInRect(&rc, pt)) {
				if (CKeyManager::GetInstance()->OnPress(KEY::PrimaryAction)) {
					if (cursorStack && inputStacks[i] && !lstrcmp(cursorStack->item->IconName, inputStacks[i]->item->IconName)) {
						targetActor->inventory->PushItemStack(cursorStack);
						Safe_Delete(cursorStack);
						ClearAllIconHand();
						dynamic_cast<CMouse*>(CObjManager::GetInstance()->GetList(OBJ::MOUSE)->front())->cursorStack = nullptr;
					}
				}
			}
		}
		SetRect(&rc, rect.left, rect.top, rect.left + 38, rect.top + 38);
		OffsetRect(&rc, 354, 81);
		if (PtInRect(&rc, pt)) {
			if (CKeyManager::GetInstance()->OnPress(KEY::PrimaryAction)) {
				if (outputStack) {
					if (cursorStack) {
						dynamic_cast<CActor*>(CObjManager::GetInstance()->GetPlayer())->inventory->PushItemStack(cursorStack);
						Safe_Delete(cursorStack);
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

void CAssemblingMachineUI::LateUpdate_Object() {

}

void CAssemblingMachineUI::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible && targetActor) {
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"GUI_Assembling-machine");
		HDC hMemSelectedSlotDC = CBitmapManager::GetInstance()->FindImage(L"GUI_SelectedSlot");
		HDC hMemDCProgress = CBitmapManager::GetInstance()->FindImage(L"GUI_CraftingProgress");

		if (nullptr == hMemDC || nullptr == hMemSelectedSlotDC || nullptr == hMemDCProgress)
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
			cRect.left + 117,
			cRect.top + 95,
			INT(233 * targetActor->progress / 100.f),
			7,
			hMemDCProgress,
			0, 0,
			SRCCOPY);

		TCHAR szBuffer[32];
		RECT rc = {};
		SetRect(&rc, cRect.left + 14, cRect.top + 14, cRect.left + 128, cRect.top + 64);
		wsprintf(szBuffer, L"%s", targetActor->GetName());
		SetTextColor(hDC, RGB(255, 255, 255));

		LOGFONT* logTitleFont = CFontManager::GetInstance()->FindFont(L"HY°ß°íµñ");
		LOGFONT* logCountFont = CFontManager::GetInstance()->FindFont(L"±¼¸²Ã¼");
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
			for (size_t i = 0; i < 3; i++) {
				SetRect(&rc, rect.left, rect.top, rect.left + 38, rect.top + 38);
				OffsetRect(&rc, 117 + i * 38, 40);
				if (targetActor && targetActor->inventory && inputStacks[i]) {
					GdiTransparentBlt(hDC,
						cRect.left + 119 + i * 38,
						cRect.top + 42,
						32,
						32,
						inputStacks[i]->hMemDC,
						0,
						0,
						32,
						32,
						RGB(255, 0, 255));
					SetTextColor(hDC, RGB(0, 0, 0));
					OffsetRect(&rc, -4, 24);
					wsprintf(szBuffer, L"%d", inputStacks[i]->size);
					DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_RIGHT | DT_NOCLIP);
					SetTextColor(hDC, RGB(255, 255, 255));
					OffsetRect(&rc, -1, -1);
					DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_RIGHT | DT_NOCLIP);
					SetTextColor(hDC, RGB(0, 0, 0));
				}
			}
			SetRect(&rc, rect.left, rect.top, rect.left + 38, rect.top + 38);
			OffsetRect(&rc, 354, 81);
			if (targetActor && targetActor->outputInventory && outputStack) {
				GdiTransparentBlt(hDC,
					cRect.left + 356,
					cRect.top + 83,
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

void CAssemblingMachineUI::Release_Object() {
}

void CAssemblingMachineUI::OnCollision(CObj* _TargetObj) {
}

