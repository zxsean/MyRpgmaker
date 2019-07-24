#ifndef _CBMP_BUTTON_H
#define _CBMP_BUTTON_H

#include "UI.h"
#include <windows.h>

class CBmpButton : public CUI
{
	bool m_In;
	char* m_InBmp;
	char* m_OutBmp;
	unsigned int m_Color; //Í¸Ã÷ÑÕÉ«

public:
	CBmpButton(
		int x1, int y1, int x2, int y2,
		char* inBmp,
		char* outBmp,
		unsigned int color = RGB(0, 255, 0));
	void CursorEnter();
	void CursorQuit();
	void SetCursorState(bool d); //ÉèÖÃm_in
	void Render();
};

#endif