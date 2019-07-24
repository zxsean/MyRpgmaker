#ifndef _SCENE_END_H_
#define _SCENE_END_H_

#include "Frame\Scene.h"
#include "Frame\GameFrame.h"

class CScene_End : public CScene
{
	CGameFrame* pGF;

	virtual void Init();
	//virtual void Enter();
	virtual void Run();
	//virtual void Quit();
	//virtual void End();
};

#endif