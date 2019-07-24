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

#define _GO_SIZE 4 //����

#define _PIC_W 32
#define _PIC_H 32

#define _LJ_W 40 //�߼���(����Ϊ��λ)
#define _LJ_H 30 //�߼���(����Ϊ��λ)
#define _LJ_S (_LJ_W * _LJ_H) //�߼��ܴ�С(����Ϊ��λ)
#define _Z_W (_LJ_W * _PIC_W) //�ܿ�(����Ϊ��λ)
#define _Z_H (_LJ_H * _PIC_H) //�ܸ�(����Ϊ��λ)

#define _SK_W 640 //�ӿڿ�(����Ϊ��λ)
#define _SK_H 480 //�ӿڸ�(����Ϊ��λ)

#define _x_y_i(x,y) ((y)*(_MAP_W)+(x)) //����ת�±�
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
	//��Ϸ��������
	int g_Mapid;
	CMapData g_Map; //��ͼ
	std::map<int, CMapData> g_MapList; //��ͼӳ��
	char* g_MapDX; //��ͼ���β�
	char* g_MapBuild; //��ͼ������
	_Crash_Data* g_MapCrash; //��ͼ��ײ��
	char* g_MapObject; //��ͼ�����
	
	//�Ի�ս��
	int m_MonsterType;
	int m_BattleBc;

	//������
	MapYuDi g_YuDi;

	//Ӣ������
	int m_HeroX; //x����
	int m_HeroY; //y����
	int m_NowHero_x; //Ӣ������x
	int m_NowHero_y; //Ӣ������y
	int m_Dir; //����
	int m_Animation; //����֡��
	bool m_CanGo; //�ƶ���ʾ
	int Scene_State; //����״̬
	int Shop_State; //�̵곡��

	//������
	int m_JZ_HeroX, m_JZ_HeroY; //Ӣ�����Ͻ�����
	int m_JZ_ViewX, m_JZ_ViewY; //�ӿ�(�ͻ���)���Ͻ�����

	//�Ի���
	std::vector<CTalkData> m_TalkData;

	//Ӣ������
	CScene_Data* HeroData;

	CGameFrame* pGF;

	virtual void Init();
	virtual void Enter();
	virtual void Run();
	virtual void Quit();
	//virtual void End();

	void Keypress(int Key); //��Ӧ�ƶ�����
	void HeroMove(); //Ӣ���ƶ�
	void ChangeMap(int MapId); //�л���ͼ
	void GetMB_XY(int& x, int& y, int Key); //�õ�Ŀ��X,Y
	void SetTalkData(char* Talk, int TalkBmp, char* TalkName = "???");

	//��Ⱦ
	void DrawHero();
	void DrawDX(); //��Ⱦ����
	void DrawUpHero(); //��Ⱦ��ͼ-->��ʾ��Ӣ��֮��,�����ڸ�Ч��
	void DrawDownHero(); //��Ⱦ��ͼ-->��ʾ��Ӣ��֮��,�����ڸ�Ч��

	//ս��������������
	void SetBattleData(int BmpId, int Enemy1, int Enemy2 = -1, int Enemy3 = -1);

	//����
	void YuDi();	

	//�̵�
	void Shop();

	//�����ͼ
	void LoadMapData();

	//����
	//�����ӿ�
	void UpdateView();
public:
	//��¼����
	char* m_CJ;

	//���ó���
	void SetScene_State(int id);
	void SetShop_State(int id);
	void SetReset(); //��������
	void LoadData(); //����
};

#endif