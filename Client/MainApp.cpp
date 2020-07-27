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

	INSERT_TEXTURE(L"GUI/Title.bmp", L"Title");
	INSERT_TEXTURE(L"entity/character/hr-level1_idle.bmp", L"hr-level1_idle");

	INSERT_TEXTURE(L"entity/character/hr-level1_running.bmp", L"hr-level1_running");
	INSERT_TEXTURE(L"entity/character/hr-level1_mining_tool.bmp", L"hr-level1_mining_tool");
	INSERT_TEXTURE(L"entity/character/hr-level1_idle_gun.bmp", L"hr-level1_idle_gun");


	INSERT_TEXTURE(L"gui/GUI_Panel.bmp", L"GUI_Panel");
	INSERT_TEXTURE(L"gui/GUI_Inventory.bmp", L"GUI_Inventory");
	INSERT_TEXTURE(L"gui/GUI_InventoryMerged.bmp", L"GUI_InventoryMerged");
	INSERT_TEXTURE(L"gui/GUI_SelectedSlot.bmp", L"GUI_SelectedSlot");
	INSERT_TEXTURE(L"gui/GUI_furnace.bmp", L"GUI_furnace");
	INSERT_TEXTURE(L"gui/GUI_CraftPanel.bmp", L"GUI_CraftPanel");
	INSERT_TEXTURE(L"gui/GUI_Assembling-machine.bmp", L"GUI_Assembling-machine");
	INSERT_TEXTURE(L"gui/GUI_QuickSlot.bmp", L"GUI_QuickSlot");
	INSERT_TEXTURE(L"gui/GUI_Equipment.bmp", L"GUI_Equipment");
	INSERT_TEXTURE(L"gui/GUI_BurnerEnergy.bmp", L"GUI_BurnerEnergy");
	INSERT_TEXTURE(L"gui/GUI_FurnaceProgress.bmp", L"GUI_FurnaceProgress");
	INSERT_TEXTURE(L"gui/GUI_CraftingProgress.bmp", L"GUI_CraftingProgress");
	INSERT_TEXTURE(L"gui/GUI_ProgressBarPanel.bmp", L"GUI_ProgressBarPanel");
	INSERT_TEXTURE(L"gui/GUI_ProgressBarProgress.bmp", L"GUI_ProgressBarProgress");
	INSERT_TEXTURE(L"gui/GUI_Mission.bmp", L"GUI_Mission");
	INSERT_TEXTURE(L"gui/GUI_MissionAndTip.bmp", L"GUI_MissionAndTip");
	INSERT_TEXTURE(L"gui/GUI_Equipment.bmp", L"GUI_Equipment");
	INSERT_TEXTURE(L"gui/GUI_EquipedArmor.bmp", L"GUI_EquipedArmor");
	INSERT_TEXTURE(L"gui/GUI_EquipedMagazine.bmp", L"GUI_EquipedMagazine");
	INSERT_TEXTURE(L"gui/GUI_EquipedSMG.bmp", L"GUI_EquipedSMG");

	INSERT_TEXTURE(L"item-group/ICON_intermediate.bmp", L"ICON_intermediate");
	INSERT_TEXTURE(L"item-group/ICON_logistics.bmp", L"ICON_logistics");
	INSERT_TEXTURE(L"item-group/ICON_military.bmp", L"ICON_military");
	INSERT_TEXTURE(L"item-group/ICON_production.bmp", L"ICON_production");

	
	INSERT_TEXTURE(L"entity/worm/hr-worm-die.bmp",      L"hr-worm-die");
	INSERT_TEXTURE(L"entity/worm/hr-worm-attack.bmp",   L"hr-worm-attack");
	
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
	INSERT_TEXTURE(L"entity/stone-furnace/hr-stone-furnace.bmp",            L"hr-stone-furnace");
	INSERT_TEXTURE(L"entity/stone-furnace/hr-stone-furnace-placable.bmp",   L"hr-stone-furnace-placable");
	INSERT_TEXTURE(L"entity/stone-furnace/hr-stone-furnace-unplacable.bmp", L"hr-stone-furnace-unplacable");
	INSERT_TEXTURE(L"entity/assembling-machine/hr-assembling-machine.bmp",            L"hr-assembling-machine");
	INSERT_TEXTURE(L"entity/assembling-machine/hr-assembling-machine-placable.bmp",   L"hr-assembling-machine-placable");
	INSERT_TEXTURE(L"entity/assembling-machine/hr-assembling-machine-unplacable.bmp", L"hr-assembling-machine-unplacable");

	INSERT_TEXTURE(L"entity/resource-ore/hr-coal.bmp", L"hr-coal");
	INSERT_TEXTURE(L"entity/resource-ore/hr-copper-ore.bmp", L"hr-copper-ore");
	INSERT_TEXTURE(L"entity/resource-ore/hr-iron-ore.bmp", L"hr-iron-ore");
	INSERT_TEXTURE(L"entity/resource-ore/hr-stone.bmp", L"hr-stone");

	INSERT_TEXTURE(L"icon/ICON_back.bmp", L"ICON_back");
	INSERT_TEXTURE(L"icon/ICON_hand.bmp", L"ICON_hand");
	INSERT_TEXTURE(L"icon/ICON_electronic-circuit.bmp", L"ICON_electronic-circuit");
	INSERT_TEXTURE(L"icon/ICON_copper-cable.bmp", L"ICON_copper-cable");
	INSERT_TEXTURE(L"icon/ICON_assembling-machine.bmp", L"ICON_assembling-machine");
	INSERT_TEXTURE(L"icon/ICON_burner-mining-drill.bmp", L"ICON_burner-mining-drill");
	INSERT_TEXTURE(L"icon/ICON_coal.bmp", L"ICON_coal");
	INSERT_TEXTURE(L"icon/ICON_copper-ore.bmp", L"ICON_copper-ore");
	INSERT_TEXTURE(L"icon/ICON_copper-plate.bmp", L"ICON_copper-plate");
	INSERT_TEXTURE(L"icon/ICON_firearm-magazine.bmp", L"ICON_firearm-magazine");
	INSERT_TEXTURE(L"icon/ICON_inserter.bmp", L"ICON_inserter");
	INSERT_TEXTURE(L"icon/ICON_iron-chest.bmp", L"ICON_iron-chest");
	INSERT_TEXTURE(L"icon/ICON_iron-gear-wheel.bmp", L"ICON_iron-gear-wheel");
	INSERT_TEXTURE(L"icon/ICON_iron-ore.bmp", L"ICON_iron-ore");
	INSERT_TEXTURE(L"icon/ICON_iron-plate.bmp", L"ICON_iron-plate");
	INSERT_TEXTURE(L"icon/ICON_light-armor.bmp", L"ICON_light-armor");
	INSERT_TEXTURE(L"icon/ICON_solar-panel.bmp", L"ICON_solar-panel");
	INSERT_TEXTURE(L"icon/ICON_stone.bmp", L"ICON_stone");
	INSERT_TEXTURE(L"icon/ICON_stone-furnace.bmp", L"ICON_stone-furnace");
	INSERT_TEXTURE(L"icon/ICON_submachine-gun.bmp", L"ICON_submachine-gun");
	INSERT_TEXTURE(L"icon/ICON_transport-belt.bmp", L"ICON_transport-belt");

	INSERT_TEXTURE(L"terrian/dirt.bmp", L"dirt");
	INSERT_TEXTURE(L"entity/bullet.bmp", L"bullet");
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

	pLogFont->lfHeight = 14;
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
	lstrcpy(pLogFont->lfFaceName, L"µ¸¿òÃ¼");

	CFontManager::GetInstance()->InsertFont(pLogFont, L"µ¸¿òÃ¼");
	
	pLogFont->lfHeight = 14;
	pLogFont->lfWidth = 0;
	pLogFont->lfEscapement = 0;
	pLogFont->lfOrientation = 0;
	pLogFont->lfWeight = 600;
	pLogFont->lfItalic = 0;
	pLogFont->lfUnderline = 0;
	pLogFont->lfStrikeOut = 1;
	pLogFont->lfCharSet = DEFAULT_CHARSET;
	pLogFont->lfOutPrecision = 0;
	pLogFont->lfClipPrecision = 0;
	pLogFont->lfQuality = 0;
	pLogFont->lfPitchAndFamily = 0;
	lstrcpy(pLogFont->lfFaceName, L"µ¸¿òÃ¼");

	CFontManager::GetInstance()->InsertFont(pLogFont, L"µ¸¿òÃ¼_Ãë¼Ò¼±");


	CSoundMgr::Get_Instance()->Initialize();

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

	CSoundMgr::Destroy_Instance();
	CBitmapManager::GetInstance()->DestroyInstance();
}
