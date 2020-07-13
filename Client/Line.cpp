#include "framework.h"
#include "Line.h"


CLine::CLine()
{
}

CLine::CLine(const LINEINFO & rLineInfo)
	: m_tInfo(rLineInfo)
{
}


CLine::~CLine()
{
}

void CLine::RenderLine(HDC hDC)
{
	MoveToEx(hDC, int(m_tInfo.LPoint.fX), int(m_tInfo.LPoint.fY), nullptr); 
	LineTo(hDC, (int)m_tInfo.RPoint.fX, (int)m_tInfo.RPoint.fY); 
}
