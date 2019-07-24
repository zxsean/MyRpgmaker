#ifndef _LOADMISSION_H_
#define _LOADMISSION_H_
#include "Rpg.h"

Mission* _MissionData;

int LoadMissionini()
{
	char acSectionName[256];//ģ����
	int iSectionLen = 0;//��ȡ����
	char acMissionNum[32];
	int iMissionNumShow;

	GetPrivateProfileSectionNamesA(
		acSectionName, 
		256, 
		".\\Data\\Mission.ini");
	strcpy_s(acMissionNum,32,acSectionName + iSectionLen);
	iSectionLen += int(strlen(acMissionNum) + 1);
	//std::cout <<acMissionNum<<std::endl ;
	//��ȡ�������
	iMissionNumShow = GetPrivateProfileIntA(
		acMissionNum, //ָ����ģ��
		"��������", //ָ���ļ�
		-1, //���Ҳ���ָ�������ݷ��ص�ֵ
		".\\Data\\Mission.ini"); //ָ����ini�ļ�

	//std::cout <<iMissionNumShow<<std::endl;
	_MissionData = new Mission[iMissionNumShow * sizeof(Mission)];
	char *TempName = new char[32 * iMissionNumShow];

	for (int i = 0;i < iMissionNumShow;++i)
	{
		strcpy_s(TempName,32,acSectionName + iSectionLen);
		iSectionLen += int(strlen(TempName) + 1);

		_MissionData[i].id = GetPrivateProfileIntA(
			TempName, //ָ����ģ��
			"Id", //ָ���ļ�
			-1, //���Ҳ���ָ�������ݷ��ص�ֵ
			".\\Data\\Mission.ini"); //ָ����ini�ļ�

		_MissionData[i].qxid = GetPrivateProfileIntA(
			TempName, //ָ����ģ��
			"Qxid", //ָ���ļ�
			-1, //���Ҳ���ָ�������ݷ��ص�ֵ
			".\\Data\\Mission.ini"); //ָ����ini�ļ�

		_MissionData[i].hxid = GetPrivateProfileIntA(
			TempName, //ָ����ģ��
			"Hxid", //ָ���ļ�
			-1, //���Ҳ���ָ�������ݷ��ص�ֵ
			".\\Data\\Mission.ini"); //ָ����ini�ļ�

		GetPrivateProfileStringA(
			TempName,
			"MissionText",
			"!?", //���Ҳ���ָ�������ݷ��ص��ַ���
			_MissionData[i].MissionText, //���ڵõ��ַ������ַ�����
			256, //���ڵõ��ַ������ַ����鳤��
			".\\Data\\Mission.ini");
	}
	return iMissionNumShow;
}
#endif