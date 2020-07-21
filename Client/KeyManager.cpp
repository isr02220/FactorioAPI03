#include "framework.h"
#include "KeyManager.h"

CKeyManager* CKeyManager::m_pInstance = nullptr;

CKeyManager* CKeyManager::GetInstance() {
	if (nullptr == m_pInstance)
		m_pInstance = new CKeyManager();

	return m_pInstance;
}

void CKeyManager::DestroyInstance() {
	if (m_pInstance) {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

CKeyManager::CKeyManager() {
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::MoveUp, 'W'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::MoveRight, 'D'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::MoveLeft, 'A'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::MoveDown, 'S'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::Inventory, 'E'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::Technology, 'T'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::CloseGUI, 'E'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::PrimaryAction, VK_LBUTTON));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::SecondaryAction, VK_RBUTTON));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::ShowInfo, VK_MENU));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::ClearCursor, 'Q'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::DropItem, 'Z'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::Rotate, 'R'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::PickUp, 'F'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::Shoot, VK_SPACE));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::ShootTo, 'C'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::Enter, VK_RETURN));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::ChangeQuickBar, 'X'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::ZoomIn, VK_NUMPAD6));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::ZoomOut, VK_NUMPAD9));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::Num1, '1'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::Num2, '2'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::Num3, '3'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::Num4, '4'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::Num5, '5'));
		  
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::SHIFT, VK_SHIFT));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::CONTROL, VK_CONTROL));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::ALT, VK_MENU));
}


CKeyManager::~CKeyManager() {
	DestroyInstance();
}

void CKeyManager::UpdateKeyManager() {
	m_dwKeyEx = m_dwKey;
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
	KEY_CHECK(Num5);
	KEY_CHECK(SHIFT);
	KEY_CHECK(CONTROL);
	KEY_CHECK(ALT);
}

void CKeyManager::SetKey(KEY::ID _keyID, SHORT _newKey) { keyMap[_keyID] = _newKey; }