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
	
	//����ͼƬĿ¼
	pGF->GetGO()->LoadDirectory("Pic");

	//���ô��ڱ���
	pGF->GetGO()->SetWindowTitle("ĳ��ѧ��Rpg��Ϸ");

	pGF->LoadScene(new CScene_Data, "���ݴ��泡��");
	pGF->LoadScene(new CScene_Menu, "����1");
	pGF->LoadScene(new CScene_Game, "����2");
	pGF->LoadScene(new CScene_Game_Menu, "��Ϸ�˵�����");
	pGF->LoadScene(new CScene_Attack, "ս������");
	pGF->LoadScene(new CScene_Loading, "�л�����");
	pGF->LoadScene(new CScene_Load, "�浵����");	
	pGF->LoadScene(new CScene_End, "��������");
	pGF->LoadScene(new CScene_Start, "��ʼ����");
	pGF->LoadScene(new CScene_Help, "��������");

	//װ�ؿؼ�
	pGF->GetScene("����1")->LoadUI(new CButton_Start, "��ʼ��ť");
	pGF->GetScene("����1")->LoadUI(new CButton_Load, "��ȡ��ť");
	pGF->GetScene("����1")->LoadUI(new CButton_Help, "������ť");
	pGF->GetScene("����1")->LoadUI(new CButton_Quit, "�˳���ť");

	pGF->GetScene("����2")->LoadUI(new CButton_Return, "���ذ�ť");
	pGF->GetScene("����2")->LoadUI(new CButton_Sell, "���۰�ť");
	pGF->GetScene("����2")->LoadUI(new CButton_Buy, "����ť");

	//���õ�ǰ����
	pGF->SetCurScene("��ʼ����");

	pGF->Run();

	pGF->End();

	return 1;
}