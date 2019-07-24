#ifndef _Hero_DATA_H_
#define _Hero_DATA_H_

#include <vector>
#include "Mission.h"
#include "Equip.h"

class Hero
{
public:
	int Hp;//����ֵ
	int MaxHp;//�������ֵ
	int Mp;//ħ��ֵ
	int MaxMp;//�������ֵ
	int Atk;//����
	int Def;//����

	int Agi;//����(��������)
	int Miss;//����
	int Critical;//����

	int Mag;//ħ��
	int Money;//��Ǯ
	int Exp;//����
	int MaxExp;//������Ҫ����
	int Level;//�ȼ�
	//char Name[32];//����
	char* Name;

	CEquip Equip;//װ��

	Hero();
	Hero(char* n);
	//~Hero();
	int getHP();
	int getMP();
	int getMaxHP();
	int getMaxMP();
	int getGongJiLi();
	int getFangYuLi();

	int getAgi();//����(��������)
	int getMag();//ħ��
	int getMiss();//����
	int getCritical();//����

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
	void AgiAdd(int Addnum);//����(��������)
	void MagAdd(int Addnum);

	//װ��
	void SetEquip_W(int id);
	void SetEquip_F(int id);
	void SetEquip_P(int id);

	//�ָ�
	void Heal();

	int GetEquip_W();
	int GetEquip_F();
	int GetEquip_P();

	std::vector<Item> Dj; //���߱�
};

#endif

