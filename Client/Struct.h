#pragma once

typedef struct tagInfo {
	TCHAR chName[32];
	float fX;
	float fY;
	int iCX;
	int iCY;

}INFO;

typedef struct tagItem {
	tagItem(ITEM::ID _item, POINT _pos, DWORD _timer) : item(_item), pos(_pos), timer(_timer) {}
	ITEM::ID item;
	POINT pos;
	DWORD timer;
}ITEMDATA;
typedef INT SCENE_NUMBER;