#ifndef _SCENE_H_
#define _SCENE_H_

#include "UI.h"
#include "sound//soundmanage.h"
#include <string>
#include <map>

class CScene
{
public:
	std::map<std::string, CUI*> m_UI;
	CUI* m_KeyInputUI;

	bool LoadUI(CUI* pUI, const char* ID);
	bool ReleaseUI(const char* ID);
	bool SetKeyInputUI(const char* ID = 0);

	static CSoundManage GameSound;

	CScene();
	virtual ~CScene();

	virtual void Init();
	virtual void Enter();
	virtual void Run();
	virtual void Quit();
	virtual void End();
};

#endif