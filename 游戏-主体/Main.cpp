#include <windows.h>
#include "Frame\GameFrame.h"
#include "Scene_Menu.h"
#include "Scene_Game.h"
#include "Scene_Game_Menu.h"
#include "Scene_Attack.h"
#include "Scene_Loading.h"
#include "Scene_Data.h"
#include "Scene_Load.h"
#include "Scene_End.h"
#include "Scene_HY.h"
#include "Scene_Help.h"

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CGameFrame::SetClient(640, 480);
	CGameFrame* pGF = CGameFrame::GetObject();
	
	//载入图片目录
	pGF->GetGO()->LoadDirectory("Pic");

	//设置窗口标题
	pGF->GetGO()->SetWindowTitle("某科学的Rpg游戏");

	pGF->LoadScene(new CScene_Data, "数据储存场景");
	pGF->LoadScene(new CScene_Menu, "场景1");
	pGF->LoadScene(new CScene_Game, "场景2");
	pGF->LoadScene(new CScene_Game_Menu, "游戏菜单场景");
	pGF->LoadScene(new CScene_Attack, "战斗场景");
	pGF->LoadScene(new CScene_Loading, "切换场景");
	pGF->LoadScene(new CScene_Load, "存档场景");	
	pGF->LoadScene(new CScene_End, "结束场景");
	pGF->LoadScene(new CScene_Start, "开始场景");
	pGF->LoadScene(new CScene_Help, "帮助场景");

	//装载控件
	pGF->GetScene("场景1")->LoadUI(new CButton_Start, "开始按钮");
	pGF->GetScene("场景1")->LoadUI(new CButton_Load, "读取按钮");
	pGF->GetScene("场景1")->LoadUI(new CButton_Help, "帮助按钮");
	pGF->GetScene("场景1")->LoadUI(new CButton_Quit, "退出按钮");

	pGF->GetScene("场景2")->LoadUI(new CButton_Return, "返回按钮");
	pGF->GetScene("场景2")->LoadUI(new CButton_Sell, "出售按钮");
	pGF->GetScene("场景2")->LoadUI(new CButton_Buy, "购买按钮");

	//设置当前场景
	pGF->SetCurScene("开始场景");

	pGF->Run();

	pGF->End();

	return 1;
}