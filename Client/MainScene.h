#pragma once
#include "framework.h"
#include "Scene.h"
class CMainScene :
    public CScene {
public:
	CMainScene() {};
	~CMainScene() {};

public:
	virtual void ReadyScene();
	virtual void UpdateScene();
	virtual void LateUpdateScene();
	virtual void RenderScene(HDC hDC);
	virtual void ReleaseScene();
private:
	bool key1 = false;
	bool key2 = false;
	bool key3 = false;
	bool key4 = false;
};