#pragma once
#include "framework.h"
class CItem {
public:
	CItem();
	virtual ~CItem();
public:

protected:
	TCHAR name[32];
	ITEM::GROUP group;

	DWORD timer = GetTickCount();
};

