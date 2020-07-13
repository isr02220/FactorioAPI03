#include "framework.h"
#include "Main.h"

CMain::CMain()
{
}


CMain::~CMain()
{
	Release_Main(); 
}

void CMain::Ready_Main()
{
	m_hDC = GetDC(g_hWnd); 
}

void CMain::Update_Main()
{
	CKeyManager::GetInstance()->UpdateKeyManager();
	CLineManager::Get_Instance()->UpdateLineManager();
}

void CMain::Render_Main()
{
	CLineManager::Get_Instance()->RenderLineManager(m_hDC); 

}

void CMain::Release_Main()
{
	CLineManager::DestroyInstance(); 
	CKeyManager::DestroyInstance(); 
}
