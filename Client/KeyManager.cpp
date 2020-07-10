#include "framework.h"
#include "KeyManager.h"

CKeyManager* CKeyManager::m_pInstance = nullptr;

CKeyManager::CKeyManager() {
	ZeroMemory(&m_dwKeyUp, sizeof(DWORD));
	ZeroMemory(&m_dwKeyDown, sizeof(DWORD));
	m_dwKeyDown = ~m_dwKeyDown;
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

	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::SHIFT, VK_SHIFT));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::CONTROL, VK_CONTROL));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::ALT, VK_MENU));
}


CKeyManager::~CKeyManager() {
	DestroyInstance();
}