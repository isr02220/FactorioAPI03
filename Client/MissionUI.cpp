#include "MissionUI.h"
#include "FuelTank.h"
#include "Inventory.h"
#include "ItemStack.h"
#include "Obj.h"
#include "Actor.h"
#include "Worm.h"
#include "Mouse.h"
#include "ResourceOre.h"

#include "ItemHand.h"

CMissionUI::CMissionUI() {
	SetName(L"Mission");
	objectType = OBJ::UI;
	strokeColor = RGB(128, 128, 255);
	fillColor = RGB(0, 255, 255);
	lstrcpy(missionStrings[0], L"철판 10개 제작하기");
	lstrcpy(missionStrings[1], L"구리판 10개 제작하기");
	lstrcpy(missionStrings[2], L"기관단총 1개 제작하기");
	lstrcpy(missionStrings[3], L"화기용 탄창 10개 제작하기");
	lstrcpy(missionStrings[4], L"동쪽에 불시착한 선생님 구출하기");


	lstrcpy(tipStrings[0],  L"- WASD 키를 이용하여 걷습니다.");
	lstrcpy(tipStrings[1],  L"- 오른쪽 마우스 버튼으로 채집합니다.");
	lstrcpy(tipStrings[2],  L"- E 키를 눌러 인벤토리를 엽니다.");
	lstrcpy(tipStrings[3],  L"- Q 키를 눌러 선택한 아이템을 인벤토리에");
	lstrcpy(tipStrings[4],  L"  수납합니다.");
	lstrcpy(tipStrings[5],  L"- R 키를 눌러 커서나 구조물의 방향을");
	lstrcpy(tipStrings[6],  L"  회전할 수 있습니다.");
	lstrcpy(tipStrings[7],  L"- 구조물을 왼쪽 마우스 버튼으로 클릭하면");
	lstrcpy(tipStrings[8],  L"  구조물의 UI패널을 엽니다.");
	lstrcpy(tipStrings[9],  L"- 아이템을 선택한 상태에서 구조물을 CTRL 키와");
	lstrcpy(tipStrings[10], L"  함께 클릭하면 아이템을 삽입합니다.");
	lstrcpy(tipStrings[11], L"- 구조물을 오른쪽 마우스로 클릭을 유지하면");
	lstrcpy(tipStrings[12], L"  구조물을 해체합니다.");

}

CMissionUI::~CMissionUI() {
}

void CMissionUI::Ready_Object() {
	isVisible = false;
	info.iCX = 403;
	info.iCY = 180;
	info.CCX = 403;
	info.CCY = 180;

}

INT CMissionUI::Update_Object() {
	Update_Rect_Object();
	if (CKeyManager::GetInstance()->OnPress(KEY::Mission)) {
		if (++UIstate > 2)
			UIstate = 0;

	}
	CheckMisionComplete();
	
	if (UIstate == 1) {
		info.CCY = 180;
		info.iCY = 180;
		isVisible = true;
	}
	else if (UIstate == 2) {
		info.CCY = 420;
		info.iCY = 420;
		isVisible = true;
	}
	else {
		isVisible = false;
	}

	if (!isVisible) {
		active = false;
		return STATE_NO_EVENT;
	}
	info.position.x = FLOAT(info.CCX >> 1);
	info.position.y = FLOAT(info.CCY >> 1);

	if (!active) {
		active = true;
		return STATE_NO_EVENT;
	}
	POINT pt = {};
	RECT rc = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	SetRect(&rc, rect.left + 12, rect.top + 144, rect.left + 40, rect.top + 172);
	if (CKeyManager::GetInstance()->OnPress(KEY::PrimaryAction) && PtInRect(&rc, pt)) {
		if (UIstate == 1)
			UIstate = 2;
		else
			UIstate = 1;

	}
	return STATE_NO_EVENT;
}

void CMissionUI::LateUpdate_Object() {

}

void CMissionUI::Render_Object(HDC hDC) {
	CObj::Update_Rect_Object();
	if (isVisible) {
		HDC hMemDC = nullptr;
		if(UIstate == 1)
			hMemDC = CBitmapManager::GetInstance()->FindImage(L"GUI_Mission");
		else if(UIstate == 2)
			hMemDC = CBitmapManager::GetInstance()->FindImage(L"GUI_MissionAndTip");

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

		TCHAR szBuffer[32];
		RECT rc = {};

		LOGFONT* logTitleFont = CFontManager::GetInstance()->FindFont(L"HY견고딕");
		LOGFONT* logRegularFont = CFontManager::GetInstance()->FindFont(L"돋움체");
		LOGFONT* logStrikedFont = CFontManager::GetInstance()->FindFont(L"돋움체_취소선");
		HFONT TitleFont = CreateFontIndirect(logTitleFont);
		HFONT RegularFont = CreateFontIndirect(logRegularFont);
		HFONT StrikedFont = CreateFontIndirect(logStrikedFont);
		HFONT oldFont = (HFONT)SelectObject(hDC, TitleFont);

		SetRect(&rc, cRect.left + 14, cRect.top + 14, cRect.left + 200, cRect.top + 200);
		wsprintf(szBuffer, L"%s", GetName());
		SetTextColor(hDC, RGB(255, 255, 255));
		DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_LEFT | DT_NOCLIP);


		SetRect(&rc, rect.left, rect.top, rect.right - 30, rect.bottom - 54);
		OffsetRect(&rc, 15, 28);
		for (size_t i = 0; i < 5; i++) {
			OffsetRect(&rc, 0, 18);
			if ((missionState >> i) & 0x00000001) {
				SetTextColor(hDC, RGB(164, 164, 164));
				SelectObject(hDC, StrikedFont);
			}
			else {
				SetTextColor(hDC, RGB(255, 255, 255));
				SelectObject(hDC, RegularFont);
			}
			DrawText(hDC, missionStrings[i], lstrlen(missionStrings[i]), &rc, DT_LEFT | DT_NOCLIP);
		}

		if (UIstate == 2) {
			SetRect(&rc, rect.left, rect.top, rect.right - 30, rect.bottom - 54);
			OffsetRect(&rc, 15, 172);
			SetTextColor(hDC, RGB(255, 255, 255));
			SelectObject(hDC, RegularFont);
			for (size_t i = 0; i < 13; i++) {
				OffsetRect(&rc, 0, 16);
				DrawText(hDC, tipStrings[i], lstrlen(tipStrings[i]), &rc, DT_LEFT | DT_NOCLIP);
			}
		}

		SelectObject(hDC, oldFont);
		DeleteObject(TitleFont);
		DeleteObject(RegularFont);
		DeleteObject(StrikedFont);
	}
}

void CMissionUI::Release_Object() {
}

void CMissionUI::OnCollision(CObj* _TargetObj) {
}

void CMissionUI::CheckMisionComplete() {
	if (!((missionState >> 0) & 0x00000001) && targetActor->inventory) {
		INT amount = 0;
		for (auto itemStack : targetActor->inventory->listItemStack) {
			if (!lstrcmp(itemStack->item->IconName, L"ICON_iron-plate")) {
				amount += itemStack->size;
			}
		}
		if (amount >= 10) {
			missionState += 1;
			CSoundMgr::Get_Instance()->PlaySound(L"research-completed.wav", CSoundMgr::PLAYER);
		}
	}
	if (!((missionState >> 1) & 0x00000001) && targetActor->inventory) {
		INT amount = 0;
		for (auto itemStack : targetActor->inventory->listItemStack) {
			if (!lstrcmp(itemStack->item->IconName, L"ICON_copper-plate")) {
				amount += itemStack->size;
			}
		}
		if (amount >= 10) {
			missionState += 2;
			CSoundMgr::Get_Instance()->PlaySound(L"research-completed.wav", CSoundMgr::PLAYER);
		}
	}
	if (!((missionState >> 2) & 0x00000001) && targetActor->inventory) {
		for (auto itemStack : targetActor->inventory->listItemStack) {
			if (!lstrcmp(itemStack->item->IconName, L"ICON_submachine-gun")) {
				missionState += 4;
				CSoundMgr::Get_Instance()->PlaySound(L"research-completed.wav", CSoundMgr::PLAYER);
				break;
			}
		}
	}
	if (!((missionState >> 3) & 0x00000001) && targetActor->inventory) {
		INT amount = 0;
		for (auto itemStack : targetActor->inventory->listItemStack) {
			if (!lstrcmp(itemStack->item->IconName, L"ICON_firearm-magazine")) {
				amount += itemStack->size;
			}
		}
		if (amount >= 10) {
			missionState += 8;
			CSoundMgr::Get_Instance()->PlaySound(L"research-completed.wav", CSoundMgr::PLAYER);
		}
	}
	if (!((missionState >> 4) & 0x00000001) && targetActor->inventory) {
		INT amount = 0;
		list<CObj*>* listMonster = CObjManager::GetInstance()->GetList(OBJ::MONSTER);
		for (auto monster : *listMonster) {
			if (!lstrcmp(monster->GetName(), L"땅굴 벌레")) {
				if (dynamic_cast<CWorm*>(monster)->GetHP() <= 0) {
					missionState += 16;
					CSoundMgr::Get_Instance()->PlaySound(L"research-completed.wav", CSoundMgr::PLAYER);
					break;
				}
			}
		}
	}
}

