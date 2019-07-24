#ifndef _SCENE_SHOP_H_
#define _SCENE_SHOP_H_

#include "Frame\Scene.h"
#include "Frame\GameFrame.h"
#include "Frame\CBmpButton.h"
#include "Scene_Data.h"

class CScene_Load : public CScene
{
	CGameFrame* pGF;

	//гЂалЪ§Он
	CScene_Data* HeroData;

	virtual void Init();
	virtual void Enter();
	virtual void Run();
	virtual void Quit();
	//virtual void End();
public:
	void SaveGame();
};

#endif