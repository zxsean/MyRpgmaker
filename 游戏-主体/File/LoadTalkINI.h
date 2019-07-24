#ifndef _Talk_H_
#define _Talk_H_

#include "File/Mission.h"
Type_Talk* TalkData;

int LoadTalkini()
{
	char acSectionName[512];//ģ����
	int iSectionLen = 0;//��ȡ����
	char acTalkNum[32];
	int iTalkNumShow;

	GetPrivateProfileSectionNamesA(
		acSectionName, 
		512, 
		".\\Data\\Talk.ini");
	strcpy_s(acTalkNum,32,acSectionName + iSectionLen);
	iSectionLen += int(strlen(acTalkNum) + 1);

	//��ȡ�������
	iTalkNumShow = GetPrivateProfileIntA(
		acTalkNum, //ָ����ģ��
		"�������", //ָ���ļ�
		-1, //���Ҳ���ָ�������ݷ��ص�ֵ
		".\\Data\\Talk.ini"); //ָ����ini�ļ�

	TalkData = new Type_Talk[iTalkNumShow * sizeof(Type_Talk)];
	char *TempName = new char[32 * iTalkNumShow];

	for (int i = 0;i < iTalkNumShow;++i)
	{
		strcpy_s(TempName,32,acSectionName + iSectionLen);
		iSectionLen += int(strlen(TempName) + 1);

		TalkData[i].id = GetPrivateProfileIntA(
			TempName, //ָ����ģ��
			"Id", //ָ���ļ�
			-1, //���Ҳ���ָ�������ݷ��ص�ֵ
			".\\Data\\Talk.ini"); //ָ����ini�ļ�
		
		TalkData[i].BmpId = GetPrivateProfileIntA(
			TempName, //ָ����ģ��
			"BmpId", //ָ���ļ�
			0, //���Ҳ���ָ�������ݷ��ص�ֵ
			".\\Data\\Talk.ini"); //ָ����ini�ļ�

		GetPrivateProfileStringA(
			TempName,
			"Talk",
			"!?", //���Ҳ���ָ�������ݷ��ص��ַ���
			TalkData[i].talk, //���ڵõ��ַ������ַ�����
			256, //���ڵõ��ַ������ַ����鳤��
			".\\Data\\Talk.ini");

		GetPrivateProfileStringA(
			TempName,
			"Name",
			"???", //���Ҳ���ָ�������ݷ��ص��ַ���
			TalkData[i].name, //���ڵõ��ַ������ַ�����
			256, //���ڵõ��ַ������ַ����鳤��
			".\\Data\\Talk.ini");

		//OutputDebugStr(itoa(TalkData[i].id));
	}
	return iTalkNumShow;
};


#endif