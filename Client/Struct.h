#pragma once
#pragma warning(disable: 4351)

typedef struct tagForce {
	tagForce() : x(0), y(0) {}
	tagForce(FLOAT _x, FLOAT _y) : x(_x), y(_y) {}
	tagForce operator+(const tagForce& dst) { return tagForce(x + dst.x, y + dst.y); }
	tagForce operator-(const tagForce& dst) { return tagForce(x - dst.x, y - dst.y); }
	tagForce operator*(const FLOAT& dst) { return tagForce(x * dst, y * dst); }
	tagForce operator/(const FLOAT& dst) { return tagForce(x / dst, y / dst); }
	tagForce operator+=(const tagForce& dst) { x += dst.x; y += dst.y; return *this; }
	tagForce operator-=(const tagForce& dst) { x -= dst.x; y -= dst.y; return *this; }
	tagForce operator*=(const FLOAT& dst) { x *= dst; y *= dst; return *this; }
	tagForce operator/=(const FLOAT& dst) { x /= dst; y /= dst; return *this; }
	FLOAT x;
	FLOAT y;
}FORCE;

typedef struct tagPosition {
	tagPosition() : x(0), y(0) {}
	tagPosition(FLOAT _x, FLOAT _y) : x(_x), y(_y) {}
	tagPosition operator+(const tagPosition& dst) { return tagPosition(x + dst.x, y + dst.y); }
	tagPosition operator+=(const tagForce& dst) { x += dst.x; y += dst.y; return *this; }
	tagPosition operator-(const tagPosition& dst) { return tagPosition(x - dst.x, y - dst.y); }
	FLOAT x;
	FLOAT y;
}POSITION;

typedef struct tagWalkingState {
	tagWalkingState() : walking(false), direction(DIRECTION::DIR::NORTH) {}
	void operator=(const BOOL& dst) { walking = dst; }
	BOOL walking;
	DIRECTION::DIR direction;
}WALKINGSTATE;

typedef struct tagMiningState {
	tagMiningState() : mining(false), position(0, 0) {}
	void operator=(const BOOL& dst) { mining = dst; }
	BOOL mining;
	POSITION position;
}MININGSTATE;

typedef struct tagShootingState {
	tagShootingState() : shooting(false), position(0, 0) {}
	void operator=(const BOOL& dst) { shooting = dst; }
	BOOL shooting;
	POSITION position;
}SHOOTINGSTATE;

typedef BOOL PICKINGSTATE;

typedef struct tagRepairState {
	tagRepairState() : shooting(false), position(0, 0) {}
	void operator=(const BOOL& dst) { shooting = dst; }
	BOOL shooting;
	POSITION position;
}REPAIRSTATE;

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