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