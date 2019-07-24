#include "Scene_End.h"

void CScene_End::Init()
{
	pGF = CGameFrame::GetObject();
}

void CScene_End::Run()
{
	pGF->GetGO()->DrawBmp(0, 0, pGF->GetW(), pGF->GetH(), 0, 0, "Pic\\System\\End.bmp");

	if(pGF->GetGI()->Get(_GI_K_RETURN) == _KS_DC)
		exit(1);
}
