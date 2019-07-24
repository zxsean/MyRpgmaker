#ifndef _Item_H_
#define _Item_H_

Item* ItemData;

int LoadItemini()
{
	char acSectionName[256];//ģ����
	int iSectionLen = 0;//��ȡ����
	char acItemNum[32];
	int iItemNumShow;


	GetPrivateProfileSectionNamesA(
		acSectionName, 
		256, 
		".\\Data\\Item.ini");
	strcpy_s(acItemNum,32,acSectionName + iSectionLen);
	iSectionLen += int(strlen(acItemNum) + 1);

	//��ȡ����
	iItemNumShow = GetPrivateProfileIntA(
		acItemNum, //ָ����ģ��
		"��������", //ָ���ļ�
		-1, //���Ҳ���ָ�������ݷ��ص�ֵ
		".\\Data\\Item.ini"); //ָ����ini�ļ�

	//std::cout <<iTalkNumShow<<std::endl;
	ItemData = new Item[iItemNumShow * sizeof(Item)];
	char *TempName = new char[32 * iItemNumShow];

	for (int i = 0;i < iItemNumShow;++i)
	{
		strcpy_s(TempName,32,acSectionName + iSectionLen);
		iSectionLen += int(strlen(TempName) + 1);

		GetPrivateProfileStringA(
			TempName,
			"Name",
			"!?", //���Ҳ���ָ�������ݷ��ص��ַ���
			ItemData[i].name, //���ڵõ��ַ������ַ�����
			256, //���ڵõ��ַ������ַ����鳤��
			".\\Data\\Item.ini");

		GetPrivateProfileStringA(
			TempName,
			"Text",
			"!?", //���Ҳ���ָ�������ݷ��ص��ַ���
			ItemData[i].ItemText, //���ڵõ��ַ������ַ�����
			256, //���ڵõ��ַ������ַ����鳤��
			".\\Data\\Item.ini");
		//Num
		ItemData[i].ItemNum = GetPrivateProfileIntA(
			TempName, //ָ����ģ��
			"ItemNum", //ָ���ļ�
			-1, //���Ҳ���ָ�������ݷ��ص�ֵ
			".\\Data\\Item.ini"); //ָ����ini�ļ�
		//ID
		ItemData[i].id = GetPrivateProfileIntA(
			TempName, //ָ����ģ��
			"Id", //ָ���ļ�
			-1, //���Ҳ���ָ�������ݷ��ص�ֵ
			".\\Data\\Item.ini"); //ָ����ini�ļ�
		//����ֵ
		ItemData[i].HpAdd = GetPrivateProfileIntA(
			TempName, //ָ����ģ��
			"Hp", //ָ���ļ�
			-1, //���Ҳ���ָ�������ݷ��ص�ֵ
			".\\Data\\Item.ini"); //ָ����ini�ļ�
		//ħ��ֵ
		ItemData[i].MpAdd = GetPrivateProfileIntA(
			TempName, //ָ����ģ��
			"Mp", //ָ���ļ�
			-1, //���Ҳ���ָ�������ݷ��ص�ֵ
			".\\Data\\Item.ini"); //ָ����ini�ļ�
		//������
		ItemData[i].AtkAdd = GetPrivateProfileIntA(
			TempName, //ָ����ģ��
			"Atk", //ָ���ļ�
			-1, //���Ҳ���ָ�������ݷ��ص�ֵ
			".\\Data\\Item.ini"); //ָ����ini�ļ�
		//������
		ItemData[i].DefAdd = GetPrivateProfileIntA(
			TempName, //ָ����ģ��
			"Def", //ָ���ļ�
			-1, //���Ҳ���ָ�������ݷ��ص�ֵ
			".\\Data\\Item.ini"); //ָ����ini�ļ�
		//����	
		ItemData[i].AgiAdd = GetPrivateProfileIntA(
			TempName, //ָ����ģ��
			"Agi", //ָ���ļ�
			-1, //���Ҳ���ָ�������ݷ��ص�ֵ
			".\\Data\\Item.ini"); //ָ����ini�ļ�
		//ħ��
		ItemData[i].MagAdd = GetPrivateProfileIntA(
			TempName, //ָ����ģ��
			"Mag", //ָ���ļ�
			-1, //���Ҳ���ָ�������ݷ��ص�ֵ
			".\\Data\\Item.ini"); //ָ����ini�ļ�
		//�۸�
		ItemData[i].Price = GetPrivateProfileIntA(
			TempName, //ָ����ģ��
			"Price", //ָ���ļ�
			-1, //���Ҳ���ָ�������ݷ��ص�ֵ
			".\\Data\\Item.ini"); //ָ����ini�ļ�
		//����
		ItemData[i].Type = GetPrivateProfileIntA(
			TempName, //ָ����ģ��
			"Type", //ָ���ļ�
			-1, //���Ҳ���ָ�������ݷ��ص�ֵ
			".\\Data\\Item.ini"); //ָ����ini�ļ�
	}
	return iItemNumShow;
}

#endif