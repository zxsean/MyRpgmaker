#ifndef _CDBMP_BUTTON_H
#define _CDBMP_BUTTON_H

#include "UI.h"
#include <windows.h>

#define _in_Out 0
#define _in_Left 1
#define _in_Right 2
#define _in_Center 3

class CDBmpButton : public CUI
{
	int m_In; //λ��
	char* m_InBmp;
	char* m_OutBmp;
	char* m_InRightBmp;
	char* m_InLeftBmp;
	int m_Button_W; //����С��ť��
	unsigned int m_Color; //͸����ɫ
	int m_Data; //����

public:
	CDBmpButton(
		int x1, int y1, int x2, int y2,
		char* inBmp,
		char* outBmp,
		char* inRightBmp,
		char* inLeftBmp,
		int w,
		unsigned int color = RGB(0, 255, 0));
	void CursorInMove(int x, int y);
	void CursorQuit();
	int GetM_in();
	void Render();
	int GetData();
	void SetData(int d);
};

#endif