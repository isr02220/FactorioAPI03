#pragma once
class CLine; 
class CLineManager
{
public:
	static CLineManager* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CLineManager; 
		return m_pInstance; 
	}
	static void DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance; 
			m_pInstance = nullptr; 
		}
	}
private:
	CLineManager();
	~CLineManager();
public:
	void SaveData(); 
public:
	void ReadyLineManager(); 
	void UpdateLineManager(); 
	void RenderLineManager(HDC hDC); 
	void ReleaseLineManager(); 


private:
	list<CLine*> m_listLine; 
	static CLineManager* m_pInstance; 
};

