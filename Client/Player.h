#pragma once
#include "Actor.h"
class CUI;
class CMouse;
class CInventory;
class CPlayer : public CActor {
public:
	CPlayer();
	CPlayer(FLOAT _positionX, FLOAT _positionY);
	virtual ~CPlayer();
public:
	virtual void Ready_Object() override;
	virtual int Update_Object() override;
	virtual void LateUpdate_Object() override;
	virtual void Render_Object(HDC hDC) override;
	virtual void Release_Object() override;
	virtual void OnCollision(CObj* _TargetObj) override;

	virtual CObj* GetNewActor() override;
	virtual CItem* GetNewItem() override;
public:
	void Move();
	void SecondaryAction();
	void PlaceEntity();
	void UnPlaceEntity();
	void GatherResource();
	void RotateEntity();
	void RotateCursor();
	void UpdateSelectedUI(CUI* _targetUI);
public:
	CMouse* playerMouse = nullptr;
	CUI* selectedUI;
	CUI* focusedUI;
	CUI* QuickSlotUI;
	CUI* ProgressBarUI;
	

};

