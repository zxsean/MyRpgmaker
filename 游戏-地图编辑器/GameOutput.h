#ifndef _GAME_OUTPUT_H_
#define _GAME_OUTPUT_H_

//二次缓冲
//装载图片、选入设备、绘制设备
//用某颜色画笔绘制图形

#include <windows.h>
#include <map>
#include <string>
#include <vector>

#pragma comment(lib, "Msimg32.lib")

#define _M_N 0 //不镜像
#define _M_H 1 //水平镜像
#define _M_V 2 //垂直镜像
#define _M_HV 3 //水平垂直镜像

class CGameOutput
{
	HWND m_hWnd; //窗口
	int m_ClientW; //客户区宽
	int m_ClientH; //客户区高
	HDC m_MainDC; //主显示设备
	HDC m_BackDC; //后备显示设备
	HDC m_MirrorDC; //镜像设备

	//struct MYIMAGE
	//{
	//	int w, h;
	//	HDC hdc;
	//};
	//std::map<std::string, MYIMAGE> m_Bmp; //位图映射

	std::map<std::string, HDC> m_Bmp; //位图映射
	std::map<std::string, HFONT> m_Font; //字体映射

public:
	CGameOutput(HWND hWnd);
	~CGameOutput();

	void Begin();
	void End();

	//绘制点(x坐标,y坐标,颜色)
	void DrawDot(int x, int y, unsigned int c);

	//绘制线
	void DrawLine(
		int x1,
		int y1,
		int x2,
		int y2,
		unsigned int c = RGB(0, 0, 0));
	
	//绘制矩形
	void DrawRectangle(
		int x,
		int y,
		int w,
		int h,
		unsigned int pc = RGB(0, 0, 0),
		unsigned int bc = RGB(255, 255, 255));

	//绘制圆
	void DrawEllipse(
		int x,
		int y,
		int w,
		int h,
		unsigned int pc = RGB(0, 0, 0),
		unsigned int bc = RGB(255, 255, 255));

	//装载图片
	bool LoadBmp(const char* bmpFile, const char* Key);
	bool LoadBmp(const char* bmpFile);

	//卸载图片(DeleteDC、erase)
	bool ReleaseBmp(const char* Key);

	//绘制图片
	bool DrawBmp(
		int dx,
		int dy,
		int dw,
		int dh,
		int sx,
		int sy,
		const char* Key);

	//绘制位图(带透明色)
	bool tDrawBmp(
		int dx, 
		int dy, 
		int dw, 
		int dh, 
		int sx, 
		int sy, 
		const char* bmp,
		unsigned int tc = RGB(0, 255, 0));

	//加载一个目录下面的所有位图
	int LoadDirectory(const char* d);

	//绘制位图(带镜像)
	bool mDrawBmp(int dx, int dy, int dw, int dh, int sx, int sy, const char* bmp, char m = _M_N);

	//绘制位图(带透明色、镜像)
	bool tmDrawBmp(int dx, int dy, int dw, int dh, int sx, int sy, const char* bmp, unsigned int tc = RGB(0, 255, 0), char m = _M_N);

	//创建文字字体
	bool CreateFont(int h, const char* n, const char* f);

	//释放字体
	bool ReleaseFont(const char* f);

	//绘制单行文字
	bool DrawText(const char* t, int x, int y, unsigned int c = RGB(0, 0, 0), const char* f = 0);

	//绘制多行文字
	bool DrawText(const char* t, int x, int y, int w, int h, unsigned int c = RGB(0, 0, 0), const char* f = 0);
};

bool dfsFolder(std::string folderPath, const char* Extensions, std::vector<std::string>& FileName);

#endif