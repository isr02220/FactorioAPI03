#include "framework.h"
#include "LineManager.h"
#include "Line.h"

CLineManager* CLineManager::m_pInstance = nullptr; 
CLineManager::CLineManager()
{
}


CLineManager::~CLineManager()
{
	ReleaseLineManager(); 
}

void CLineManager::SaveData()
{

	HANDLE hFile = CreateFile(__T("../Data/Line.dat"),GENERIC_WRITE, 0, NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, nullptr); 

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(nullptr, __T("SaveData Failed"), __T("LineManager"), MB_OK);
		return;
	}
	DWORD dwByte = 0; 
	for (auto& pLine : m_listLine)
	{
		WriteFile(hFile, pLine->GetLineInfo(), sizeof(LINEINFO), &dwByte, nullptr);
	}
	MessageBox(nullptr, L"LineSave 성공!", L"라인매니저!", MB_OK);
	CloseHandle(hFile);
}

void CLineManager::ReadyLineManager()
{
}

void CLineManager::UpdateLineManager()
{
	// 여기에서 사용자가 딱 마우스를 찍었을 때 ! 
	//선을 생성하고 선의 시작점을 잡아주자! 
	POINT pt = {};
	GetCursorPos(&pt); 
	ScreenToClient(g_hWnd, &pt); 

	if (CKeyManager::GetInstance()->OnPress(KEY::PrimaryAction))
	{
		CLine* pLine = new CLine(LINEINFO(LINEPOS(float(pt.x), float(pt.y)), LINEPOS(float(pt.x), float(pt.y)))); 
		m_listLine.emplace_back(pLine);
	}
	if (CKeyManager::GetInstance()->OnRelease(KEY::PrimaryAction))
	{
		m_listLine.back()->SetRightPos(LINEPOS(float(pt.x), float(pt.y)));
	}
	if (CKeyManager::GetInstance()->OnPress(KEY::Enter))
	{
		SaveData();
	}

}

void CLineManager::RenderLineManager(HDC hDC)
{
	for (auto& pLine : m_listLine)
	{
		pLine->RenderLine(hDC); 
	}
}

void CLineManager::ReleaseLineManager()
{
	for_each(m_listLine.begin(), m_listLine.end(), Safe_Delete<CLine*>); 
}
