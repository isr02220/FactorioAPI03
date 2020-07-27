#pragma once
#include "UI.h"
class CActor;
class CItemStack;
class CMissionUI :
	public CUI {
public:
	CMissionUI();
	~CMissionUI();
	virtual void Ready_Object() override;
	virtual INT Update_Object() override;
	virtual void LateUpdate_Object() override;
	virtual void Render_Object(HDC hDC) override;
	virtual void Release_Object() override;
	virtual void OnCollision(CObj* _TargetObj) override;
	void CheckMisionComplete();
	CActor* targetActor = nullptr;
	UINT UIstate = 1;
	DWORD missionState = 0;
	TCHAR missionStrings[5][64];
	TCHAR tipStrings[13][32];
};

