#ifndef _GAME_OUTPUT_H_
#define _GAME_OUTPUT_H_

//���λ���
//װ��ͼƬ��ѡ���豸�������豸
//��ĳ��ɫ���ʻ���ͼ��

#include <windows.h>
#include <map>
#include <string>
#include <vector>

#pragma comment(lib, "Msimg32.lib")

#define _M_N 0 //������
#define _M_H 1 //ˮƽ����
#define _M_V 2 //��ֱ����
#define _M_HV 3 //ˮƽ��ֱ����

class CGameOutput
{
	HWND m_hWnd; //����
	int m_ClientW; //�ͻ�����
	int m_ClientH; //�ͻ�����
	HDC m_MainDC; //����ʾ�豸
	HDC m_BackDC; //����ʾ�豸
	HDC m_MirrorDC; //�����豸

	//struct MYIMAGE
	//{
	//	int w, h;
	//	HDC hdc;
	//};
	//std::map<std::string, MYIMAGE> m_Bmp; //λͼӳ��

	std::map<std::string, HDC> m_Bmp; //λͼӳ��
	std::map<std::string, HFONT> m_Font; //����ӳ��

public:
	CGameOutput(HWND hWnd);
	~CGameOutput();

	void Begin();
	void End();

	//���Ƶ�(x����,y����,��ɫ)
	void DrawDot(int x, int y, unsigned int c);

	//������
	void DrawLine(
		int x1,
		int y1,
		int x2,
		int y2,
		unsigned int c = RGB(0, 0, 0));
	
	//���ƾ���
	void DrawRectangle(
		int x,
		int y,
		int w,
		int h,
		unsigned int pc = RGB(0, 0, 0),
		unsigned int bc = RGB(255, 255, 255));

	//����Բ
	void DrawEllipse(
		int x,
		int y,
		int w,
		int h,
		unsigned int pc = RGB(0, 0, 0),
		unsigned int bc = RGB(255, 255, 255));

	//װ��ͼƬ
	bool LoadBmp(const char* bmpFile, const char* Key);
	bool LoadBmp(const char* bmpFile);

	//ж��ͼƬ(DeleteDC��erase)
	bool ReleaseBmp(const char* Key);

	//����ͼƬ
	bool DrawBmp(
		int dx,
		int dy,
		int dw,
		int dh,
		int sx,
		int sy,
		const char* Key);

	//����λͼ(��͸��ɫ)
	bool tDrawBmp(
		int dx, 
		int dy, 
		int dw, 
		int dh, 
		int sx, 
		int sy, 
		const char* bmp,
		unsigned int tc = RGB(0, 255, 0));

	//����һ��Ŀ¼���������λͼ
	int LoadDirectory(const char* d);

	//����λͼ(������)
	bool mDrawBmp(int dx, int dy, int dw, int dh, int sx, int sy, const char* bmp, char m = _M_N);

	//����λͼ(��͸��ɫ������)
	bool tmDrawBmp(int dx, int dy, int dw, int dh, int sx, int sy, const char* bmp, unsigned int tc = RGB(0, 255, 0), char m = _M_N);

	//������������
	bool CreateFont(int h, const char* n, const char* f);

	//�ͷ�����
	bool ReleaseFont(const char* f);

	//���Ƶ�������
	bool DrawText(const char* t, int x, int y, unsigned int c = RGB(0, 0, 0), const char* f = 0);

	//���ƶ�������
	bool DrawText(const char* t, int x, int y, int w, int h, unsigned int c = RGB(0, 0, 0), const char* f = 0);
};

bool dfsFolder(std::string folderPath, const char* Extensions, std::vector<std::string>& FileName);

#endif