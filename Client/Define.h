#pragma once
#pragma warning(disable: 26812)

#define STATE_DEAD 1
#define STATE_NO_EVENT 0

const int WINCX = 1200;
const int WINCY = 900;
const FLOAT pi = 3.141592f;
const FLOAT radian = 180 / pi;

#define SCENE_MAIN 0
#define SCENE_PLAY 1

#define KEY_CHECK(keyId) if (GetAsyncKeyState(keyMap[KEY::ID::##keyId]) & 0x8000) m_dwKey |= KEY::##keyId;