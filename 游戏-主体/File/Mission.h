#ifndef _Mission_H_
#define _Mission_H_

struct Item
{
	int id;
	int ItemNum; //道具数量
	char name[32];
	char ItemText[256]; //道具描述
	int HpAdd;//生命值值增减量
	int MpAdd;//法力值增减量
	int AtkAdd;//攻击力增减量
	int DefAdd;//防御值增减量
	int AgiAdd;//敏捷增减量
	int MagAdd;//魔力增减量
	int Price;//售价
	int Type;//判断是道具还是装备
};

struct Type_Talk//对话
{
	int id; //对话Id
	char talk[256]; //对话内容
	int BmpId; //对话头像id
	char name[256]; //对话人物名字
};

struct Type_Level//级别
{
	int level;
};

struct Type_Item//物品
{
	int wupinID;
	int wupinNum;
	Item Item;
};

struct MapYuDi
{
	int YuDiLv; //遇敌率
	int YuDiMapId; //遇敌地图id
	char Type[8]; //遇敌类型
};

struct Things
{
	int id; //事情ID
	int hxid[8]; //后续事情ID数组
	int type; //事情类型
	union Data//事情数据
	{
		Type_Talk t1;
		Type_Level t2;
		Type_Item t3;
	}data;
};

struct Mission//任务数组
{
	int id; //事情ID
	int qxid; //前续ID
	int hxid; //后续事情ID,如果没有就-1
	char MissionText[256];//任务描述
};

struct Monster
{
	int id; //id
	char name[32];
	int Hp;//生命值
	int Atk;//攻击力
	int Def;//防御值
	int Gold;//金币掉落
	int Exp;//经验值
};

#endif