#include "MapData.h"

CMapData::CMapData()
:
m_Map_W(_MAP_W),
m_Map_H(_MAP_H),
m_ID(0)
{
	m_MapCrash = new _Crash_Data[m_Map_W * m_Map_H];
	m_MapObject = new char[m_Map_W * m_Map_H];
	m_MapDX = new char[m_Map_W * m_Map_H];
	m_MapJZ = new char[m_Map_W * m_Map_H];
	ClearMap();
}

CMapData::CMapData(int ID)
:
m_Map_W(_MAP_W),
m_Map_H(_MAP_H),
m_ID(ID)
{
	m_MapCrash = new _Crash_Data[m_Map_W * m_Map_H];
	m_MapObject = new char[m_Map_W * m_Map_H];
	m_MapDX = new char[m_Map_W * m_Map_H];
	m_MapJZ = new char[m_Map_W * m_Map_H];
	ClearMap();
}

CMapData::CMapData(const CMapData& that)
:
m_Map_W(that.m_Map_W),
m_Map_H(that.m_Map_H),
m_ID(that.m_ID)
{
	m_MapCrash = new _Crash_Data[m_Map_W * m_Map_H];
	m_MapObject = new char[m_Map_W * m_Map_H];
	m_MapDX = new char[m_Map_W * m_Map_H];
	m_MapJZ = new char[m_Map_W * m_Map_H];

	for (int i = 0; i < m_Map_W * m_Map_H; ++i)
	{
		m_MapCrash[i] = that.m_MapCrash[i];
		m_MapJZ[i] = that.m_MapJZ[i];
		m_MapDX[i] = that.m_MapDX[i];
		m_MapObject[i] = that.m_MapObject[i];
	}
}

CMapData& CMapData::operator = (const CMapData& that)
{
	if (this != &that)
	{
		m_Map_W = that.m_Map_W; //地图宽
		m_Map_H = that.m_Map_H; //地图高
		m_ID = that.m_ID; //地图ID
		delete [] m_MapCrash;
		delete [] m_MapObject;
		delete [] m_MapDX;
		delete [] m_MapJZ;
		m_MapCrash = new _Crash_Data[m_Map_W * m_Map_H];
		m_MapDX = new char[m_Map_W * m_Map_H];
		m_MapObject = new char[m_Map_W * m_Map_H];
		m_MapJZ = new char[m_Map_W * m_Map_H];

		for (int i = 0; i < m_Map_W * m_Map_H; ++i)
		{
			m_MapCrash[i] = that.m_MapCrash[i];
			m_MapJZ[i] = that.m_MapJZ[i];
			m_MapDX[i] = that.m_MapDX[i];
			m_MapObject[i] = that.m_MapObject[i];
		}
	}
	return *this;
}

CMapData::~CMapData()
{
	if(m_MapCrash)
		delete [] m_MapCrash;
	if(m_MapObject)
		delete [] m_MapObject;
	if(m_MapDX)
		delete [] m_MapDX;
	if(m_MapJZ)
		delete [] m_MapJZ;
}

int CMapData::GetMap_W() //得到地图宽
{
	return m_Map_W;
}

int CMapData::GetMap_H() //得到地图高
{
	return m_Map_H;
}

int CMapData::GetMap_ID() //得到地图ID
{
	return m_ID;
}

int CMapData::GetMap_S() //得到地图大小
{
	return m_Map_W * m_Map_H;
}

_Crash_Data* CMapData::GetMap_Crash() //得到碰撞层
{
	return m_MapCrash;
}

char* CMapData::GetMap_Object() //得到物件层
{
	return m_MapObject;
}

char* CMapData::GetMap_DX() //得到地形层
{
	return m_MapDX;
}

char* CMapData::GetMap_JZ() //得到建筑层
{
	return m_MapJZ;
}

void CMapData::ClearMap()
{
	//全部初始化为-1
	for (int i = 0; i < m_Map_W * m_Map_H; ++i)
	{
		m_MapCrash[i].Type = 0;
		m_MapCrash[i].Id = 0;
		m_MapCrash[i].x = 0;
		m_MapCrash[i].y = 0;

		m_MapObject[i] = -1;
		m_MapDX[i] = -1;
		m_MapJZ[i] = -1;
	}
}

void CMapData::SetMap_ID(int id)
{
	m_ID = id;
}

void CMapData::SetNewMap(int id)
{
	SetMap_ID(id);
	ClearMap();
}

bool CMapData::SetMapData_Crash(int x, int y, _Crash_Data i)
{
	if (x < 0 || x > m_Map_W || y < 0 || y > m_Map_H)
		return false;
	m_MapCrash[x + y * m_Map_W] = i;
	return true;
}

bool CMapData::SetMapData_Object(int x, int y, int i)
{
	if (x < 0 || x > m_Map_W || y < 0 || y > m_Map_H)
		return false;
	m_MapObject[x + y * m_Map_W] = i;
	return true;
}

bool CMapData::SetMapData_DX(int x, int y, int i)
{
	if (x < 0 || x > m_Map_W || y < 0 || y > m_Map_H)
		return false;
	m_MapDX[x + y * m_Map_W] = i;
	return true;
}

bool CMapData::SetMapData_JZ(int x, int y, int i)
{
	if (x < 0 || x > m_Map_W || y < 0 || y > m_Map_H)
		return false;
	m_MapJZ[x + y * m_Map_W] = i;
	return true;
}

_Crash_Data CMapData::GetMap_CrashData(int x, int y, int w)
{
	return m_MapCrash[x + y * w];
}

void CMapData::FillDx(int Data)
{
	for (int i = 0; i < m_Map_W * m_Map_H; ++i)
	m_MapDX[i] = Data;
}
