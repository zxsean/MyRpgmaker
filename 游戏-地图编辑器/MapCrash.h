#ifndef _MAP_CRASH_H
#define _MAP_CRASH_H

#define _CRASH_NO -1 //δ����
#define _CRASH_TL 0 //ͨ·
#define _CRASH_ZA 1 //�ϰ�
#define _CRASH_CS 2 //���͵�
#define _CRASH_NPC 3 //�¼�����

struct _Crash_Data
{
	int Type;
	int Id;
	int x;
	int y;

	_Crash_Data()
		:
	Type(0),
		Id(0),
		x(0),
		y(0)
	{
	}
};

#endif