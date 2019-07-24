#include <windows.h>
#include <iostream>
#include <string>
#include <map>
#include "resource.h"
#include "MapData.h"
#include "GameOutput.h"
#include "MapCrashId.h"

#define _PIC_W 32
#define _PIC_H 32

//#define _CLIENT_W (_PIC_W * _MAP_W)
//#define _CLIENT_H (_PIC_H * _MAP_H)
#define _CLIENT_W 640
#define _CLIENT_H 480

#define _ZA 0 //障碍
#define _DX 1 //地形
#define _JW 2 //景物
#define _NPC 3 //NPC
#define _JZ 4 //建筑
#define _ID 5 //ID
#define _SHOW 6 //数据页
#define _MapType 7 //地图数据

#define _PIC_W 32
#define _PIC_H 32

int ViewX, ViewY; //视口(客户区)左上角坐标

int g_MapNum; //地图数量
CMapData g_Map; //地图
std::map<int, CMapData> g_MapList; //地图映射
char* g_MapDX; //地图地形层
char* g_MapBuild; //地图建筑层
_Crash_Data* g_MapCrash; //地图碰撞层
char* g_MapObject; //地图物件层
int g_XuanZe = -1; //选择物件
int g_XuanZeType = -1; //选择类型
CGameOutput* g_Cr; //渲染器指针
_Crash_Data g_TempCrash; //设置碰撞用临时

//对话框设置
#define _DIALOG_NUM 8
HWND MapEdit[_DIALOG_NUM];
HINSTANCE g_hInstance; //全局应用程序实例句柄
BOOL g_Act = true;
HWND g_hwnd;

//地形
#define _DX_PIC_NUM 100
HBITMAP g_Bmp_DX[_DX_PIC_NUM]; //位图
HDC g_BmpDC_DX[_DX_PIC_NUM]; //位图兼容设备
HDC g_MainDC_DX; //地形mainDC
char g_BmpMap_DX[_DX_PIC_NUM]; //逻辑数组
#define g_BmpMapW_DX 10
#define g_BmpMapH_DX 10

//建筑
#define _Build_PIC_NUM 100
HBITMAP g_Bmp_Build[_Build_PIC_NUM]; //位图
HDC g_BmpDC_Build[_Build_PIC_NUM]; //位图兼容设备
HDC g_MainDC_Build; //地形mainDC
char g_BmpMap_Build[_Build_PIC_NUM]; //逻辑数组
#define g_BmpMapW_Build 10
#define g_BmpMapH_Build 10

//装饰物
#define _Object_PIC_NUM 100
HBITMAP g_Bmp_Object[_Object_PIC_NUM]; //位图
HDC g_BmpDC_Object[_Object_PIC_NUM]; //位图兼容设备
HDC g_MainDC_Object; //装饰物mainDC
char g_BmpMap_Object[_Object_PIC_NUM]; //逻辑数组
#define g_BmpMapW_Object 10
#define g_BmpMapH_Object 10

//障碍层
#define _Crash_PIC_NUM 6
HBITMAP g_Bmp_Crash[_Crash_PIC_NUM]; //位图
HDC g_BmpDC_Crash[_Crash_PIC_NUM]; //位图兼容设备
HDC g_MainDC_Crash; //装饰物mainDC
char g_BmpMap_Crash[_Crash_PIC_NUM]; //逻辑数组
#define g_BmpMapW_Crash 10
#define g_BmpMapH_Crash 10

//地图数据
INT_PTR CALLBACK MAPEDIT_DATASHOW(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
//地图ID
INT_PTR CALLBACK MAPEDIT_ID(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
//地形
INT_PTR CALLBACK MAPEDIT_DX(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
//障碍
INT_PTR CALLBACK MAPEDIT_ZA(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
//建筑
INT_PTR CALLBACK MAPEDIT_JZ(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
//NPC
INT_PTR CALLBACK MAPEDIT_NPC(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
//景物
INT_PTR CALLBACK MAPEDIT_JW(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
//地图类型设置
INT_PTR CALLBACK MAPEDIT_MapSet(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		{
			//障碍
			MapEdit[_ZA] = CreateDialog(
				g_hInstance, 
				MAKEINTRESOURCE(IDD_DIALOG4), 
				hwnd,
				MAPEDIT_ZA); 
			//景物
			MapEdit[_JW] = CreateDialog(
				g_hInstance, 
				MAKEINTRESOURCE(IDD_DIALOG2), 
				hwnd, 
				MAPEDIT_JW); 
			//NPC
			MapEdit[_NPC] = CreateDialog(
				g_hInstance, 
				MAKEINTRESOURCE(IDD_DIALOG3), 
				hwnd, 
				MAPEDIT_NPC); 
			//地形
			MapEdit[_DX] = CreateDialog(
				g_hInstance, 
				MAKEINTRESOURCE(IDD_DIALOG1), 
				hwnd,
				MAPEDIT_DX); 
			//建筑
			MapEdit[_JZ] = CreateDialog(
				g_hInstance, 
				MAKEINTRESOURCE(IDD_DIALOG5), 
				hwnd, 
				MAPEDIT_JZ); 

			//地图数据显示
			MapEdit[_SHOW] = CreateDialog(
				g_hInstance, 
				MAKEINTRESOURCE(IDD_DIALOG7), 
				hwnd, 
				MAPEDIT_DATASHOW); 

			return 0;
		}
	case WM_ACTIVATEAPP:
		{
			g_Act = (BOOL)wParam;
			return 0;
		}
	case WM_COMMAND:
		{
			if (HIWORD(wParam) == 0)
			{
				switch (LOWORD(wParam))
				{
				case ID_40001: //新建
					{
						int r = MessageBox(hwnd, "新建地图会销毁当前地图,请确认地图正常保存后再新建", "提示", MB_YESNO);
						if (r == IDYES)
						{
							INT_PTR ReData = DialogBox(
								g_hInstance, //应用程序实例句柄
								MAKEINTRESOURCE(IDD_DIALOG6), //对话框资源ID
								hwnd, //父窗口
								MAPEDIT_ID); //对话框消息处理函数
							if (ReData != -1)
								g_Map.SetNewMap((int)ReData);
						}
						break;
					}
				case ID_40002: //打开
					{
						INT_PTR ReData = DialogBox(
							g_hInstance, //应用程序实例句柄
							MAKEINTRESOURCE(IDD_DIALOG6), //对话框资源ID
							hwnd, //父窗口
							MAPEDIT_ID); //对话框消息处理函数
						if (ReData != -1)
						{
							std::map<int, CMapData>::iterator i = g_MapList.find(ReData);
							{
								if (i != g_MapList.end()) //找到了
									MessageBox(hwnd, "已存在的地图Id,请先删除该Id对应地图!", "提示", 0);
								else
								{
									FILE* pF = 0;
									char FileName[256];
									sprintf_s(FileName, 256, "map\\Map%d.MapData", ReData);
									fopen_s(&pF, FileName, "rb");

									if (!pF) //检查地图文件是否存在
										MessageBox(hwnd, "非法地图Id!", "提示", 0);
									else
									{
										fseek(pF, 0, SEEK_END);
										int fileSize = ftell(pF);
										rewind(pF); 
										int MapId; //Id
										fread(&MapId, 1, 4, pF);

										CMapData Temp;
										//设置地图ID
										Temp.SetMap_ID(MapId);
										//读取碰撞层
										fread(Temp.GetMap_Crash(), 1, _MAP_S * sizeof(int) * 4, pF);
										//读取地形层
										fread(Temp.GetMap_DX(), 1, _MAP_S * sizeof(char), pF);
										//读取建筑层
										fread(Temp.GetMap_JZ(), 1, _MAP_S * sizeof(char), pF);
										//读取物件层
										fread(Temp.GetMap_Object(), 1, _MAP_S * sizeof(char), pF);

										fclose(pF);
										//推入地图表
										g_MapList.insert(std::pair<int, CMapData>(MapId, Temp));

										std::map<int, CMapData>::iterator i = g_MapList.find(MapId);
										{
											if (i != g_MapList.end()) //找到了
												g_Map = i->second;
										}
										MessageBox(hwnd, "载入成功!", "提示", 0);
									}
								}
							}
						}
						break;
					}
				case ID_40003: //保存
					{
						//若找到了就返回失败
						if (g_MapList.find(g_Map.GetMap_ID()) != g_MapList.end())
							MessageBox(hwnd, "已存在的地图ID!,请先删除该Id对应地图!", 0, MB_OK);
						else
						{
							g_MapList.insert(std::pair<int, CMapData>(g_Map.GetMap_ID(), g_Map));
							MessageBox(hwnd, "当前地图区域已保存!", "提示", MB_OK);
						}
						break;
					}
				case ID_40018: //删除 
					{
						INT_PTR ReData = DialogBox(
							g_hInstance, //应用程序实例句柄
							MAKEINTRESOURCE(IDD_DIALOG6), //对话框资源ID
							hwnd, //父窗口
							MAPEDIT_ID); //对话框消息处理函数

						if (ReData != -1)
						{
							std::map<int, CMapData>::iterator i = g_MapList.find(ReData);
							if (i != g_MapList.end())
							{
								g_MapList.erase(i);
								MessageBox(hwnd, "删除成功!", "提示", MB_OK);
							}
							else
								MessageBox(hwnd, "不合法的地图ID!", 0, MB_OK);
						}

						break;
					}
				case ID_40019: //退出
					{
						DestroyWindow(hwnd);
						break;
					}
				case ID_40006: //障碍
					{
						if (IsWindow(MapEdit[_ZA]))
							ShowWindow(MapEdit[_ZA], SW_SHOWNORMAL);
						break;
					}
				case ID_40007: //地形
					{
						if (IsWindow(MapEdit[_DX]))
						{
							ShowWindow(MapEdit[_DX], SW_SHOWNORMAL);
							PostMessage(MapEdit[_DX], WM_ACTIVATE, 0, 0);
						}
						break;
					}
				case ID_40021: //填充
					{
						if (g_XuanZeType == _Type_DX)
							g_Map.FillDx(g_XuanZe);
						else
							MessageBox(hwnd, "请先选取需要填充的地形!", 0, 0);
						break;
					}
				case ID_40008: //景物
					{
						if (IsWindow(MapEdit[_JW]))
						{
							ShowWindow(MapEdit[_JW], SW_SHOWNORMAL);
							PostMessage(MapEdit[_JW], WM_ACTIVATE, 0, 0);
						}
						break;
					}
				case ID_40009: //NPC
					{
						if (IsWindow(MapEdit[_NPC]))
							ShowWindow(MapEdit[_NPC], SW_SHOWNORMAL);
						break;
					}
				case ID_40010: //建筑
					{
						if (IsWindow(MapEdit[_JZ]))
						{
							ShowWindow(MapEdit[_JZ], SW_SHOWNORMAL);
							PostMessage(MapEdit[_JZ], WM_ACTIVATE, 0, 0);
						}
						break;
					}
				case ID_40011: //设置地图ID
					{
						INT_PTR ReData = DialogBox(
							g_hInstance, //应用程序实例句柄
							MAKEINTRESOURCE(IDD_DIALOG6), //对话框资源ID
							hwnd, //父窗口
							MAPEDIT_ID); //对话框消息处理函数
						if (ReData != -1)
							g_Map.SetMap_ID((int)ReData);

						break;
					}
				case ID_40012: //显示地图数据
					{
						if (IsWindow(MapEdit[_SHOW]))
							ShowWindow(MapEdit[_SHOW], SW_SHOWNORMAL);

						break;
					}
				case ID_40013: //切换地图
					{
						INT_PTR ReData = DialogBox(
							g_hInstance, //应用程序实例句柄
							MAKEINTRESOURCE(IDD_DIALOG6), //对话框资源ID
							hwnd, //父窗口
							MAPEDIT_ID); //对话框消息处理函数
						if (ReData != -1)
						{
							std::map<int, CMapData>::iterator i = g_MapList.find(ReData);
							{
								if (i != g_MapList.end()) //找到了
								{
									g_Map = i->second;
									MessageBox(hwnd, "载入成功!", "提示", 0);
								}
								else
									MessageBox(hwnd, "不合法的地图ID!", 0, 0);
							}
						}
						break;
					}
				case ID_40020: //生成
					{
						std::map<int, CMapData>::iterator i = g_MapList.begin();
						for (; i != g_MapList.end(); ++i)
						{
							char fileName[256];
							sprintf_s(fileName, 256, "Map\\Map%d.MapData", i->first);

							int fileSize = _MAP_S * sizeof(int) * 4; //碰撞层大小
							fileSize += _MAP_S * 3;
							fileSize += sizeof(int); //记录地图数量
							char* _Save_Crash = new char[fileSize];
							int Py = 0;

							////地图总数量
							//int Num = (int)g_MapList.size(); //地图数量
							//memcpy( _Save_Crash + Py, &Num, sizeof(int)); //先写入地图数量
							//地图ID
							int MapId = (int)i->first; //地图Id
							memcpy( _Save_Crash + Py, &MapId, sizeof(int)); //先写入地图Id
							Py += sizeof(int);
							//碰撞层
							memcpy( _Save_Crash + Py, i->second.GetMap_Crash(), _MAP_S * sizeof(int) * 4); //写入碰撞层
							Py += _MAP_S * sizeof(int) * 4;
							//地形层
							memcpy( _Save_Crash + Py, i->second.GetMap_DX(), sizeof(char) * _MAP_S); //写入地形层
							Py += sizeof(char) * _MAP_S;
							//建筑层
							memcpy( _Save_Crash + Py, i->second.GetMap_JZ(), sizeof(char) * _MAP_S); //写入建筑层
							Py += sizeof(char) * _MAP_S;
							//物件层
							memcpy( _Save_Crash + Py, i->second.GetMap_Object(), sizeof(char) * _MAP_S); //写入物件层
							Py += sizeof(char) * _MAP_S;

							FILE* fp1 = 0;
							fopen_s(&fp1, fileName, "wb");
							fwrite(_Save_Crash, 1, fileSize, fp1);
							fclose(fp1);

							delete [] _Save_Crash;
						}
						MessageBox(hwnd, "生成地图成功!", "提示", 0);
						break;
					}
				}
			}

			return 0;
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void Init();
void Run();
void End();

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	g_hInstance = hInstance;

	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = "Test";
	RegisterClass(&wc);

	RECT r
		=
	{
		(GetSystemMetrics(SM_CXSCREEN) - _CLIENT_W) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - _CLIENT_H) / 2,
		(GetSystemMetrics(SM_CXSCREEN) - _CLIENT_W) / 2 + _CLIENT_W,
		(GetSystemMetrics(SM_CYSCREEN) - _CLIENT_H) / 2 + _CLIENT_H
	};

	AdjustWindowRect(&r, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, TRUE);

	HMENU menu = LoadMenu(
		hInstance, 
		MAKEINTRESOURCE(IDR_MENU1)); 

	g_hwnd = CreateWindow(
		wc.lpszClassName,
		"MapEdit",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		r.left,
		r.top,
		r.right - r.left,
		r.bottom - r.top,
		HWND_DESKTOP,
		menu,
		wc.hInstance,
		0);

	ShowWindow(g_hwnd, nCmdShow);
	UpdateWindow(g_hwnd);

	Init(); //初始化

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (g_Act)
			Run(); 
		else
			WaitMessage();
	}

	End(); //结束

	return 1;
}

void Init()
{
	g_Cr = new CGameOutput(g_hwnd);
	g_Cr->LoadDirectory("Pic");
}

void Run()
{
	int x1 = ViewX / _PIC_W;
	int y1 = ViewY / _PIC_H;
	int x2 = (ViewX + _CLIENT_W - 1) / _PIC_W;
	int y2 = (ViewY + _CLIENT_H - 1) / _PIC_H;

	if (g_hwnd == GetForegroundWindow()) //判断编辑器窗口是否为前置窗口
	{
		//鼠标
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if(g_XuanZeType != -1)
			{
				POINT p;
				GetCursorPos(&p); //得到当前光标位置,相对于桌面
				ScreenToClient(g_hwnd, &p); //将光标位置转换为客户区位置
				if(p.x > 0 && p.x < 32 * _MAP_W && p.y > 0 && p.y < 32 * _MAP_H)
				{
					//int cx = p.x / _PIC_W;
					//int cy = p.y / _PIC_H;
					int cx = p.x / _PIC_W + x1;
					int cy = p.y / _PIC_H + y1;
					switch (g_XuanZeType)
					{
					case _Type_DX:
						{
							g_Map.SetMapData_DX(cx, cy, g_XuanZe); //设置地图块
							break;
						}
					case _Type_Build:
						{
							g_Map.SetMapData_JZ(cx, cy, g_XuanZe); //设置地图块
							_Crash_Data Temp;
							Temp.Type = 1;
							g_Map.SetMapData_Crash(cx, cy, Temp);
							break;
						}
					case _Type_Crash:
						{
							break;
						}
					case _Type_Object:
						{
							g_Map.SetMapData_Object(cx, cy, g_XuanZe); //设置地图块
							break;
						}
					}
				}
			}
		}

		//删除
		if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		{
			if(g_XuanZeType != -1)
			{
				POINT p;
				GetCursorPos(&p); //得到当前光标位置,相对于桌面
				ScreenToClient(g_hwnd, &p); //将光标位置转换为客户区位置
				if(p.x > 0 && p.x < 32 * _MAP_W && p.y > 0 && p.y < 32 * _MAP_H)
				{
					//int cx = p.x / _PIC_W;
					//int cy = p.y / _PIC_H;
					int cx = p.x / _PIC_W + x1;
					int cy = p.y / _PIC_H + y1;

					switch (g_XuanZeType)
					{
					case _Type_DX:
						{
							g_Map.SetMapData_DX(cx, cy, _Map_Zero); //设置地图块
							break;
						}
					case _Type_Build:
						{
							g_Map.SetMapData_JZ(cx, cy, _Map_Zero); //设置地图块
							break;
						}
					case _Type_Crash:
						{
							break;
						}
					case _Type_Object:
						{
							g_Map.SetMapData_Object(cx, cy, _Map_Zero); //设置地图块
							break;
						}
					}
				}
			}
		}

		//设置碰撞
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			POINT p;
			GetCursorPos(&p); //得到当前光标位置,相对于桌面
			ScreenToClient(g_hwnd, &p); //将光标位置转换为客户区位置
			//int cx = p.x / _PIC_W;
			//int cy = p.y / _PIC_H;
			int cx = p.x / _PIC_W + x1;
			int cy = p.y / _PIC_H + y1;

			DialogBox(
				g_hInstance, //应用程序实例句柄
				MAKEINTRESOURCE(IDD_DIALOG8), //对话框资源ID
				g_hwnd, //父窗口
				MAPEDIT_MapSet); //对话框消息处理函数

			g_Map.SetMapData_Crash(cx, cy, g_TempCrash);
		}

		if (GetAsyncKeyState('D') & 0x0001 && ViewX < _MAP_W * _PIC_W - _CLIENT_W)
			ViewX += _PIC_W;
		if (GetAsyncKeyState('A') & 0x0001 && ViewX > 0)
			ViewX -= _PIC_W;
		if (GetAsyncKeyState('S') & 0x0001 && ViewY < _MAP_H * _PIC_H - _CLIENT_H)
			ViewY += _PIC_H;
		if (GetAsyncKeyState('W') & 0x0001 && ViewY > 0)
			ViewY -= _PIC_H;
	}
	//初始化编辑数组
	g_MapCrash = g_Map.GetMap_Crash();
	g_MapObject = g_Map.GetMap_Object();
	g_MapDX = g_Map.GetMap_DX();
	g_MapBuild = g_Map.GetMap_JZ();
	g_Cr->Begin();

	for (int x = x1; x <= x2; ++x)
	{
		for (int y = y1; y <= y2; ++y)
		{
			int  i = x + y * _MAP_W;
			//地形层
			if (g_MapDX[i] > 0)
			{
				char buf[256];
				sprintf_s(buf, 256, "Pic\\Map_1\\%d.bmp", g_MapDX[i] - 1);
				g_Cr->DrawBmp((x - x1) * _PIC_W, (y - y1) * _PIC_H, _PIC_W, _PIC_H, 0, 0, buf);
			}
			else
				g_Cr->DrawRectangle((x - x1) * _PIC_W, (y - y1) * _PIC_H, _PIC_W, _PIC_H);

			//建筑层,障碍层
			if (g_MapBuild[i] > 0)
			{
				char buf[256];
				sprintf_s(buf, 256, "Pic\\Map_2\\%d.bmp", g_MapBuild[i] - 1);
				g_Cr->tDrawBmp((x - x1) * _PIC_W, (y - y1) * _PIC_H, _PIC_W, _PIC_H, 0, 0, buf);
			}

			//装饰层
			if (g_MapObject[i] > 0)
			{
				char buf[256];
				sprintf_s(buf, 256, "Pic\\Map_3\\%d.bmp", g_MapObject[i] - 1);
				g_Cr->tDrawBmp((x - x1) * _PIC_W, (y - y1) * _PIC_H, _PIC_W, _PIC_H, 0, 0, buf);
			}
		}
	}

	g_Cr->End();

	PostMessage(MapEdit[_SHOW], WM_ACTIVATE, 0, 0);

	Sleep(33);
}

void End()
{
}

//地图数据
INT_PTR CALLBACK MAPEDIT_DATASHOW(HWND hwndDlg,
								  UINT uMsg,
								  WPARAM wParam,
								  LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		{
			g_MainDC_Crash = GetDC(hwndDlg);

			for (int i = 0; i < _Crash_PIC_NUM; ++i)
			{
				char buf[256];
				sprintf_s(buf, 256, "Pic\\Map_Set\\%d.bmp", i);
				g_Bmp_Crash[i] = (HBITMAP)LoadImageA(0, buf, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			}

			//创建兼容显示设备
			for (int i = 0; i < _Crash_PIC_NUM; ++i)
				g_BmpDC_Crash[i] = CreateCompatibleDC(g_MainDC_Crash);

			//将位图选入到兼容显示设备
			for (int i = 0; i < _Crash_PIC_NUM; ++i)
				SelectObject(g_BmpDC_Crash[i], g_Bmp_Crash[i]);

			//初始化数组
			for (int i = 0; i < _Crash_PIC_NUM; ++i)
				g_BmpMap_Crash[i] = i;

			g_MapCrash = g_Map.GetMap_Crash();
			return 1;
		}
	case WM_ACTIVATE:
		{
			char buf[256];

			//地图所有ID序号
			std::string Temp;
			for (std::map<int, CMapData>::iterator i = g_MapList.begin(); i != g_MapList.end(); ++i)
			{
				char buf[32];
				sprintf_s(buf, 32, "%d ", i->second.GetMap_ID());
				Temp += buf;
			}
			SetWindowText(GetDlgItem(MapEdit[_SHOW], IDC_EDIT3), Temp.c_str());	
			//地图ID显示
			sprintf_s(buf, 256, "%d", g_Map.GetMap_ID());
			SetWindowText(GetDlgItem(MapEdit[_SHOW], IDC_EDIT1), buf);
			//总地图大小显示
			sprintf_s(buf, 256, "%d", g_MapList.size());
			SetWindowText(GetDlgItem(MapEdit[_SHOW], IDC_EDIT2), buf);

			//char Test[256];
			//sprintf_s(Test, 256, "%d,%d",ViewX / _PIC_W, ViewY / _PIC_H);
			//SetWindowText(hwndDlg,Test);

			//渲染
			for (int i = 0; i < _MAP_S; ++i)
			{
				int cx = i % _MAP_W;
				int cy = i / _MAP_W;
				switch (g_MapCrash[i].Type)
				{
				case _CRASH_NO:
					{
						if (cx == ViewX / _PIC_W && cy == ViewY / _PIC_H)
							Ellipse(g_MainDC_Crash, cx * 16, cy * 16, cx * 16 + 16, cy * 16 + 16);
						else
							BitBlt(g_MainDC_Crash, cx * 16, cy * 16, 16, 16, g_BmpDC_Crash[_CRASH_NO], 0, 0, SRCCOPY);		
						break;
					}
				case _CRASH_TL:
					{
						if (cx == ViewX / _PIC_W && cy == ViewY / _PIC_H)
							Ellipse(g_MainDC_Crash, cx * 16, cy * 16, cx * 16 + 16, cy * 16 + 16);
						else
							BitBlt(g_MainDC_Crash, cx * 16, cy * 16, 16, 16, g_BmpDC_Crash[_CRASH_TL], 0, 0, SRCCOPY);		
						break;
					}
				case _CRASH_ZA:
					{
						BitBlt(g_MainDC_Crash, cx * 16, cy * 16, 16, 16, g_BmpDC_Crash[_CRASH_ZA], 0, 0, SRCCOPY);		
						break;
					}
				case _CRASH_CS:
					{
						BitBlt(g_MainDC_Crash, cx * 16, cy * 16, 16, 16, g_BmpDC_Crash[_CRASH_CS], 0, 0, SRCCOPY);		
						break;
					}
				case _CRASH_NPC:
					{
						BitBlt(g_MainDC_Crash, cx * 16, cy * 16, 16, 16, g_BmpDC_Crash[_CRASH_NPC], 0, 0, SRCCOPY);		
						break;
					}
				}
			}

			return 1;
		}
	case WM_COMMAND:
		{
			if (BN_CLICKED == HIWORD(wParam))
			{
				switch (LOWORD(wParam))
				{
				case IDCANCEL: 
					{
						ShowWindow(hwndDlg, SW_HIDE);
						break;
					}
				}
			}
			return 1;
		}
	case WM_RBUTTONDOWN:
		{
			POINT p;
			GetCursorPos(&p); //得到当前光标位置,相对于桌面
			ScreenToClient(hwndDlg, &p); //将光标位置转换为客户区位置
			_Crash_Data Temp;
			//Temp.Type = _CRASH_NO;
			//Temp.Id = _CRASH_NO;
			//Temp.x = _CRASH_NO;
			//Temp.y = _CRASH_NO;

			if(p.x > 0 && p.x < 32 * _MAP_W && p.y > 0 && p.y < 32 * _MAP_H)
			{
				int cx = p.x / 16;
				int cy = p.y / 16;
				g_Map.SetMapData_Crash(cx, cy, Temp);
			}

			//char buf[32];
			//sprintf_s(buf, 32, "%d,%d", p.x / 16, p.y / 16);
			//SetWindowText(hwndDlg, buf);

			return 1;
		}
	case WM_LBUTTONDOWN:
		{
			POINT p;
			GetCursorPos(&p); //得到当前光标位置,相对于桌面
			ScreenToClient(hwndDlg, &p); //将光标位置转换为客户区位置
			_Crash_Data Temp;

			if(p.x > 0 && p.x < 32 * _MAP_W && p.y > 0 && p.y < 32 * _MAP_H)
			{
				int cx = p.x / 16;
				int cy = p.y / 16;
				Temp = g_Map.GetMap_CrashData(cx, cy, _MAP_W);
			}

			char buf[32];
			sprintf_s(buf, 32, "ID:%d", Temp.Id);
			SetWindowText(GetDlgItem(hwndDlg, IDC_EDIT4), buf);
			sprintf_s(buf, 32, "Tpye:%d", Temp.Type);
			SetWindowText(GetDlgItem(hwndDlg, IDC_EDIT5), buf);
			sprintf_s(buf, 32, "x:%d", Temp.x);
			SetWindowText(GetDlgItem(hwndDlg, IDC_EDIT6), buf);
			sprintf_s(buf, 32, "y:%d", Temp.y);
			SetWindowText(GetDlgItem(hwndDlg, IDC_EDIT7), buf);
	
			sprintf_s(buf, 32, "%d,%d", p.x / 16, p.y / 16);
			SetWindowText(hwndDlg, buf);

			return 1;
		}
	case WM_DESTROY:
		{
			ReleaseDC(hwndDlg, g_MainDC_Crash); //释放显示设备
			PostQuitMessage(0);
			return 0;
		}
	}
	return 0; 
}

//地图ID
INT_PTR CALLBACK MAPEDIT_ID(HWND hwndDlg,
							UINT uMsg,
							WPARAM wParam,
							LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		{

			return 1;
		}
	case WM_COMMAND:
		{
			if (BN_CLICKED == HIWORD(wParam))
			{
				switch (LOWORD(wParam))
				{
				case IDOK: 
					{
						char buf[256];
						GetWindowText(GetDlgItem(hwndDlg, IDC_EDIT1), buf, 256);
						if(atoi(buf) <= 255)
							EndDialog(hwndDlg, atoi(buf)); 
						else
							MessageBox(hwndDlg, "地图ID不合法", 0, MB_OK);
						break;
					}
				case IDCANCEL: 
					{
						EndDialog(
							hwndDlg, 
							-1); 

						break;
					}
				}
			}

			return 1;
		}
	}

	return 0; 
}

//地形
INT_PTR CALLBACK MAPEDIT_DX(HWND hwndDlg,
							UINT uMsg,
							WPARAM wParam,
							LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		{
			//绘图
			g_MainDC_DX = GetDC(hwndDlg);

			for (int i = 0; i < _DX_PIC_NUM; ++i)
			{
				char buf[256];
				sprintf_s(buf, 256, "Pic\\Map_1\\%d.bmp", i);
				g_Bmp_DX[i] = (HBITMAP)LoadImageA(0, buf, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			}

			//创建兼容显示设备
			for (int i = 0; i < _DX_PIC_NUM; ++i)
				g_BmpDC_DX[i] = CreateCompatibleDC(g_MainDC_DX);

			//将位图选入到兼容显示设备
			for (int i = 0; i < _DX_PIC_NUM; ++i)
				SelectObject(g_BmpDC_DX[i], g_Bmp_DX[i]);

			//初始化数组
			for (int i = 0; i < _DX_PIC_NUM; ++i)
				g_BmpMap_DX[i] = i;

			//MoveWindow(hwndDlg, 0, 0, 500, 500, true);

			return 1;
		}
	case WM_ACTIVATE:
		{
			for (int i = 0; i < _DX_PIC_NUM; ++i)
			{
				int cx = i % g_BmpMapW_DX;
				int cy = i / g_BmpMapW_DX;
				BitBlt(g_MainDC_DX, cx * _PIC_W, cy * _PIC_H, _PIC_W, _PIC_H, g_BmpDC_DX[g_BmpMap_DX[i]], 0, 0, SRCCOPY);		
			}

			return 1;
		}
	case WM_DESTROY:
		{
			ReleaseDC(hwndDlg, g_MainDC_DX); //释放显示设备
			PostQuitMessage(0);
			return 0;
		}
	case WM_COMMAND:
		{
			if (BN_CLICKED == HIWORD(wParam))
			{
				switch (LOWORD(wParam))
				{
				case IDCANCEL: 
					{
						ShowWindow(hwndDlg, SW_HIDE);
						break;
					}
				}
			}

			return 1;
		}
	case WM_LBUTTONDOWN:
		{
			int x = LOWORD(lParam); //Low Word:低字
			int y = HIWORD(lParam); //High Word:高字
			RECT Rc;
			Rc.left = 0;
			Rc.top = 0;
			if (_DX_PIC_NUM < g_BmpMapW_DX)
				Rc.right = _DX_PIC_NUM * _PIC_W;
			else
				Rc.right = g_BmpMapW_DX * _PIC_W;

			if (_DX_PIC_NUM < g_BmpMapW_DX)
				Rc.bottom = _PIC_H;
			else if (_DX_PIC_NUM % g_BmpMapW_DX == 0)
				Rc.bottom = (_DX_PIC_NUM / g_BmpMapW_DX) * _PIC_H;
			else
				Rc.bottom = (_DX_PIC_NUM / g_BmpMapW_DX + 1) * _PIC_H;

			POINT p = {x, y};
			if (PtInRect(&Rc, p))
			{
				g_XuanZe = g_BmpMap_DX[p.x / _PIC_W + (p.y / _PIC_H) * g_BmpMapW_DX] + 1;
				g_XuanZeType = _Type_DX;
			}

			return 0;
		}
	}

	return 0; 
}

//障碍
INT_PTR CALLBACK MAPEDIT_ZA(HWND hwndDlg,
							UINT uMsg,
							WPARAM wParam,
							LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		{

			return 1;
		}
	case WM_COMMAND:
		{
			if (BN_CLICKED == HIWORD(wParam))
			{
				switch (LOWORD(wParam))
				{
				case IDCANCEL: 
					{
						ShowWindow(hwndDlg, SW_HIDE);
						break;
					}
				}
			}

			return 1;
		}
	}

	return 0;
}

//建筑
INT_PTR CALLBACK MAPEDIT_JZ(HWND hwndDlg,
							UINT uMsg,
							WPARAM wParam,
							LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		{
			//绘图
			g_MainDC_Build = GetDC(hwndDlg);

			for (int i = 0; i < _Build_PIC_NUM; ++i)
			{
				char buf[256];
				sprintf_s(buf, 256, "Pic\\Map_2\\%d.bmp", i);
				g_Bmp_Build[i] = (HBITMAP)LoadImageA(0, buf, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			}

			//创建兼容显示设备
			for (int i = 0; i < _Build_PIC_NUM; ++i)
				g_BmpDC_Build[i] = CreateCompatibleDC(g_MainDC_Build);

			//将位图选入到兼容显示设备
			for (int i = 0; i < _Build_PIC_NUM; ++i)
				SelectObject(g_BmpDC_Build[i], g_Bmp_Build[i]);

			//初始化数组
			for (int i = 0; i < _Build_PIC_NUM; ++i)
				g_BmpMap_Build[i] = i;

			//MoveWindow(hwndDlg, 0, 0, 500, 500, true);

			return 1;
		}
	case WM_ACTIVATE:
		{
			for (int i = 0; i < _Build_PIC_NUM; ++i)
			{
				int cx = i % g_BmpMapW_Build;
				int cy = i / g_BmpMapW_Build;
				TransparentBlt(
					g_MainDC_Build, //目标设备
					cx * _PIC_W, //目标矩形左上角x
					cy * _PIC_H, //目标矩形左上角y
					_PIC_W, //目标矩形宽
					_PIC_H, //目标矩形高
					g_BmpDC_Build[g_BmpMap_Build[i]], //源设备
					0, //源矩形左上角x
					0, //源矩形左上角x
					_PIC_W, //源矩形宽
					_PIC_H, //源矩形高
					RGB(0, 255, 0)); //要过滤的颜色
			}

			return 1;
		}
	case WM_DESTROY:
		{
			ReleaseDC(hwndDlg, g_MainDC_Build); //释放显示设备
			PostQuitMessage(0);
			return 0;
		}
	case WM_COMMAND:
		{
			if (BN_CLICKED == HIWORD(wParam))
			{
				switch (LOWORD(wParam))
				{
				case IDCANCEL: 
					{
						ShowWindow(hwndDlg, SW_HIDE);
						break;
					}
				}
			}

			return 1;
		}
	case WM_LBUTTONDOWN:
		{
			int x = LOWORD(lParam); //Low Word:低字
			int y = HIWORD(lParam); //High Word:高字
			RECT Rc;
			Rc.left = 0;
			Rc.top = 0;
			if (_Build_PIC_NUM < g_BmpMapW_Build)
				Rc.right = _Build_PIC_NUM * _PIC_W;
			else
				Rc.right = g_BmpMapW_Build * _PIC_W;

			if (_Build_PIC_NUM < g_BmpMapW_Build)
				Rc.bottom = _PIC_H;
			else if (_Build_PIC_NUM % g_BmpMapW_Build == 0)
				Rc.bottom = (_Build_PIC_NUM / g_BmpMapW_Build) * _PIC_H;
			else
				Rc.bottom = (_Build_PIC_NUM / g_BmpMapW_Build + 1) * _PIC_H;

			POINT p = {x, y};
			if (PtInRect(&Rc, p))
			{
				g_XuanZe = g_BmpMap_Build[p.x / _PIC_W + (p.y / _PIC_H) * g_BmpMapW_Build] + 1;
				g_XuanZeType = _Type_Build;
			}

			return 0;
		}
	}

	return 0; 
}

//NPC
INT_PTR CALLBACK MAPEDIT_NPC(HWND hwndDlg,
							 UINT uMsg,
							 WPARAM wParam,
							 LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		{

			return 1;
		}
	case WM_COMMAND:
		{
			if (BN_CLICKED == HIWORD(wParam))
			{
				switch (LOWORD(wParam))
				{
				case IDCANCEL: 
					{
						ShowWindow(hwndDlg, SW_HIDE);
						break;
					}
				}
			}

			return 1;
		}
	}

	return 0; 
}

//景物
INT_PTR CALLBACK MAPEDIT_JW(HWND hwndDlg,
							UINT uMsg,
							WPARAM wParam,
							LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		{
			//绘图
			g_MainDC_Object = GetDC(hwndDlg);

			for (int i = 0; i < _Object_PIC_NUM; ++i)
			{
				char buf[256];
				sprintf_s(buf, 256, "Pic\\Map_3\\%d.bmp", i);
				g_Bmp_Object[i] = (HBITMAP)LoadImageA(0, buf, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			}

			//创建兼容显示设备
			for (int i = 0; i < _Object_PIC_NUM; ++i)
				g_BmpDC_Object[i] = CreateCompatibleDC(g_MainDC_Object);

			//将位图选入到兼容显示设备
			for (int i = 0; i < _Object_PIC_NUM; ++i)
				SelectObject(g_BmpDC_Object[i], g_Bmp_Object[i]);

			//初始化数组
			for (int i = 0; i < _Object_PIC_NUM; ++i)
				g_BmpMap_Object[i] = i;

			//MoveWindow(hwndDlg, 0, 0, 500, 500, true);

			return 1;
		}
	case WM_ACTIVATE:
		{
			for (int i = 0; i < _Object_PIC_NUM; ++i)
			{
				int cx = i % g_BmpMapW_Object;
				int cy = i / g_BmpMapW_Object;
				TransparentBlt(
					g_MainDC_Object, //目标设备
					cx * _PIC_W, //目标矩形左上角x
					cy * _PIC_H, //目标矩形左上角y
					_PIC_W, //目标矩形宽
					_PIC_H, //目标矩形高
					g_BmpDC_Object[g_BmpMap_Object[i]], //源设备
					0, //源矩形左上角x
					0, //源矩形左上角x
					_PIC_W, //源矩形宽
					_PIC_H, //源矩形高
					RGB(0, 255, 0)); //要过滤的颜色
			}
			return 1;
		}
	case WM_DESTROY:
		{
			ReleaseDC(hwndDlg, g_MainDC_Object); //释放显示设备
			PostQuitMessage(0);
			return 0;
		}
	case WM_COMMAND:
		{
			if (BN_CLICKED == HIWORD(wParam))
			{
				switch (LOWORD(wParam))
				{
				case IDCANCEL: 
					{
						ShowWindow(hwndDlg, SW_HIDE);
						break;
					}
				}
			}

			return 1;
		}
	case WM_LBUTTONDOWN:
		{
			int x = LOWORD(lParam); //Low Word:低字
			int y = HIWORD(lParam); //High Word:高字
			RECT Rc;
			Rc.left = 0;
			Rc.top = 0;
			if (_Object_PIC_NUM < g_BmpMapW_Object)
				Rc.right = _Object_PIC_NUM * _PIC_W;
			else
				Rc.right = g_BmpMapW_Object * _PIC_W;

			if (_Object_PIC_NUM < g_BmpMapW_Object)
				Rc.bottom = _PIC_H;
			else if (_Object_PIC_NUM % g_BmpMapW_Object == 0)
				Rc.bottom = (_Object_PIC_NUM / g_BmpMapW_Object) * _PIC_H;
			else
				Rc.bottom = (_Object_PIC_NUM / g_BmpMapW_Object + 1) * _PIC_H;

			POINT p = {x, y};
			if (PtInRect(&Rc, p))
			{
				g_XuanZe = g_BmpMap_Object[p.x / _PIC_W + (p.y / _PIC_H) * g_BmpMapW_Object] + 1;
				g_XuanZeType = _Type_Object;
			}

			return 0;
		}
	}

	return 0; 
}

//地图类型设置
INT_PTR CALLBACK MAPEDIT_MapSet(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		{

			return 1;
		}
	case WM_COMMAND:
		{
			if (BN_CLICKED == HIWORD(wParam))
			{
				switch (LOWORD(wParam))
				{
				case IDOK: 
					{
						char Type[256];
						char Id[256];
						char x[256];
						char y[256];
						GetWindowText(GetDlgItem(hwndDlg, IDC_EDIT1), Type, 256); //地图类型
						g_TempCrash.Type = atoi(Type);
						GetWindowText(GetDlgItem(hwndDlg, IDC_EDIT3), Id, 256); //ID
						g_TempCrash.Id = atoi(Id);
						GetWindowText(GetDlgItem(hwndDlg, IDC_EDIT2), x, 256); //x
						g_TempCrash.x = atoi(x);
						GetWindowText(GetDlgItem(hwndDlg, IDC_EDIT4), y, 256); //y
						g_TempCrash.y = atoi(y);

						EndDialog(hwndDlg, 0); 
						break;
					}
				case IDCANCEL: 
					{
						EndDialog(
							hwndDlg, 
							-1); 

						break;
					}
				}
			}

			return 1;
		}
	}

	return 0; 
}