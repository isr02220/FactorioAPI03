#pragma once
#include "framework.h"
#include "Scene.h"
class CObj;
class CMainApp final {
public:
	CMainApp();
	~CMainApp();

public:
	void Ready_MainApp();
	void Update_MainApp();
	void LateUpdate_MainApp();
	void Render_MainApp();
	void Release_MainApp();
private:
	HDC m_hDC;
	DWORD m_dwOldTime = 0;
	map<SCENE_NUMBER, CScene*> m_mapScene;
};

