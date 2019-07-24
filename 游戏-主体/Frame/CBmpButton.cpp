#include "CBmpButton.h"
#include "GameFrame.h"

CBmpButton::CBmpButton(int x1, int y1, int x2, int y2, char* inBmp, char* outBmp, unsigned int color)
:
CUI(x1, y1, x2, y2),
m_In(false),
m_InBmp(inBmp),
m_OutBmp(outBmp),
m_Color(color)
{
}

void CBmpButton::CursorEnter()
{
	m_In = true;
}

void CBmpButton::CursorQuit()
{
	m_In = false;
}

void CBmpButton::Render()
{
	CGameFrame* pGF = CGameFrame::GetObject();

	if (m_In)
		pGF->GetGO()->tDrawBmp(x1, y1, x2 - x1, y2 - y1, 0, 0, m_InBmp, m_Color);
	else
		pGF->GetGO()->tDrawBmp(x1, y1, x2 - x1, y2 - y1, 0, 0, m_OutBmp, m_Color);
}

void CBmpButton::SetCursorState(bool d)
{
	m_In = d;
}
