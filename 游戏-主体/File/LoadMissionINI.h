#ifndef _LOADMISSION_H_
#define _LOADMISSION_H_
#include "Rpg.h"

Mission* _MissionData;

int LoadMissionini()
{
	char acSectionName[256];//模块名
	int iSectionLen = 0;//读取长度
	char acMissionNum[32];
	int iMissionNumShow;

	GetPrivateProfileSectionNamesA(
		acSectionName, 
		256, 
		".\\Data\\Mission.ini");
	strcpy_s(acMissionNum,32,acSectionName + iSectionLen);
	iSectionLen += int(strlen(acMissionNum) + 1);
	//std::cout <<acMissionNum<<std::endl ;
	//读取语句数量
	iMissionNumShow = GetPrivateProfileIntA(
		acMissionNum, //指定的模块
		"任务数量", //指定的键
		-1, //当找不到指定的数据返回的值
		".\\Data\\Mission.ini"); //指定的ini文件

	//std::cout <<iMissionNumShow<<std::endl;
	_MissionData = new Mission[iMissionNumShow * sizeof(Mission)];
	char *TempName = new char[32 * iMissionNumShow];

	for (int i = 0;i < iMissionNumShow;++i)
	{
		strcpy_s(TempName,32,acSectionName + iSectionLen);
		iSectionLen += int(strlen(TempName) + 1);

		_MissionData[i].id = GetPrivateProfileIntA(
			TempName, //指定的模块
			"Id", //指定的键
			-1, //当找不到指定的数据返回的值
			".\\Data\\Mission.ini"); //指定的ini文件

		_MissionData[i].qxid = GetPrivateProfileIntA(
			TempName, //指定的模块
			"Qxid", //指定的键
			-1, //当找不到指定的数据返回的值
			".\\Data\\Mission.ini"); //指定的ini文件

		_MissionData[i].hxid = GetPrivateProfileIntA(
			TempName, //指定的模块
			"Hxid", //指定的键
			-1, //当找不到指定的数据返回的值
			".\\Data\\Mission.ini"); //指定的ini文件

		GetPrivateProfileStringA(
			TempName,
			"MissionText",
			"!?", //当找不到指定的数据返回的字符串
			_MissionData[i].MissionText, //用于得到字符串的字符数组
			256, //用于得到字符串的字符数组长度
			".\\Data\\Mission.ini");
	}
	return iMissionNumShow;
}
#endif