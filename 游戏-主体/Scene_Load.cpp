#include "Scene_Load.h"

void CScene_Load::Init()
{
	pGF = CGameFrame::GetObject();
}

void CScene_Load::Enter()
{
	HeroData = (CScene_Data*)pGF->GetScene("数据储存场景");
}

void CScene_Load::Run()
{
	pGF->GetGO()->DrawBmp(
		0,
		0, 
		pGF->GetW(),
		pGF->GetH(),
		0,
		0,
		"Pic\\System\\Save.bmp");

	if(pGF->GetGI()->Get(_GI_K_ESC) == _KS_DC)
	{
		SaveGame();
		pGF->SetCurScene("场景2");
	}
}

void CScene_Load::Quit()
{
}

void CScene_Load::SaveGame()
{
	int DjNum = (int)HeroData->Hero.YxHero.Dj.size(); //英雄道具数
	int DoneNum = (int)HeroData->Hero._Done_Things.size(); //已做任务数大小
	int DoingNum = (int)HeroData->Hero._Doing_Things.size(); //正在做任务表大小

	int fileSize = 3 * sizeof(int);
	fileSize += DjNum * sizeof(int); //道具表大小
	fileSize += (DoneNum + DoingNum) * sizeof(int); //任务id
	fileSize += (14 + 3) * sizeof(int); //英雄数据
	fileSize += 32 + 4; //英雄姓名

	char* _Save_Data = new char[fileSize];
	int Py = 0;

	memcpy( _Save_Data + Py, &DjNum, sizeof(int)); //写入英雄道具数
	Py += sizeof(int);
	memcpy( _Save_Data + Py, &DoneNum, sizeof(int)); //写入已做任务数大小
	Py += sizeof(int);
	memcpy( _Save_Data + Py, &DoingNum, sizeof(int)); //写入正在做任务表大小
	Py += sizeof(int);

	//存入道具ID
	std::vector<Item>::iterator i = HeroData->Hero.YxHero.Dj.begin();
	for (; i != HeroData->Hero.YxHero.Dj.end(); ++i)
	{
		memcpy( _Save_Data + Py, &i->id,sizeof(int)); 
		Py += sizeof(int);

		memcpy( _Save_Data + Py, &i->ItemNum,sizeof(int)); 
		Py += sizeof(int);
	}

	//存入完成任务ID
	std::map<int, Mission>::iterator j = HeroData->Hero._Done_Things.begin();
	for (; j != HeroData->Hero._Done_Things.end(); ++j)
	{
		memcpy( _Save_Data + Py, &j->second.id, sizeof(int)); 
		Py += sizeof(int);
	}

	//存入正在做任务ID
	j = HeroData->Hero._Doing_Things.begin();
	for (; j != HeroData->Hero._Doing_Things.end(); ++j)
	{
		memcpy( _Save_Data + Py, &j->second.id, sizeof(int)); 
		Py += sizeof(int);
	}

	//存入英雄数据
	//攻击力
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Atk, sizeof(int)); 
	Py += sizeof(int);
	//防御力
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Def, sizeof(int)); 
	Py += sizeof(int);
	//敏捷
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Agi, sizeof(int)); 
	Py += sizeof(int);
	//魔力
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Mag, sizeof(int)); 
	Py += sizeof(int);
	//闪避
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Miss, sizeof(int)); 
	Py += sizeof(int);
	//暴击
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Critical, sizeof(int)); 
	Py += sizeof(int);
	//Hp
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Hp, sizeof(int)); 
	Py += sizeof(int);
	//MaxHp
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.MaxHp, sizeof(int)); 
	Py += sizeof(int);
	//Mp
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Mp, sizeof(int)); 
	Py += sizeof(int);
	//MaxMp
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.MaxMp, sizeof(int)); 
	Py += sizeof(int);
	//金币
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Money, sizeof(int)); 
	Py += sizeof(int);
	//等级
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Level, sizeof(int)); 
	Py += sizeof(int);
	//经验
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Exp, sizeof(int)); 
	Py += sizeof(int);
	//经验
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.MaxExp, sizeof(int)); 
	Py += sizeof(int);
	//装备
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Equip.weapon, sizeof(int)); 
	Py += sizeof(int);
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Equip.shield, sizeof(int)); 
	Py += sizeof(int);
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Equip.pendant, sizeof(int)); 
	Py += sizeof(int);

	//姓名
	char* Name = HeroData->Hero.YxHero.getName();
	int Len = (int)strlen(Name);
	//先写入字符串长度
	memcpy( _Save_Data + Py, &Len, sizeof(int)); 
	Py += sizeof(int);
	memcpy( _Save_Data + Py, Name, Len); 
	Py += Len;

	FILE* fp1 = 0;
	fopen_s(&fp1, "Save", "wb");
	fwrite(_Save_Data, 1, fileSize, fp1);
	fclose(fp1);
}

