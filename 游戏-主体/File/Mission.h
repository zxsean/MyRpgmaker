#ifndef _Mission_H_
#define _Mission_H_

struct Item
{
	int id;
	int ItemNum; //��������
	char name[32];
	char ItemText[256]; //��������
	int HpAdd;//����ֵֵ������
	int MpAdd;//����ֵ������
	int AtkAdd;//������������
	int DefAdd;//����ֵ������
	int AgiAdd;//����������
	int MagAdd;//ħ��������
	int Price;//�ۼ�
	int Type;//�ж��ǵ��߻���װ��
};

struct Type_Talk//�Ի�
{
	int id; //�Ի�Id
	char talk[256]; //�Ի�����
	int BmpId; //�Ի�ͷ��id
	char name[256]; //�Ի���������
};

struct Type_Level//����
{
	int level;
};

struct Type_Item//��Ʒ
{
	int wupinID;
	int wupinNum;
	Item Item;
};

struct MapYuDi
{
	int YuDiLv; //������
	int YuDiMapId; //���е�ͼid
	char Type[8]; //��������
};

struct Things
{
	int id; //����ID
	int hxid[8]; //��������ID����
	int type; //��������
	union Data//��������
	{
		Type_Talk t1;
		Type_Level t2;
		Type_Item t3;
	}data;
};

struct Mission//��������
{
	int id; //����ID
	int qxid; //ǰ��ID
	int hxid; //��������ID,���û�о�-1
	char MissionText[256];//��������
};

struct Monster
{
	int id; //id
	char name[32];
	int Hp;//����ֵ
	int Atk;//������
	int Def;//����ֵ
	int Gold;//��ҵ���
	int Exp;//����ֵ
};

#endif