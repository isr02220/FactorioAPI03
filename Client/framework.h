// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

#include "Extern.h"
#include "Enum.h"
#include "Define.h"
#include "Struct.h"
#include "Function.h"
#include "ObjManager.h"
#include "CollisionManager.h"
#include "KeyManager.h"
#include "LineManager.h"
#include "ScrollManager.h"
#include "BitmapManager.h"