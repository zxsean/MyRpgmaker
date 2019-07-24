#include "CDBmpButton.h"
#include "GameFrame.h"

CDBmpButton::CDBmpButton(int x1, int y1, int x2, int y2, char* inBmp, char* outBmp, char* inRightBmp, char* inLeftBmp, int w,unsigned int color)
:
CUI(x1, y1, x2, y2),
m_In(false),
m_InBmp(inBmp),
m_OutBmp(outBmp),
m_Color(color),
m_InRightBmp(inRightBmp),
m_InLeftBmp(inLeftBmp),
m_Button_W(w),
m_Data(0)
{
}

void CDBmpButton::CursorInMove(int x, int y)
{
	RECT Rc_Left = {0, 0, m_Button_W, y2 - y1};
	RECT Rc_Right = {x2 - m_Button_W - x1, 0, x2 - x1, y2 - y1};
	RECT Rc_Center = {0, 0, x2 - x1, y2 - y1};
	POINT Temp = {x, y};
	if (PtInRect(&Rc_Left, Temp)) //ÔÚ×ó±ß
		m_In = _in_Left;
	else if (PtInRect(&Rc_Right, Temp)) //ÔÚÓÒ±ß
		m_In = _in_Right;
	else
		m_In = _in_Center;
}

void CDBmpButton::CursorQuit()
{
	m_In = _in_Out;
}

void CDBmpButton::Render()
{
	CGameFrame* pGF = CGameFrame::GetObject();

	switch (m_In)
	{
	case _in_Center:
		{
			pGF->GetGO()->tDrawBmp(x1, y1, x2 - x1, y2 - y1, 0, 0, m_InBmp, m_Color);
			break;
		}
	case _in_Left:
		{
			pGF->GetGO()->tDrawBmp(x1, y1, x2 - x1, y2 - y1, 0, 0, m_InLeftBmp, m_Color);
			break;
		}
	case _in_Right:
		{
			pGF->GetGO()->tDrawBmp(x1, y1, x2 - x1, y2 - y1, 0, 0, m_InRightBmp, m_Color);
			break;
		}
	case _in_Out:
		{
			pGF->GetGO()->tDrawBmp(x1, y1, x2 - x1, y2 - y1, 0, 0, m_OutBmp, m_Color);
			break;
		}
	}
	char buf[32];
	sprintf_s(buf, 32, "%d", m_Data);
	pGF->GetGO()->DrawText(buf, x1 + 30, y1 + 10);
}

int CDBmpButton::GetM_in()
{
	return m_In;
}

int CDBmpButton::GetData()
{
	return m_Data;
}

void CDBmpButton::SetData(int d)
{
	m_Data = d;
}
