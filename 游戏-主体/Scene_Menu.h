#ifndef _SCENE1_H_
#define _SCENE1_H_

#include "Frame\Scene.h"
#include "Frame\GameFrame.h"
#include "Frame\ColorButton.h"
#include "Frame\CBmpButton.h"

class CButton_Start : public CBmpButton
{
public:
	CButton_Start();
	void CursorEnter();
	void CursorQuit();
	void LButtonInUp(int x, int y);
};

class CButton_Load : public CBmpButton
{
public:
	CButton_Load();
	void CursorEnter();
	void CursorQuit();
	void LButtonInUp(int x, int y);
};

class CButton_Help : public CBmpButton
{
public:
	CButton_Help();
	void CursorEnter();
	void CursorQuit();
	void LButtonInUp(int x, int y);
};

class CButton_Quit : public CBmpButton
{
public:
	CButton_Quit();
	void CursorEnter();
	void CursorQuit();
	void LButtonInUp(int x, int y);
};

class CScene_Menu : public CScene
{
	int ShowPicId;

	CGameFrame* pGF;

	virtual void Init();
	virtual void Enter();
	virtual void Run();
	virtual void Quit();
	//virtual void End();
public:
	void SetShowPicId(int id);
};

#endif