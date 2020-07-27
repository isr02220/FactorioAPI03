#include "CraftUI.h"
#include "Inventory.h"
#include "ItemStack.h"
#include "Obj.h"
#include "Actor.h"
#include "Mouse.h"
#include "RecipeManager.h"
#include "CraftRecipe.h"
#include "ItemHand.h"

list<CCraftRecipe*>* CCraftUI::listLogisticsRecipe    = nullptr;
list<CCraftRecipe*>* CCraftUI::listProductionRecipe   = nullptr;
list<CCraftRecipe*>* CCraftUI::listIntermediateRecipe = nullptr;
list<CCraftRecipe*>* CCraftUI::listCombatRecipe       = nullptr;

CCraftUI::CCraftUI() {
	if (!listLogisticsRecipe) {
		listLogisticsRecipe    = new list<CCraftRecipe*>;
		listProductionRecipe   = new list<CCraftRecipe*>;
		listIntermediateRecipe = new list<CCraftRecipe*>;
		listCombatRecipe       = new list<CCraftRecipe*>;

		listLogisticsRecipe->emplace_back(CRecipeManager::GetInstance()->FindRecipe(L"ICON_inserter"));
		listLogisticsRecipe->emplace_back(CRecipeManager::GetInstance()->FindRecipe(L"ICON_iron-chest"));
		listLogisticsRecipe->emplace_back(CRecipeManager::GetInstance()->FindRecipe(L"ICON_transport-belt"));

		listProductionRecipe->emplace_back(CRecipeManager::GetInstance()->FindRecipe(L"ICON_assembling-machine"));
		listProductionRecipe->emplace_back(CRecipeManager::GetInstance()->FindRecipe(L"ICON_burner-mining-drill"));
		listProductionRecipe->emplace_back(CRecipeManager::GetInstance()->FindRecipe(L"ICON_stone-furnace"));
		listProductionRecipe->emplace_back(CRecipeManager::GetInstance()->FindRecipe(L"ICON_solar-panel"));

		listIntermediateRecipe->emplace_back(CRecipeManager::GetInstance()->FindRecipe(L"ICON_copper-cable"));
		listIntermediateRecipe->emplace_back(CRecipeManager::GetInstance()->FindRecipe(L"ICON_electronic-circuit"));
		listIntermediateRecipe->emplace_back(CRecipeManager::GetInstance()->FindRecipe(L"ICON_iron-gear-wheel"));

		listCombatRecipe->emplace_back(CRecipeManager::GetInstance()->FindRecipe(L"ICON_light-armor"));
		listCombatRecipe->emplace_back(CRecipeManager::GetInstance()->FindRecipe(L"ICON_firearm-magazine"));
		listCombatRecipe->emplace_back(CRecipeManager::GetInstance()->FindRecipe(L"ICON_submachine-gun"));

	}
	SetName(L"CraftUI");
	objectType = OBJ::UI;
	strokeColor = RGB(128, 128, 255);
	fillColor = RGB(0, 255, 255);
}

CCraftUI::~CCraftUI() {
}

void CCraftUI::Ready_Object() {
	isVisible = false;
	info.iCX = 402;
	info.iCY = 437;
	info.CCX = 402;
	info.CCY = 437;
}

INT CCraftUI::Update_Object() {


	if (!isVisible) {
		active = false;
		return STATE_NO_EVENT;
	}
	if (!active) {
		active = true;
		return STATE_NO_EVENT;
	}
	dynamic_cast<CActor*>(CObjManager::GetInstance()->GetPlayer())->GUI->SetVisible(false);
	POINT pt = {};
	RECT rc = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	INT index = 0;
	for (size_t i = 0; i < 4; i++) {
		INT cx = rect.left + 12 + (i % 10 * 70);
		INT cy = rect.top + 40 + (i / 10 * 70);
		SetRect(&rc, cx, cy, cx + 68, cy + 68);
		if (CKeyManager::GetInstance()->OnPress(KEY::PrimaryAction) && PtInRect(&rc, pt)) {
			selectedItemGroup = (ITEM::GROUP)i;
			switch (selectedItemGroup) {
			case ITEM::GROUP::LOGISTICS:
				listSelected = listLogisticsRecipe;
				break;
			case ITEM::GROUP::PRODUCTION:
				listSelected = listProductionRecipe;
				break;
			case ITEM::GROUP::INTERMEDIATE:
				listSelected = listIntermediateRecipe;
				break;
			case ITEM::GROUP::COMBAT:
				listSelected = listCombatRecipe;
				break;
			default:
				listSelected = listLogisticsRecipe;
				break;
			}
			break;
		}
	}
	if (listSelected) {
		index = 0;
		selectedIndex = 0;
		for (auto recipe : *listSelected) {
			INT cx = rect.left + 12 + (index % 10 * 38);
			INT cy = rect.top + 112 + (index / 10 * 38);
			SetRect(&rc, cx, cy, cx + 36, cy + 36);
			if (PtInRect(&rc, pt)) {
				selectedIndex = index + 1;
				if (CKeyManager::GetInstance()->OnPress(KEY::PrimaryAction)) {
					SelectedRecipe = recipe;
				}
			}
			index++;
		}
	}

	return STATE_NO_EVENT;
}

void CCraftUI::LateUpdate_Object() {
}

void CCraftUI::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible && targetActor) {
		HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"GUI_CraftPanel");
		HDC hMemSelectedSlotDC = CBitmapManager::GetInstance()->FindImage(L"GUI_SelectedSlot");
		HDC hMemSelectedGroupDC;
		switch (selectedItemGroup) {
		case ITEM::GROUP::LOGISTICS:
			hMemSelectedGroupDC = CBitmapManager::GetInstance()->FindImage(L"ICON_logistics");
			break;
		case ITEM::GROUP::PRODUCTION:
			hMemSelectedGroupDC = CBitmapManager::GetInstance()->FindImage(L"ICON_production");
			break;
		case ITEM::GROUP::INTERMEDIATE:
			hMemSelectedGroupDC = CBitmapManager::GetInstance()->FindImage(L"ICON_intermediate");
			break;
		case ITEM::GROUP::COMBAT:
			hMemSelectedGroupDC = CBitmapManager::GetInstance()->FindImage(L"ICON_military");
			break;
		default:
			hMemSelectedGroupDC = CBitmapManager::GetInstance()->FindImage(L"ICON_logistics");
			break;
		}

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
		BitBlt(hDC,
			cRect.left + 12 + (INT(selectedItemGroup) * 70),
			cRect.top + 40,
			68,
			68,
			hMemSelectedGroupDC,
			0,
			0,
			SRCCOPY);

		TCHAR szBuffer[32];
		RECT rc = {};
		SetRect(&rc, cRect.left + 14, cRect.top + 14, cRect.left + 128, cRect.top + 64);
		wsprintf(szBuffer, L"%s", targetActor->GetName());
		SetTextColor(hDC, RGB(255, 255, 255));

		LOGFONT* logTitleFont = CFontManager::GetInstance()->FindFont(L"HY°ß°íµñ");
		HFONT titleFont = CreateFontIndirect(logTitleFont);
		HFONT oldFont = (HFONT)SelectObject(hDC, titleFont);
		DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_LEFT | DT_NOCLIP);

		SetTextColor(hDC, RGB(0, 0, 0));
		SelectObject(hDC, oldFont);
		DeleteObject(titleFont);

		if (selectedIndex)
			BitBlt(hDC,
				cRect.left + 12 + ((selectedIndex - 1) % 10 * 38),
				cRect.top + 112 + ((selectedIndex - 1) / 10 * 38),
				36,
				36,
				hMemSelectedSlotDC,
				0,
				0,
				SRCCOPY);

		if (listSelected) {
			INT index = 0;
			for (auto recipe : *listSelected) {
				GdiTransparentBlt(hDC,
					cRect.left + 14 + (index % 10 * 38),
					cRect.top + 114 + (index / 10 * 38),
					32,
					32,
					recipe->hMemDC,
					0,
					0,
					32,
					32,
					RGB(255, 0, 255));
				index++;
			}
		}
	}
}

void CCraftUI::Release_Object() {
}

void CCraftUI::OnCollision(CObj* _TargetObj) {
}

