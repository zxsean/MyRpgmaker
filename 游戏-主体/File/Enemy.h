#ifndef _Enemy_DATA_H_
#define _Enemy_DATA_H_

#include "File/Mission.h"
Monster* MonsterData;

int LoadEnemyini()
{
	char acSectionName[256];//模块名
	int iSectionLen = 0;//读取长度
	char acMonsterNum[32];
	int iMonsterNumShow;

	GetPrivateProfileSectionNamesA(
		acSectionName, 
		256, 
		".\\Data\\Monster.ini");
	strcpy_s(acMonsterNum,32,acSectionName + iSectionLen);
	iSectionLen += int(strlen(acMonsterNum) + 1);

	//读取数量
	iMonsterNumShow = GetPrivateProfileIntA(
		acMonsterNum, //指定的模块
		"怪物数量", //指定的键
		-1, //当找不到指定的数据返回的值
		".\\Data\\Monster.ini"); //指定的ini文件

	MonsterData = new Monster[iMonsterNumShow * sizeof(Monster)];
	char *TempName = new char[32 * iMonsterNumShow];

	for (int i = 0;i < iMonsterNumShow;++i)
	{
		strcpy_s(TempName,32,acSectionName + iSectionLen);
		iSectionLen += int(strlen(TempName) + 1);

		GetPrivateProfileStringA(
			TempName,
			"Name",
			"!?", //当找不到指定的数据返回的字符串
			MonsterData[i].name, //用于得到字符串的字符数组
			256, //用于得到字符串的字符数组长度
			".\\Data\\Monster.ini");
		
		//id
		MonsterData[i].id = GetPrivateProfileIntA(
			TempName, //指定的模块
			"Id", //指定的键
			-1, //当找不到指定的数据返回的值
			".\\Data\\Monster.ini"); //指定的ini文件
		//生命值
		MonsterData[i].Hp = GetPrivateProfileIntA(
			TempName, //指定的模块
			"Hp", //指定的键
			-1, //当找不到指定的数据返回的值
			".\\Data\\Monster.ini"); //指定的ini文件
		//攻击力
		MonsterData[i].Atk = GetPrivateProfileIntA(
			TempName, //指定的模块
			"Atk", //指定的键
			-1, //当找不到指定的数据返回的值
			".\\Data\\Monster.ini"); //指定的ini文件
		//防御力
		MonsterData[i].Def = GetPrivateProfileIntA(
			TempName, //指定的模块
			"Def", //指定的键
			-1, //当找不到指定的数据返回的值
			".\\Data\\Monster.ini"); //指定的ini文件
		//金币
		MonsterData[i].Gold = GetPrivateProfileIntA(
			TempName, //指定的模块
			"Gold", //指定的键
			-1, //当找不到指定的数据返回的值
			".\\Data\\Monster.ini"); //指定的ini文件
		//经验值
		MonsterData[i].Exp = GetPrivateProfileIntA(
			TempName, //指定的模块
			"Exp", //指定的键
			-1, //当找不到指定的数据返回的值
			".\\Data\\Monster.ini"); //指定的ini文件

		//测试
	}
	return iMonsterNumShow;
}

#endif