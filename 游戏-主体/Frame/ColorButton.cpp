#include "ColorButton.h"
#include "GameFrame.h"

CColorButton::CColorButton(int x1, int y1, int x2, int y2,
						   unsigned int incolor,
						   unsigned int outcolor)
						   :
CUI(x1, y1, x2, y2),
m_In(false),
m_InColor(incolor),
m_OutColor(outcolor)
{}
void CColorButton::CursorEnter()
{
	m_In = true;
}
void CColorButton::CursorQuit()
{
	m_In = false;
}
void CColorButton::Render()
{
	CGameFrame* pGF = CGameFrame::GetObject();

	if (m_In)
		pGF->GetGO()->DrawEllipse(x1, y1, x2 - x1, y2 - y1, RGB(0, 0, 0), m_InColor);
	else
		pGF->GetGO()->DrawEllipse(x1, y1, x2 - x1, y2 - y1, RGB(0, 0, 0), m_OutColor);
}

void CColorButton::SetCursorState(bool d)
{
	m_In = d;
}
