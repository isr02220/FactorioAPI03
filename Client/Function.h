#pragma once

template<typename T>
void Safe_Delete(T& rObj) {
	if (rObj) {
		delete rObj;
		rObj = nullptr;
	}
}


inline float DEGREE_RADIAN(float _deg) { return _deg * pi / 180.f; }