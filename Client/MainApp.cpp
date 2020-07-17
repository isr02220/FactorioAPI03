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

	INSERT_TEXTURE(L"entity/character/bmp/hr-level1_idle.bmp", L"hr-level1_idle");

	INSERT_TEXTURE(L"entity/character/bmp/hr-level1_running.bmp", L"hr-level1_running");
	
	INSERT_TEXTURE(L"entity/character/bmp/hr-level1_mining_tool.bmp", L"hr-level1_mining_tool");

	INSERT_TEXTURE(L"entity/transport-belt/bmp/hr-transport-belt.bmp", L"hr-transport-belt");

	INSERT_TEXTURE(L"entity/transport-belt/bmp/hr-transport-belt-placable.bmp", L"hr-transport-belt-placable");

	INSERT_TEXTURE(L"entity/transport-belt/bmp/hr-transport-belt-unplacable.bmp", L"hr-transport-belt-unplacable");

	INSERT_TEXTURE(L"bmp/GUI_Panel.bmp", L"GUI_Panel");

	INSERT_TEXTURE(L"bmp/GUI_Inventory.bmp", L"GUI_Inventory");

	INSERT_TEXTURE(L"bmp/GUI_InventoryMerged.bmp", L"GUI_InventoryMerged");

	INSERT_TEXTURE(L"bmp/GUI_QuickSlot.bmp", L"GUI_QuickSlot");

	INSERT_TEXTURE(L"bmp/GUI_ProgressBarPanel.bmp", L"GUI_ProgressBarPanel");

	INSERT_TEXTURE(L"bmp/GUI_ProgressBarProgress.bmp", L"GUI_ProgressBarProgress");

	INSERT_TEXTURE(L"bmp/hr-coal.bmp", L"hr-coal");

	INSERT_TEXTURE(L"bmp/dirt.bmp", L"dirt");

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
