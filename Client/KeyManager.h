#pragma once
#include "framework.h"
namespace KEY {
	const DWORD MoveUp          = 0x00000001;
	const DWORD MoveRight       = 0x00000002;
	const DWORD MoveLeft        = 0x00000004;
	const DWORD MoveDown        = 0x00000008;
	const DWORD Inventory       = 0x00000010;
	const DWORD Technology      = 0x00000020;
	const DWORD CloseGUI        = 0x00000040;
	const DWORD PrimaryAction   = 0x00000080;
	const DWORD SecondaryAction = 0x00000100;
	const DWORD ShowInfo        = 0x00000200;
	const DWORD ClearCursor     = 0x00000400;
	const DWORD DropItem        = 0x00000800;
	const DWORD Rotate          = 0x00001000;
	const DWORD PickUp          = 0x00002000;
	const DWORD Shoot           = 0x00004000;
	const DWORD ShootTo         = 0x00008000;
	const DWORD Enter           = 0x00010000;
	const DWORD ChangeQuickBar  = 0x00020000;
	const DWORD ZoomIn          = 0x00040000;
	const DWORD ZoomOut         = 0x00080000;
	const DWORD Num1            = 0x00100000;
	const DWORD Num2            = 0x00200000;
	const DWORD Num3            = 0x00400000;
	const DWORD Num4            = 0x00800000;
	

	const DWORD SHIFT           = 0x10000000;
	const DWORD CONTROL         = 0x20000000;
	const DWORD ALT			    = 0x40000000;

	enum class ID {
		MoveUp         ,
		MoveRight      ,
		MoveLeft       ,
		MoveDown       ,
		Inventory      ,
		Technology     ,
		CloseGUI    ,
		PrimaryAction  ,    //상호작용
		SecondaryAction,         //채집 삭제 등
		ShowInfo       ,
		ClearCursor    ,
		DropItem       ,
		Rotate         ,
		PickUp         ,
		Shoot          ,
		ShootTo        ,
		Enter          ,
		ChangeQuickBar ,
		ZoomIn         ,
		ZoomOut        ,
		Num1           ,
		Num2           ,
		Num3           ,
		Num4           ,
		SHIFT          ,
		CONTROL        ,
		ALT
	};
};
class CKeyManager {
public:
	static CKeyManager* GetInstance() {
		if (nullptr == m_pInstance)
			m_pInstance = new CKeyManager();

		return m_pInstance;
	}
	static void DestroyInstance() {
		if (m_pInstance) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	CKeyManager();
	~CKeyManager();
public:
	void UpdateKeyManager() {
		m_dwKey = 0;
		KEY_CHECK(MoveUp);
		KEY_CHECK(MoveRight);
		KEY_CHECK(MoveLeft);
		KEY_CHECK(MoveDown);
		KEY_CHECK(Inventory);
		KEY_CHECK(Technology);
		KEY_CHECK(CloseGUI);
		KEY_CHECK(PrimaryAction);
		KEY_CHECK(SecondaryAction);
		KEY_CHECK(ShowInfo);
		KEY_CHECK(ClearCursor);
		KEY_CHECK(DropItem);
		KEY_CHECK(Rotate);
		KEY_CHECK(PickUp);
		KEY_CHECK(Shoot);
		KEY_CHECK(ShootTo);
		KEY_CHECK(Enter);
		KEY_CHECK(ChangeQuickBar);
		KEY_CHECK(ZoomIn);
		KEY_CHECK(ZoomOut);
		KEY_CHECK(Num1);
		KEY_CHECK(Num2);
		KEY_CHECK(Num3);
		KEY_CHECK(Num4);
		KEY_CHECK(SHIFT);
		KEY_CHECK(CONTROL);
		KEY_CHECK(ALT);
	}

	bool KeyUp(DWORD dwKey) {
		if (m_dwKey & dwKey)
			return false;
		else
			return true;
	}

	bool KeyDown(DWORD dwKey) {
		if (m_dwKey & dwKey)
			return true;
		else
			return false;
	}

	bool KeyOnUp(DWORD dwKey) {
		if (m_dwKey & dwKey) {
			m_dwKeyUp |= dwKey;
			return false;
		}
		else if (m_dwKeyUp & dwKey) {
			m_dwKeyUp ^= dwKey;
			return true;
		}

		return false;
	}

	bool KeyOnDown(DWORD dwKey) {
		if (m_dwKey & dwKey) {
			if (m_dwKeyDown & dwKey) {
				m_dwKeyDown &= ~dwKey;
				return true;
			}
		}
		else if (!(m_dwKeyDown & dwKey)){
			m_dwKeyDown ^= dwKey;
		}

		return false;
	}
	void SetKey(KEY::ID _keyID, SHORT _newKey) { keyMap[_keyID] = _newKey; }
private:
	DWORD m_dwKey = 0;
	DWORD m_dwKeyUp = 0;
	DWORD m_dwKeyDown = 0;
	map<KEY::ID, SHORT> keyMap;
	static CKeyManager* m_pInstance;

};