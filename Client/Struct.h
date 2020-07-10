#pragma once
#pragma warning(disable: 4351)
typedef struct tagInfo {
	TCHAR chName[32];
	FLOAT fX;
	FLOAT fY;
	INT iCX;
	INT iCY;

}INFO;

typedef struct tagPosition {
	FLOAT x;
	FLOAT y;
}POSITION;

typedef struct tagItem {
	tagItem(POINT _pos, DWORD _timer) : pos(_pos), timer(_timer) {}
	POINT pos;
	DWORD timer;
}ITEMDATA;



typedef INT SCENE_NUMBER;