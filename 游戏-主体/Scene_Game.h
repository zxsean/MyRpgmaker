#ifndef _SCENE2_H_
#define _SCENE2_H_

#include "Frame\Scene.h"
#include "Frame\GameFrame.h"
#include "Frame\CBmpButton.h"
#include "File\MapData.h"
#include "File\TalkData.h"
#include "File\NpcData.h"
#include "Scene_Data.h"
#include <vector>

#define _SCENE_WALK 0
#define _SCENE_TALK 1
#define _SCENE_SHOP 2
#define _SCENE_SHOPIN 3
#define _SCENE_BATTLE 4

#define _GODIR_DOWN 1
#define _GODIR_LEFT 2
#define _GODIR_RIGHT 3
#define _GODIR_UP 4

#define _GO_SIZE 4 //步长

#define _PIC_W 32
#define _PIC_H 32

#define _LJ_W 40 //逻辑宽(格子为单位)
#define _LJ_H 30 //逻辑高(格子为单位)
#define _LJ_S (_LJ_W * _LJ_H) //逻辑总大小(格子为单位)
#define _Z_W (_LJ_W * _PIC_W) //总宽(像素为单位)
#define _Z_H (_LJ_H * _PIC_H) //总高(像素为单位)

#define _SK_W 640 //视口宽(像素为单位)
#define _SK_H 480 //视口高(像素为单位)

#define _x_y_i(x,y) ((y)*(_MAP_W)+(x)) //坐标转下标
class CButton_Return : public CBmpButton
{
public:
	CButton_Return();
	void LButtonInUp(int x, int y);
};

class CButton_Buy : public CBmpButton
{
public:
	CButton_Buy();
	void LButtonInUp(int x, int y);
};

class CButton_Sell : public CBmpButton
{
public:
	CButton_Sell();
	void LButtonInUp(int x, int y);
};

class CScene_Game : public CScene
{
	//游戏场景数据
	int g_Mapid;
	CMapData g_Map; //地图
	std::map<int, CMapData> g_MapList; //地图映射
	char* g_MapDX; //地图地形层
	char* g_MapBuild; //地图建筑层
	_Crash_Data* g_MapCrash; //地图碰撞层
	char* g_MapObject; //地图物件层
	
	//对话战斗
	int m_MonsterType;
	int m_BattleBc;

	//遇敌率
	MapYuDi g_YuDi;

	//英雄数据
	int m_HeroX; //x坐标
	int m_HeroY; //y坐标
	int m_NowHero_x; //英雄现在x
	int m_NowHero_y; //英雄现在y
	int m_Dir; //方向
	int m_Animation; //动画帧数
	bool m_CanGo; //移动标示
	int Scene_State; //场景状态
	int Shop_State; //商店场景

	//卷轴用
	int m_JZ_HeroX, m_JZ_HeroY; //英雄左上角坐标
	int m_JZ_ViewX, m_JZ_ViewY; //视口(客户区)左上角坐标

	//对话用
	std::vector<CTalkData> m_TalkData;

	//英雄数据
	CScene_Data* HeroData;

	CGameFrame* pGF;

	virtual void Init();
	virtual void Enter();
	virtual void Run();
	virtual void Quit();
	//virtual void End();

	void Keypress(int Key); //响应移动按键
	void HeroMove(); //英雄移动
	void ChangeMap(int MapId); //切换地图
	void GetMB_XY(int& x, int& y, int Key); //得到目标X,Y
	void SetTalkData(char* Talk, int TalkBmp, char* TalkName = "???");

	//渲染
	void DrawHero();
	void DrawDX(); //渲染地形
	void DrawUpHero(); //渲染地图-->显示在英雄之上,制造遮盖效果
	void DrawDownHero(); //渲染地图-->显示在英雄之下,制造遮盖效果

	//战斗场景数据设置
	void SetBattleData(int BmpId, int Enemy1, int Enemy2 = -1, int Enemy3 = -1);

	//遇敌
	void YuDi();	

	//商店
	void Shop();

	//载入地图
	void LoadMapData();

	//卷轴
	//更新视口
	void UpdateView();
public:
	//记录场景
	char* m_CJ;

	//设置场景
	void SetScene_State(int id);
	void SetShop_State(int id);
	void SetReset(); //重置数据
	void LoadData(); //读档
};

#endif