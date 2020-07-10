#pragma once
#include "framework.h"
#include "ObjManager.h"
#include "ItemManager.h"
#include "Scene.h"
#include "Background.h"
class CPlayScene :
	public CScene {
public:
	CPlayScene();
	~CPlayScene();

public:
	
	virtual void ReadyScene();
	virtual void UpdateScene();
	virtual void LateUpdateScene();
	virtual void RenderScene(HDC hDC);
	virtual void ReleaseScene();
private:
	CObjManager* ObjManager = CObjManager::GetInstance();
	CItemManager itemManager;
	CBackground* m_bg = nullptr;
	int m_iFPS = 0;
	TCHAR m_szFPS[32] = L"";
	DWORD m_dwOldTime = 0;
};

