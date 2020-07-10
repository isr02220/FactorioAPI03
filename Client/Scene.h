#pragma once
#include "framework.h"
#include "ObjManager.h"
class CScene abstract{
public:
	CScene() {};
	virtual ~CScene() {};
public:
	virtual void ReadyScene();
	virtual void UpdateScene();
	virtual void LateUpdateScene();
	virtual void RenderScene(HDC hDC);
	virtual void ReleaseScene();
	BOOL GetActive() { return m_Active; };
	void SetActive(BOOL _Active) { m_Active = _Active; };
protected:

	DWORD m_dwOldTime = 0;
	BOOL m_Active = false;
};

