#pragma once

template<typename T>
void Safe_Delete(T& rObj) {
	if (rObj) {
		delete rObj;
		rObj = nullptr;
	}
}


inline FLOAT ToRadian(FLOAT _deg) { return _deg * pi / 180.f; }
inline FLOAT ToDegree(FLOAT _rad) { return _rad / pi * 180.f; }
inline INT PosToIndex(const POSITION & _position) {
	return ((INT)_position.y / GRIDCY * GRIDX) + ((INT)_position.x / GRIDCX);
}
inline POSITION ToGridPos(const POSITION& _position, const INT& _tileSize) {

	INT gridPosX = (INT)_position.x / GRIDCX;
	INT gridPosY = (INT)_position.y / GRIDCY;

	//POINT Pos = {};
	//Pos.x = (INT)_position.x;
	//Pos.y = (INT)_position.y;
	//if (labs(Pos.x % _tileSize) < (_tileSize >> 1))
	//	Pos.x -= (Pos.x % _tileSize);
	//else if(Pos.x < 0.f)
	//	Pos.x -= (Pos.x % _tileSize) + _tileSize;
	//else
	//	Pos.x -= (Pos.x % _tileSize) - _tileSize;

	//if (labs(Pos.y % _tileSize) < (_tileSize >> 1))
	//	Pos.y -= (Pos.y % _tileSize);
	//else if (Pos.y < 0.f)
	//	Pos.y -= (Pos.y % _tileSize) + _tileSize;
	//else
	//	Pos.y -= (Pos.y % _tileSize) - _tileSize;

	return POSITION(FLOAT(gridPosX * GRIDCX + (_tileSize >> 1)), FLOAT(gridPosY * GRIDCY + (_tileSize >> 1)));
}