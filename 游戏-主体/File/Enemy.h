#ifndef _Enemy_DATA_H_
#define _Enemy_DATA_H_

#include "File/Mission.h"
Monster* MonsterData;

int LoadEnemyini()
{
	char acSectionName[256];//ģ����
	int iSectionLen = 0;//��ȡ����
	char acMonsterNum[32];
	int iMonsterNumShow;

	GetPrivateProfileSectionNamesA(
		acSectionName, 
		256, 
		".\\Data\\Monster.ini");
	strcpy_s(acMonsterNum,32,acSectionName + iSectionLen);
	iSectionLen += int(strlen(acMonsterNum) + 1);

	//��ȡ����
	iMonsterNumShow = GetPrivateProfileIntA(
		acMonsterNum, //ָ����ģ��
		"��������", //ָ���ļ�
		-1, //���Ҳ���ָ�������ݷ��ص�ֵ
		".\\Data\\Monster.ini"); //ָ����ini�ļ�

	MonsterData = new Monster[iMonsterNumShow * sizeof(Monster)];
	char *TempName = new char[32 * iMonsterNumShow];

	for (int i = 0;i < iMonsterNumShow;++i)
	{
		strcpy_s(TempName,32,acSectionName + iSectionLen);
		iSectionLen += int(strlen(TempName) + 1);

		GetPrivateProfileStringA(
			TempName,
			"Name",
			"!?", //���Ҳ���ָ�������ݷ��ص��ַ���
			MonsterData[i].name, //���ڵõ��ַ������ַ�����
			256, //���ڵõ��ַ������ַ����鳤��
			".\\Data\\Monster.ini");
		
		//id
		MonsterData[i].id = GetPrivateProfileIntA(
			TempName, //ָ����ģ��
			"Id", //ָ���ļ�
			-1, //���Ҳ���ָ�������ݷ��ص�ֵ
			".\\Data\\Monster.ini"); //ָ����ini�ļ�
		//����ֵ
		MonsterData[i].Hp = GetPrivateProfileIntA(
			TempName, //ָ����ģ��
			"Hp", //ָ���ļ�
			-1, //���Ҳ���ָ�������ݷ��ص�ֵ
			".\\Data\\Monster.ini"); //ָ����ini�ļ�
		//������
		MonsterData[i].Atk = GetPrivateProfileIntA(
			TempName, //ָ����ģ��
			"Atk", //ָ���ļ�
			-1, //���Ҳ���ָ�������ݷ��ص�ֵ
			".\\Data\\Monster.ini"); //ָ����ini�ļ�
		//������
		MonsterData[i].Def = GetPrivateProfileIntA(
			TempName, //ָ����ģ��
			"Def", //ָ���ļ�
			-1, //���Ҳ���ָ�������ݷ��ص�ֵ
			".\\Data\\Monster.ini"); //ָ����ini�ļ�
		//���
		MonsterData[i].Gold = GetPrivateProfileIntA(
			TempName, //ָ����ģ��
			"Gold", //ָ���ļ�
			-1, //���Ҳ���ָ�������ݷ��ص�ֵ
			".\\Data\\Monster.ini"); //ָ����ini�ļ�
		//����ֵ
		MonsterData[i].Exp = GetPrivateProfileIntA(
			TempName, //ָ����ģ��
			"Exp", //ָ���ļ�
			-1, //���Ҳ���ָ�������ݷ��ص�ֵ
			".\\Data\\Monster.ini"); //ָ����ini�ļ�

		//����
	}
	return iMonsterNumShow;
}

#endif