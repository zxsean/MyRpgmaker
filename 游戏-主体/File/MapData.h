#ifndef _MAP_DATA_H
#define _MAP_DATA_H

#include "MapCrash.h"

#define _MAP_W 40
#define _MAP_H 30
#define _MAP_S (_MAP_W * _MAP_H)

class CMapData //��ǰ��ͼ��Ϣ�ṹ��
{
	int m_Map_W; //��ͼ��
	int m_Map_H; //��ͼ��
	int m_ID; //��ͼID
	char* m_MapDX; //��ͼ���β�
	char* m_MapJZ; //��ͼ������
	_Crash_Data* m_MapCrash; //��ͼ��ײ��
	char* m_MapObject; //��ͼ�����

public:	
	CMapData();
	CMapData(int ID);
	~CMapData();
	CMapData(const CMapData& that);
	CMapData& operator = (const CMapData& that);

	int GetMap_W(); //�õ���ͼ��
	int GetMap_H(); //�õ���ͼ��
	int GetMap_ID(); //�õ���ͼID
	int GetMap_S(); //�õ���ͼ��С

	_Crash_Data* GetMap_Crash(); //�õ���ײ��
	char* GetMap_Object(); //�õ������
	char* GetMap_DX(); //�õ����β�
	char* GetMap_JZ(); //�õ�������

	void SetMap_ID(int id); //���õ�ͼid
	void ClearMap(); //��յ�ͼ
	void SetNewMap(int id); //�½���ͼ

	bool SetMapData_Crash(int x, int y, _Crash_Data i); //���õ�ͼ����
	bool SetMapData_Object(int x, int y, int i); 
	bool SetMapData_DX(int x, int y, int i); 
	bool SetMapData_JZ(int x, int y, int i); 
	_Crash_Data GetMap_CrashData(int x, int y, int w);

	void FillDx(int i); //������
};

#endif