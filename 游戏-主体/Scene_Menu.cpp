#include "Scene_Menu.h"
#include "Scene_Game.h"

#pragma comment (lib,"Gdi32.lib")
//-------------按钮内容
//开始按钮
CButton_Start::CButton_Start()
:
CBmpButton(450, 270, 600, 308, "","", RGB(192, 192, 192))
{}
void CButton_Start::LButtonInUp(int x, int y)
{
	CGameFrame* pGF = CGameFrame::GetObject();
	CScene_Game* SGame = (CScene_Game*)pGF->GetScene("场景2");
	SGame->SetReset();
	
	SGame->GameSound.Stop(0);
	pGF->SetCurScene("场景2");
}	

void CButton_Start::CursorEnter()
{
	CScene_Menu* Temp;
	CGameFrame* pGF = CGameFrame::GetObject();
	Temp = (CScene_Menu*)pGF->GetScene("场景1");
	Temp->SetShowPicId(1);
}

void CButton_Start::CursorQuit()
{
	CScene_Menu* Temp;
	CGameFrame* pGF = CGameFrame::GetObject();
	Temp = (CScene_Menu*)pGF->GetScene("场景1");
	Temp->SetShowPicId(0);
}

//帮助按钮
CButton_Help::CButton_Help()
:
CBmpButton(450, 370, 600, 408, "","", RGB(192, 192, 192))
{}
void CButton_Help::LButtonInUp(int x, int y)
{
	CGameFrame* pGF = CGameFrame::GetObject();
	pGF->SetCurScene("帮助场景");
}	

void CButton_Help::CursorEnter()
{
	CScene_Menu* Temp;
	CGameFrame* pGF = CGameFrame::GetObject();
	Temp = (CScene_Menu*)pGF->GetScene("场景1");
	Temp->SetShowPicId(3);
}

void CButton_Help::CursorQuit()
{
	CScene_Menu* Temp;
	CGameFrame* pGF = CGameFrame::GetObject();
	Temp = (CScene_Menu*)pGF->GetScene("场景1");
	Temp->SetShowPicId(0);
}

//读取按钮
CButton_Load::CButton_Load()
:
CBmpButton(450, 320, 600, 358, "","", RGB(192, 192, 192))
{}
void CButton_Load::LButtonInUp(int x, int y)
{
	CGameFrame* pGF = CGameFrame::GetObject();
	CScene_Game* SGame = (CScene_Game*)pGF->GetScene("场景2");
	SGame->LoadData();
	
	SGame->GameSound.Stop(0);
	pGF->SetCurScene("场景2");
}	

void CButton_Load::CursorEnter()
{
	CScene_Menu* Temp;
	CGameFrame* pGF = CGameFrame::GetObject();
	Temp = (CScene_Menu*)pGF->GetScene("场景1");
	Temp->SetShowPicId(2);
}

void CButton_Load::CursorQuit()
{
	CScene_Menu* Temp;
	CGameFrame* pGF = CGameFrame::GetObject();
	Temp = (CScene_Menu*)pGF->GetScene("场景1");
	Temp->SetShowPicId(0);
}

//退出按钮
CButton_Quit::CButton_Quit()
:
CBmpButton(450, 420, 600, 458, "","", RGB(192, 192, 192))
{}
void CButton_Quit::LButtonInUp(int x, int y)
{
	CGameFrame* pGF = CGameFrame::GetObject();
	pGF->Quit();
}	

void CButton_Quit::CursorEnter()
{
	CScene_Menu* Temp;
	CGameFrame* pGF = CGameFrame::GetObject();
	Temp = (CScene_Menu*)pGF->GetScene("场景1");
	Temp->SetShowPicId(4);
}

void CButton_Quit::CursorQuit()
{
	CScene_Menu* Temp;
	CGameFrame* pGF = CGameFrame::GetObject();
	Temp = (CScene_Menu*)pGF->GetScene("场景1");
	Temp->SetShowPicId(0);
}
//-------------按钮内容

void CScene_Menu::Init()
{
	pGF = CGameFrame::GetObject();

	//添加字体资源
	AddFontResource ("msyhbd.ttf");

	GameSound.ReadFile(0, "Bgm\\0.mp3");
	GameSound.ReadFile(1, "Bgm\\024-Door01.ogg");
	GameSound.ReadFile(2, "Bgm\\094-Attack06.ogg");
	GameSound.ReadFile(3, "Bgm\\117-Fire03.ogg");
	GameSound.ReadFile(4, "Bgm\\Okay.wav");
	GameSound.ReadFile(5, "Bgm\\Battle5.ogg");
	GameSound.ReadFile(6, "Bgm\\AKITO - 迎え火.ogg");
}

void CScene_Menu::Enter()
{
	ShowPicId = 0;
	GameSound.Stop(1);
	GameSound.Stop(2);
	GameSound.Stop(3);
	GameSound.Stop(4);
	GameSound.Stop(5);
	GameSound.Stop(6);

	GameSound.play(0);
}

void CScene_Menu::Run()
{
	char buf[256];
	sprintf_s(buf, 256, "Pic\\System\\Logo\\%d.bmp", ShowPicId);
	pGF->GetGO()->DrawBmp(
		0,
		0, 
		pGF->GetW(),
		pGF->GetH(),
		0,
		0,
		buf);

	GameSound.Tick();
}

void CScene_Menu::Quit()
{
	//GameSound.Stop(0);
}

void CScene_Menu::SetShowPicId(int id)
{
	ShowPicId = id;
}
