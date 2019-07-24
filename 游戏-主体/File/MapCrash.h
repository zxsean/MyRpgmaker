#ifndef _MAP_CRASH_H
#define _MAP_CRASH_H

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