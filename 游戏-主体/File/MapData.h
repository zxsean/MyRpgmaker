#ifndef _MAP_DATA_H
#define _MAP_DATA_H

#include "MapCrash.h"

#define _MAP_W 40
#define _MAP_H 30
#define _MAP_S (_MAP_W * _MAP_H)

class CMapData //当前地图信息结构体
{
	int m_Map_W; //地图宽
	int m_Map_H; //地图高
	int m_ID; //地图ID
	char* m_MapDX; //地图地形层
	char* m_MapJZ; //地图建筑层
	_Crash_Data* m_MapCrash; //地图碰撞层
	char* m_MapObject; //地图物件层

public:	
	CMapData();
	CMapData(int ID);
	~CMapData();
	CMapData(const CMapData& that);
	CMapData& operator = (const CMapData& that);

	int GetMap_W(); //得到地图宽
	int GetMap_H(); //得到地图高
	int GetMap_ID(); //得到地图ID
	int GetMap_S(); //得到地图大小

	_Crash_Data* GetMap_Crash(); //得到碰撞层
	char* GetMap_Object(); //得到物件层
	char* GetMap_DX(); //得到地形层
	char* GetMap_JZ(); //得到建筑层

	void SetMap_ID(int id); //设置地图id
	void ClearMap(); //清空地图
	void SetNewMap(int id); //新建地图

	bool SetMapData_Crash(int x, int y, _Crash_Data i); //设置地图数据
	bool SetMapData_Object(int x, int y, int i); 
	bool SetMapData_DX(int x, int y, int i); 
	bool SetMapData_JZ(int x, int y, int i); 
	_Crash_Data GetMap_CrashData(int x, int y, int w);

	void FillDx(int i); //填充地形
};

#endif