#include "framework.h"
#include "MainApp.h"
#include "MainScene.h"
#include "PlayScene.h"
#include "Player.h"
#include "Mouse.h"


extern bool DebugRectDraw = false;
extern LONG DeadLineMargin = 0;

CMainApp::CMainApp() {
	m_hDC = GetDC(g_hWnd);
}


CMainApp::~CMainApp() {
	Release_MainApp();
}

void CMainApp::Ready_MainApp() {
	m_hDC = GetDC(g_hWnd);
	m_mapScene.insert(map<SCENE_NUMBER, CScene*>::value_type(SCENE_MAIN, new CMainScene()));
	TCHAR szBuffer[200];
	lstrcpy(szBuffer, GRAPHICS_DIR);

	INSERT_TEXTURE(L"entity/character/hr-level1_idle.bmp", L"hr-level1_idle");

	INSERT_TEXTURE(L"entity/character/hr-level1_running.bmp", L"hr-level1_running");
	
	INSERT_TEXTURE(L"entity/character/hr-level1_mining_tool.bmp", L"hr-level1_mining_tool");


	INSERT_TEXTURE(L"gui/GUI_Panel.bmp", L"GUI_Panel");
	INSERT_TEXTURE(L"gui/GUI_Inventory.bmp", L"GUI_Inventory");
	INSERT_TEXTURE(L"gui/GUI_InventoryMerged.bmp", L"GUI_InventoryMerged");
	INSERT_TEXTURE(L"gui/GUI_SelectedSlot.bmp", L"GUI_SelectedSlot");
	INSERT_TEXTURE(L"gui/GUI_furnace.bmp", L"GUI_furnace");
	INSERT_TEXTURE(L"gui/GUI_Assembling-machine.bmp", L"GUI_Assembling-machine");
	INSERT_TEXTURE(L"gui/GUI_QuickSlot.bmp", L"GUI_QuickSlot");
	INSERT_TEXTURE(L"gui/GUI_BurnerEnergy.bmp", L"GUI_BurnerEnergy");
	INSERT_TEXTURE(L"gui/GUI_FurnaceProgress.bmp", L"GUI_FurnaceProgress");
	INSERT_TEXTURE(L"gui/GUI_CraftingProgress.bmp", L"GUI_CraftingProgress");
	INSERT_TEXTURE(L"gui/GUI_ProgressBarPanel.bmp", L"GUI_ProgressBarPanel");
	INSERT_TEXTURE(L"gui/GUI_ProgressBarProgress.bmp", L"GUI_ProgressBarProgress");

	
	INSERT_TEXTURE(L"entity/iron-chest/hr-iron-chest.bmp",            L"hr-iron-chest");
	INSERT_TEXTURE(L"entity/iron-chest/hr-iron-chest-placable.bmp",   L"hr-iron-chest-placable");
	INSERT_TEXTURE(L"entity/iron-chest/hr-iron-chest-unplacable.bmp", L"hr-iron-chest-unplacable");

	INSERT_TEXTURE(L"entity/transport-belt/hr-transport-belt.bmp", L"hr-transport-belt");
	INSERT_TEXTURE(L"entity/transport-belt/hr-transport-belt-placable.bmp", L"hr-transport-belt-placable");
	INSERT_TEXTURE(L"entity/transport-belt/hr-transport-belt-unplacable.bmp", L"hr-transport-belt-unplacable");
	
	INSERT_TEXTURE(L"entity/inserter/hr-inserter.bmp",            L"hr-inserter");
	INSERT_TEXTURE(L"entity/inserter/hr-inserter-placable.bmp",   L"hr-inserter-placable");
	INSERT_TEXTURE(L"entity/inserter/hr-inserter-unplacable.bmp", L"hr-inserter-unplacable");
	INSERT_TEXTURE(L"entity/burner-mining-drill/hr-burner-mining-drill.bmp", L"hr-burner-mining-drill");
	INSERT_TEXTURE(L"entity/burner-mining-drill/hr-burner-mining-drill-placable.bmp", L"hr-burner-mining-drill-placable");
	INSERT_TEXTURE(L"entity/burner-mining-drill/hr-burner-mining-drill-unplacable.bmp", L"hr-burner-mining-drill-unplacable");

	INSERT_TEXTURE(L"entity/resource-ore/hr-coal.bmp", L"hr-coal");
	INSERT_TEXTURE(L"entity/resource-ore/hr-copper-ore.bmp", L"hr-copper-ore");
	INSERT_TEXTURE(L"entity/resource-ore/hr-iron-ore.bmp", L"hr-iron-ore");
	INSERT_TEXTURE(L"entity/resource-ore/hr-stone.bmp", L"hr-stone");

	INSERT_TEXTURE(L"icon/ICON_hand.bmp", L"ICON_hand");
	INSERT_TEXTURE(L"icon/ICON_coal.bmp", L"ICON_coal");
	INSERT_TEXTURE(L"icon/ICON_copper-ore.bmp", L"ICON_copper-ore");
	INSERT_TEXTURE(L"icon/ICON_iron-ore.bmp", L"ICON_iron-ore");
	INSERT_TEXTURE(L"icon/ICON_stone.bmp", L"ICON_stone");

	INSERT_TEXTURE(L"terrian/dirt.bmp", L"dirt");
	//30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"±Ã¼­Ã¼"
	LOGFONT* pLogFont = new LOGFONT;
	pLogFont->lfHeight = 30;
	pLogFont->lfWidth = 0;
	pLogFont->lfEscapement = 0;
	pLogFont->lfOrientation = 0;
	pLogFont->lfWeight = 0;
	pLogFont->lfItalic = 0;
	pLogFont->lfUnderline = 0;
	pLogFont->lfStrikeOut = 0;
	pLogFont->lfCharSet = DEFAULT_CHARSET;
	pLogFont->lfOutPrecision = 0;
	pLogFont->lfClipPrecision = 0;
	pLogFont->lfQuality = 0;
	pLogFont->lfPitchAndFamily = 0;
	lstrcpy(pLogFont->lfFaceName, L"±Ã¼­Ã¼");

	CFontManager::GetInstance()->InsertFont(pLogFont, L"±Ã¼­Ã¼");

	pLogFont->lfHeight = 20;
	pLogFont->lfWidth = 0;
	pLogFont->lfEscapement = 0;
	pLogFont->lfOrientation = 0;
	pLogFont->lfWeight = 0;
	pLogFont->lfItalic = 0;
	pLogFont->lfUnderline = 0;
	pLogFont->lfStrikeOut = 0;
	pLogFont->lfCharSet = DEFAULT_CHARSET;
	pLogFont->lfOutPrecision = 0;
	pLogFont->lfClipPrecision = 0;
	pLogFont->lfQuality = 0;
	pLogFont->lfPitchAndFamily = 0;
	lstrcpy(pLogFont->lfFaceName, L"HY°ß°íµñ");

	CFontManager::GetInstance()->InsertFont(pLogFont, L"HY°ß°íµñ");

	pLogFont->lfHeight = 12;
	pLogFont->lfWidth = 0;
	pLogFont->lfEscapement = 0;
	pLogFont->lfOrientation = 0;
	pLogFont->lfWeight = 600;
	pLogFont->lfItalic = 0;
	pLogFont->lfUnderline = 0;
	pLogFont->lfStrikeOut = 0;
	pLogFont->lfCharSet = DEFAULT_CHARSET;
	pLogFont->lfOutPrecision = 0;
	pLogFont->lfClipPrecision = 0;
	pLogFont->lfQuality = 0;
	pLogFont->lfPitchAndFamily = 0;
	lstrcpy(pLogFont->lfFaceName, L"±¼¸²Ã¼");

	CFontManager::GetInstance()->InsertFont(pLogFont, L"±¼¸²Ã¼");



	m_mapScene[SCENE_MAIN]->ReadyScene();

}

void CMainApp::Update_MainApp() {
	if (m_mapScene.size() == 2 && m_mapScene[SCENE_PLAY]->GetActive() && dynamic_cast<CPlayer*>(CObjManager::GetInstance()->GetPlayer())->GetHP() < 0) {
		m_mapScene[SCENE_MAIN]->SetActive(true);
		m_mapScene[SCENE_PLAY]->ReleaseScene();
		spanX = 0;
		spanY = 0;
		auto iter = m_mapScene.begin();
		iter++;
		m_mapScene.erase(iter);
	}
	if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
		m_mapScene[SCENE_MAIN]->SetActive(false);
		if (m_mapScene.size() == 1)
			m_mapScene.insert(map<SCENE_NUMBER, CScene*>::value_type(SCENE_PLAY, new CPlayScene()));
		m_mapScene[SCENE_PLAY]->ReadyScene();
	}
	for (auto Scene : m_mapScene) {
		if (Scene.second->GetActive()) Scene.second->UpdateScene();
	}
}

void CMainApp::LateUpdate_MainApp() {
	for (auto Scene : m_mapScene) {
		if (Scene.second->GetActive()) Scene.second->LateUpdateScene();
	}

}

void CMainApp::Render_MainApp() {
	for (auto Scene : m_mapScene) {
		if (Scene.second->GetActive()) Scene.second->RenderScene(m_hDC);
	}

}

void CMainApp::Release_MainApp() {
	for (auto Scene : m_mapScene) {
		if (Scene.second->GetActive()) Scene.second->ReleaseScene();
	}

}
