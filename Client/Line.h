#pragma once
class CLine final
{
public:
	explicit CLine();
	explicit CLine(const LINEINFO& rLineInfo); 
	virtual ~CLine();
public:
	LINEINFO* GetLineInfo() { return &m_tInfo; }
	void SetRightPos(const LINEPOS& rRightPos) { m_tInfo.RPoint = rRightPos; }
public:
	void RenderLine(HDC hDC); 
private:
	LINEINFO m_tInfo; 
};

