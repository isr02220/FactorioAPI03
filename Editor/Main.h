#pragma once
class CMain
{
public:
	CMain();
	~CMain();
public:
	void Ready_Main(); 
	void Update_Main(); 
	void Render_Main(); 
	void Release_Main(); 

public:
	HDC m_hDC; 
};

