#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "UI.h"

class CColorButton : public CUI
{
	bool m_In;
	unsigned int m_InColor;
	unsigned int m_OutColor;

public:
	CColorButton(
		int x1, int y1, int x2, int y2,
		unsigned int incolor,
		unsigned int outcolor);
	void CursorEnter();
	void CursorQuit();
	void SetCursorState(bool d); //…Ë÷√m_in
	void Render();
};

#endif