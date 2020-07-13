#include "framework.h"
#include "LineManager.h"

CLine::CLine() {
}

CLine::CLine(const LINEINFO& rLineInfo)
	: m_tInfo(rLineInfo) {
}


CLine::~CLine() {
}

void CLine::RenderLine(HDC hDC) {
	MoveToEx(hDC, int(m_tInfo.LPoint.fX), int(m_tInfo.LPoint.fY), nullptr);
	LineTo(hDC, (int)m_tInfo.RPoint.fX, (int)m_tInfo.RPoint.fY);
}

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
	MessageBox(nullptr, L"LineSave ����!", L"���θŴ���!", MB_OK);
	CloseHandle(hFile);
}

void CLineManager::ReadyLineManager()
{
}

void CLineManager::UpdateLineManager()
{
	// ���⿡�� ����ڰ� �� ���콺�� ����� �� ! 
	//���� �����ϰ� ���� �������� �������! 
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
