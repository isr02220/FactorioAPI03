#pragma once
#include "framework.h"
class CItem {
public:
	CItem();
	virtual ~CItem();
public:

protected:
	ITEM::GROUP group;
	DWORD timer = GetTickCount();
};

