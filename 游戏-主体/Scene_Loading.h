#ifndef _SCENE_LOADING_H_
#define _SCENE_LOADING_H_

#include "Frame\Scene.h"
#include "Frame\GameFrame.h"
#include "Scene_Game.h"

class CScene_Loading : public CScene
{
	//∂Øª≠ªÏ∫œ”√
	int m_Alpha;
	bool m_ShowOK;

	CScene_Game* m_Cj;

	CGameFrame* pGF;

	virtual void Init();
	virtual void Enter();
	virtual void Run();
	virtual void Quit();
	//virtual void End();
};

#endif