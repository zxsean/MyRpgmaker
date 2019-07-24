#include "Scene_Game_Menu.h"

void CScene_Game_Menu::Init()
{
	pGF = CGameFrame::GetObject();

	//字体
	pGF->GetGO()->CreateFont(20, "微软雅黑", "游戏菜单字体");
	pGF->GetGO()->CreateFont(30, "微软雅黑", "游戏菜单字体2");
	pGF->GetGO()->CreateFont(22, "微软雅黑", "道具字体");
	m_Cursor_Pic = 0;
	m_Cursor_PicTimer = 0;
	m_Cursor_Y = 0;

	m_Menu = _MENU_WAIT;

	m_HeroBattle_PicTimer = 0;
	m_HeroBattle_Animation = 0;

	m_HpBar_Animation = 0;
}

void CScene_Game_Menu::Enter()
{
	HeroData = (CScene_Data*)pGF->GetScene("数据储存场景");
}

void CScene_Game_Menu::Run()
{
	DrawBackBmp();

	switch (m_Menu)
	{
	case _MENU_WAIT:
		{
			DrawHand();

			if(pGF->GetGI()->Get(_GI_K_S) == _KS_DC && m_Cursor_Y < 3)
			{
				m_Cursor_Y++;
				GameSound.play(4);
			}
			if(pGF->GetGI()->Get(_GI_K_W) == _KS_DC && m_Cursor_Y > 0)
			{
				m_Cursor_Y--;
				GameSound.play(4);
			}
			if(pGF->GetGI()->Get(_GI_K_RETURN) == _KS_DC)
			{
				switch (m_Cursor_Y)
				{
				case 0: m_Menu = _MENU_STATE; break;
				case 1: m_Menu = _MENU_ITEM; break;
				case 2: m_Menu = _MENU_EQUIP; break;
				case 3: m_Menu = _MENU_MISSION; break;
				}
			}

			if(pGF->GetGI()->Get(_GI_K_ESC) == _KS_DC)
				pGF->SetCurScene("场景2");
			break;
		}
	case _MENU_STATE:
		{
			if(pGF->GetGI()->Get(_GI_K_ESC) == _KS_DC)
				m_Menu = _MENU_WAIT;
			DrawState();
			break;
		}
	case _MENU_ITEM:
		{
			if(pGF->GetGI()->Get(_GI_K_ESC) == _KS_DC)
				m_Menu = _MENU_WAIT;
			DrawItem();
			break;
		}
	case _MENU_EQUIP:
		{
			if(pGF->GetGI()->Get(_GI_K_ESC) == _KS_DC)
				m_Menu = _MENU_WAIT;
			DrawEquip();
			break;
		}
	case _MENU_MISSION:
		{
			if(pGF->GetGI()->Get(_GI_K_ESC) == _KS_DC)
				m_Menu = _MENU_WAIT;

			int c_i = 0;
			std::map<int, Mission>::iterator i = HeroData->Hero._Doing_Things.begin();
			for (; i != HeroData->Hero._Doing_Things.end(); ++i, c_i++)
			{
				int c_x = c_i % 1 * 100 + 300;
				int c_y = c_i / 1 * 40 + 100;
				pGF->GetGO()->DrawText(i->second.MissionText, c_x, c_y, RGB(0, 0, 0), "游戏菜单字体2");
			}

			break;
		}
	}
}

void CScene_Game_Menu::Quit()
{
}

void CScene_Game_Menu::DrawBackBmp()
{
	pGF->GetGO()->DrawBmp(
		0,
		0, 
		pGF->GetW(),
		pGF->GetH(),
		0,
		0,
		"Pic\\System\\Menu.bmp");
}

void CScene_Game_Menu::DrawHand()
{
	pGF->GetGO()->tDrawBmp(
		25,
		263 + m_Cursor_Y * 50, 
		32,
		32,
		m_Cursor_Pic * 32,
		0,
		"Pic\\System\\Menu1.bmp");

	if (m_Cursor_PicTimer < 2)
	{
		m_Cursor_PicTimer++;
	}
	else
	{
		if (m_Cursor_Pic != 2)
			m_Cursor_Pic++;
		else
			m_Cursor_Pic = 0;
		m_Cursor_PicTimer = 0;
	}
}

void CScene_Game_Menu::DrawState()
{
	pGF->GetGO()->tDrawBmp(450, 20, 114, 270, 0, 0, "Pic\\System\\Hero.bmp");

	//英雄小人图
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
	pGF->GetGO()->tDrawBmp(491, 276, 32, 32, m_HeroBattle_Animation * 32, 0, "Pic\\Hero\\3.bmp"); //英雄

	//血条
	if (m_HpBar_Animation + 10 > 640 - 128)
		m_HpBar_Animation = 0;
	else
		m_HpBar_Animation += 10;

	int DarwX, DrawY;
	DarwX = 300;
	DrawY = 200;

	double ShowHp = (double)HeroData->Hero.YxHero.getHP() / HeroData->Hero.YxHero.getMaxHP();

	pGF->GetGO()->tDrawBmp(DarwX, DrawY, (int)(128 * ShowHp), 7, m_HpBar_Animation, 0, "Pic\\System\\1.bmp"); 
	pGF->GetGO()->tDrawBmp(DarwX, DrawY, (int)(128 * ShowHp), 7, m_HpBar_Animation - 640 - 128, 0, "Pic\\System\\1.bmp"); 

	double ShowMp = (double)HeroData->Hero.YxHero.getMP() / HeroData->Hero.YxHero.getMaxMP();

	pGF->GetGO()->tDrawBmp(DarwX, DrawY + 38, (int)(128 * ShowMp), 7, m_HpBar_Animation, 0, "Pic\\System\\3.bmp"); 
	pGF->GetGO()->tDrawBmp(DarwX, DrawY + 38, (int)(128 * ShowMp), 7, m_HpBar_Animation - 640 - 128, 0, "Pic\\System\\3.bmp"); 	

	//边框
	pGF->GetGO()->tDrawBmp(DarwX - 2, DrawY - 2, 132, 11, 0, 0, "Pic\\System\\2.bmp"); 
	pGF->GetGO()->tDrawBmp(DarwX - 2, DrawY + 36, 132, 11, 0, 0, "Pic\\System\\2.bmp"); 

	//姓名
	pGF->GetGO()->DrawText(HeroData->Hero.YxHero.getName(), DarwX + 30, DrawY - 60, RGB(0, 0, 0),"游戏菜单字体2");
	//等级
	char buf[256];
	sprintf_s(buf, 256, "Lv: %d", HeroData->Hero.YxHero.getLevel());
	pGF->GetGO()->DrawText(buf, DarwX + 25, DrawY - 35, RGB(0, 0, 0),"游戏菜单字体2");
	//Hp
	pGF->GetGO()->DrawText("HP:", DarwX - 30, DrawY - 8, RGB(255, 0, 0),"游戏菜单字体");
	sprintf_s(buf, 256, "%d / %d", HeroData->Hero.YxHero.getHP(), HeroData->Hero.YxHero.getMaxHP());
	pGF->GetGO()->DrawText(buf, DarwX + 30, DrawY + 10, RGB(100, 0, 100),"游戏菜单字体");

	//Mp
	pGF->GetGO()->DrawText("MP:", DarwX - 30, DrawY + 30, RGB(255, 0, 0),"游戏菜单字体");
	sprintf_s(buf, 256, "%d / %d", HeroData->Hero.YxHero.getMP(), HeroData->Hero.YxHero.getMaxMP());
	pGF->GetGO()->DrawText(buf, DarwX + 30, DrawY + 48, RGB(100, 0, 100),"游戏菜单字体");

	//攻击
	pGF->GetGO()->DrawText("ATK:", DarwX - 30, DrawY + 68, RGB(255, 0, 0),"游戏菜单字体");
	sprintf_s(buf, 256, "%d", HeroData->Hero.YxHero.getGongJiLi());
	pGF->GetGO()->DrawText(buf, DarwX + 30, DrawY + 68, RGB(100, 0, 100),"游戏菜单字体");

	//防御
	pGF->GetGO()->DrawText("DEF:", DarwX - 30, DrawY + 88, RGB(255, 0, 0),"游戏菜单字体");
	sprintf_s(buf, 256, "%d", HeroData->Hero.YxHero.getFangYuLi());
	pGF->GetGO()->DrawText(buf, DarwX + 30, DrawY + 88, RGB(100, 0, 100),"游戏菜单字体");

	//敏捷
	pGF->GetGO()->DrawText("AGI:", DarwX - 30, DrawY + 108, RGB(255, 0, 0),"游戏菜单字体");
	sprintf_s(buf, 256, "%d", HeroData->Hero.YxHero.getAgi());
	pGF->GetGO()->DrawText(buf, DarwX + 30, DrawY + 108, RGB(100, 0, 100),"游戏菜单字体");

	//躲闪
	pGF->GetGO()->DrawText("MIS:", DarwX - 30, DrawY + 128, RGB(255, 0, 0),"游戏菜单字体");
	sprintf_s(buf, 256, "%d %%", HeroData->Hero.YxHero.getMiss());
	pGF->GetGO()->DrawText(buf, DarwX + 30, DrawY + 128, RGB(100, 0, 100),"游戏菜单字体");

	//暴击
	pGF->GetGO()->DrawText("CRI:", DarwX - 30, DrawY + 148, RGB(255, 0, 0),"游戏菜单字体");
	sprintf_s(buf, 256, "%d %%", HeroData->Hero.YxHero.getCritical());
	pGF->GetGO()->DrawText(buf, DarwX + 30, DrawY + 148, RGB(100, 0, 100),"游戏菜单字体");

	//魔力
	pGF->GetGO()->DrawText("MAG:", DarwX - 30, DrawY + 168, RGB(255, 0, 0),"游戏菜单字体");
	sprintf_s(buf, 256, "%d", HeroData->Hero.YxHero.getMag());
	pGF->GetGO()->DrawText(buf, DarwX + 30, DrawY + 168, RGB(100, 0, 100),"游戏菜单字体");

	//经验值
	pGF->GetGO()->DrawText("EXP:", DarwX - 30, DrawY + 188, RGB(255, 0, 0),"游戏菜单字体");
	sprintf_s(buf, 256, "%d / %d", HeroData->Hero.YxHero.getExp(), HeroData->Hero.YxHero.getMaxExp());
	pGF->GetGO()->DrawText(buf, DarwX + 30, DrawY + 188, RGB(100, 0, 100),"游戏菜单字体");

	//金币
	pGF->GetGO()->DrawText("Gold:", DarwX - 30, DrawY + 208, RGB(255, 0, 0),"游戏菜单字体");
	sprintf_s(buf, 256, "%dG", HeroData->Hero.YxHero.getMoney());
	pGF->GetGO()->DrawText(buf, DarwX + 30, DrawY + 208, RGB(100, 0, 100),"游戏菜单字体");
}

void CScene_Game_Menu::DrawItem()
{
	pGF->GetGO()->SetAlphaBlend(180, 30, 320, 420, 0, 0, 155, "Pic\\System\\Menu_Item.bmp");

	std::vector<Item>::iterator i = HeroData->Hero.YxHero.Dj.begin();
	int Site = 0;
	for (; i != HeroData->Hero.YxHero.Dj.end(); ++i, ++Site)
	{
		int cx = Site % 3 * 100 + 195;
		int cy = Site / 3 * 40 + 40;
		pGF->GetGO()->DrawText(i->name, cx, cy, RGB(255, 255, 255), "道具字体");
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
		//显示
		if (c_i < (int)HeroData->Hero.YxHero.Dj.size())
		{
			std::vector<Item>::iterator i = HeroData->Hero.YxHero.Dj.begin();
			i += c_i;

			//选中效果
			pGF->GetGO()->DrawText(i->name, c_i % 3 * 100 + 195, c_i / 3 * 40 + 40, RGB(255, 0, 0), "道具字体");	

			pGF->GetGO()->tDrawBmp(Temp_x, Temp_y, 200, 71, 0, 0, "Pic\\System\\Tips.bmp");
			pGF->GetGO()->DrawText(i->ItemText, Temp_x + 15, Temp_y + 20, RGB(255, 0, 0), "游戏菜单字体");
			char buf[256];
			sprintf_s(buf, 256, "数量:%d", i->ItemNum);
			pGF->GetGO()->DrawText(buf, Temp_x + 15, Temp_y + 40, RGB(255, 255, 255), "游戏菜单字体");

			if (pGF->GetGI()->Get(_GI_M_L) == _KS_DC)
			{
				if (i->Type == 0) //判断是道具还是装备
				{
					HeroData->Hero.YxHero.HpAdd(i->HpAdd);
					HeroData->Hero.YxHero.MpAdd(i->MpAdd);

					if (i->ItemNum > 1)
						i->ItemNum -= 1;
					else
						i = HeroData->Hero.YxHero.Dj.erase(i);
				}
				//根据装备属性判断是什么位置装备
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
}

void CScene_Game_Menu::DrawEquip()
{
	pGF->GetGO()->tDrawBmp(450, 20, 114, 270, 0, 0, "Pic\\System\\Hero.bmp");

	//英雄小人图
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
	pGF->GetGO()->tDrawBmp(491, 276, 32, 32, m_HeroBattle_Animation * 32, 0, "Pic\\Hero\\3.bmp"); //英雄

	int DrawX,DrawY;
	DrawX = 250;
	DrawY = 250;

	if (HeroData->Hero.YxHero.GetEquip_W() != -1)
	{
		std::map<int, Item>::iterator i = HeroData->_ItemData.find(HeroData->Hero.YxHero.GetEquip_W());
		if (i != HeroData->_ItemData.end())
		{
			char buf[256];
			sprintf_s(buf, 256, "武器: %s", i->second.name);
			pGF->GetGO()->DrawText(buf, DrawX, DrawY, RGB(255, 0, 0), "游戏菜单字体2");
		}
	}
	else
		pGF->GetGO()->DrawText("武器: 未装备", DrawX, DrawY, RGB(255, 0, 0), "游戏菜单字体2");
	pGF->GetGO()->tDrawBmp(DrawX - 60, DrawY - 20, 60, 60, 0, 0, "Pic\\System\\Equip\\W.bmp");

	if (HeroData->Hero.YxHero.GetEquip_F() != -1)
	{
		std::map<int, Item>::iterator i = HeroData->_ItemData.find(HeroData->Hero.YxHero.GetEquip_F());
		if (i != HeroData->_ItemData.end())
		{
			char buf[256];
			sprintf_s(buf, 256, "护甲: %s", i->second.name);
			pGF->GetGO()->DrawText(buf, DrawX, DrawY + 60, RGB(255, 0, 0), "游戏菜单字体2");
		}
	}
	else
		pGF->GetGO()->DrawText("护甲: 未装备", DrawX, DrawY + 60, RGB(255, 0, 0), "游戏菜单字体2");
	pGF->GetGO()->tDrawBmp(DrawX - 60, DrawY + 40, 60, 60, 0, 0, "Pic\\System\\Equip\\F.bmp");

	if (HeroData->Hero.YxHero.GetEquip_P() != -1)
	{
		std::map<int, Item>::iterator i = HeroData->_ItemData.find(HeroData->Hero.YxHero.GetEquip_P());
		if (i != HeroData->_ItemData.end())
		{
			char buf[256];
			sprintf_s(buf, 256, "饰品: %s", i->second.name);
			pGF->GetGO()->DrawText(buf, DrawX, DrawY + 120, RGB(255, 0, 0), "游戏菜单字体2");
		}
	}
	else
		pGF->GetGO()->DrawText("饰品: 未装备", DrawX, DrawY + 120, RGB(255, 0, 0), "游戏菜单字体2");
	pGF->GetGO()->tDrawBmp(DrawX - 60, DrawY + 100, 60, 60, 0, 0, "Pic\\System\\Equip\\P.bmp");

	int c_x, c_y, c_i;
	pGF->GetGI()->GetCursorPosition(&c_x, &c_y);
	c_x = (c_x - 250) / 100;
	c_y = (c_y - 250) / 60;
	c_i = c_x + c_y * 1;

	int Temp_x, Temp_y;
	pGF->GetGI()->GetCursorPosition(&Temp_x, &Temp_y);
	if ((Temp_x > 250 && Temp_x < 350) && (Temp_y > 250 && Temp_y < 430))
	{
		if (c_i < 3)
		{
			if (pGF->GetGI()->Get(_GI_M_L) == _KS_DC)
			{
				//char buf[32];
				//sprintf_s(buf, 32, "%d,%d,%d", c_x,c_y,c_i);
				//SetWindowText(pGF->GetHwnd(), buf);
				switch (c_i)
				{
				case 0: //武器
					{
						if (HeroData->Hero.YxHero.GetEquip_W() != -1)
							HeroData->EraseEquip(HeroData->Hero.YxHero.GetEquip_W(), 1);
						break;
					}
				case 1: //护甲
					{
						if (HeroData->Hero.YxHero.GetEquip_F() != -1)
							HeroData->EraseEquip(HeroData->Hero.YxHero.GetEquip_F(), 2);
						break;
					}
				case 2: //饰品
					{
						if (HeroData->Hero.YxHero.GetEquip_P() != -1)
							HeroData->EraseEquip(HeroData->Hero.YxHero.GetEquip_P(), 3);
						break;
					}
				}
			}
		}
	}
}
