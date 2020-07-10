#pragma once
#include "framework.h"
namespace KEY {
	const DWORD ATTACK = 0x00000001;
	const DWORD JUMP = 0x00000002;
	const DWORD LEFT = 0x00000004;
	const DWORD RIGHT = 0x00000008;
	enum class ID {
		ATTACK,
		JUMP,
		LEFT,
		RIGHT
	};
};

class CKeyManager {
public:
	static CKeyManager* GetInstance() {
		if (nullptr == m_pInstance)
			m_pInstance = new CKeyManager;

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
		if (GetAsyncKeyState(keyMap[KEY::ID::ATTACK]) & 0x8000)
			m_dwKey |= KEY::ATTACK;
		if (GetAsyncKeyState(keyMap[KEY::ID::JUMP]) & 0x8000)
			m_dwKey |= KEY::JUMP;
		if (GetAsyncKeyState(keyMap[KEY::ID::LEFT]) & 0x8000)
			m_dwKey |= KEY::LEFT;
		if (GetAsyncKeyState(keyMap[KEY::ID::RIGHT]) & 0x8000)
			m_dwKey |= KEY::RIGHT;
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
			m_dwKeyEx |= dwKey;
			return false;
		}
		else if (m_dwKeyEx & dwKey) {
			m_dwKeyEx ^= dwKey;
			return true;
		}

		return false;
	}

	bool KeyOnDown(DWORD dwKey) {
		if (m_dwKeyEx & dwKey) {
			m_dwKeyEx |= dwKey;
			return true;
		}
		else if (m_dwKey & dwKey) {
			m_dwKeyEx ^= dwKey;
			return false;
		}

		return false;
	}
	void SetKey(KEY::ID _keyID, SHORT _newKey) { keyMap[_keyID] = _newKey; }
private:
	DWORD m_dwKey = 0;
	DWORD m_dwKeyEx = 0;
	map<KEY::ID, SHORT> keyMap;
	static CKeyManager* m_pInstance;

};