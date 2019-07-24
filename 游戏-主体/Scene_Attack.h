#ifndef _SCENE_ATTACK_H_
#define _SCENE_ATTACK_H_

#include "Frame\Scene.h"
#include "Frame\GameFrame.h"
#include "Frame\Vector2D.h"
#include "Scene_Data.h"

#define _BATTLE_WAIT 0 //�ȴ�����
#define _BATTLE_SELECT 1 //ѡ�����
#define _BATTLE_ANIMATION 2 //�����ҷ�ս��
#define _BATTLE_ENEMY 3 //���˻غ�
#define _BATTLE_VICTORY 4 //ʤ��
#define _BATTLE_ITEM 5 //����
#define _BATTLE_JN 6 //����
#define _BATTLE_OVER 7 //GameOver

#define _TYPE_GJ 0
#define _TYPE_JN 1

#define _HERO_NORMAL 0
#define _HERO_VICTORY 1
#define _HERO_DEAD 2

#define _GETITEM 20

class CScene_Attack : public CScene
{
	//��������
	int m_Battle_BackBmp; //ս������ͼid
	Monster m_Battle_Enemy[3]; //��������,-1�����޵���
	int m_Battle_EnemyNum;

	//ѡ��
	int m_Select_X; //ѡ������
	int m_Select_Animation;
	int m_Select_PicTimer;
	int m_HeroAttackType;
	//ս������
	int m_Attack_Animation;
	bool m_ShowAttack;
	//�ж��Ƿ�������bossս
	bool m_LastFight;
	//Ӣ��ս������
	int m_HeroBattle_Animation; 
	int m_HeroBattle_PicTimer;
	int m_HeroBattle_Victory; //�Ƿ񲥷�ʤ������

	//Ӣ�۶���
	CVector2D m_HeroBattleMove;
	bool m_HeroBattleMoveGo;
	CVector2D TempTest;

	//Ѫ������
	int m_HpBar_Animation;

	//����ѡ��
	CVector2D m_Battle_Enemy_XY[3];
	int m_Battle_EnemySelect;

	//���˹����߼�
	int m_EnemyTimer;
	int m_EnemyAttackSelect;
	int m_E_Attack_Animation;
	bool m_E_ShowAttack;

	//�ж��Ƿ񱩻�
	bool m_BaoJi;
	//�ж��Ƿ�����
	bool m_Miss;

	//ս������
	int m_Battle_Scene; 

	//��д����
	int m_CutInTimer;
	
	//����ʤ������
	int m_GetGold;
	int m_GetExp;
	int m_GetItem;
	int m_GetItemId;
	int m_LevelUp;

	////Ӣ������
	//CScene_Data* HeroData;

	CGameFrame* pGF;

public:
	virtual void Init();
	virtual void Enter();
	virtual void Run();
	virtual void Quit();
	//virtual void End();

	void SetData(int id, int Enemy1, int Enemy2 = -1, int Enemy3 = -1);
	
	//�õ���������
	void GetEnemyData();
	//��Ⱦ
	void DrawBackBmp();
	void DrawEnemy();
	void DrawHero();
	void DrawState();
	void DrawSelect();
	void DrawAttack();
	void DrawHpBar();
	void DrawHeroShadow();
	//Ӣ���ƶ�
	void HeroMove();
	//���˹����߼�
	void EnemyAttack();
	void DrawEnemyAttack();
	//������д
	void ShowCutIn();
	//Ӣ������
	CScene_Data* HeroData;
};


#endif