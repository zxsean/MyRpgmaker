#include "Scene_Help.h"

void CScene_Help::Init()
{
	pGF = CGameFrame::GetObject();
}

void CScene_Help::Run()
{
	pGF->GetGO()->DrawBmp(0, 0, pGF->GetW(), pGF->GetH(), 0, 0, "Pic\\System\\Help.bmp");

	if(pGF->GetGI()->Get(_GI_K_ESC) == _KS_DC)
		pGF->SetCurScene("³¡¾°1");

	GameSound.Tick();
}
