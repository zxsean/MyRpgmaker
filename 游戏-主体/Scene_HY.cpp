#include "Scene_HY.h"

void CScene_Start::Init()
{
	pGF = CGameFrame::GetObject();
}

void CScene_Start::Run()
{
	pGF->GetGO()->DrawBmp(0, 0, pGF->GetW(), pGF->GetH(), 0, 0, "Pic\\System\\Start.bmp");

	if(pGF->GetGI()->Get(_GI_K_RETURN) == _KS_DC)
		pGF->SetCurScene("³¡¾°1");

	GameSound.Tick();
}

void CScene_Start::Enter()
{
	GameSound.play(0);
}
