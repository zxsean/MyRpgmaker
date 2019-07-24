#include "Scene_Game.h"
#include "Scene_Attack.h"

#include "File/Rpg.h"
//-------------��ť����
//���ذ�ť
CButton_Return::CButton_Return()
:
CBmpButton(450, 120, 533, 155, "Pic\\System\\Button\\�뿪1.bmp","Pic\\System\\Button\\�뿪.bmp")
{}
void CButton_Return::LButtonInUp(int x, int y)
{
	CGameFrame* pGF = CGameFrame::GetObject();
	CScene_Game* Temp;
	Temp = (CScene_Game*)pGF->GetScene("����2");
	Temp->SetScene_State(_SCENE_WALK);

	std::map<std::string, CUI*>::iterator i = ((CScene_Game*)scene)->m_UI.find("���ذ�ť");
	if (i != ((CScene_Game*)scene)->m_UI.end())
	{
		i->second->SetActive(false);
		CButton_Return *Temp = (CButton_Return*)i->second;
		Temp->SetCursorState(false);
	}

	i = ((CScene_Game*)scene)->m_UI.find("����ť");
	if (i != ((CScene_Game*)scene)->m_UI.end())
		i->second->SetActive(false);

	i = ((CScene_Game*)scene)->m_UI.find("���۰�ť");
	if (i != ((CScene_Game*)scene)->m_UI.end())
		i->second->SetActive(false);
}	

CButton_Sell::CButton_Sell()
:
CBmpButton(450, 80, 533, 115, "Pic\\System\\Button\\����1.bmp","Pic\\System\\Button\\����.bmp")
{}
void CButton_Sell::LButtonInUp(int x, int y)
{
	CGameFrame* pGF = CGameFrame::GetObject();
	CScene_Game* Temp;
	Temp = (CScene_Game*)pGF->GetScene("����2");
	Temp->SetShop_State(1);
}	

CButton_Buy::CButton_Buy()
:
CBmpButton(450, 40, 533, 75, "Pic\\System\\Button\\����1.bmp","Pic\\System\\Button\\����.bmp")
{}
void CButton_Buy::LButtonInUp(int x, int y)
{
	CGameFrame* pGF = CGameFrame::GetObject();
	CScene_Game* Temp;
	Temp = (CScene_Game*)pGF->GetScene("����2");
	Temp->SetShop_State(0);
}	
//-------------��ť����

void CScene_Game::Init()
{
	pGF = CGameFrame::GetObject();
	HeroData = (CScene_Data*)pGF->GetScene("���ݴ��泡��");
	//��ȡ��ͼ
	g_Mapid = 0;
	LoadMapData();

	//��ʼ��
	m_HeroX = 9;
	m_HeroY = 12;

	m_NowHero_x = m_HeroX * _PIC_W;
	m_NowHero_y = m_HeroY * _PIC_H;
	m_Animation = 0;
	m_Dir = _GODIR_UP;
	m_CanGo = true;

	//����
	pGF->GetGO()->CreateFont(24, "΢���ź�", "�Ի�����");
	pGF->GetGO()->CreateFont(22, "΢���ź�", "��������");

	//����
	m_JZ_HeroX = m_HeroX  * _PIC_W;
	m_JZ_HeroY = m_HeroY * _PIC_H;

	//��ʼ����������
	Scene_State = _SCENE_WALK;
	Shop_State = 0;

	m_MonsterType = -1;
	m_BattleBc = -1;

	std::map<std::string, CUI*>::iterator i = m_UI.find("����ť");
	if (i != m_UI.end())
		i->second->SetActive(false);
	i = m_UI.find("���۰�ť");
	if (i != m_UI.end())
		i->second->SetActive(false);
	i = m_UI.find("���ذ�ť");
	if (i != m_UI.end())
		i->second->SetActive(false);
}

void CScene_Game::Enter()
{
	HeroData = (CScene_Data*)pGF->GetScene("���ݴ��泡��");

	std::map<std::string, CUI*>::iterator i = m_UI.find("����ť");
	if (i != m_UI.end())
		i->second->SetActive(false);
	i = m_UI.find("���۰�ť");
	if (i != m_UI.end())
		i->second->SetActive(false);
	i = m_UI.find("���ذ�ť");
	if (i != m_UI.end())
		i->second->SetActive(false);

	GameSound.play(6);
}

void CScene_Game::Run()
{
	//GameSound.Tick();

	//�õ���ͼ����
	g_MapCrash = g_Map.GetMap_Crash();
	g_MapObject = g_Map.GetMap_Object();
	g_MapDX = g_Map.GetMap_DX();
	g_MapBuild = g_Map.GetMap_JZ();

	//�����ӿ�
	UpdateView();

	//����
	pGF->GetGO()->DrawBmp(0, 0, pGF->GetW(), pGF->GetH(), 0, 0, "Pic\\System\\Bc.bmp");

	//��Ⱦ��ͼ
	DrawDX();

	//��Ⱦ��ͼ-->��ʾ��Ӣ��֮��,�����̤Ч��
	DrawDownHero();

	//��ȾӢ��
	DrawHero();

	//��Ⱦ��ͼ-->��ʾ��Ӣ��֮��,�����ڸ�Ч��
	DrawUpHero();

	////----------���Դ���----------
	//ս�����԰�ť
	//if(pGF->GetGI()->Get(_GI_K_T) == _KS_DC)
	//	SetBattleData(0, 9); //����ս����������

	//if(pGF->GetGI()->Get(_GI_K_Y) == _KS_DC)
	//	SetBattleData(1, 0); //����ս����������

	//if(pGF->GetGI()->Get(_GI_K_U) == _KS_DC)
	//	SetBattleData(1, 0, 1); //����ս����������

	//if(pGF->GetGI()->Get(_GI_K_I) == _KS_DC)
	//	SetBattleData(0, 1, 2, 4); //����ս����������

	//if(pGF->GetGI()->Get(_GI_K_1) == _KS_DC)
	//{
	//	if(HeroData->AddItem(1))
	//		MessageBox(0,"��ӳɹ�",0,0);
	//	else
	//		MessageBox(0,"ʧ��",0,0);
	//}
	//if(pGF->GetGI()->Get(_GI_K_2) == _KS_DC)
	//{
	//	if(HeroData->AddItem(2))
	//		MessageBox(0,"��ӳɹ�",0,0);
	//	else
	//		MessageBox(0,"ʧ��",0,0);
	//}
	//if(pGF->GetGI()->Get(_GI_K_3) == _KS_DC)
	//{
	//	if(HeroData->AddItem(0))
	//		MessageBox(0,"��ӳɹ�",0,0);
	//	else
	//		MessageBox(0,"ʧ��",0,0);
	//}
	//----------���Դ���----------

	////Ѱ·
	//if(pGF->GetGI()->Get(_GI_M_L) == _KS_DC)
	//{
	//	m_Dir = _GODIR_DOWN;
	//}

	switch (Scene_State)
	{
	case _SCENE_WALK:
		{
			//������Ӧ
			if(pGF->GetGI()->Get(_GI_K_W) == _KS_DH && m_HeroY > 0 && m_CanGo == true) //w
			{
				m_Dir = _GODIR_UP;
				Keypress(_GODIR_UP);
			}
			if(pGF->GetGI()->Get(_GI_K_S) == _KS_DH && m_HeroY < _MAP_H - 1 && m_CanGo == true) //s
			{
				m_Dir = _GODIR_DOWN;
				Keypress(_GODIR_DOWN);
			}
			if(pGF->GetGI()->Get(_GI_K_A) == _KS_DH && m_HeroX > 0 && m_CanGo == true) //a
			{
				m_Dir = _GODIR_LEFT;
				Keypress(_GODIR_LEFT);
			}
			if(pGF->GetGI()->Get(_GI_K_D) == _KS_DH && m_HeroX < _MAP_W - 1 && m_CanGo == true) //d
			{
				m_Dir = _GODIR_RIGHT;
				Keypress(_GODIR_RIGHT);
			}

			//�浵
			if(pGF->GetGI()->Get(_GI_K_C) == _KS_DC)
			{
				pGF->SetCurScene("�浵����");
			}

			//�˵���ť
			if(pGF->GetGI()->Get(_GI_K_ESC) == _KS_DC)
			{
				pGF->SetCurScene("��Ϸ�˵�����");
			}

			break;
		}
	case _SCENE_TALK:
		{
			std::vector<CTalkData>::iterator i = m_TalkData.begin();
			pGF->GetGO()->SetAlphaBlend(160, 330, 320, 120, 0, 0, 150,"Pic\\System\\Talk.bmp");
			pGF->GetGO()->SetAlphaBlend(283, 320, 64, 24, 0, 0, 150,"Pic\\System\\Talk2.bmp");

			char buf[256];
			sprintf_s(buf, 256, "Pic\\Face\\%d.bmp", i->m_TalkBmp);
			pGF->GetGO()->tDrawBmp(172, 342, 96, 96, 0, 0, buf); //ͷ��

			pGF->GetGO()->DrawText(i->m_TalkStr, 280, 340, 188, 93, RGB(255, 255, 255), "�Ի�����");
			pGF->GetGO()->DrawText(i->m_name, 300, 320, 64, 24, RGB(255, 255, 255), "��������");	

			if(pGF->GetGI()->Get(_GI_K_RETURN) == _KS_DC) //�س�
			{
				if (i != m_TalkData.end())
				{
					i = m_TalkData.erase(i);
					if (i == m_TalkData.end())
						Scene_State = _SCENE_WALK;
				}
				else
					Scene_State = _SCENE_WALK;
			}
			break;
		}
	case _SCENE_SHOP:
		{
			std::vector<CTalkData>::iterator i = m_TalkData.begin();
			pGF->GetGO()->SetAlphaBlend(160, 330, 320, 120, 0, 0, 150,"Pic\\System\\Talk.bmp");
			pGF->GetGO()->SetAlphaBlend(283, 320, 64, 24, 0, 0, 150,"Pic\\System\\Talk2.bmp");

			char buf[256];
			sprintf_s(buf, 256, "Pic\\Face\\%d.bmp", i->m_TalkBmp);
			pGF->GetGO()->tDrawBmp(172, 342, 96, 96, 0, 0, buf); //ͷ��

			pGF->GetGO()->DrawText(i->m_TalkStr, 280, 340, 188, 93, RGB(255, 255, 255), "�Ի�����");
			pGF->GetGO()->DrawText(i->m_name, 300, 320, 64, 24, RGB(255, 255, 255), "��������");	

			if(pGF->GetGI()->Get(_GI_K_RETURN) == _KS_DC) //�س�
			{
				if (i != m_TalkData.end())
				{
					i = m_TalkData.erase(i);
					if (i == m_TalkData.end())
					{
						//pGF->GetScene("����2")->LoadUI(new CButton_Return, "���ذ�ť");
						//pGF->GetScene("����2")->LoadUI(new CButton_Sell, "���۰�ť");
						//pGF->GetScene("����2")->LoadUI(new CButton_Buy, "����ť");
						std::map<std::string, CUI*>::iterator i = m_UI.find("����ť");
						if (i != m_UI.end())
							i->second->SetActive(true);
						i = m_UI.find("���۰�ť");
						if (i != m_UI.end())
							i->second->SetActive(true);
						i = m_UI.find("���ذ�ť");
						if (i != m_UI.end())
							i->second->SetActive(true);

						Scene_State = _SCENE_SHOPIN;
					}
				}
				else
				{
					//pGF->GetScene("����2")->LoadUI(new CButton_Return, "���ذ�ť");
					//pGF->GetScene("����2")->LoadUI(new CButton_Sell, "���۰�ť");
					//pGF->GetScene("����2")->LoadUI(new CButton_Buy, "����ť");
					std::map<std::string, CUI*>::iterator i = m_UI.find("����ť");
					if (i != m_UI.end())
						i->second->SetActive(true);
					i = m_UI.find("���۰�ť");
					if (i != m_UI.end())
						i->second->SetActive(true);
					i = m_UI.find("���ذ�ť");
					if (i != m_UI.end())
						i->second->SetActive(true);

					Scene_State = _SCENE_SHOPIN;
				}
			}
			break;
		}
	case _SCENE_SHOPIN:
		{
			Shop();
			break;
		}
	case _SCENE_BATTLE:
		{
			std::vector<CTalkData>::iterator i = m_TalkData.begin();
			pGF->GetGO()->SetAlphaBlend(160, 330, 320, 120, 0, 0, 150,"Pic\\System\\Talk.bmp");
			pGF->GetGO()->SetAlphaBlend(283, 320, 64, 24, 0, 0, 150,"Pic\\System\\Talk2.bmp");

			char buf[256];
			sprintf_s(buf, 256, "Pic\\Face\\%d.bmp", i->m_TalkBmp);
			pGF->GetGO()->tDrawBmp(172, 342, 96, 96, 0, 0, buf); //ͷ��

			pGF->GetGO()->DrawText(i->m_TalkStr, 280, 340, 188, 93, RGB(255, 255, 255), "�Ի�����");
			pGF->GetGO()->DrawText(i->m_name, 300, 320, 64, 24, RGB(255, 255, 255), "��������");	

			if(pGF->GetGI()->Get(_GI_K_RETURN) == _KS_DC) //�س�
			{
				if (i != m_TalkData.end())
				{
					i = m_TalkData.erase(i);
					if (i == m_TalkData.end())
						SetBattleData(m_BattleBc, m_MonsterType); //����ս����������
				}
				else
					SetBattleData(m_BattleBc, m_MonsterType); //����ս����������
			}
			break;
		}
	}

	HeroMove(); //Ӣ���ƶ���Ӧ
}

void CScene_Game::Quit()
{
	GameSound.Stop(6);
}

void CScene_Game::Keypress(int Key)
{
	int Mb_X = m_HeroX; //Ŀ���x,y
	int Mb_Y = m_HeroY; 
	GetMB_XY(Mb_X, Mb_Y, Key); //�õ�Ŀ��x,y

	switch(g_MapCrash[_x_y_i(Mb_X, Mb_Y)].Type)
	{
	case 0: //�����ƶ�
		{
			m_NowHero_x = m_HeroX * _PIC_W;
			m_NowHero_y = m_HeroY * _PIC_H;

			m_HeroX = Mb_X;
			m_HeroY = Mb_Y;

			m_CanGo = false;
			break;
		}
	case 2: //��ͼ�л�
		{
			m_HeroX = g_MapCrash[_x_y_i(Mb_X, Mb_Y)].x; //����Hero������
			m_HeroY = g_MapCrash[_x_y_i(Mb_X, Mb_Y)].y;
			m_NowHero_x = m_HeroX * _PIC_W; //������������
			m_NowHero_y = m_HeroY * _PIC_H; 
			//����
			m_JZ_HeroX = m_HeroX  * _PIC_W;
			m_JZ_HeroY = m_HeroY * _PIC_H;

			ChangeMap(g_MapCrash[_x_y_i(Mb_X, Mb_Y)].Id); //�л���ͼ

			m_CJ = "����2";
			pGF->SetCurScene("�л�����"); //����Ч��

			GameSound.play(1);
			break;
		}
	case 3: //�¼�
		{
			switch(g_MapCrash[_x_y_i(Mb_X, Mb_Y)].Id) //��ȡ����id
			{
			case _CF_LP1:
				{
					m_TalkData.clear();
					std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(41);
					SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					break;
				}
			case _CF_LP2:
				{
					m_TalkData.clear();
					std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(42);
					SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					break;
				}
			case _CF_LP3:
				{
					m_TalkData.clear();
					std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(43);
					SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					break;
				}
			case _CF_LP4:
				{
					m_TalkData.clear();
					std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(44);
					SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					break;
				}
				//����
			case _CF_BX1:
				{
					if (HeroData->MissionCheck(6))
					{
						HeroData->AddItem(g_MapCrash[_x_y_i(Mb_X, Mb_Y)].x);
						std::map<int, Item>::iterator i = HeroData->_ItemData.find(g_MapCrash[_x_y_i(Mb_X, Mb_Y)].x);
						if (i != HeroData->_ItemData.end())
						{
							m_TalkData.clear();
							char* buf;
							buf = new char[256];
							sprintf_s(buf, 256, "�����:%s", i->second.name);
							SetTalkData(buf, 1, HeroData->Hero.YxHero.getName());
						}
					}
					else
					{
						m_TalkData.clear();
						SetTalkData("����һ���ձ���~~", 6, HeroData->Hero.YxHero.getName());
					}
					break;
				}
				//����
			case _CF_BX2:
				{
					if (HeroData->MissionCheck(11))
					{
						HeroData->AddItem(g_MapCrash[_x_y_i(Mb_X, Mb_Y)].x);
						std::map<int, Item>::iterator i = HeroData->_ItemData.find(g_MapCrash[_x_y_i(Mb_X, Mb_Y)].x);
						if (i != HeroData->_ItemData.end())
						{
							m_TalkData.clear();
							char* buf;
							buf = new char[256];
							sprintf_s(buf, 256, "�����:%s", i->second.name);
							SetTalkData(buf, 1, HeroData->Hero.YxHero.getName());
						}
					}
					else
					{
						m_TalkData.clear();
						SetTalkData("����һ���ձ���~~", 6, HeroData->Hero.YxHero.getName());
					}
					break;
				}
				//�̵�
			case _CF_SHOP:
				{
					HeroData->MissionCheck(4);

					m_TalkData.clear();
					SetTalkData("��?������?", 21, "�̵�");
					Shop_State = 0;
					Scene_State = _SCENE_SHOP;
					break;
				}

				//NPC
			case _CF_NPC1: //����ָ��
				{
					m_TalkData.clear();
					if (HeroData->MissionCheck(0))
					{
						std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(1);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
						i = HeroData->_TalkData.find(2);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
						i = HeroData->_TalkData.find(3);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
						i = HeroData->_TalkData.find(4);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
						i = HeroData->_TalkData.find(5);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
						i = HeroData->_TalkData.find(6);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
						i = HeroData->_TalkData.find(7);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
						i = HeroData->_TalkData.find(8);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					}
					else
					{
						std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(9);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
						i = HeroData->_TalkData.find(10);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					}
					break;
				}

			case _CF_NPC2: //��������
				{
					m_TalkData.clear();
					//HeroData->MissionCheck(2);
					if (HeroData->MissionCheck(2))
					{
						std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(12);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
						i = HeroData->_TalkData.find(13);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
						i = HeroData->_TalkData.find(14);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
						i = HeroData->_TalkData.find(15);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
						i = HeroData->_TalkData.find(16);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
						i = HeroData->_TalkData.find(17);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
						i = HeroData->_TalkData.find(18);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
						i = HeroData->_TalkData.find(19);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					}
					else
					{
						std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(20);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
						i = HeroData->_TalkData.find(14);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
						i = HeroData->_TalkData.find(15);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					}
					break;
				}

			case _CF_NPC3: //�͵��ߵ�����
				{
					if (HeroData->Hero.YxHero.getLevel() > 1)
					{
						if (HeroData->MissionCheck(3))
						{
							std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(22);
							SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
							HeroData->AddItem(0);
						}
						else
						{
							std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(23);
							SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
						}
					}
					else
					{
						std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(21);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					}
					break;
				}

			case _CF_NPC4: //����ָ��
				{
					m_TalkData.clear();
					if (HeroData->MissionCheck(8))
					{
						std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(48);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					}
					else
					{
						if (HeroData->MissionCheck(10))
						{
							std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(51);
							SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
						}
						else
						{
							std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(50);
							SetTalkData(i->second.talk, i->second.BmpId, i->second.name);

						}
					}
					break;
				}
			case _CF_NPC5: //����ָ��
				{
					m_TalkData.clear();
					if (HeroData->MissionCheck(9))
					{
						std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(52);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					}
					else
					{
						std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(49);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					}
					break;
				}
				//����NPC
			case _CF_JYNPC1: //����Ů
				{
					int r = rand() % 3 + 24;
					std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(r);
					SetTalkData(i->second.talk, i->second.BmpId, i->second.name);

					i = HeroData->_TalkData.find(31);
					SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					break;
				}
			case _CF_JYNPC2: //������
				{
					int r = rand() % 3 + 27;
					std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(r);
					SetTalkData(i->second.talk, i->second.BmpId, i->second.name);

					i = HeroData->_TalkData.find(30);
					SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					break;
				}
			case _CF_JYNPC3: //����������
				{
					std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(32);
					SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					i = HeroData->_TalkData.find(33);
					SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					i = HeroData->_TalkData.find(34);
					SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					break;
				}
			case _CF_JYNPC4: //���ʹ���
				{
					std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(35);
					SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					break;
				}
			case _CF_JYNPC5: //���������ӳ�
				{
					std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(36);
					SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					break;
				}
			case _CF_JYNPC6: //��������
				{
					int r = rand() % 3 + 37;
					std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(r);
					SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					break;
				}

				//boos
			case _CF_BOSS:
				{
					std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(45);
					SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					i = HeroData->_TalkData.find(46);
					SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					i = HeroData->_TalkData.find(47);
					SetTalkData(i->second.talk, i->second.BmpId, i->second.name);

					m_BattleBc = g_MapCrash[_x_y_i(Mb_X, Mb_Y)].x; //����
					m_MonsterType = g_MapCrash[_x_y_i(Mb_X, Mb_Y)].y; //��������
					Scene_State = _SCENE_BATTLE;
					break;
				}
				//����������
			case _CF_CS:
				{
					m_TalkData.clear();
					if (HeroData->MissionCheck(1)) //���ǰ������
					{
						m_HeroX = g_MapCrash[_x_y_i(Mb_X, Mb_Y)].x; //����Hero������
						m_HeroY = g_MapCrash[_x_y_i(Mb_X, Mb_Y)].y;
						m_NowHero_x = m_HeroX * _PIC_W; //������������
						m_NowHero_y = m_HeroY * _PIC_H; 
						//����
						m_JZ_HeroX = m_HeroX  * _PIC_W;
						m_JZ_HeroY = m_HeroY * _PIC_H;

						ChangeMap(2); //�л���ͼ

						m_CJ = "����2";
						pGF->SetCurScene("�л�����"); //����Ч��

						GameSound.play(1);
					}
					else
					{
						std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(11);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					}
					break;
				}

				//����������
			case _CF_CS2:
				{
					m_TalkData.clear();
					if (HeroData->MissionCheck(5)) //���ǰ������
					{
						m_HeroX = g_MapCrash[_x_y_i(Mb_X, Mb_Y)].x; //����Hero������
						m_HeroY = g_MapCrash[_x_y_i(Mb_X, Mb_Y)].y;
						m_NowHero_x = m_HeroX * _PIC_W; //������������
						m_NowHero_y = m_HeroY * _PIC_H; 
						//����
						m_JZ_HeroX = m_HeroX  * _PIC_W;
						m_JZ_HeroY = m_HeroY * _PIC_H;

						ChangeMap(3); //�л���ͼ

						m_CJ = "����2";
						pGF->SetCurScene("�л�����"); //����Ч��
					}
					else
					{
						std::map<int, Type_Talk>::iterator i = HeroData->_TalkData.find(40);
						SetTalkData(i->second.talk, i->second.BmpId, i->second.name);
					}
					break;
				}
			}
			break;
		}
	}
}

void CScene_Game::HeroMove()
{
	if (!m_CanGo)
	{
		switch (m_Dir)
		{
		case _GODIR_UP:
			{
				if (m_NowHero_y > m_HeroY * _PIC_H)
				{
					if (m_Animation != 7)
						m_Animation += 1;
					else
						m_Animation = 0;

					m_NowHero_y -= _GO_SIZE;
					//����
					m_JZ_HeroY -= _GO_SIZE;
				}
				else 
				{
					m_CanGo = true;
					YuDi();
				}
				break;
			}
		case _GODIR_DOWN:
			{
				if (m_NowHero_y < m_HeroY * _PIC_H)
				{
					if (m_Animation != 7)
						m_Animation += 1;
					else
						m_Animation = 0;

					m_NowHero_y += _GO_SIZE;
					//����
					m_JZ_HeroY += _GO_SIZE;
				}
				else
				{
					m_CanGo = true;
					YuDi();
				}
				break;
			}
		case _GODIR_LEFT:
			{
				if (m_NowHero_x > m_HeroX * _PIC_W)
				{
					if (m_Animation != 7)
						m_Animation += 1;
					else
						m_Animation = 0;

					m_NowHero_x -= _GO_SIZE;
					//����
					m_JZ_HeroX -= _GO_SIZE;
				}
				else
				{
					m_CanGo = true;
					YuDi();
				}
				break;
			}
		case _GODIR_RIGHT:
			{
				if (m_NowHero_x < m_HeroX * _PIC_W)
				{
					if (m_Animation != 7)
						m_Animation += 1;
					else
						m_Animation = 0;

					m_NowHero_x += _GO_SIZE;
					//����
					m_JZ_HeroX += _GO_SIZE;
				}
				else
				{
					m_CanGo = true;
					YuDi();
				}
				break;
			}
		}
	}
}

void CScene_Game::GetMB_XY(int& x, int& y, int Key)
{
	switch (Key)
	{
	case _GODIR_UP:
		{
			y--;
			break;
		}
	case _GODIR_DOWN:
		{
			y++;
			break;
		}
	case _GODIR_LEFT:
		{
			x--;
			break;
		}
	case _GODIR_RIGHT:
		{
			x++;
			break;
		}
	}
}

void CScene_Game::ChangeMap(int MapId)
{
	//װ��Ŀ���ͼ
	g_Mapid = MapId;
	std::map<int, CMapData>::iterator j = g_MapList.find(MapId);
	{
		if (j != g_MapList.end()) //�ҵ���
			g_Map = j->second;
	}
}

void CScene_Game::SetTalkData(char* Talk, int TalkBmp, char* TalkName)
{
	CTalkData Temp;
	Temp.m_TalkStr = Talk;
	Temp.m_TalkBmp = TalkBmp;
	Temp.m_name = TalkName;
	m_TalkData.push_back(Temp);

	Scene_State = _SCENE_TALK;
}

void CScene_Game::DrawHero()
{
	//��ȾӢ��
	pGF->GetGO()->tDrawBmp(m_NowHero_x - m_JZ_ViewX,
		m_NowHero_y - m_JZ_ViewY,
		_PIC_W, _PIC_H, 
		m_Animation * _PIC_W, 
		(m_Dir - 1) * _PIC_H, 
		"Pic\\Hero\\0.bmp");
}

//�Ǿ���
//void CScene_Game::DrawDX()
//{
//	for (int i = 0; i < _MAP_S; ++i)
//	{
//		int cx = i % _MAP_W;
//		int cy = i / _MAP_W;
//		//���β�
//		if (g_MapDX[i] > 0)
//		{
//			char buf[256];
//			sprintf_s(buf, 256, "Pic\\Map_1\\%d.bmp", g_MapDX[i] - 1);
//			pGF->GetGO()->DrawBmp(cx * _PIC_W, cy * _PIC_H, _PIC_W, _PIC_H, 0, 0, buf);
//		}
//	}
//}

//����
void CScene_Game::DrawDX()
{
	//�õ��ӿڿ�ѡ�����ϡ����µ�ͼ����߼�����(����Ϊ��λ)
	int x1 = m_JZ_ViewX / _PIC_W;
	int y1 = m_JZ_ViewY / _PIC_H;
	int x2 = (m_JZ_ViewX + _SK_W - 1) / _PIC_W;
	int y2 = (m_JZ_ViewY + _SK_H - 1) / _PIC_H;

	//�õ���ͼ����ʼλ��
	int bx = x1 * _PIC_W - m_JZ_ViewX;
	int by = y1 * _PIC_H - m_JZ_ViewY;

	//��ͼ
	for (int x = x1; x <= x2; ++x)
	{
		for (int y = y1; y <= y2; ++y)
		{
			int i =x + y  * _LJ_W;
			if (g_MapDX[i] > 0)
			{
				char buf[256];
				sprintf_s(buf, 256, "Pic\\Map_1\\%d.bmp", g_MapDX[i] - 1);
				pGF->GetGO()->DrawBmp((x - x1) * _PIC_W + bx, (y - y1) * _PIC_H + by, _PIC_W, _PIC_H, 0, 0, buf);
			}
		}
	}
}

////�Ǿ���
//void CScene_Game::DrawUpHero()
//{
//	for (int i = 0; i < _MAP_S; ++i)
//	{
//		int cx = i % _MAP_W;
//		int cy = i / _MAP_W;
//
//		//������,�ϰ���
//		if (g_MapBuild[i] > 0)
//		{
//			char buf[256];
//			sprintf_s(buf, 256, "Pic\\Map_2\\%d.bmp", g_MapBuild[i] - 1);
//			pGF->GetGO()->tDrawBmp(cx * _PIC_W, cy * _PIC_H, _PIC_W, _PIC_H, 0, 0, buf);
//		}
//		//װ�β�
//		if (g_MapObject[i] > 0)
//		{
//			char buf[256];
//			sprintf_s(buf, 256, "Pic\\Map_3\\%d.bmp", g_MapObject[i] - 1);
//			pGF->GetGO()->tDrawBmp(cx * _PIC_W, cy * _PIC_H, _PIC_W, _PIC_H, 0, 0, buf);
//		}
//	}
//}

//����
void CScene_Game::DrawUpHero()
{
	//�õ��ӿڿ�ѡ�����ϡ����µ�ͼ����߼�����(����Ϊ��λ)
	int x1 = m_JZ_ViewX / _PIC_W;
	int y1 = m_JZ_ViewY / _PIC_H;
	int x2 = (m_JZ_ViewX + _SK_W - 1) / _PIC_W;
	int y2 = (m_JZ_ViewY + _SK_H - 1) / _PIC_H;

	//�õ���ͼ����ʼλ��
	int bx = x1 * _PIC_W - m_JZ_ViewX;
	int by = y1 * _PIC_H - m_JZ_ViewY;

	//��ͼ
	for (int x = x1; x <= x2; ++x)
	{
		for (int y = y1; y <= y2; ++y)
		{
			int i =x + y  * _LJ_W;
			//������,�ϰ���
			if (g_MapBuild[i] > 0)
			{
				char buf[256];
				sprintf_s(buf, 256, "Pic\\Map_2\\%d.bmp", g_MapBuild[i] - 1);
				pGF->GetGO()->tDrawBmp((x - x1) * _PIC_W + bx, (y - y1) * _PIC_H + by, _PIC_W, _PIC_H, 0, 0, buf);
			}
			//װ�β�
			if (g_MapObject[i] > 0 && g_MapObject[i] < 50)
			{
				char buf[256];
				sprintf_s(buf, 256, "Pic\\Map_3\\%d.bmp", g_MapObject[i] - 1);
				pGF->GetGO()->tDrawBmp((x - x1) * _PIC_W + bx, (y - y1) * _PIC_H + by, _PIC_W, _PIC_H, 0, 0, buf);
			}
		}
	}
}

void CScene_Game::DrawDownHero()
{
	//�õ��ӿڿ�ѡ�����ϡ����µ�ͼ����߼�����(����Ϊ��λ)
	int x1 = m_JZ_ViewX / _PIC_W;
	int y1 = m_JZ_ViewY / _PIC_H;
	int x2 = (m_JZ_ViewX + _SK_W - 1) / _PIC_W;
	int y2 = (m_JZ_ViewY + _SK_H - 1) / _PIC_H;

	//�õ���ͼ����ʼλ��
	int bx = x1 * _PIC_W - m_JZ_ViewX;
	int by = y1 * _PIC_H - m_JZ_ViewY;

	//��ͼ
	for (int x = x1; x <= x2; ++x)
	{
		for (int y = y1; y <= y2; ++y)
		{
			int i =x + y  * _LJ_W;
			////������,�ϰ���
			//if (g_MapBuild[i] > 0)
			//{
			//	char buf[256];
			//	sprintf_s(buf, 256, "Pic\\Map_2\\%d.bmp", g_MapBuild[i] - 1);
			//	pGF->GetGO()->tDrawBmp((x - x1) * _PIC_W + bx, (y - y1) * _PIC_H + by, _PIC_W, _PIC_H, 0, 0, buf);
			//}
			//װ�β�
			if (g_MapObject[i] > 50)
			{
				char buf[256];
				sprintf_s(buf, 256, "Pic\\Map_3\\%d.bmp", g_MapObject[i] - 1);
				pGF->GetGO()->tDrawBmp((x - x1) * _PIC_W + bx, (y - y1) * _PIC_H + by, _PIC_W, _PIC_H, 0, 0, buf);
			}
		}
	}
}

void CScene_Game::SetBattleData(int BmpId, int Enemy1, int Enemy2, int Enemy3)
{
	CScene_Attack* Temp;
	Temp = (CScene_Attack*)pGF->GetScene("ս������");
	Temp->SetData(BmpId, Enemy1, Enemy2, Enemy3);

	m_CJ = "ս������";
	pGF->SetCurScene("�л�����"); //����Ч��
}

void CScene_Game::UpdateView()
{
	//�õ�Ӣ�ۡ��ӿڵ�x����������ֵ
	int xcz = (_SK_W - _PIC_W) / 2;

	//�õ�Ӣ�ۡ��ӿڵ�y����������ֵ
	int ycz = (_SK_H - _PIC_H) / 2;

	//x�����3�����
	if (m_JZ_HeroX < xcz)
		m_JZ_ViewX = 0;
	else if (m_JZ_HeroX > _Z_W - xcz - _PIC_W)
		m_JZ_ViewX = _Z_W - _SK_W;
	else
		m_JZ_ViewX = m_JZ_HeroX - xcz;

	//y�����3�����
	if (m_JZ_HeroY < ycz)
		m_JZ_ViewY = 0;
	else if (m_JZ_HeroY > _Z_H - ycz - _PIC_H)
		m_JZ_ViewY = _Z_H - _SK_H;
	else
		m_JZ_ViewY = m_JZ_HeroY - ycz;
}

void CScene_Game::LoadMapData()
{
	int MapNum = HeroData->GetMapNum();

	for (int i = 0;i < MapNum; ++i)
	{
		FILE* pF = 0;
		char FileName[256];
		sprintf_s(FileName, 256, "map\\Map%d.MapData", i);
		fopen_s(&pF, FileName, "rb");

		if (!pF) //����ͼ�ļ��Ƿ����
		{
			MessageBox(pGF->GetHwnd(), "�Ƿ���ͼId!", "��ʾ", 0);
		}
		else
		{
			fseek(pF, 0, SEEK_END);
			int fileSize = ftell(pF);
			rewind(pF); 
			int MapId; //Id
			fread(&MapId, 1, 4, pF);

			CMapData Temp;
			//���õ�ͼID
			Temp.SetMap_ID(MapId);
			//��ȡ��ײ��
			fread(Temp.GetMap_Crash(), 1, _MAP_S * sizeof(int) * 4, pF);
			//��ȡ���β�
			fread(Temp.GetMap_DX(), 1, _MAP_S * sizeof(char), pF);
			//��ȡ������
			fread(Temp.GetMap_JZ(), 1, _MAP_S * sizeof(char), pF);
			//��ȡ�����
			fread(Temp.GetMap_Object(), 1, _MAP_S * sizeof(char), pF);

			fclose(pF);

			//�����ͼ��
			g_MapList.insert(std::pair<int, CMapData>(MapId, Temp));
		}

		std::map<int, CMapData>::iterator j = g_MapList.find(g_Mapid);
		{
			if (j != g_MapList.end()) //�ҵ���
				g_Map = j->second;
		}
	}
}

void CScene_Game::SetScene_State(int id)
{
	Scene_State = id;
}

void CScene_Game::SetShop_State(int id)
{
	Shop_State = id;
}

void CScene_Game::Shop()
{
	pGF->GetGO()->SetAlphaBlend(120, 30, 320, 420, 0, 0, 155, "Pic\\System\\Menu_Item.bmp");

	//Ӣ�۽��
	char buf[256];
	sprintf_s(buf, 256, "���н����:%d", HeroData->Hero.YxHero.getMoney());
	pGF->GetGO()->DrawText(buf, 300, 420, RGB(255, 255, 255), "��������");

	switch (Shop_State)
	{
	case 0: //�������
		{
			std::map<int, Item>::iterator i = HeroData->_ItemData.begin();
			int c_i = 0;
			for(; i != HeroData->_ItemData.end(); ++i, ++c_i)
			{
				int cx = c_i % 1 * 100 + 145;
				int cy = c_i / 1 * 40 + 60;
				pGF->GetGO()->DrawText(i->second.name, cx, cy, RGB(255, 255, 255), "��������");

				//����������
				std::vector<Item>::iterator j = HeroData->Hero.YxHero.Dj.begin();
				for (; j != HeroData->Hero.YxHero.Dj.end(); ++j)
				{
					if (j->id == i->second.id)
					{
						char buf[256];
						sprintf_s(buf, 256, "%d", j->ItemNum);
						pGF->GetGO()->DrawText(buf, cx + 150, cy, RGB(255, 255, 255), "��������");
					}
				}

				//�۸�
				char buf[256];
				sprintf_s(buf, 256, "%d", i->second.Price);
				pGF->GetGO()->DrawText(buf, cx + 250, cy, RGB(255, 255, 255), "��������");
			}

			//���
			int c_x, c_y;
			pGF->GetGI()->GetCursorPosition(&c_x, &c_y);
			c_x = (c_x - 145) / 100;
			c_y = (c_y - 60) / 40;
			c_i = c_x + c_y * 1;

			int Temp_x, Temp_y;
			pGF->GetGI()->GetCursorPosition(&Temp_x, &Temp_y);
			if ((Temp_x > 145 && Temp_x < 250) && (Temp_y > 60 && Temp_y < 450))
			{
				//��ʾ
				if (c_i < (int)HeroData->_ItemData.size())
				{
					std::map<int, Item>::iterator i = HeroData->_ItemData.begin();
					for (int j = 0; j < c_i; ++j)
						i++;

					//ѡ��Ч��
					pGF->GetGO()->DrawText(i->second.name, c_i % 1 * 100 + 145, c_i / 1 * 40 + 60, RGB(255, 0, 0), "��������");	

					pGF->GetGO()->tDrawBmp(Temp_x, Temp_y, 200, 71, 0, 0, "Pic\\System\\Tips.bmp");
					pGF->GetGO()->DrawText(i->second.ItemText, Temp_x + 15, Temp_y + 20, RGB(255, 0, 0), "��Ϸ�˵�����");

					if (pGF->GetGI()->Get(_GI_M_L) == _KS_DC)
					{
						if (HeroData->Hero.YxHero.getMoney() - i->second.Price < 0)
						{
							MessageBox(pGF->GetHwnd(), "��Ǯ����", 0, 0);
						}
						else
						{
							HeroData->AddItem(i->first);
							HeroData->Hero.YxHero.MoneyAdd(-i->second.Price);
						}
					}
				}
			}
			break;
		}
	case 1: //���۽���
		{
			std::vector<Item>::iterator i = HeroData->Hero.YxHero.Dj.begin();
			int c_i = 0;
			for(; i != HeroData->Hero.YxHero.Dj.end(); ++i, ++c_i)
			{
				int cx = c_i % 1 * 100 + 145;
				int cy = c_i / 1 * 40 + 60;
				pGF->GetGO()->DrawText(i->name, cx, cy, RGB(255, 255, 255), "��������");

				//����������
				char buf[256];
				sprintf_s(buf, 256, "%d", i->ItemNum);
				pGF->GetGO()->DrawText(buf, cx + 100, cy, RGB(255, 255, 255), "��������");
				//�۸�
				sprintf_s(buf, 256, "%d", i->Price / 2);
				pGF->GetGO()->DrawText(buf, cx + 200, cy, RGB(255, 255, 255), "��������");
			}

			//���
			int c_x, c_y;
			pGF->GetGI()->GetCursorPosition(&c_x, &c_y);
			c_x = (c_x - 145) / 100;
			c_y = (c_y - 60) / 40;
			c_i = c_x + c_y * 1;

			int Temp_x, Temp_y;
			pGF->GetGI()->GetCursorPosition(&Temp_x, &Temp_y);
			if ((Temp_x > 145 && Temp_x < 250) && (Temp_y > 60 && Temp_y < 450))
			{
				//��ʾ
				if (c_i < (int)HeroData->Hero.YxHero.Dj.size())
				{
					std::vector<Item>::iterator i = HeroData->Hero.YxHero.Dj.begin();
					i += c_i;

					//ѡ��Ч��
					pGF->GetGO()->DrawText(i->name, c_i % 1 * 100 + 145, c_i / 1 * 40 + 60, RGB(255, 0, 0), "��������");	

					pGF->GetGO()->tDrawBmp(Temp_x, Temp_y, 200, 71, 0, 0, "Pic\\System\\Tips.bmp");
					pGF->GetGO()->DrawText(i->ItemText, Temp_x + 15, Temp_y + 20, RGB(255, 0, 0), "��Ϸ�˵�����");

					if (pGF->GetGI()->Get(_GI_M_L) == _KS_DC)
					{
						HeroData->Hero.YxHero.MoneyAdd(i->Price / 2);

						if (i->ItemNum > 1)
							i->ItemNum -= 1;
						else
							i = HeroData->Hero.YxHero.Dj.erase(i);
					}
				}
			}
			break;
		}
	}
}

void CScene_Game::YuDi()
{
	std::vector<MapYuDi>::iterator i = HeroData->_MapYuDiData.begin();
	for (; i != HeroData->_MapYuDiData.end(); ++i)
	{
		if (i->YuDiMapId == g_Mapid)
		{
			int YuDiR = rand() % 100;
			int YuDiNum = 0;
			int YuDiType[8];
			if (YuDiR < i->YuDiLv)
			{
				for (int j = 0; j < 8; ++j)
				{
					if (i->Type[j] != -1)
					{
						YuDiType[YuDiNum] = i->Type[j];
						YuDiNum++;
					}
				}
				int EmNum = rand() % 3 + 1; //��������
				int YuDiTypeLast[3];
				for (int i = 0; i < 3; ++i)
					YuDiTypeLast[i] = -1;
				for (int i = 0; i < EmNum; ++i)
				{
					int TypeR = rand() % YuDiNum;
					YuDiTypeLast[i] = YuDiType[TypeR];
				}

				SetBattleData(rand() % 2, YuDiTypeLast[0], YuDiTypeLast[1], YuDiTypeLast[2]); //����ս����������
			}
		}
	}
}

void CScene_Game::SetReset()
{
	//��ȡ��ͼ
	g_Mapid = 0;

	//��ʼ��
	m_HeroX = 9;
	m_HeroY = 12;

	m_NowHero_x = m_HeroX * _PIC_W;
	m_NowHero_y = m_HeroY * _PIC_H;
	m_Animation = 0;
	m_Dir = _GODIR_UP;
	m_CanGo = true;

	//����
	m_JZ_HeroX = m_HeroX  * _PIC_W;
	m_JZ_HeroY = m_HeroY * _PIC_H;

	//��ʼ����������
	Scene_State = _SCENE_WALK;
	Shop_State = 0;

	HeroData->NewGame("С��");

	ChangeMap(g_Mapid);
}

void CScene_Game::LoadData()
{
	//��ȡ��ͼ
	g_Mapid = 0;

	//��ʼ��
	m_HeroX = 9;
	m_HeroY = 12;

	m_NowHero_x = m_HeroX * _PIC_W;
	m_NowHero_y = m_HeroY * _PIC_H;
	m_Animation = 0;
	m_Dir = _GODIR_UP;
	m_CanGo = true;

	//����
	m_JZ_HeroX = m_HeroX  * _PIC_W;
	m_JZ_HeroY = m_HeroY * _PIC_H;

	//��ʼ����������
	Scene_State = _SCENE_WALK;
	Shop_State = 0;

	HeroData->LoadGame();

	ChangeMap(g_Mapid);
}
