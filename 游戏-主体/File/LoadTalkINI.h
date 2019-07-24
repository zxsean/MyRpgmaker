#ifndef _Talk_H_
#define _Talk_H_

#include "File/Mission.h"
Type_Talk* TalkData;

int LoadTalkini()
{
	char acSectionName[512];//模块名
	int iSectionLen = 0;//读取长度
	char acTalkNum[32];
	int iTalkNumShow;

	GetPrivateProfileSectionNamesA(
		acSectionName, 
		512, 
		".\\Data\\Talk.ini");
	strcpy_s(acTalkNum,32,acSectionName + iSectionLen);
	iSectionLen += int(strlen(acTalkNum) + 1);

	//读取语句数量
	iTalkNumShow = GetPrivateProfileIntA(
		acTalkNum, //指定的模块
		"语句数量", //指定的键
		-1, //当找不到指定的数据返回的值
		".\\Data\\Talk.ini"); //指定的ini文件

	TalkData = new Type_Talk[iTalkNumShow * sizeof(Type_Talk)];
	char *TempName = new char[32 * iTalkNumShow];

	for (int i = 0;i < iTalkNumShow;++i)
	{
		strcpy_s(TempName,32,acSectionName + iSectionLen);
		iSectionLen += int(strlen(TempName) + 1);

		TalkData[i].id = GetPrivateProfileIntA(
			TempName, //指定的模块
			"Id", //指定的键
			-1, //当找不到指定的数据返回的值
			".\\Data\\Talk.ini"); //指定的ini文件
		
		TalkData[i].BmpId = GetPrivateProfileIntA(
			TempName, //指定的模块
			"BmpId", //指定的键
			0, //当找不到指定的数据返回的值
			".\\Data\\Talk.ini"); //指定的ini文件

		GetPrivateProfileStringA(
			TempName,
			"Talk",
			"!?", //当找不到指定的数据返回的字符串
			TalkData[i].talk, //用于得到字符串的字符数组
			256, //用于得到字符串的字符数组长度
			".\\Data\\Talk.ini");

		GetPrivateProfileStringA(
			TempName,
			"Name",
			"???", //当找不到指定的数据返回的字符串
			TalkData[i].name, //用于得到字符串的字符数组
			256, //用于得到字符串的字符数组长度
			".\\Data\\Talk.ini");

		//OutputDebugStr(itoa(TalkData[i].id));
	}
	return iTalkNumShow;
};


#endif