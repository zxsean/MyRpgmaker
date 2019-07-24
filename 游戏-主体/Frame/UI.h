#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

class CScene;

class CUI
{
public:
	//�ؼ�����
	int x1, y1, x2, y2;

	//�ؼ������־
	//ֻ��activeΪtrue�Ŀؼ����ܱ����ơ���Ӧ��Ϣ
	bool active;

	//��������
	CScene* scene;

	//����
	CUI(int X1, int Y1, int X2, int Y2, bool Active = true);

	//���ÿؼ�����
	void SetPosition(int X1, int Y1, int X2, int Y2);

	//���ÿؼ������־
	void SetActive(bool Active);

	//����չ����

	//���
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

	//����
	virtual void KeyDown(int Key);
	virtual void KeyUp(int Key);
	//virtual void Char(int c, bool doublebyte);

	//���
	virtual void Render();

	//��ʼ��
	virtual void Init();

	//����
	virtual void End();
};

#endif