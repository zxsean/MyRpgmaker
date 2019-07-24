#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

class CScene;

class CUI
{
public:
	//控件矩形
	int x1, y1, x2, y2;

	//控件激活标志
	//只有active为true的控件才能被绘制、响应消息
	bool active;

	//所属场景
	CScene* scene;

	//构造
	CUI(int X1, int Y1, int X2, int Y2, bool Active = true);

	//设置控件矩形
	void SetPosition(int X1, int Y1, int X2, int Y2);

	//设置控件激活标志
	void SetActive(bool Active);

	//可扩展部分

	//鼠标
	virtual void CursorEnter();
	virtual void CursorQuit();

	virtual void CursorInMove(int x, int y);
	virtual void CursorOutMove();

	virtual void LButtonInDown(int x, int y);
	virtual void MButtonInDown(int x, int y);
	virtual void RButtonInDown(int x, int y);
	virtual void LButtonInUp(int x, int y);
	virtual void MButtonInUp(int x, int y);
	virtual void RButtonInUp(int x, int y);

	virtual void LButtonOutDown();
	virtual void MButtonOutDown();
	virtual void RButtonOutDown();
	virtual void LButtonOutUp();
	virtual void MButtonOutUp();
	virtual void RButtonOutUp();

	//键盘
	virtual void KeyDown(int Key);
	virtual void KeyUp(int Key);
	//virtual void Char(int c, bool doublebyte);

	//输出
	virtual void Render();

	//初始化
	virtual void Init();

	//结束
	virtual void End();
};

#endif