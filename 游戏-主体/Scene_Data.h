#ifndef _SCENE_DATA_H_
#define _SCENE_DATA_H_

#include "Frame\Scene.h"
#include "Frame\GameFrame.h"
#include "File\Rpg.h"

#define _MAX_ITEMNUM 20 //��������

class CScene_Data : public CScene
{
	CGameFrame* pGF;

	virtual void Init();
	//virtual void Enter();
	virtual void Run();
	//virtual void Quit();
	//virtual void End();

	//����Ի�
	void LoadTalkData();
	//�������
	void LoadEnemyData();
	//�������
	void LoadItemData();
	//��������
	void LoadMission();
	//�����ͼ��������
	void LoadYuDiData();
public:
	CRpg Hero;//����Ӣ��
	//�Ի�
	std::map<int, Type_Talk> _TalkData;
	//����
	std::map<int, Item> _ItemData;
	//����
	std::map<int, Monster> _MonsterData;
	//��ͼ������
	int m_MapNum;
	std::vector<MapYuDi> _MapYuDiData;
	int GetMapNum();

	bool AddItem(int id);
	void NewGame(char* n);
	void LoadGame();
	//����ϵͳ
	bool MissionCheck(int Mission_ID); //����

	//װ��ϵͳ
	void AddEquip(int id, int Type);
	void EraseEquip(int id, int Type);
};

#endif