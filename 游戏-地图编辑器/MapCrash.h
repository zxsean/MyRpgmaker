#ifndef _MAP_CRASH_H
#define _MAP_CRASH_H

#define _CRASH_NO -1 //未定义
#define _CRASH_TL 0 //通路
#define _CRASH_ZA 1 //障碍
#define _CRASH_CS 2 //传送点
#define _CRASH_NPC 3 //事件触发

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