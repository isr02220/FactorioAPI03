#include "Obj.h"

CObj::CObj() {
	ZeroMemory(&info, sizeof(INFO));
}
CObj::CObj(FLOAT _positionX, FLOAT _positionY){
	ZeroMemory(&info, sizeof(INFO));
	info.position.x = _positionX;
	info.position.y = _positionY;
}

CObj::~CObj() {
}

void CObj::Update_Rect_Object() {
	rect.left   = LONG(info.position.x - (info.iCX >> 1));
	rect.top    = LONG(info.position.y - (info.iCY >> 1));
	rect.right  = LONG(info.position.x + (info.iCX >> 1));
	rect.bottom = LONG(info.position.y + (info.iCY >> 1));

	cRect.left   = LONG(info.position.x - (info.CCX >> 1));
	cRect.top    = LONG(info.position.y - (info.CCY >> 1));
	cRect.right  = LONG(info.position.x + (info.CCX >> 1));
	cRect.bottom = LONG(info.position.y + (info.CCY >> 1));
}
