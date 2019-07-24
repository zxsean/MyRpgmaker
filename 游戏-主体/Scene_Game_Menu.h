#ifndef _SCENE_GAME_MENU_H_
#define _SCENE_GAME_MENU_H_

#include "Frame\Scene.h"
#include "Frame\GameFrame.h"
#include "Scene_Data.h"

#define _MENU_WAIT 0 //初始菜单
#define _MENU_STATE 1 //状态
#define _MENU_ITEM 2 //道具
#define _MENU_EQUIP 3 //装备
#define _MENU_MISSION 4 //任务

class CScene_Game_Menu : public CScene
{
	//箭头动画帧数
	int m_Cursor_Pic;
	int m_Cursor_PicTimer;
	int m_Cursor_Y;

	//菜单状态
	int m_Menu;

	//英雄动画
	int m_HeroBattle_PicTimer;
	int m_HeroBattle_Animation;
	//血条动画
	int m_HpBar_Animation;

	CScene_Data* HeroData;

	CGameFrame* pGF;

	virtual void Init();
	virtual void Enter();
	virtual void Run();
	virtual void Quit();
	//virtual void End();

	void DrawBackBmp(); //显示背景
	void DrawHand(); //绘制手图标
	void DrawState(); //绘制状态
	void DrawItem(); //道具
	void DrawEquip(); //装备
};

#endif