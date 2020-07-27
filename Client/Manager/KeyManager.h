#pragma once
namespace KEY {
	enum class ID {
		MoveUp,
		MoveRight,
		MoveLeft,
		MoveDown,
		Inventory,
		Technology,
		CloseGUI,
		PrimaryAction,           //상호작용
		SecondaryAction,         //채집 삭제 등
		ShowInfo,
		Mission,
		ClearCursor,
		ClearSlot,
		DropItem,
		Rotate,
		PickUp,
		Shoot,
		ShootTo,
		Enter,
		ChangeQuickBar,
		ZoomIn,
		ZoomOut,
		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Cheat,
		SHIFT,
		CONTROL,
		ALT
	};
	const DWORD MoveUp          = 1 << (INT)ID::MoveUp         ;
	const DWORD MoveRight       = 1 << (INT)ID::MoveRight      ;
	const DWORD MoveLeft        = 1 << (INT)ID::MoveLeft       ;
	const DWORD MoveDown        = 1 << (INT)ID::MoveDown       ;
	const DWORD Inventory       = 1 << (INT)ID::Inventory      ;
	const DWORD Technology      = 1 << (INT)ID::Technology     ;
	const DWORD CloseGUI        = 1 << (INT)ID::CloseGUI       ;
	const DWORD PrimaryAction   = 1 << (INT)ID::PrimaryAction  ;
	const DWORD SecondaryAction = 1 << (INT)ID::SecondaryAction;
	const DWORD ShowInfo        = 1 << (INT)ID::ShowInfo       ;
	const DWORD Mission         = 1 << (INT)ID::Mission        ;
	const DWORD ClearCursor     = 1 << (INT)ID::ClearCursor    ;
	const DWORD ClearSlot       = 1 << (INT)ID::ClearSlot      ;
	const DWORD DropItem        = 1 << (INT)ID::DropItem       ;
	const DWORD Rotate          = 1 << (INT)ID::Rotate         ;
	const DWORD PickUp          = 1 << (INT)ID::PickUp         ;
	const DWORD Shoot           = 1 << (INT)ID::Shoot          ;
	const DWORD ShootTo         = 1 << (INT)ID::ShootTo        ;
	const DWORD Enter           = 1 << (INT)ID::Enter          ;
	const DWORD ChangeQuickBar  = 1 << (INT)ID::ChangeQuickBar ;
	const DWORD ZoomIn          = 1 << (INT)ID::ZoomIn         ;
	const DWORD ZoomOut         = 1 << (INT)ID::ZoomOut        ;
	const DWORD Num1            = 1 << (INT)ID::Num1           ;
	const DWORD Num2            = 1 << (INT)ID::Num2           ;
	const DWORD Num3            = 1 << (INT)ID::Num3           ;
	const DWORD Num4            = 1 << (INT)ID::Num4           ;
	const DWORD Num5            = 1 << (INT)ID::Num5           ;
	const DWORD Cheat           = 1 << (INT)ID::Cheat          ;
												

	const DWORD SHIFT           = 1 << (INT)ID::SHIFT          ;
	const DWORD CONTROL         = 1 << (INT)ID::CONTROL        ;
	const DWORD ALT			    = 1 << (INT)ID::ALT		       ;

	
};

class CKeyManager {
public:
	static CKeyManager* GetInstance();
	static void DestroyInstance();
private:
	CKeyManager();
	~CKeyManager();
public:
	void UpdateKeyManager();
	bool Release(DWORD dwKey) {
		if (m_dwKey & dwKey)
			return false;
		else
			return true;
	}

	bool Press(DWORD dwKey) {
		if (m_dwKey & dwKey)
			return true;
		else
			return false;
	}

	bool OnRelease(DWORD dwKey) {
		if (!(m_dwKey & dwKey) && (m_dwKeyEx & dwKey))
			return true;
		else 
			return false;
		
		return false;

	}

	bool OnPress(DWORD dwKey) {
		if ((m_dwKey & dwKey) && !(m_dwKeyEx & dwKey))
			return true;
		else
			return false;

		return false;
	}
	void SetKey(KEY::ID _keyID, SHORT _newKey);
private:
	DWORD m_dwKey = 0;
	DWORD m_dwKeyEx = 0;
	map<KEY::ID, SHORT> keyMap;
	static CKeyManager* m_pInstance;

};