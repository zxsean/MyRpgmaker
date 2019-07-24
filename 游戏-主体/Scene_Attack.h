#ifndef _SCENE_ATTACK_H_
#define _SCENE_ATTACK_H_

#include "Frame\Scene.h"
#include "Frame\GameFrame.h"
#include "Frame\Vector2D.h"
#include "Scene_Data.h"

#define _BATTLE_WAIT 0 //等待命令
#define _BATTLE_SELECT 1 //选择敌人
#define _BATTLE_ANIMATION 2 //播放我方战斗
#define _BATTLE_ENEMY 3 //敌人回合
#define _BATTLE_VICTORY 4 //胜利
#define _BATTLE_ITEM 5 //道具
#define _BATTLE_JN 6 //技能
#define _BATTLE_OVER 7 //GameOver

#define _TYPE_GJ 0
#define _TYPE_JN 1

#define _HERO_NORMAL 0
#define _HERO_VICTORY 1
#define _HERO_DEAD 2

#define _GETITEM 20

class CScene_Attack : public CScene
{
	//场景数据
	int m_Battle_BackBmp; //战斗背景图id
	Monster m_Battle_Enemy[3]; //敌人数据,-1代表无敌人
	int m_Battle_EnemyNum;

	//选择
	int m_Select_X; //选择坐标
	int m_Select_Animation;
	int m_Select_PicTimer;
	int m_HeroAttackType;
	//战斗动画
	int m_Attack_Animation;
	bool m_ShowAttack;
	//判断是否是最终boss战
	bool m_LastFight;
	//英雄战斗动画
	int m_HeroBattle_Animation; 
	int m_HeroBattle_PicTimer;
	int m_HeroBattle_Victory; //是否播放胜利动画

	//英雄动作
	CVector2D m_HeroBattleMove;
	bool m_HeroBattleMoveGo;
	CVector2D TempTest;

	//血条动画
	int m_HpBar_Animation;

	//敌人选择
	CVector2D m_Battle_Enemy_XY[3];
	int m_Battle_EnemySelect;

	//敌人攻击逻辑
	int m_EnemyTimer;
	int m_EnemyAttackSelect;
	int m_E_Attack_Animation;
	bool m_E_ShowAttack;

	//判断是否暴击
	bool m_BaoJi;
	//判断是否命中
	bool m_Miss;

	//战斗场景
	int m_Battle_Scene; 

	//特写动画
	int m_CutInTimer;
	
	//场景胜利奖励
	int m_GetGold;
	int m_GetExp;
	int m_GetItem;
	int m_GetItemId;
	int m_LevelUp;

	////英雄数据
	//CScene_Data* HeroData;

	CGameFrame* pGF;

public:
	virtual void Init();
	virtual void Enter();
	virtual void Run();
	virtual void Quit();
	//virtual void End();

	void SetData(int id, int Enemy1, int Enemy2 = -1, int Enemy3 = -1);
	
	//得到敌人数据
	void GetEnemyData();
	//渲染
	void DrawBackBmp();
	void DrawEnemy();
	void DrawHero();
	void DrawState();
	void DrawSelect();
	void DrawAttack();
	void DrawHpBar();
	void DrawHeroShadow();
	//英雄移动
	void HeroMove();
	//敌人攻击逻辑
	void EnemyAttack();
	void DrawEnemyAttack();
	//技能特写
	void ShowCutIn();
	//英雄数据
	CScene_Data* HeroData;
};


#endif