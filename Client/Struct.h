#pragma once
#pragma warning(disable: 4351)

typedef struct tagPosition {
	tagPosition() : x(0), y(0) {}
	tagPosition(FLOAT _x, FLOAT _y) : x(_x), y(_y) {}
	tagPosition operator+(tagPosition dst) { return tagPosition(x + dst.x, y + dst.y); }
	tagPosition operator-(tagPosition& dst) { return tagPosition(x - dst.x, y - dst.y); }
	FLOAT x;
	FLOAT y;
}POSITION;

typedef struct tagForce {
	tagForce() : x(0), y(0) {}
	tagForce(FLOAT _x, FLOAT _y) : x(_x), y(_y) {}
	tagForce operator+(tagForce& dst) { return tagForce(x + dst.x, y + dst.y); }
	tagForce operator-(tagForce& dst) { return tagForce(x - dst.x, y - dst.y); }
	FLOAT x;
	FLOAT y;
}FORCE;

typedef struct tagInfo {
	TCHAR name[32];
	POSITION position;
	FORCE force;
	INT iCX;
	INT iCY;

}INFO;



typedef struct tagItem {
	tagItem(POINT _pos, DWORD _timer) : pos(_pos), timer(_timer) {}
	POINT pos;
	DWORD timer;
}ITEMDATA;



typedef INT SCENE_NUMBER;