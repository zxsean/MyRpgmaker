#ifndef _LOAD_MAP_INI_H_
#define _LOAD_MAP_INI_H_

#include "File/Mission.h"
MapYuDi* MapYuDiData;

int LoadMapini()
{
	char acSectionName[256];//ģ����
	int iSectionLen = 0;//��ȡ����
	char acTalkNum[32];
	int iMapNumShow;

	GetPrivateProfileSectionNamesA(
		acSectionName, 
		256, 
		".\\Map\\Map.ini");
	strcpy_s(acTalkNum,32,acSectionName + iSectionLen);
	iSectionLen += int(strlen(acTalkNum) + 1);

	//��ȡ�������
	iMapNumShow = GetPrivateProfileIntA(
		acTalkNum, //ָ����ģ��
		"��ͼ����", //ָ���ļ�
		-1, //���Ҳ���ָ�������ݷ��ص�ֵ
		".\\Map\\Map.ini"); //ָ����ini�ļ�

	MapYuDiData = new MapYuDi[iMapNumShow * sizeof(MapYuDi)];
	char *TempName = new char[32 * iMapNumShow];

	for (int i = 0;i < iMapNumShow;++i)
	{
		strcpy_s(TempName,32,acSectionName + iSectionLen);
		iSectionLen += int(strlen(TempName) + 1);

		//��������
		for (int j = 0; j < 8; ++j)
		{
			char buf[256];
			sprintf_s(buf, 256, "Type_%d", j);
			MapYuDiData[i].Type[j] = GetPrivateProfileIntA(
				TempName, //ָ����ģ��
				buf, //ָ���ļ�
				-1, //���Ҳ���ָ�������ݷ��ص�ֵ
				".\\Map\\Map.ini"); //ָ����ini�ļ�
		}

		//������
		MapYuDiData[i].YuDiLv = GetPrivateProfileIntA(
			TempName, //ָ����ģ��
			"������", //ָ���ļ�
			-1, //���Ҳ���ָ�������ݷ��ص�ֵ
			".\\Map\\Map.ini"); //ָ����ini�ļ�
		//��ͼid
		MapYuDiData[i].YuDiMapId = GetPrivateProfileIntA(
			TempName, //ָ����ģ��
			"MapId", //ָ���ļ�
			-1, //���Ҳ���ָ�������ݷ��ص�ֵ
			".\\Map\\Map.ini"); //ָ����ini�ļ�
	}
	return iMapNumShow;
};


#endif