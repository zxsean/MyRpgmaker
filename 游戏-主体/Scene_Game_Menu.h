#ifndef _SCENE_GAME_MENU_H_
#define _SCENE_GAME_MENU_H_

#include "Frame\Scene.h"
#include "Frame\GameFrame.h"
#include "Scene_Data.h"

#define _MENU_WAIT 0 //��ʼ�˵�
#define _MENU_STATE 1 //״̬
#define _MENU_ITEM 2 //����
#define _MENU_EQUIP 3 //װ��
#define _MENU_MISSION 4 //����

class CScene_Game_Menu : public CScene
{
	//��ͷ����֡��
	int m_Cursor_Pic;
	int m_Cursor_PicTimer;
	int m_Cursor_Y;

	//�˵�״̬
	int m_Menu;

	//Ӣ�۶���
	int m_HeroBattle_PicTimer;
	int m_HeroBattle_Animation;
	//Ѫ������
	int m_HpBar_Animation;

	CScene_Data* HeroData;

	CGameFrame* pGF;

	virtual void Init();
	virtual void Enter();
	virtual void Run();
	virtual void Quit();
	//virtual void End();

	void DrawBackBmp(); //��ʾ����
	void DrawHand(); //������ͼ��
	void DrawState(); //����״̬
	void DrawItem(); //����
	void DrawEquip(); //װ��
};

#endif