#pragma once
#include "UI.h"
class CProgressBar :
    public CUI {
public:
	CProgressBar();
	~CProgressBar();
	virtual void Ready_Object() override;
	virtual INT Update_Object() override;
	virtual void LateUpdate_Object() override;
	virtual void Render_Object(HDC hDC) override;
	virtual void Release_Object() override;

public:
	FLOAT GetProgress()   { return progress; }
	void  ResetProgress() { progress = 0.f;  }
	BOOL  IncreaseProgress(const FLOAT& value) {
		if (progress < 1.f) {
			progress += value;
			return false;
		}
		else {
			progress = 0.f;
			return true;
		}
	}
public:
	FLOAT progress = 0.f;
};

