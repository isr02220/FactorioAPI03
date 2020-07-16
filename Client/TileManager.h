#pragma once
class CObj; 
class CTileManager
{
public:
	static CTileManager* GetInstance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CTileManager; 
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
	CTileManager();
	~CTileManager();
public:
	void Ready(); 
	void Update(); 
	void Render(HDC hDC); 
	void Release(); 
public:

private:
	static CTileManager* m_pInstance; 
	vector<CObj*> m_vecTile;
};

