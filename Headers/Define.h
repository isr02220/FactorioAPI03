#pragma once
#pragma warning(disable: 26812)

#define STATE_DEAD 1
#define STATE_NO_EVENT 0

const int WINCX = 1600;
const int WINCY = 900;
const FLOAT pi = 3.141592f;
const FLOAT radian = 180 / pi;

#define SCENE_MAIN 0
#define SCENE_PLAY 1

#define GRIDCX 64
#define GRIDCY 64
#define GRIDX 200
#define GRIDY 200

#define TILECX 256
#define TILECY 256
#define TILEX 50
#define TILEY 50

#define KEY_CHECK(keyId) if (GetAsyncKeyState(keyMap[KEY::ID::##keyId]) & 0x8000) m_dwKey |= KEY::##keyId
#define GRAPHICS_DIR L"C:/Program Files (x86)/Steam/steamapps/common/Factorio/data/base/graphics/"
#define INSERT_TEXTURE(dir, key) lstrcpy(szBuffer, GRAPHICS_DIR);\
								 lstrcat(szBuffer, ##dir);\
								 CBitmapManager::GetInstance()->InsertTexture(szBuffer, ##key)

typedef INT SCENE_NUMBER;
typedef INT TYPEORDER;
typedef FLOAT ORIENTATION;
