#ifndef _CURSOR_POSITION_GAME_INPUT_H_
#define _CURSOR_POSITION_GAME_INPUT_H_

#include "GameInput.h"

class CCPGameInput : public CGameInput
{
public:
	virtual bool GetCursorPosition(int* pX, int* pY);
};

#endif