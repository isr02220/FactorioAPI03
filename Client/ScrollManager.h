#pragma once
class CScrollManager {
public:
	static CScrollManager* GetInstance();
	void DestroyInstance();
private:
	CScrollManager();
	~CScrollManager();

public:
	INT GetScrollX() { return (INT)scrollX; }
	INT GetScrollY() { return (INT)scrollY; }
	void SetScrollX(const FLOAT& _scrollX) { scrollX += _scrollX; }
	void SetScrollY(const FLOAT& _scrollY) { scrollY += _scrollY; }
	void SetScroll(const FORCE& _force) { scrollX += _force.x; scrollY += _force.y; }
	void SetScroll(const POSITION& _pos) { scrollX = _pos.x; scrollY = _pos.y; }
private:
	static CScrollManager* m_pInstance;
	FLOAT scrollX;
	FLOAT scrollY;
};

