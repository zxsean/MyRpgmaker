#ifndef _Hero_DATA_H_
#define _Hero_DATA_H_

#include <vector>
#include "Mission.h"
#include "Equip.h"

class Hero
{
public:
	int Hp;//生命值
	int MaxHp;//最大生命值
	int Mp;//魔法值
	int MaxMp;//最大生命值
	int Atk;//攻击
	int Def;//防御

	int Agi;//敏捷(换算闪避)
	int Miss;//躲闪
	int Critical;//暴击

	int Mag;//魔力
	int Money;//金钱
	int Exp;//经验
	int MaxExp;//升级需要经验
	int Level;//等级
	//char Name[32];//名字
	char* Name;

	CEquip Equip;//装备

	Hero();
	Hero(char* n);
	//~Hero();
	int getHP();
	int getMP();
	int getMaxHP();
	int getMaxMP();
	int getGongJiLi();
	int getFangYuLi();

	int getAgi();//敏捷(换算闪避)
	int getMag();//魔力
	int getMiss();//躲闪
	int getCritical();//暴击

	int getMoney();
	int getExp();
	int getMaxExp();
	int getLevel();
	char* getName();
	bool HpAdd(int Addnum);
	bool MpAdd(int Addnum);
	void MaxHpAdd(int Addnum);
	void MaxMpAdd(int Addnum);
	void AtkAdd(int Addnum);
	void DefAdd(int Addnum);
	int ExpAdd(int Addnum);
	void MaxExpAdd(int Addnum);
	void MoneyAdd(int Addnum);
	void SetName(char* Str);
	void AgiAdd(int Addnum);//敏捷(换算闪避)
	void MagAdd(int Addnum);

	//装备
	void SetEquip_W(int id);
	void SetEquip_F(int id);
	void SetEquip_P(int id);

	//恢复
	void Heal();

	int GetEquip_W();
	int GetEquip_F();
	int GetEquip_P();

	std::vector<Item> Dj; //道具表
};

#endif

