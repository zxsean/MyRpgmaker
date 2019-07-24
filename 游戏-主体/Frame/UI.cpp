#include "UI.h"
#include "Scene.h"

CUI::CUI(int X1, int Y1, int X2, int Y2, bool Active)
:
x1(X1),
y1(Y1),
x2(X2),
y2(Y2),
active(Active),
scene(0)
{}

void CUI::SetPosition(int X1, int Y1, int X2, int Y2)
{
	x1 = X1;
	y1 = Y1;
	x2 = X2;
	y2 = Y2;
}

void CUI::SetActive(bool Active)
{
	active = Active;
}

void CUI::CursorEnter(){}
void CUI::CursorQuit(){}
void CUI::CursorInMove(int x, int y){}
void CUI::LButtonInDown(int x, int y){}
void CUI::MButtonInDown(int x, int y){}
void CUI::RButtonInDown(int x, int y){}
void CUI::LButtonInUp(int x, int y){}
void CUI::MButtonInUp(int x, int y){}
void CUI::RButtonInUp(int x, int y){}
void CUI::CursorOutMove(){}
void CUI::LButtonOutDown(){}
void CUI::MButtonOutDown(){}
void CUI::RButtonOutDown(){}
void CUI::LButtonOutUp(){}
void CUI::MButtonOutUp(){}
void CUI::RButtonOutUp(){}
void CUI::KeyDown(int Key){}
void CUI::KeyUp(int Key){}
void CUI::Render(){}
void CUI::Init(){}
void CUI::End(){}