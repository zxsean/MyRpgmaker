#ifndef _LOAD_MAP_INI_H_
#define _LOAD_MAP_INI_H_

#include "File/Mission.h"
MapYuDi* MapYuDiData;

int LoadMapini()
{
	char acSectionName[256];//模块名
	int iSectionLen = 0;//读取长度
	char acTalkNum[32];
	int iMapNumShow;

	GetPrivateProfileSectionNamesA(
		acSectionName, 
		256, 
		".\\Map\\Map.ini");
	strcpy_s(acTalkNum,32,acSectionName + iSectionLen);
	iSectionLen += int(strlen(acTalkNum) + 1);

	//读取语句数量
	iMapNumShow = GetPrivateProfileIntA(
		acTalkNum, //指定的模块
		"地图总数", //指定的键
		-1, //当找不到指定的数据返回的值
		".\\Map\\Map.ini"); //指定的ini文件

	MapYuDiData = new MapYuDi[iMapNumShow * sizeof(MapYuDi)];
	char *TempName = new char[32 * iMapNumShow];

	for (int i = 0;i < iMapNumShow;++i)
	{
		strcpy_s(TempName,32,acSectionName + iSectionLen);
		iSectionLen += int(strlen(TempName) + 1);

		//遇敌类型
		for (int j = 0; j < 8; ++j)
		{
			char buf[256];
			sprintf_s(buf, 256, "Type_%d", j);
			MapYuDiData[i].Type[j] = GetPrivateProfileIntA(
				TempName, //指定的模块
				buf, //指定的键
				-1, //当找不到指定的数据返回的值
				".\\Map\\Map.ini"); //指定的ini文件
		}

		//遇敌率
		MapYuDiData[i].YuDiLv = GetPrivateProfileIntA(
			TempName, //指定的模块
			"遇敌率", //指定的键
			-1, //当找不到指定的数据返回的值
			".\\Map\\Map.ini"); //指定的ini文件
		//地图id
		MapYuDiData[i].YuDiMapId = GetPrivateProfileIntA(
			TempName, //指定的模块
			"MapId", //指定的键
			-1, //当找不到指定的数据返回的值
			".\\Map\\Map.ini"); //指定的ini文件
	}
	return iMapNumShow;
};


#endif