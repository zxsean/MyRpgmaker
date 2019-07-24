#ifndef _GAME_FRAME_H_
#define _GAME_FRAME_H_

#include <windows.h>
#include <string>
#include <map>
#include "CPGameInput.h"
#include "GameOutput.h"
#include "Scene.h"

class CGameFrame
{
private:
	WNDCLASS m_WndClass;
	int m_ClientW;
	int m_ClientH;
	int m_SleepTime;
	HWND m_hWnd;
	BOOL m_Act;
	CCPGameInput* m_pGameInput;
	CGameOutput* m_pGameOutput;
	std::map<std::string, CScene*> m_Scene;
	CScene* m_pCurScene;
	POINT m_pP; //前一次的光标位置

	static int m_DefClientW, m_DefClientH, m_DefSleepTime;
	static CGameFrame* m_pGameFrame;

	static __w64 long __stdcall _GameWndProc(HWND hwnd, unsigned int uMsg, __w64 unsigned int wParam, __w64 long lParam);
	
	CGameFrame();
	CGameFrame(const CGameFrame& that);
	CGameFrame& operator = (const CGameFrame& that);

public:
	~CGameFrame();

	void Run();
	void End();

	//场景相关
	bool LoadScene(CScene* pScene, const char* ID);
	bool ReleaseScene(const char* ID);
	bool SetCurScene(const char* ID);
	CScene* GetScene(const char* ID);

	//框架
	static bool SetClient(int ClientW, int ClientH);
	static CGameFrame* GetObject();

	//其它
	int GetW() const;
	int GetH() const;
	CCPGameInput* GetGI();
	CGameOutput* GetGO();
	HWND GetHwnd();
	void SetSleepTime(int SleepTime);
	void Quit();
};

#endif