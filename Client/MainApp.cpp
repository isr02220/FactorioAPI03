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
	TCHAR szBuffer[128];
	lstrcpy(szBuffer, GRAPHICS_DIR);
	lstrcat(szBuffer, L"entity/character/bmp/hr-level1_idle.bmp");
	CBitmapManager::GetInstance()->InsertTexture(szBuffer, L"hr-level1_idle");

	lstrcpy(szBuffer, GRAPHICS_DIR);
	lstrcat(szBuffer, L"entity/character/bmp/hr-level1_running.bmp");
	CBitmapManager::GetInstance()->InsertTexture(szBuffer, L"hr-level1_running");

	lstrcpy(szBuffer, GRAPHICS_DIR);
	lstrcat(szBuffer, L"entity/transport-belt/bmp/hr-transport-belt.bmp");
	CBitmapManager::GetInstance()->InsertTexture(szBuffer, L"hr-transport-belt");
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
