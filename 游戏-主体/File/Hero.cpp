#include "Hero.h"

int Hero::getHP()
{
	return Hp;
}

int Hero::getMP()
{
	return Mp;
}

int Hero::getGongJiLi()
{
	return Atk;
}

int Hero::getFangYuLi()
{
	return Def;
}

char* Hero::getName()
{
	return Name;
}

int Hero::getMoney()
{
	return Money;
}

int Hero::getExp()
{
	return Exp;
}

int Hero::getMaxExp()
{
	return MaxExp;
}

int Hero::getLevel()
{
	return Level;
}

Hero::Hero()
{
	Hp = 100;
	MaxHp = 100;
	Mp = 50;
	MaxMp = 50;
	Atk = 10;
	Def = 11;
	Agi = 12;
	Mag = 13;
	Miss = Agi / 12;
	Critical = Agi / 10;

	Name = "ะกรศ";

	Money = 100;
	Exp = 0;
	MaxExp = 100;
	Level = 1;
}

Hero::Hero(char* n)
{
	Hp = 100;
	MaxHp = 100;
	Mp = 50;
	MaxMp = 50;
	Atk = 10;
	Def = 11;
	Agi = 12;
	Mag = 13;
	Miss = Agi / 12;
	Critical = Agi / 10;

	Name = n;

	Money = 100;
	Exp = 0;
	MaxExp = 100;
	Level = 1;
}

bool Hero::HpAdd(int Addnum)
{
	if (Hp + Addnum < MaxHp)
	{
		Hp += Addnum;
		return true;
	}
	else if (Hp < MaxHp)
	{
		Hp = MaxHp;
		return true;
	}
	else
		return false;
}

bool Hero::MpAdd(int Addnum)
{
	if (Mp + Addnum < MaxMp)
	{
		Mp += Addnum;
		return true;
	}
	else if (Mp < MaxMp)
	{
		Mp = MaxMp;
		return true;
	}
	else
		return false;
}

void Hero::AtkAdd(int Addnum)
{
	Atk += Addnum;
}

void Hero::DefAdd(int Addnum)
{
	Def += Addnum;
}

void Hero::MoneyAdd(int Addnum)
{
	Money += Addnum;
}

int Hero::ExpAdd(int Addnum)
{
	if (Exp + Addnum< MaxExp)
	{
		Exp += Addnum;
		return 0;
	}
	else
	{
		MaxExpAdd(100);
		Level ++;
		AtkAdd(2);
		DefAdd(2);
		AgiAdd(2);
		MagAdd(2);
		MaxHpAdd(10);
		MaxMpAdd(10);

		Heal();

		Exp = 0;
		return 1;
	}
}

void Hero::MaxExpAdd(int Addnum)
{
	MaxExp += Addnum;
}

void Hero::SetName(char* Str)
{
	strlen(Str);
	strcpy_s(Name, strlen(Str) + 1, Str);
}

int Hero::getAgi()
{
	return Agi;
}

int Hero::getMag()
{
	return Mag;
}

int Hero::getMiss()
{
	return Miss;
}

int Hero::getCritical()
{
	return Critical;
}

void Hero::AgiAdd(int Addnum)
{
	Agi += Addnum;
	Miss = Agi / 12;
	Critical = Agi / 10;
}

void Hero::MagAdd(int Addnum)
{
	Mag += Addnum;
}

int Hero::getMaxHP()
{
	return MaxHp;
}

int Hero::getMaxMP()
{
	return MaxMp;
}

void Hero::SetEquip_W(int id)
{
	Equip.weapon = id;
}

void Hero::SetEquip_F(int id)
{
	Equip.shield = id;
}

void Hero::SetEquip_P(int id)
{
	Equip.pendant = id;
}

int Hero::GetEquip_W()
{
	return Equip.weapon;
}

int Hero::GetEquip_F()
{
	return Equip.shield;
}

int Hero::GetEquip_P()
{
	return Equip.pendant;
}

void Hero::MaxHpAdd( int Addnum )
{
	MaxHp += Addnum;
}

void Hero::MaxMpAdd( int Addnum )
{
	MaxMp += Addnum;
}

void Hero::Heal()
{
	Hp = MaxHp;
	Mp = MaxMp;
}
