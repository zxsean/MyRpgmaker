#include "Scene_Data.h"
#include "File\LoadTalkINI.h"
#include "File\Enemy.h"
#include "File\LoadItemINI.h"
#include "File\LoadMissionINI.h"
#include "File\LoadMapINI.h"

void CScene_Data::Init()
{
	LoadTalkData();
	LoadEnemyData();
	LoadItemData();
	LoadMission();
	LoadYuDiData();
}

void CScene_Data::Run()
{
}

void CScene_Data::LoadTalkData()
{
	int Len = LoadTalkini();
	for (int i = 0; i < Len; ++i)
		_TalkData.insert(std::pair<int, Type_Talk>(TalkData[i].id, TalkData[i]));

	////以下为测试对话代码
	//std::map<int, Type_Talk>::iterator i = _TalkData.begin();
	//char buf[32];
	//sprintf_s(buf, 32, "共%d句台词,%d",Len,_TalkData.size());
	//MessageBox(0,i->second.talk,0,0);
	//MessageBox(0,i->second.talk,0,0);
}

void CScene_Data::LoadEnemyData()
{
	int Len = LoadEnemyini();
	for (int i = 0; i < Len; ++i)
		_MonsterData.insert(std::pair<int, Monster>(MonsterData[i].id, MonsterData[i]));
}

void CScene_Data::LoadItemData()
{
	int Len = LoadItemini();
	for (int i = 0; i < Len;++i)
		_ItemData.insert(std::pair<int, Item>(ItemData[i].id, ItemData[i]));

	////以下为测试对话代码
	//std::map<int, Item>::iterator i = _ItemData.begin();
	//char buf[32];
	//sprintf_s(buf, 32, "共%d道具,%d",Len,_ItemData.size());
	//MessageBox(0, buf, 0, 0);
	//for (; i != _ItemData.end(); ++i)
	//	MessageBox(0,i->second.name,0,0);
}

void CScene_Data::LoadMission()
{
	//初始化任务
	int Len = LoadMissionini();
	for (int i = 0; i < Len;++i)
		Hero._CanDo_Things.insert(std::pair<int, Mission>(_MissionData[i].id, _MissionData[i]));
}

bool CScene_Data::AddItem(int id)
{
	std::map<int, Item>::iterator i = _ItemData.find(id);
	//if (i != _ItemData.end() && Hero.YxHero.Dj.size() < _MAX_ITEMNUM)
	//{
	//	Hero.YxHero.Dj.push_back(i->second);
	//	return true;
	//}
	//else
	//	return false;
	if (i != _ItemData.end())
	{
		//Hero.YxHero.Dj.push_back(i->second);
		//return true;
		if (Hero.YxHero.Dj.size() > 0)
		{
			std::vector<Item>::iterator j = Hero.YxHero.Dj.begin();
			for (; j != Hero.YxHero.Dj.end(); ++j)
			{
				if (j->id == i->second.id) //表中存在该物品
				{
					j->ItemNum += i->second.ItemNum;
					return true;
				}
			}
			Hero.YxHero.Dj.push_back(i->second);
		}
		else
			Hero.YxHero.Dj.push_back(i->second);
		return true;
	}
	else
		return false;
}

void CScene_Data::NewGame(char* n)
{
	Hero.YxHero.Hero::Hero(n);
	std::map<int, Mission>::iterator i = Hero._Doing_Things.begin();
	if (i != Hero._Doing_Things.end())
		i = Hero._Doing_Things.erase(i);

	i = Hero._Done_Things.begin();
	if (i != Hero._Done_Things.end())
		i = Hero._Done_Things.erase(i);
}

void CScene_Data::LoadGame()
{
	Hero.YxHero.Hero::Hero();
	std::map<int, Mission>::iterator i = Hero._Doing_Things.begin();
	if (i != Hero._Doing_Things.end())
		i = Hero._Doing_Things.erase(i);

	i = Hero._Done_Things.begin();
	if (i != Hero._Done_Things.end())
		i = Hero._Done_Things.erase(i);

	FILE* pF = 0;
	fopen_s(&pF, "Save", "rb");

	if (!pF) //检查地图文件是否存在
		MessageBox(pGF->GetHwnd(), "非法地图Id!", "提示", 0);
	else
	{
		fseek(pF, 0, SEEK_END);
		int fileSize = ftell(pF);
		rewind(pF); 

		int DjNum; //英雄道具数
		int DoneNum; //已做任务数大小
		int DoingNum; //正在做任务表大小
		fread(&DjNum, 1, 4, pF);
		fread(&DoneNum, 1, 4, pF);
		fread(&DoingNum, 1, 4, pF);

		for (int i = 0; i < DjNum; ++i)
		{
			Item Temp;
			fread(&Temp.id, 1, sizeof(int), pF);
			fread(&Temp.ItemNum, 1, sizeof(int), pF);

			std::map<int, Item>::iterator j = _ItemData.find(Temp.id);
			if (j != _ItemData.end())
			{
				Item Temp_Dj = j->second;
				Temp_Dj.ItemNum = Temp.ItemNum;
				Hero.YxHero.Dj.push_back(Temp_Dj);
			}
		}

		for (int i = 0; i < DoneNum; ++i)
		{
			Mission Temp;
			fread(&Temp.id, 1, sizeof(int), pF);

			std::map<int, Mission>::iterator j = Hero._CanDo_Things.find(Temp.id);
			if (j != Hero._CanDo_Things.end())
			{
				Mission Temp_Dj = j->second;
				Hero._Done_Things.insert(std::pair<int, Mission>(Temp_Dj.id, Temp_Dj));
			}
		}

		for (int i = 0; i < DoingNum; ++i)
		{
			Mission Temp;
			fread(&Temp.id, 1, sizeof(int), pF);

			std::map<int, Mission>::iterator j = Hero._CanDo_Things.find(Temp.id);
			if (j != Hero._CanDo_Things.end())
			{
				Mission Temp_Dj = j->second;
				Hero._Doing_Things.insert(std::pair<int, Mission>(Temp_Dj.id, Temp_Dj));
			}
		}

		//读取英雄数据
		//攻击力
		fread(&Hero.YxHero.Atk, 1, sizeof(int), pF);
		//防御力
		fread(&Hero.YxHero.Def, 1, sizeof(int), pF);
		//敏捷
		fread(&Hero.YxHero.Agi, 1, sizeof(int), pF);
		//魔力
		fread(&Hero.YxHero.Mag, 1, sizeof(int), pF);	
		//闪避
		fread(&Hero.YxHero.Miss, 1, sizeof(int), pF);	
		//暴击
		fread(&Hero.YxHero.Critical, 1, sizeof(int), pF);	
		//Hp
		fread(&Hero.YxHero.Hp, 1, sizeof(int), pF);	
		//MaxHp
		fread(&Hero.YxHero.MaxHp, 1, sizeof(int), pF);	
		//Mp
		fread(&Hero.YxHero.Mp, 1, sizeof(int), pF);	
		//MaxMp
		fread(&Hero.YxHero.MaxMp, 1, sizeof(int), pF);	
		//金币
		fread(&Hero.YxHero.Money, 1, sizeof(int), pF);	
		//等级
		fread(&Hero.YxHero.Level, 1, sizeof(int), pF);	
		//经验
		fread(&Hero.YxHero.Exp, 1, sizeof(int), pF);	
		//经验
		fread(&Hero.YxHero.MaxExp, 1, sizeof(int), pF);	
		//装备
		fread(&Hero.YxHero.Equip.weapon, 1, sizeof(int), pF);	
		fread(&Hero.YxHero.Equip.shield, 1, sizeof(int), pF);	
		fread(&Hero.YxHero.Equip.pendant, 1, sizeof(int), pF);	

		//姓名
		int Len;
		fread(&Len, 1, sizeof(int), pF);	
		char * buf;
		buf = new char[Len + 1];
		buf[Len] = 0;
		fread(buf, 1, Len, pF);	
		Hero.YxHero.Name = buf;

		fclose(pF);
	}
}

bool CScene_Data::MissionCheck(int Mission_ID)
{
	Mission M;
	//在可以做的任务表中查找任务id
	std::map<int, Mission>::iterator i = Hero._CanDo_Things.find(Mission_ID);
	if (i != Hero._CanDo_Things.end())
		M = i->second;

	if (M.qxid == -1) //有前续任务
	{
		//检查任务是否完成过
		i = Hero._Done_Things.find(M.id); //查找表中是否存在该任务ID
		if (i == Hero._Done_Things.end()) //不存在表示未做过该任务
		{
			//如果没有完成,推入完成表,表示任务完成
			Hero._Done_Things.insert(std::pair<int, Mission>(M.id, M));
			//完成后续以后删除前序任务
			i = Hero._Doing_Things.find(M.id);
			if (i != Hero._Doing_Things.end())
				i = Hero._Doing_Things.erase(i);

			if (M.hxid != -1) //有后续
			{
				i = Hero._Doing_Things.find(M.hxid);
				if (i == Hero._Doing_Things.end()) //后续没做过
				{
					std::map<int, Mission>::iterator j = Hero._Doing_Things.find(M.hxid);
					if (j == Hero._Doing_Things.end())
					{
						j = Hero._CanDo_Things.find(M.hxid);
						if (j != Hero._CanDo_Things.end())
							Hero._Doing_Things.insert(std::pair<int, Mission>(j->first, j->second));
					}
				}
			}
			return true;
		}
		else
			return false;
	}
	else //无前续任务
	{
		i = Hero._Done_Things.begin();
		for (; i != Hero._Done_Things.end(); ++i)
		{
			if (M.id == i->second.hxid) //前序任务已完成
			{
				//如果没有完成,推入完成表,表示任务完成
				Hero._Done_Things.insert(std::pair<int, Mission>(M.id, M));
				//完成后续以后删除前序任务
				i = Hero._Doing_Things.find(M.id);
				if (i != Hero._Doing_Things.end())
					i = Hero._Doing_Things.erase(i);

				if (M.hxid != -1) //有后续
				{
					i = Hero._Doing_Things.find(M.hxid);
					if (i == Hero._Doing_Things.end()) //后续没做过
					{
						std::map<int, Mission>::iterator j = Hero._Doing_Things.find(M.hxid);
						if (j == Hero._Doing_Things.end())
						{
							j = Hero._CanDo_Things.find(M.hxid);
							if (j != Hero._CanDo_Things.end())
								Hero._Doing_Things.insert(std::pair<int, Mission>(j->first, j->second));
						}
					}
				}
				return true;
			}
		}
		//前序未完成
		return false;
	}
}

void CScene_Data::AddEquip(int id, int Type)
{
	switch (Type)
	{
	case 1:
		{
			std::map<int, Item>::iterator i = _ItemData.find(Hero.YxHero.GetEquip_W());
			if (i != _ItemData.end())
			{
				AddItem(i->first);
				Hero.YxHero.AtkAdd(-i->second.AtkAdd);
				Hero.YxHero.DefAdd(-i->second.DefAdd);
				Hero.YxHero.MagAdd(-i->second.MagAdd);
				Hero.YxHero.AgiAdd(-i->second.AgiAdd);
			}

			i = _ItemData.find(id);
			if (i != _ItemData.end())
			{
				Hero.YxHero.AtkAdd(i->second.AtkAdd);
				Hero.YxHero.DefAdd(i->second.DefAdd);
				Hero.YxHero.MagAdd(i->second.MagAdd);
				Hero.YxHero.AgiAdd(i->second.AgiAdd);
				Hero.YxHero.SetEquip_W(id);
			}
			break;
		}
	case 2:
		{
			std::map<int, Item>::iterator i = _ItemData.find(Hero.YxHero.GetEquip_F());
			if (i != _ItemData.end())
			{
				AddItem(i->first);
				Hero.YxHero.AtkAdd(-i->second.AtkAdd);
				Hero.YxHero.DefAdd(-i->second.DefAdd);
				Hero.YxHero.MagAdd(-i->second.MagAdd);
				Hero.YxHero.AgiAdd(-i->second.AgiAdd);
			}

			i = _ItemData.find(id);
			if (i != _ItemData.end())
			{
				Hero.YxHero.AtkAdd(i->second.AtkAdd);
				Hero.YxHero.DefAdd(i->second.DefAdd);
				Hero.YxHero.MagAdd(i->second.MagAdd);
				Hero.YxHero.AgiAdd(i->second.AgiAdd);
				Hero.YxHero.SetEquip_F(id);
			}
			break;
		}
	case 3:
		{
			std::map<int, Item>::iterator i = _ItemData.find(Hero.YxHero.GetEquip_P());
			if (i != _ItemData.end())
			{
				AddItem(i->first);
				Hero.YxHero.AtkAdd(-i->second.AtkAdd);
				Hero.YxHero.DefAdd(-i->second.DefAdd);
				Hero.YxHero.MagAdd(-i->second.MagAdd);
				Hero.YxHero.AgiAdd(-i->second.AgiAdd);
			}

			i = _ItemData.find(id);
			if (i != _ItemData.end())
			{
				Hero.YxHero.AtkAdd(i->second.AtkAdd);
				Hero.YxHero.DefAdd(i->second.DefAdd);
				Hero.YxHero.MagAdd(i->second.MagAdd);
				Hero.YxHero.AgiAdd(i->second.AgiAdd);
				Hero.YxHero.SetEquip_P(id);
			}
			break;
		}
	}
}

void CScene_Data::EraseEquip( int id, int Type )
{
	switch (Type)
	{
	case 1:
		{
			std::map<int, Item>::iterator i = _ItemData.find(Hero.YxHero.GetEquip_W());
			if (i != _ItemData.end())
			{
				AddItem(i->first);
				Hero.YxHero.AtkAdd(-i->second.AtkAdd);
				Hero.YxHero.DefAdd(-i->second.DefAdd);
				Hero.YxHero.MagAdd(-i->second.MagAdd);
				Hero.YxHero.AgiAdd(-i->second.AgiAdd);
			}
			Hero.YxHero.SetEquip_W(-1);
			break;
		}
	case 2:
		{
			std::map<int, Item>::iterator i = _ItemData.find(Hero.YxHero.GetEquip_F());
			if (i != _ItemData.end())
			{
				AddItem(i->first);
				Hero.YxHero.AtkAdd(-i->second.AtkAdd);
				Hero.YxHero.DefAdd(-i->second.DefAdd);
				Hero.YxHero.MagAdd(-i->second.MagAdd);
				Hero.YxHero.AgiAdd(-i->second.AgiAdd);
			}
			Hero.YxHero.SetEquip_F(-1);
			break;
		}
	case 3:
		{
			std::map<int, Item>::iterator i = _ItemData.find(Hero.YxHero.GetEquip_P());
			if (i != _ItemData.end())
			{
				AddItem(i->first);
				Hero.YxHero.AtkAdd(-i->second.AtkAdd);
				Hero.YxHero.DefAdd(-i->second.DefAdd);
				Hero.YxHero.MagAdd(-i->second.MagAdd);
				Hero.YxHero.AgiAdd(-i->second.AgiAdd);
			}
			Hero.YxHero.SetEquip_P(-1);
			break;
		}
	}
}

void CScene_Data::LoadYuDiData()
{
	//初始化地图
	m_MapNum = LoadMapini();
	for (int i = 0; i < m_MapNum;++i)
		_MapYuDiData.push_back(MapYuDiData[i]);
}

int CScene_Data::GetMapNum()
{
	return m_MapNum;
}


