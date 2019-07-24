#include "Scene_Loading.h"

void CScene_Loading::Init()
{
	pGF = CGameFrame::GetObject();
}

void CScene_Loading::Enter()
{
	m_Alpha = 0;
	m_ShowOK = true;
	m_Cj = (CScene_Game*)pGF->GetScene("³¡¾°2");
}

void CScene_Loading::Run()
{
	if (m_ShowOK)
	{
		if (m_Alpha + 15 < 255)
			m_Alpha += 15;
		else
			m_ShowOK = false;
	}
	else
		pGF->SetCurScene(m_Cj->m_CJ);

	pGF->GetGO()->DrawBmp(
		0,
		0, 
		pGF->GetW(),
		pGF->GetH(),
		0,
		0,
		"Pic\\System\\Load\\0.bmp");

	pGF->GetGO()->SetAlphaBlend(
		0,
		0, 
		pGF->GetW(),
		pGF->GetH(),
		0,
		0,
		m_Alpha,
		"Pic\\System\\Load\\1.bmp");
}

void CScene_Loading::Quit()
{

}
