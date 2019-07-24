#include "GameFrame.h"
#include "..\\resource.h"

#define _DEF_CLIENT_W 640
#define _DEF_CLIENT_H 480
#define _SLEEP_TIME 33u
#define _SLEEP_TIME_MIN 10u

int CGameFrame::m_DefClientW = _DEF_CLIENT_W;
int CGameFrame::m_DefClientH = _DEF_CLIENT_H;

CGameFrame* CGameFrame::m_pGameFrame = 0;

__w64 long __stdcall CGameFrame::_GameWndProc(HWND hwnd, unsigned int uMsg, __w64 unsigned int wParam, __w64 long lParam)
{
	CGameFrame* pGF = CGameFrame::GetObject();

	switch (uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_ACTIVATEAPP:
		{
			m_pGameFrame->m_Act = BOOL(wParam);
			return 0;
		}
	case WM_MOUSEMOVE:
		{
			POINT cp = {LOWORD(lParam), HIWORD(lParam)};

			if (pGF->m_pCurScene)
			{
				std::map<std::string, CUI*>* pUI = &pGF->m_pCurScene->m_UI;
				std::map<std::string, CUI*>::iterator i;

				//遍历所有UI
				for (i = pUI->begin(); i != pUI->end(); ++i)
				{
					//当UI为激活
					if (i->second->active)
					{
						RECT r 
							=
						{
							i->second->x1,
							i->second->y1,
							i->second->x2,
							i->second->y2
						};

						if (PtInRect(&r, pGF->m_pP) && !PtInRect(&r, cp)) //上次在这次不在
							i->second->CursorQuit(); //多态
						else if (!PtInRect(&r, pGF->m_pP) && PtInRect(&r, cp)) //上次不在这次在
							i->second->CursorEnter(); //多态
						else if (PtInRect(&r, pGF->m_pP) && PtInRect(&r, cp)) //上次在这次在
							i->second->CursorInMove(cp.x - i->second->x1, cp.y - i->second->y1);
						else //上次不在这次不在
							i->second->CursorOutMove();
					}
				}
			}

			//将被位置赋给前次位置
			pGF->m_pP = cp;

			return 0;
		}
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		{
			POINT cp = {LOWORD(lParam), HIWORD(lParam)};

			if (pGF->m_pCurScene)
			{
				std::map<std::string, CUI*>* pUI = &pGF->m_pCurScene->m_UI;
				std::map<std::string, CUI*>::iterator i;

				//遍历所有UI
				for (i = pUI->begin(); i != pUI->end(); ++i)
				{
					//当UI为激活
					if (i->second->active)
					{
						RECT r 
							=
						{
							i->second->x1,
							i->second->y1,
							i->second->x2,
							i->second->y2
						};

						//点中控件
						if (PtInRect(&r, cp))
						{
							switch (uMsg)
							{
							case WM_LBUTTONDOWN: i->second->LButtonInDown(cp.x - i->second->x1, cp.y - i->second->y1); break;
							case WM_LBUTTONUP: i->second->LButtonInUp(cp.x - i->second->x1, cp.y - i->second->y1); break;
							case WM_MBUTTONDOWN: i->second->MButtonInDown(cp.x - i->second->x1, cp.y - i->second->y1); break;
							case WM_MBUTTONUP: i->second->MButtonInUp(cp.x - i->second->x1, cp.y - i->second->y1); break;
							case WM_RBUTTONDOWN: i->second->RButtonInDown(cp.x - i->second->x1, cp.y - i->second->y1); break;
							case WM_RBUTTONUP: i->second->RButtonInUp(cp.x - i->second->x1, cp.y - i->second->y1); break;
							}
						}
						//未点中控件
						else
						{
							switch (uMsg)
							{
							case WM_LBUTTONDOWN: i->second->LButtonOutDown(); break;
							case WM_LBUTTONUP: i->second->LButtonOutUp(); break;
							case WM_MBUTTONDOWN: i->second->MButtonOutDown(); break;
							case WM_MBUTTONUP: i->second->MButtonOutUp(); break;
							case WM_RBUTTONDOWN: i->second->RButtonOutDown(); break;
							case WM_RBUTTONUP: i->second->RButtonOutUp(); break;
							}
						}
					}
				}
			}

			return 0;
		}
	case WM_KEYDOWN:
		{
			if (pGF->m_pCurScene && pGF->m_pCurScene->m_KeyInputUI)
				pGF->m_pCurScene->m_KeyInputUI->KeyDown((int)wParam);

			return 0;
		}
	case WM_KEYUP:
		{
			if (pGF->m_pCurScene && pGF->m_pCurScene->m_KeyInputUI)
				pGF->m_pCurScene->m_KeyInputUI->KeyUp((int)wParam);

			return 0;
		}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

CGameFrame::CGameFrame()
:
m_ClientW(m_DefClientW),
m_ClientH(m_DefClientH),
m_SleepTime(_SLEEP_TIME),
m_hWnd(0),
m_pGameInput(0),
m_pGameOutput(0),
m_pCurScene(0)
{
	m_WndClass.style = CS_HREDRAW | CS_VREDRAW;
	m_WndClass.lpfnWndProc = _GameWndProc;
	m_WndClass.cbClsExtra = 0;
	m_WndClass.cbWndExtra = 0;
	m_WndClass.hInstance = GetModuleHandle(0);
	m_WndClass.hIcon = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON1));
	m_WndClass.hCursor = LoadCursor(GetModuleHandle(0), MAKEINTRESOURCE(IDC_CURSOR1));
	m_WndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	m_WndClass.lpszMenuName = 0;
	m_WndClass.lpszClassName = "Test";

	RegisterClass(&m_WndClass);

	RECT r =
	{
		(GetSystemMetrics(SM_CXSCREEN) - m_ClientW) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - m_ClientH) / 2,
		(GetSystemMetrics(SM_CXSCREEN) - m_ClientW) / 2 + m_ClientW,
		(GetSystemMetrics(SM_CYSCREEN) - m_ClientH) / 2 + m_ClientH
	};
	AdjustWindowRect(&r, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);

	m_hWnd = CreateWindow(
		m_WndClass.lpszClassName,
		0,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		r.left,
		r.top,
		r.right - r.left,
		r.bottom - r.top,
		HWND_DESKTOP,
		0,
		m_WndClass.hInstance,
		0);

	m_Act = TRUE;

	m_pGameInput = new CCPGameInput;
	m_pGameOutput = new CGameOutput(m_hWnd);

	m_pGameFrame = this;

	////设置窗口标题
	//m_pGameOutput->SetWindowTitle("标题Test");

	//初始化前次的光标位置
	m_pP.x = 0;
	m_pP.y = 0;
}

CGameFrame::CGameFrame(const CGameFrame& that)
{}

CGameFrame& CGameFrame::operator = (const CGameFrame& that)
{
	return *this;
}

CGameFrame::~CGameFrame()
{
	std::map<std::string, CScene*>::iterator i;
	for (i = m_Scene.begin(); i != m_Scene.end(); ++i)
	{
		i->second->End();
		delete i->second;
	}
	delete m_pGameOutput;
	delete m_pGameInput;
	UnregisterClass(m_WndClass.lpszClassName, m_WndClass.hInstance);
}

void CGameFrame::Run()
{
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (m_Act)
		{
			unsigned int bt = GetTickCount();

			m_pGameInput->Run();
			m_pGameOutput->Begin();

			if (m_pCurScene)
			{
				m_pCurScene->Run();

				std::map<std::string, CUI*>::iterator i;

				for (i = m_pCurScene->m_UI.begin(); i != m_pCurScene->m_UI.end(); ++i)
				{
					if (i->second->active)
						i->second->Render();
				}
			}

			m_pGameOutput->End();

			unsigned int t = GetTickCount() - bt;
			Sleep(t < (unsigned int)m_SleepTime ? m_SleepTime - t : _SLEEP_TIME_MIN);
		}
		else
			WaitMessage();
	}
}

void CGameFrame::End()
{
	if (m_pGameFrame)
	{
		delete m_pGameFrame;
		m_pGameFrame = 0;
	}
}

bool CGameFrame::LoadScene(CScene* pScene, const char* ID)
{
	std::string s = ID;
	std::map<std::string, CScene*>::iterator i = m_Scene.find(s);
	if (i != m_Scene.end())
		return false;

	pScene->Init();

	m_Scene.insert(std::pair<std::string, CScene*>(std::string(ID), pScene));

	return true;
}

bool CGameFrame::ReleaseScene(const char* ID)
{
	std::string s = ID;
	std::map<std::string, CScene*>::iterator i = m_Scene.find(s);
	if (i == m_Scene.end())
		return false;

	i->second->End();
	delete i->second;
	m_Scene.erase(i);

	return true;
}

bool CGameFrame::SetCurScene(const char* ID)
{
	std::string s = ID;
	std::map<std::string, CScene*>::iterator i = m_Scene.find(s);
	if (i == m_Scene.end())
		return false;

	if (m_pCurScene)
		m_pCurScene->Quit();

	m_pCurScene = i->second;

	m_pCurScene->Enter();

	return true;
}

CScene* CGameFrame::GetScene(const char* ID)
{
	std::string s = ID;
	std::map<std::string, CScene*>::iterator i = m_Scene.find(s);
	return i != m_Scene.end() ? i->second : 0;
}

bool CGameFrame::SetClient(int ClientW, int ClientH)
{
	if (ClientW > 1 && ClientH > 1)
	{
		m_DefClientW = ClientW;
		m_DefClientH = ClientH;
		return true;
	}
	else
		return false;
}

CGameFrame* CGameFrame::GetObject()
{
	if (!m_pGameFrame)
		m_pGameFrame = new CGameFrame;
	return m_pGameFrame;
}

int CGameFrame::GetW() const
{
	return m_ClientW;
}

int CGameFrame::GetH() const
{
	return m_ClientH;
}

CCPGameInput* CGameFrame::GetGI()
{
	return m_pGameInput;
}

CGameOutput* CGameFrame::GetGO()
{
	return m_pGameOutput;
}

void CGameFrame::SetSleepTime(int SleepTime)
{
	if (SleepTime > 0)
		m_SleepTime = SleepTime;
}

void CGameFrame::Quit()
{
	PostQuitMessage(1);
}

HWND CGameFrame::GetHwnd()
{
	return m_hWnd;
}
