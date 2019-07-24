#include "Scene_Attack.h"
#include <time.h>

void CScene_Attack::Init()
{
	pGF = CGameFrame::GetObject();
	pGF->GetGO()->CreateFont(30, "΢���ź�", "ʤ������");
	pGF->GetGO()->CreateFont(22, "΢���ź�", "Ѫ������");
	pGF->GetGO()->CreateFont(30, "����", "�˺�����");

	//�������������
	srand((unsigned int)time(0));
}

void CScene_Attack::Enter()
{
	//��ʼ����������
	m_Battle_EnemyNum = 0;
	//��ʼ��ս������Ϊ�ȴ������
	m_Battle_Scene = _BATTLE_WAIT;
	//��ʼ���Ƿ���ʾ��������
	m_ShowAttack = false;
	//��ʼ��Ӣ�۶���
	m_HeroBattle_Animation = 0;
	m_HeroBattle_PicTimer = 0;
	m_HeroBattle_Victory = _HERO_NORMAL;
	//��ʼ��ѡ��ť�����Լ�����
	m_Select_X = 0;
	m_Select_Animation = 0;
	m_Select_PicTimer = 0;
	//��ʼ����������
	m_Attack_Animation = 0;
	//��ʼ��Ѫ������
	m_HpBar_Animation = 0;
	//��ʼ��Ӣ������
	m_HeroBattleMove.x = 400;
	m_HeroBattleMove.y = 270;
	m_HeroBattleMoveGo = false;

	m_Battle_EnemyNum = 0;
	//��ʼ����������
	for (int i = 0; i < 3; ++i)
	{
		if (m_Battle_Enemy[i].id != -1)
			m_Battle_EnemyNum++;
	}
	m_Battle_EnemySelect = 0;

	//��ʼ������ս������
	m_EnemyTimer = 0;
	m_EnemyAttackSelect = 0;
	m_E_Attack_Animation = 0;
	m_E_ShowAttack = false;
	m_BaoJi = false;
	m_Miss = false;

	//��ʼ��ʤ������
	//��ʼ����������
	m_GetGold = 0;
	m_GetExp = 0;
	m_GetItemId = -1;
	m_LevelUp = 0;
	for (int i = 0; i < 3; ++i)
	{
		if (m_Battle_Enemy[i].id != -1)
		{
			m_GetGold += m_Battle_Enemy[i].Gold;
			m_GetExp += m_Battle_Enemy[i].Exp;
		}
	}
	//char buf[256];
	//sprintf_s(buf, 256, "Gold:%d,Exp:%d", m_GetGold, m_GetExp);
	//SetWindowText(pGF->GetHwnd(), buf);

	HeroData = (CScene_Data*)pGF->GetScene("���ݴ��泡��");

	GameSound.play(5);
}

void CScene_Attack::Run()
{
	//GameSound.Tick();

	GetEnemyData(); //���µ�������

	DrawBackBmp(); //����
	DrawState(); //����ͷ��Ѫ��
	DrawEnemy(); //����
	DrawHero(); //Ӣ��
	DrawHpBar(); //Ѫ��

	switch (m_Battle_Scene)
	{
	case _BATTLE_WAIT: 
		{
			DrawSelect(); //ѡ��ť

			if(pGF->GetGI()->Get(_GI_K_A) == _KS_DC && m_Select_X > 0)
				m_Select_X--;
			if(pGF->GetGI()->Get(_GI_K_D) == _KS_DC && m_Select_X < 2)
				m_Select_X++;

			if(pGF->GetGI()->Get(_GI_K_RETURN) == _KS_DC)
			{
				switch(m_Select_X)
				{
				case 0:
					{
						m_HeroAttackType = _TYPE_GJ;
						m_Battle_Scene = _BATTLE_SELECT;
						break;
					}
				case 1:
					{
						if (HeroData->Hero.YxHero.getMP() - 10 >= 0)
							m_Battle_Scene = _BATTLE_JN;
						else
						{
							MessageBox(pGF->GetHwnd(), "û���㹻��Mp�ͷż���!", 0, 0);
							m_Battle_Scene = _BATTLE_WAIT;
						}
						break;
					}
				case 2: //����
					{
						m_Battle_Scene = _BATTLE_ITEM;
						break;
					}
				}
			}
			//�ж�ս�����
			int TempNum = 0;
			for (int i = 0; i < 3; ++i)
			{
				if (m_Battle_Enemy[i].id != -1)
					TempNum++;
			}
			if (TempNum == 0)
			{
				//���ߵ��伸��
				m_GetItem = rand() % 100;
				if (m_GetItem < _GETITEM)
				{
					std::map<int, Item>::iterator i = HeroData->_ItemData.find(rand() % (int)HeroData->_ItemData.size());
					if (i != HeroData->_ItemData.end())
					{
						m_GetItemId = i->first;
						HeroData->AddItem(m_GetItemId);
					}
				}
				m_LevelUp = HeroData->Hero.YxHero.ExpAdd(m_GetExp);
				HeroData->Hero.YxHero.MoneyAdd(m_GetGold);
				m_Battle_Scene = _BATTLE_VICTORY;
			}

			break;
		}
	case _BATTLE_ITEM:
		{
			pGF->GetGO()->SetAlphaBlend(180, 30, 320, 420, 0, 0, 155, "Pic\\System\\Menu_Item.bmp");

			std::vector<Item>::iterator i = HeroData->Hero.YxHero.Dj.begin();
			int Site = 0;
			for (; i != HeroData->Hero.YxHero.Dj.end(); ++i, ++Site)
			{
				int cx = Site % 3 * 100 + 195;
				int cy = Site / 3 * 40 + 40;
				pGF->GetGO()->DrawText(i->name, cx, cy, RGB(255, 255, 255), "��������");
			}

			int c_x, c_y, c_i;
			pGF->GetGI()->GetCursorPosition(&c_x, &c_y);
			c_x = (c_x - 195) / 100;
			c_y = (c_y - 40) / 40;
			c_i = c_x + c_y * 3;

			int Temp_x, Temp_y;
			pGF->GetGI()->GetCursorPosition(&Temp_x, &Temp_y);
			if ((Temp_x > 180 && Temp_x < 500) && (Temp_y > 30 && Temp_y < 450))
			{
				//��ʾ
				if (c_i < (int)HeroData->Hero.YxHero.Dj.size())
				{
					std::vector<Item>::iterator i = HeroData->Hero.YxHero.Dj.begin();
					i += c_i;

					//ѡ��Ч��
					pGF->GetGO()->DrawText(i->name, c_i % 3 * 100 + 195, c_i / 3 * 40 + 40, RGB(255, 0, 0), "��������");	

					pGF->GetGO()->tDrawBmp(Temp_x, Temp_y, 200, 71, 0, 0, "Pic\\System\\Tips.bmp");
					pGF->GetGO()->DrawText(i->ItemText, Temp_x + 15, Temp_y + 20, RGB(255, 0, 0), "��Ϸ�˵�����");
					char buf[256];
					sprintf_s(buf, 256, "����:%d", i->ItemNum);
					pGF->GetGO()->DrawText(buf, Temp_x + 15, Temp_y + 40, RGB(255, 255, 255), "��Ϸ�˵�����");

					if (pGF->GetGI()->Get(_GI_M_L) == _KS_DC)
					{
						if (i->Type == 0) //�ж��ǵ��߻���װ��
						{
							HeroData->Hero.YxHero.HpAdd(i->HpAdd);
							HeroData->Hero.YxHero.MpAdd(i->MpAdd);

							if (i->ItemNum > 1)
								i->ItemNum -= 1;
							else
								i = HeroData->Hero.YxHero.Dj.erase(i);
						}
						//����װ�������ж���ʲôλ��װ��
						else
						{
							HeroData->AddEquip(i->id, i->Type);

							if (i->ItemNum > 1)
								i->ItemNum -= 1;
							else
								i = HeroData->Hero.YxHero.Dj.erase(i);
						}
					}
				}
			}

			if(pGF->GetGI()->Get(_GI_K_ESC) == _KS_DC)
				m_Battle_Scene = _BATTLE_WAIT;
			break;
		}
	case _BATTLE_JN: 
		{
			m_HeroAttackType = _TYPE_JN;
			//ShowCutIn();
			m_CutInTimer = 0;
			m_Battle_Scene = _BATTLE_SELECT;
			break;
		}
	case _BATTLE_SELECT: 
		{
			if(pGF->GetGI()->Get(_GI_K_ESC) == _KS_DC)
				m_Battle_Scene = _BATTLE_WAIT;

			if(pGF->GetGI()->Get(_GI_K_W) == _KS_DC && m_Battle_EnemySelect > 0)
				m_Battle_EnemySelect--;
			if(pGF->GetGI()->Get(_GI_K_S) == _KS_DC && m_Battle_EnemySelect < m_Battle_EnemyNum - 1)
				m_Battle_EnemySelect++;

			if(pGF->GetGI()->Get(_GI_K_RETURN) == _KS_DC && m_Battle_Enemy[m_Battle_EnemySelect].id != -1)
			{
				m_Battle_Scene = _BATTLE_ANIMATION;	

				CVector2D TempCenter; //�õ�Ŀ�������
				TempCenter.x = m_Battle_Enemy_XY[m_Battle_EnemySelect].x + 40;
				TempCenter.y = m_Battle_Enemy_XY[m_Battle_EnemySelect].y + 40;
				TempTest = TempCenter - m_HeroBattleMove;
				m_HeroBattleMoveGo = true;
			}

			pGF->GetGO()->tDrawBmp(
				220 - m_Battle_EnemySelect * 50,
				210 + m_Battle_EnemySelect * 40,
				32,
				32,
				0,
				0,
				"Pic\\System\\Menu1.bmp");

			break;
		}
	case _BATTLE_ANIMATION: 
		{
			if (m_HeroAttackType == _TYPE_JN)
				ShowCutIn();
			HeroMove(); //Ӣ���ƶ�
			DrawAttack(); //��������
			break;
		}
	case _BATTLE_ENEMY: 
		{
			EnemyAttack();
			break;
		}
	case _BATTLE_VICTORY: 
		{
			m_HeroBattle_Victory = _HERO_VICTORY;
			pGF->GetGO()->SetAlphaBlend(80, 110, 320, 259, 0, 0, 220, "Pic\\System\\Victory.bmp");
			char buf[256];
			sprintf_s(buf, 256, "Gold + %d", m_GetGold);
			pGF->GetGO()->DrawText(buf, 180, 200, RGB(255, 0, 0), "ʤ������");
			sprintf_s(buf, 256, "Exp + %d", m_GetExp);
			pGF->GetGO()->DrawText(buf, 180, 230, RGB(255, 0, 0), "ʤ������");

			//��ȡ�漴����
			if (m_GetItem < _GETITEM)
			{
				std::map<int, Item>::iterator i = HeroData->_ItemData.find(m_GetItemId);
				if (i != HeroData->_ItemData.end())		
				{
					sprintf_s(buf, 256, "�����:%s", i->second.name);
					pGF->GetGO()->DrawText(buf, 180, 270, RGB(255, 0, 0), "ʤ������");
				}
			}
			if (m_LevelUp == 1)
				pGF->GetGO()->tDrawBmp(368, 238, 96, 32, 0, 0, "Pic\\System\\Level.bmp", RGB(0, 0, 0));


			pGF->GetGO()->DrawText("����س������ص�ͼ!", 140, 330, RGB(255, 255, 255), "ʤ������");
			if(pGF->GetGI()->Get(_GI_K_RETURN) == _KS_DC)
			{
				if (!m_LastFight)
					pGF->SetCurScene("����2");
				else
					pGF->SetCurScene("��������");
			}
			break;
		}
	case _BATTLE_OVER:
		{
			m_HeroBattle_Victory = _HERO_DEAD;
			pGF->GetGO()->SetAlphaBlend(0, 0, pGF->GetW(), pGF->GetH(), 0, 0, 155, "Pic\\System\\GameOver.bmp");
			if(pGF->GetGI()->Get(_GI_K_RETURN) == _KS_DC)
				pGF->SetCurScene("����1");
			break;
		}
	}

	//if(pGF->GetGI()->Get(_GI_K_1) == _KS_DC)
	//	pGF->SetCurScene("����2");

	//���˹���Ч��
	DrawEnemyAttack();
}

void CScene_Attack::Quit()
{
	GameSound.Stop(2);
	GameSound.Stop(3);
	GameSound.Stop(5);
}

void CScene_Attack::SetData(int id, int Enemy1, int Enemy2, int Enemy3)
{
	m_Battle_BackBmp = id;

	//�ж��Ƿ�����ս
	if (Enemy1 == 9)
		m_LastFight = true;
	else
		m_LastFight = false;

	HeroData = (CScene_Data*)pGF->GetScene("���ݴ��泡��");

	std::map<int, Monster>::iterator i = HeroData->_MonsterData.find(Enemy1);
	if (i != HeroData->_MonsterData.end())
		m_Battle_Enemy[0] = i->second;
	else
		m_Battle_Enemy[0].id = -1;

	i = HeroData->_MonsterData.find(Enemy2);
	if (i != HeroData->_MonsterData.end())
		m_Battle_Enemy[1] = i->second;
	else
		m_Battle_Enemy[1].id = -1;

	i = HeroData->_MonsterData.find(Enemy3);
	if (i != HeroData->_MonsterData.end())
		m_Battle_Enemy[2] = i->second;
	else
		m_Battle_Enemy[2].id = -1;
}

void CScene_Attack::DrawBackBmp()
{
	char BackBmp[256];
	sprintf_s(BackBmp, 256, "Pic\\BattleBack\\%d.bmp", m_Battle_BackBmp);
	pGF->GetGO()->tDrawBmp(0, 0, pGF->GetW(), pGF->GetH(), 0, 0, BackBmp); //ս������
}

void CScene_Attack::DrawEnemy()
{
	for (int i = 0; i < 3; ++i)
	{
		if (m_Battle_Enemy[i].id != -1)
		{
			char Enemy[256];
			sprintf_s(Enemy, 256, "Pic\\Enemy\\%d.bmp", m_Battle_Enemy[i]);
			pGF->GetGO()->tDrawBmp((int)m_Battle_Enemy_XY[i].x, (int)m_Battle_Enemy_XY[i].y, 80, 80, 0, 0, Enemy); 

			//����
			pGF->GetGO()->DrawText(m_Battle_Enemy[i].name, (int)m_Battle_Enemy_XY[i].x - 80, (int)m_Battle_Enemy_XY[i].y, RGB(255, 255, 255), "Ѫ������");
			//����ֵ
			char buf[256];
			sprintf_s(buf, 256, "   %d", m_Battle_Enemy[i].Hp);
			pGF->GetGO()->DrawText(buf, (int)m_Battle_Enemy_XY[i].x - 80, (int)m_Battle_Enemy_XY[i].y +20, RGB(255, 255, 255), "Ѫ������");
		}
	}
}

void CScene_Attack::DrawHero()
{
	if (m_HeroBattle_PicTimer < 4)
		m_HeroBattle_PicTimer++;
	else
	{
		if (m_HeroBattle_Animation != 3)
			m_HeroBattle_Animation++;
		else
			m_HeroBattle_Animation = 0;
		m_HeroBattle_PicTimer = 0;
	}

	switch(m_HeroBattle_Victory)
	{
	case _HERO_NORMAL:
		{
			pGF->GetGO()->tDrawBmp((int)m_HeroBattleMove.x, (int)m_HeroBattleMove.y, 32, 32, m_HeroBattle_Animation * 32, 0, "Pic\\Hero\\1.bmp"); //Ӣ��
			break;
		}
	case _HERO_VICTORY:
		{
			pGF->GetGO()->tDrawBmp((int)m_HeroBattleMove.x, (int)m_HeroBattleMove.y, 32, 32, m_HeroBattle_Animation * 32, 0, "Pic\\Hero\\4.bmp"); //Ӣ��
			break;
		}
	case _HERO_DEAD:
		{
			pGF->GetGO()->tDrawBmp((int)m_HeroBattleMove.x, (int)m_HeroBattleMove.y, 32, 32, m_HeroBattle_Animation * 32, 0, "Pic\\Hero\\5.bmp"); //Ӣ��
			break;
		}
	}
}

void CScene_Attack::DrawHeroShadow() //��Ӱ
{
	pGF->GetGO()->tDrawBmp((int)m_HeroBattleMove.x + 20, (int)m_HeroBattleMove.y, 32, 32, m_HeroBattle_Animation * 32, 0, "Pic\\Hero\\Shadow\\4.bmp"); //Ӣ��
	pGF->GetGO()->tDrawBmp((int)m_HeroBattleMove.x + 16, (int)m_HeroBattleMove.y, 32, 32, m_HeroBattle_Animation * 32, 0, "Pic\\Hero\\Shadow\\3.bmp"); //Ӣ��
	pGF->GetGO()->tDrawBmp((int)m_HeroBattleMove.x + 12, (int)m_HeroBattleMove.y, 32, 32, m_HeroBattle_Animation * 32, 0, "Pic\\Hero\\Shadow\\2.bmp"); //Ӣ��
	pGF->GetGO()->tDrawBmp((int)m_HeroBattleMove.x + 8, (int)m_HeroBattleMove.y, 32, 32, m_HeroBattle_Animation * 32, 0, "Pic\\Hero\\Shadow\\1.bmp"); //Ӣ��
	pGF->GetGO()->tDrawBmp((int)m_HeroBattleMove.x + 4, (int)m_HeroBattleMove.y, 32, 32, m_HeroBattle_Animation * 32, 0, "Pic\\Hero\\Shadow\\0.bmp"); //Ӣ��
}

void CScene_Attack::DrawState()
{
	pGF->GetGO()->tDrawBmp(400, 20, 220, 230, 0, 0, "Pic\\Hero\\2.bmp"); //ͷ��

	pGF->GetGO()->tDrawBmp(440, 185, 24, 24, 0, 0, "Pic\\System\\Attack.bmp"); //����
	pGF->GetGO()->tDrawBmp(470, 185, 24, 24, 0, 0, "Pic\\System\\Magic.bmp"); //ħ��
	pGF->GetGO()->tDrawBmp(500, 185, 24, 24, 0, 0, "Pic\\System\\Item.bmp"); //��Ʒ

	pGF->GetGO()->DrawText(HeroData->Hero.YxHero.getName(), 360, 130, RGB(255, 255, 255), "�Ի�����");
}

void CScene_Attack::DrawSelect()
{
	if (m_Select_PicTimer < 4)
		m_Select_PicTimer++;
	else
	{
		if (m_Select_Animation != 1)
			m_Select_Animation++;
		else
			m_Select_Animation = 0;
		m_Select_PicTimer = 0;
	}
	pGF->GetGO()->tDrawBmp(440 + m_Select_X * 30, 210, 24, 24, m_Select_Animation * 24, 0, "Pic\\System\\Select.bmp"); 
}

void CScene_Attack::DrawAttack()
{
	switch (m_HeroAttackType)
	{
	case _TYPE_GJ:
		{
			if (m_ShowAttack)
			{
				if (m_Attack_Animation != 5)
					m_Attack_Animation++;
				else
					m_Attack_Animation = 0;

				if (m_BaoJi) //�ж��Ƿ񱩻�
				{
					if (HeroData->Hero.YxHero.getGongJiLi() * 2 - m_Battle_Enemy[m_Battle_EnemySelect].Def < 1)
					{
						char buf[256];
						sprintf_s(buf, 256, "δ�Ʒ�:-%d", 1);
						pGF->GetGO()->DrawText(buf, 
							(int)m_Battle_Enemy_XY[m_Battle_EnemySelect].x,
							(int)m_Battle_Enemy_XY[m_Battle_EnemySelect].y, 
							RGB(255, 0, 0),
							"�˺�����");
					}
					else
					{
						char buf[256];
						sprintf_s(buf, 256, "����:-%d", HeroData->Hero.YxHero.getGongJiLi() * 2 - m_Battle_Enemy[m_Battle_EnemySelect].Def);
						pGF->GetGO()->DrawText(buf, 
							(int)m_Battle_Enemy_XY[m_Battle_EnemySelect].x,
							(int)m_Battle_Enemy_XY[m_Battle_EnemySelect].y, 
							RGB(255, 0, 0),
							"�˺�����");
					}
				}
				else
				{
					if (HeroData->Hero.YxHero.getGongJiLi() - m_Battle_Enemy[m_Battle_EnemySelect].Def < 1)
					{
						char buf[256];
						sprintf_s(buf, 256, "δ�Ʒ�:-%d", 1);
						pGF->GetGO()->DrawText(buf, 
							(int)m_Battle_Enemy_XY[m_Battle_EnemySelect].x,
							(int)m_Battle_Enemy_XY[m_Battle_EnemySelect].y, 
							RGB(255, 0, 0),
							"�˺�����");
					}
					else
					{
						char buf[256];
						sprintf_s(buf, 256, "-%d", HeroData->Hero.YxHero.getGongJiLi() - m_Battle_Enemy[m_Battle_EnemySelect].Def);
						pGF->GetGO()->DrawText(buf, 
							(int)m_Battle_Enemy_XY[m_Battle_EnemySelect].x,
							(int)m_Battle_Enemy_XY[m_Battle_EnemySelect].y, 
							RGB(255, 0, 0),
							"�˺�����");
					}
				}

				pGF->GetGO()->tDrawBmp((int)m_Battle_Enemy_XY[m_Battle_EnemySelect].x, (int)m_Battle_Enemy_XY[m_Battle_EnemySelect].y - 20, 96, 96, m_Attack_Animation * 96, 0, "Pic\\System\\Attack\\0.bmp"); 
			}

			if (m_Attack_Animation == 5 && m_ShowAttack == true) //���ù�������
			{
				m_ShowAttack = false;
				if (m_BaoJi)
				{
					if (HeroData->Hero.YxHero.getGongJiLi() * 2 - m_Battle_Enemy[m_Battle_EnemySelect].Def < 1)
						m_Battle_Enemy[m_Battle_EnemySelect].Hp -= 1;
					else
						m_Battle_Enemy[m_Battle_EnemySelect].Hp -= HeroData->Hero.YxHero.getGongJiLi() * 2 - m_Battle_Enemy[m_Battle_EnemySelect].Def ;
				}
				else
				{
					if (HeroData->Hero.YxHero.getGongJiLi() - m_Battle_Enemy[m_Battle_EnemySelect].Def < 1)
						m_Battle_Enemy[m_Battle_EnemySelect].Hp -= 1;
					else
						m_Battle_Enemy[m_Battle_EnemySelect].Hp -= HeroData->Hero.YxHero.getGongJiLi() - m_Battle_Enemy[m_Battle_EnemySelect].Def ;
				}

				if(m_Battle_Enemy[m_Battle_EnemySelect].Hp <= 0)
					m_Battle_Enemy[m_Battle_EnemySelect].id = -1;

				GameSound.play(2);
			}
			break;
		}
	case _TYPE_JN:
		{
			if (m_ShowAttack)
			{
				if (m_Attack_Animation != 13)
					m_Attack_Animation++;
				else
					m_Attack_Animation = 0;


				if (HeroData->Hero.YxHero.getGongJiLi() + HeroData->Hero.YxHero.getMag() - m_Battle_Enemy[m_Battle_EnemySelect].Def < 1)
				{
					char buf[256];
					sprintf_s(buf, 256, "δ�Ʒ�:-%d", 1);
					pGF->GetGO()->DrawText(buf, 
						(int)m_Battle_Enemy_XY[m_Battle_EnemySelect].x,
						(int)m_Battle_Enemy_XY[m_Battle_EnemySelect].y, 
						RGB(255, 0, 0),
						"�˺�����");
				}
				else
				{
					char buf[256];
					//�˺�Ϊ����+ħ��
					sprintf_s(buf, 256, "-%d", HeroData->Hero.YxHero.getGongJiLi() + HeroData->Hero.YxHero.getMag() - m_Battle_Enemy[m_Battle_EnemySelect].Def);
					pGF->GetGO()->DrawText(buf, 
						(int)m_Battle_Enemy_XY[m_Battle_EnemySelect].x,
						(int)m_Battle_Enemy_XY[m_Battle_EnemySelect].y, 
						RGB(255, 0, 0),
						"�˺�����");
				}

				pGF->GetGO()->tDrawBmp((int)m_Battle_Enemy_XY[m_Battle_EnemySelect].x, (int)m_Battle_Enemy_XY[m_Battle_EnemySelect].y - 20, 96, 96, m_Attack_Animation * 96, 0, "Pic\\System\\Attack\\1.bmp"); 
			}

			if (m_Attack_Animation == 13 && m_ShowAttack == true) //���ù�������
			{
				m_ShowAttack = false;
				if (HeroData->Hero.YxHero.getGongJiLi() + HeroData->Hero.YxHero.getMag() - m_Battle_Enemy[m_Battle_EnemySelect].Def < 1)
					m_Battle_Enemy[m_Battle_EnemySelect].Hp -= 1;
				else
					m_Battle_Enemy[m_Battle_EnemySelect].Hp -= HeroData->Hero.YxHero.getGongJiLi() + HeroData->Hero.YxHero.getMag() - m_Battle_Enemy[m_Battle_EnemySelect].Def;
				HeroData->Hero.YxHero.MpAdd(-10);

				if(m_Battle_Enemy[m_Battle_EnemySelect].Hp <= 0)
					m_Battle_Enemy[m_Battle_EnemySelect].id = -1;

				GameSound.play(3);
			}
			break;
		}
	}
}

void CScene_Attack::DrawHpBar()
{
	if (m_HpBar_Animation + 10 > 640 - 128)
		m_HpBar_Animation = 0;
	else
		m_HpBar_Animation += 10;

	int DarwX, DrawY;
	DarwX = 290;
	DrawY = 160;

	double ShowHp = (double)HeroData->Hero.YxHero.getHP() / HeroData->Hero.YxHero.getMaxHP();
	pGF->GetGO()->tDrawBmp(DarwX, DrawY, (int)(128 * ShowHp), 7, m_HpBar_Animation, 0, "Pic\\System\\1.bmp"); 
	pGF->GetGO()->tDrawBmp(DarwX, DrawY, (int)(128 * ShowHp), 7, m_HpBar_Animation - 640 - 128, 0, "Pic\\System\\1.bmp"); 

	double ShowMp = (double)HeroData->Hero.YxHero.getMP() / HeroData->Hero.YxHero.getMaxMP();

	pGF->GetGO()->tDrawBmp(DarwX, DrawY + 15, (int)(128 * ShowMp), 7, m_HpBar_Animation, 0, "Pic\\System\\3.bmp"); 
	pGF->GetGO()->tDrawBmp(DarwX, DrawY + 15, (int)(128 * ShowMp), 7, m_HpBar_Animation - 640 - 128, 0, "Pic\\System\\3.bmp"); 	

	//�߿�
	pGF->GetGO()->tDrawBmp(DarwX - 2, DrawY - 2, 132, 11, 0, 0, "Pic\\System\\2.bmp"); 
	pGF->GetGO()->tDrawBmp(DarwX - 2, DrawY + 13, 132, 11, 0, 0, "Pic\\System\\2.bmp"); 
}

void CScene_Attack::GetEnemyData()
{
	//���ݵ���������ʼ������������
	for (int i = 0; i < 3; ++i)
	{
		if (m_Battle_Enemy[i].id != -1)
		{
			m_Battle_Enemy_XY[i].x = (float)220 - i * 50;
			m_Battle_Enemy_XY[i].y = (float)210 + i * 40;
		}
	}
}

void CScene_Attack::HeroMove()
{
	if (m_HeroBattleMoveGo == true && 
		m_HeroBattleMove.x > m_Battle_Enemy_XY[m_Battle_EnemySelect].x + 80)
	{
		DrawHeroShadow();
		m_HeroBattleMove.x += 10 * TempTest.Normalize().x;
		m_HeroBattleMove.y += 10 * TempTest.Normalize().y;
	}
	else if (m_HeroBattleMove.x <= m_Battle_Enemy_XY[m_Battle_EnemySelect].x + 80)
	{
		m_HeroBattleMove.x -= 5 * TempTest.Normalize().x;
		m_HeroBattleMove.y -= 5 * TempTest.Normalize().y;
		m_HeroBattleMoveGo = false;

		if (m_ShowAttack == false)
		{
			//�жϱ���
			if (rand() % 100 < HeroData->Hero.YxHero.getCritical())
				m_BaoJi = true;
			else
				m_BaoJi = false;
		}

		m_ShowAttack = true;
		m_Attack_Animation = 0;
	}
	else if (m_HeroBattleMoveGo == false && m_HeroBattleMove.x < 400)
	{
		m_HeroBattleMove.x -= 5 * TempTest.Normalize().x;
		m_HeroBattleMove.y -= 5 * TempTest.Normalize().y;
	}
	else
	{
		m_HeroBattleMove.x = 400;
		m_HeroBattleMove.y = 270;

		m_Battle_Scene = _BATTLE_ENEMY;
	}
}

void CScene_Attack::EnemyAttack()
{
	bool EnemyAttack[3] = {false, false, false};

	for (int i = 0; i < 3; ++i)
	{
		if (m_Battle_Enemy[i].id != -1) //���
			EnemyAttack[i] = true;
	}

	if (m_EnemyTimer < 10 && EnemyAttack[m_EnemyAttackSelect])
	{
		m_EnemyTimer += 1;
	}
	else if (m_EnemyTimer == 10 && EnemyAttack[m_EnemyAttackSelect])
	{
		//�ж�����
		if (rand() % 100 < HeroData->Hero.YxHero.getMiss())
			m_Miss = true;
		else
			m_Miss = false;

		m_E_ShowAttack = true;
		m_EnemyTimer += 1;
	}
	else if (m_EnemyTimer < 30 && EnemyAttack[m_EnemyAttackSelect])
	{
		m_EnemyTimer += 1;
		if (EnemyAttack[m_EnemyAttackSelect])
		{
			pGF->GetGO()->DrawText("Attack!!", 
				(int)m_Battle_Enemy_XY[m_EnemyAttackSelect].x,
				(int)m_Battle_Enemy_XY[m_EnemyAttackSelect].y, 
				RGB(255, 0, 0));
			if (m_Miss)
			{
				pGF->GetGO()->DrawText("Miss!", 
					390,
					145, 
					RGB(255, 0, 0),
					"�˺�����");
			}
			else
			{
				if (m_Battle_Enemy[m_EnemyAttackSelect].Atk - HeroData->Hero.YxHero.getFangYuLi() < 1)
				{
					char buf[256];
					sprintf_s(buf, 256, "δ�Ʒ�:-%d", 1);
					pGF->GetGO()->DrawText(buf, 
						390,
						145, 
						RGB(255, 0, 0),
						"�˺�����");
				}
				else
				{
					char buf[256];
					sprintf_s(buf, 256, "-%d", m_Battle_Enemy[m_EnemyAttackSelect].Atk - HeroData->Hero.YxHero.getFangYuLi());
					pGF->GetGO()->DrawText(buf, 
						390,
						145, 
						RGB(255, 0, 0),
						"�˺�����");
				}					
			}
		}
	}
	else
	{
		if (EnemyAttack[m_EnemyAttackSelect]) //������ʧ
		{
			if (!m_Miss)
			{
				if (m_Battle_Enemy[m_EnemyAttackSelect].Atk - HeroData->Hero.YxHero.getFangYuLi() < 1)
					HeroData->Hero.YxHero.HpAdd(-1);
				else
					HeroData->Hero.YxHero.HpAdd(-(m_Battle_Enemy[m_EnemyAttackSelect].Atk - HeroData->Hero.YxHero.getFangYuLi()));
			}
		}

		EnemyAttack[m_EnemyAttackSelect] = false;
		m_EnemyAttackSelect++;
		m_EnemyTimer = 0;

		if (HeroData->Hero.YxHero.getHP() <= 0) //����
			m_Battle_Scene = _BATTLE_OVER;
		else if (m_EnemyAttackSelect == m_Battle_EnemyNum)
		{
			m_Battle_Scene = _BATTLE_WAIT;
			m_EnemyAttackSelect = 0;
		}
	}
}

void CScene_Attack::DrawEnemyAttack()
{
	if (m_E_ShowAttack)
	{
		if (m_E_Attack_Animation != 5)
			m_E_Attack_Animation++;
		else
			m_E_Attack_Animation = 0;

		pGF->GetGO()->tDrawBmp(380, 220, 96, 96, m_E_Attack_Animation * 96, 0, "Pic\\System\\Attack\\0.bmp"); 
	}

	if (m_E_Attack_Animation == 5) //���ù�������
		m_E_ShowAttack = false;
}

void CScene_Attack::ShowCutIn()
{
	if (m_CutInTimer < 15)
	{
		m_CutInTimer++;
		int TempAlpha;
		if (m_CutInTimer < 10)
			TempAlpha = m_CutInTimer * 25;
		else
			TempAlpha = 255;

		pGF->GetGO()->SetAlphaBlend(0, 50, 640, 169, 0, 0, TempAlpha, "Pic\\System\\Attack\\2.bmp");
	}
}
