#ifndef _SCENE_DATA_H_
#define _SCENE_DATA_H_

#include "Frame\Scene.h"
#include "Frame\GameFrame.h"
#include "File\Rpg.h"

#define _MAX_ITEMNUM 20 //道具上限

class CScene_Data : public CScene
{
	CGameFrame* pGF;

	virtual void Init();
	//virtual void Enter();
	virtual void Run();
	//virtual void Quit();
	//virtual void End();

	//载入对话
	void LoadTalkData();
	//载入敌人
	void LoadEnemyData();
	//载入道具
	void LoadItemData();
	//载入任务
	void LoadMission();
	//载入地图遇敌数据
	void LoadYuDiData();
public:
	CRpg Hero;//声明英雄
	//对话
	std::map<int, Type_Talk> _TalkData;
	//道具
	std::map<int, Item> _ItemData;
	//敌人
	std::map<int, Monster> _MonsterData;
	//地图遇敌率
	int m_MapNum;
	std::vector<MapYuDi> _MapYuDiData;
	int GetMapNum();

	bool AddItem(int id);
	void NewGame(char* n);
	void LoadGame();
	//任务系统
	bool MissionCheck(int Mission_ID); //任务

	//装备系统
	void AddEquip(int id, int Type);
	void EraseEquip(int id, int Type);
};

#endif