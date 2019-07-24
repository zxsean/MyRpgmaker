#include "GameOutput.h"
#include <io.h>

CGameOutput::CGameOutput(HWND hWnd)
:
m_hWnd(hWnd) //��ʼ������
{
	//�õ��ͻ������
	RECT r;
	GetClientRect(m_hWnd, &r);
	m_ClientW = r.right - r.left;
	m_ClientH = r.bottom - r.top;

	//�õ����豸
	m_MainDC = GetDC(m_hWnd);

	//�õ����豸
	//�մ����ļ����豸��Ҳ��HBITMAP,ֻ�������HBITMAP
	//��1*1��Ϊ��ɫ��ʽ,�޷������豸����BitBlt,���Ա�
	//�봴����ɫ��ʽ�����豸���ݵ�λͼѡ��,��ô֮���
	//������������豸�����豸��λͼ�豸����ͼ����
	m_BackDC = CreateCompatibleDC(m_MainDC);
	HBITMAP hbmp = CreateCompatibleBitmap(m_MainDC, m_ClientW, m_ClientH);
	DeleteObject(SelectObject(m_BackDC, hbmp));

	m_MirrorDC = CreateCompatibleDC(m_MainDC);
	hbmp = CreateCompatibleBitmap(m_MainDC, m_ClientW, m_ClientH);
	DeleteObject(SelectObject(m_MirrorDC, hbmp));
	//�������ֱ���͸��
	SetBkMode(m_BackDC, TRANSPARENT);
}

CGameOutput::~CGameOutput()
{
	for (std::map<std::string, HDC>::iterator i = m_Bmp.begin(); i != m_Bmp.end(); ++i)
		DeleteDC(i->second);

	for (std::map<std::string, HFONT>::iterator i = m_Font.begin(); i != m_Font.end(); ++i)
		DeleteObject(i->second);

	DeleteDC(m_MirrorDC);
	DeleteDC(m_BackDC);
	ReleaseDC(m_hWnd, m_MainDC);
}

void CGameOutput::Begin()
{
	BitBlt(m_BackDC, 0, 0, m_ClientW, m_ClientH, 0, 0, 0, WHITENESS);
}

void CGameOutput::End()
{
	BitBlt(m_MainDC, 0, 0, m_ClientW, m_ClientH, m_BackDC, 0, 0, SRCCOPY);
}

void CGameOutput::DrawDot(int x, int y, unsigned int c)
{
	SetPixel(m_BackDC, x, y, c);
}

void CGameOutput::DrawLine(int x1, int y1, int x2, int y2, unsigned int c)
{
	//��ʼ���¡��ϻ��ʶ�Ϊ0
	HPEN np = 0, op = 0;

	if (c != RGB(0, 0, 0))
	{
		np = CreatePen(PS_SOLID, 1, c);
		op = (HPEN)SelectObject(m_BackDC, np);
	}

	MoveToEx(m_BackDC, x1, y1, 0);
	LineTo(m_BackDC, x2, y2);

	if (np)
	{
		SelectObject(m_BackDC, op);
		DeleteObject(np);
	}
}

void CGameOutput::DrawRectangle(int x,
								int y,
								int w,
								int h,
								unsigned int pc,
								unsigned int bc)
{
	HPEN np = 0, op = 0;
	HBRUSH nrush = 0, orush = 0;
	if (pc != RGB(0, 0, 0))
	{
		np = CreatePen(PS_SOLID, 1, pc);
		op = (HPEN)SelectObject(m_BackDC, np);
	}

	if (bc != RGB(255, 255, 255))
	{
		nrush = CreateSolidBrush(bc);
		orush = (HBRUSH)SelectObject(m_BackDC, nrush);
	}

	Rectangle(m_BackDC, x, y, x + w,y + h);

	if (nrush)
	{
		SelectObject(m_BackDC, orush);
		DeleteObject(nrush);
	}
	if (np)
	{
		SelectObject(m_BackDC, op);
		DeleteObject(np);
	}
}

void CGameOutput::DrawEllipse(int x,
							  int y,
							  int w,
							  int h,
							  unsigned int pc,
							  unsigned int bc)
{
	HPEN np = 0, op = 0;
	HBRUSH nrush = 0, orush = 0;
	if (pc != RGB(0, 0, 0))
	{
		np = CreatePen(PS_SOLID, 1, pc);
		op = (HPEN)SelectObject(m_BackDC, np);
	}

	if (bc != RGB(255, 255, 255))
	{
		nrush = CreateSolidBrush(bc);
		orush = (HBRUSH)SelectObject(m_BackDC, nrush);
	}

	Ellipse(m_BackDC, x, y, x + w,y + h);

	if (nrush)
	{
		SelectObject(m_BackDC, orush);
		DeleteObject(nrush);
	}
	if (np)
	{
		SelectObject(m_BackDC, op);
		DeleteObject(np);
	}
}

bool CGameOutput::LoadBmp(const char* bmpFile, const char* Key)
{
	//���ҵ��˾ͷ���ʧ��
	std::string s = Key;
	if (m_Bmp.find(s) != m_Bmp.end())
		return false;

	HBITMAP hbmp = (HBITMAP)LoadImage(
		0,
		bmpFile,
		IMAGE_BITMAP,
		0,
		0,
		LR_LOADFROMFILE);

	if (!hbmp)
		return false;

	HDC hdc = CreateCompatibleDC(m_MainDC);
	DeleteObject(SelectObject(hdc, hbmp));

	m_Bmp.insert(std::pair<std::string, HDC>(s, hdc));

	return true;
}

bool CGameOutput::LoadBmp(const char* bmpFile)
{
	return LoadBmp(bmpFile, bmpFile);
}

bool CGameOutput::DrawBmp(int dx,
						  int dy,
						  int dw,
						  int dh,
						  int sx,
						  int sy,
						  const char* Key)
{
	//���Ҳ����ͷ���ʧ��
	std::string s = Key;
	std::map<std::string, HDC>::iterator i = m_Bmp.find(s);
	if (i == m_Bmp.end())
		return false;

	BitBlt(m_BackDC, dx, dy, dw, dh, i->second, sx, sy, SRCCOPY);

	return true;
}

//����λͼ(��͸��ɫ)
bool CGameOutput::tDrawBmp(
						   int dx, 
						   int dy, 
						   int dw, 
						   int dh, 
						   int sx, 
						   int sy, 
						   const char* bmp,
						   unsigned int tc)
{
	//���Ҳ����ͷ���ʧ��
	std::string s = bmp;
	std::map<std::string, HDC>::iterator i = m_Bmp.find(s);
	if (i == m_Bmp.end())
		return false;

	TransparentBlt(
		m_BackDC, //Ŀ���豸
		dx, //Ŀ��������Ͻ�x
		dy, //Ŀ��������Ͻ�y
		dw, //Ŀ����ο�
		dh, //Ŀ����θ�
		i->second, //Դ�豸
		sx, //Դ�������Ͻ�x
		sy, //Դ�������Ͻ�x
		dw, //Դ���ο�
		dh, //Դ���θ�
		tc); //Ҫ���˵���ɫ

	return true;
}

//����һ��Ŀ¼���������λͼ
int CGameOutput::LoadDirectory(const char* d)
{
	std::vector<std::string> FileName;
	dfsFolder(d, ".bmp", FileName);

	if(FileName.size() > 0)
	{
		std::vector<std::string>::iterator i;
		for (i = FileName.begin(); i != FileName.end(); ++i)
		{
			LoadBmp(i->c_str(), i->c_str());
		}
	}

	return (int)FileName.size();
}

//����λͼ(������)
bool CGameOutput::mDrawBmp(int dx, int dy, int dw, int dh, int sx, int sy, const char* bmp, char m)
{
	//���Ҳ����ͷ���ʧ��
	std::string s = bmp;
	std::map<std::string, HDC>::iterator i = m_Bmp.find(s);
	if (i == m_Bmp.end())
		return false;

	switch(m)
	{
	case _M_N://������
		{
			BitBlt(m_BackDC, dx, dy, dw, dh, i->second, sx, sy, SRCCOPY);
			break;
		}
	case _M_H://ˮƽ����
		{
			StretchBlt(
				m_BackDC, //Ŀ���豸
				dx + dw - 1, //Ŀ��������Ͻ�x
				dy, //Ŀ��������Ͻ�y
				-dw, //Ŀ����ο�
				dh, //Ŀ����θ�
				i->second, //Դ�豸
				sx, //Դ�������Ͻ�x
				sy, //Դ�������Ͻ�x
				dw, //Դ���ο�
				dh, //Դ���θ�
				SRCCOPY);
			break;
		}
	case _M_V://��ֱ����
		{
			StretchBlt(
				m_BackDC, //Ŀ���豸
				dx, //Ŀ��������Ͻ�x
				dy + dh - 1, //Ŀ��������Ͻ�y
				dw, //Ŀ����ο�
				-dh, //Ŀ����θ�
				i->second, //Դ�豸
				sx, //Դ�������Ͻ�x
				sy, //Դ�������Ͻ�x
				dw, //Դ���ο�
				dh, //Դ���θ�
				SRCCOPY);
			break;
		}
	case _M_HV://ˮƽ��ֱ����
		{
			StretchBlt(
				m_BackDC, //Ŀ���豸
				dx + dw - 1, //Ŀ��������Ͻ�x
				dy + dh - 1, //Ŀ��������Ͻ�y
				-dw, //Ŀ����ο�
				-dh, //Ŀ����θ�
				i->second, //Դ�豸
				sx, //Դ�������Ͻ�x
				sy, //Դ�������Ͻ�x
				dw, //Դ���ο�
				dh, //Դ���θ�
				SRCCOPY);
			break;
		}
	}

	return true;
}

//����λͼ(��͸��ɫ������)
bool CGameOutput::tmDrawBmp(int dx, int dy, int dw, int dh, int sx, int sy, const char* bmp, unsigned int tc, char m)
{
	//���Ҳ����ͷ���ʧ��
	std::string s = bmp;
	std::map<std::string, HDC>::iterator i = m_Bmp.find(s);
	if (i == m_Bmp.end())
		return false;

	switch(m)
	{
	case _M_N://������
		{
			BitBlt(m_MirrorDC, 0, 0, dw, dh, i->second, sx, sy, SRCCOPY);
			break;
		}
	case _M_H://ˮƽ����
		{
			StretchBlt(
				m_MirrorDC, //Ŀ���豸
				0 + dw - 1, //Ŀ��������Ͻ�x
				0, //Ŀ��������Ͻ�y
				-dw, //Ŀ����ο�
				dh, //Ŀ����θ�
				i->second, //Դ�豸
				sx, //Դ�������Ͻ�x
				sy, //Դ�������Ͻ�x
				dw, //Դ���ο�
				dh, //Դ���θ�
				SRCCOPY);
			break;
		}
	case _M_V://��ֱ����
		{
			StretchBlt(
				m_MirrorDC, //Ŀ���豸
				0, //Ŀ��������Ͻ�x
				0 + dh - 1, //Ŀ��������Ͻ�y
				dw, //Ŀ����ο�
				-dh, //Ŀ����θ�
				i->second, //Դ�豸
				sx, //Դ�������Ͻ�x
				sy, //Դ�������Ͻ�x
				dw, //Դ���ο�
				dh, //Դ���θ�
				SRCCOPY);
			break;
		}
	case _M_HV://ˮƽ��ֱ����
		{
			StretchBlt(
				m_MirrorDC, //Ŀ���豸
				0 + dw - 1, //Ŀ��������Ͻ�x
				0 + dh - 1, //Ŀ��������Ͻ�y
				-dw, //Ŀ����ο�
				-dh, //Ŀ����θ�
				i->second, //Դ�豸
				sx, //Դ�������Ͻ�x
				sy, //Դ�������Ͻ�x
				dw, //Դ���ο�
				dh, //Դ���θ�
				SRCCOPY);
			break;
		}
	}
	//�Ӿ����豸���������豸
	TransparentBlt(
		m_BackDC, //Ŀ���豸
		dx, //Ŀ��������Ͻ�x
		dy, //Ŀ��������Ͻ�y
		dw, //Ŀ����ο�
		dh, //Ŀ����θ�
		m_MirrorDC, //Դ�豸
		sx, //Դ�������Ͻ�x
		sy, //Դ�������Ͻ�x
		dw, //Դ���ο�
		dh, //Դ���θ�
		tc); //Ҫ���˵���ɫ

	return true;
}

//������������
bool CGameOutput::CreateFont(int h, const char* n, const char* f)
{
	//���ҵ��˾ͷ���ʧ��
	std::string s = f;
	if (m_Font.find(s) != m_Font.end())
		return false;

	HFONT hfont = ::CreateFont(//����д��::������ϳ����е�CreateFont
		h, //����߶�(Ϊ0��Windows���ѡ��һ�����ʵĸ߶�)
		0, //������(Ϊ0��Windows����ݸ߶�����һ�����ʵĿ��)
		0, //�����е�б��,ʮ��֮��,����900,����������б90��,�����趨�߼���ͼģʽ
		0, //�����б��,ʮ��֮��,����900,��������б90��,�����趨�߼���ͼģʽ
		FW_NORMAL, //����Ĵ�ϸ
		FALSE, //�Ƿ�Ϊб����
		FALSE, //�Ƿ����»���
		FALSE, //�Ƿ��д�Խ��
		DEFAULT_CHARSET, //�ַ�����(DEFAULT_CHARSET��ǰ������Ĭ�ϱ���)
		OUT_DEFAULT_PRECIS, //��Windowsʵ���趨���ֵ����ƥ��ѡ��
		CLIP_DEFAULT_PRECIS, //��Windowsʵ���趨���ֵļ���ƥ��ѡ��
		DEFAULT_QUALITY,  //��Windowsʵ���趨���ֵ���ʾ����ƥ��ѡ��
		DEFAULT_PITCH | FF_DONTCARE, //�����ѡ��
		n); //��������

	if (!hfont)
		return false;

	m_Font.insert(std::pair<std::string, HFONT>(s, hfont));

	return true;
}

//�ͷ�����
bool CGameOutput::ReleaseFont(const char* f)
{
	//��δ�ҵ��ͷ���ʧ��
	std::string s = f;
	std::map<std::string, HFONT>::iterator i = m_Font.find(s);
	if (m_Font.find(s) == m_Font.end())
		return false;

	DeleteObject(i->second);
	i = m_Font.erase(i);
	return true;
}

//���Ƶ�������
bool CGameOutput::DrawText(const char* t, int x, int y, unsigned int c, const char* f)
{
	HFONT of = 0;
	//��������
	if (f != 0)
	{
		std::string s = f;
		std::map<std::string, HFONT>::iterator i = m_Font.find(s);
		if (i != m_Font.end())
			of = (HFONT)SelectObject(m_BackDC, i->second);
	}

	//����������ɫ
	if (c != RGB(0, 0, 0))
		SetTextColor(m_BackDC, c);

	TextOut(m_BackDC, x, y, t, (int)strlen(t));

	if (c != RGB(0, 0, 0))
		SetTextColor(m_BackDC, RGB(0, 0, 0));
	if (f != 0)
	{
		SelectObject(m_BackDC, of);
		DeleteObject(of);
	}

	return true;
}

//���ƶ�������
bool CGameOutput::DrawText(const char* t, int x, int y, int w, int h, unsigned int c, const char* f)
{
	HFONT of = 0;
	RECT r = {x, y, x + w, y + h};
	//��������
	if (f != 0)
	{
		std::string s = f;
		std::map<std::string, HFONT>::iterator i = m_Font.find(s);
		if (i != m_Font.end())
			of = (HFONT)SelectObject(m_BackDC, i->second);
	}

	//����������ɫ
	if (c != RGB(0, 0, 0))
		SetTextColor(m_BackDC, c);

	::DrawText(
		m_BackDC,
		t,
		(int)strlen(t),
		&r, //���ֻ������ھ���
		DT_WORDBREAK);


	if (c != RGB(0, 0, 0))
		SetTextColor(m_BackDC, RGB(0, 0, 0));
	if (f != 0)
	{
		SelectObject(m_BackDC, of);
		DeleteObject(of);
	}

	return true;
}

bool CGameOutput::ReleaseBmp(const char* Key)
{
	//��δ�ҵ��ͷ���ʧ��
	std::string s = Key;
	std::map<std::string, HDC>::iterator i = m_Bmp.find(s);
	if (m_Bmp.find(s) == m_Bmp.end())
		return false;

	DeleteDC(i->second);
	i = m_Bmp.erase(i);
	return true;
}

void CGameOutput::SetWindowTitle(const char* n)
{
	SetWindowText(m_hWnd, n);
}

bool CGameOutput::SetAlphaBlend(int dx, int dy, int dw, int dh, int sx, int sy, int Alpha, const char* bmp)
{
	//����Alpha���
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = Alpha; //Alphaֵ
	bf.AlphaFormat = 0;

	//���Ҳ����ͷ���ʧ��
	std::string s = bmp;
	std::map<std::string, HDC>::iterator i = m_Bmp.find(s);
	if (i == m_Bmp.end())
		return false;

	//Alpha���
	AlphaBlend(
		m_BackDC,
		dx, //Ŀ��������Ͻ�x
		dy, //Ŀ��������Ͻ�y
		dw, //Ŀ����ο�
		dh, //Ŀ����θ�
		i->second, //���ͼ
		sx, //Ŀ��������Ͻ�x
		sy, //Ŀ��������Ͻ�y
		dw, //Ŀ����ο�
		dh, //Ŀ����θ�
		bf);

	return true;
}

bool CGameOutput::tSetAlphaBlend(int dx, int dy, int dw, int dh, int sx, int sy, int Alpha, const char* bmp, unsigned int tc)
{
	////����Alpha���
	//BLENDFUNCTION bf;
	//bf.BlendOp = AC_SRC_OVER;
	//bf.BlendFlags = 0;
	//bf.SourceConstantAlpha = Alpha; //Alphaֵ
	//bf.AlphaFormat = 0;

	////���Ҳ����ͷ���ʧ��
	//std::string s = bmp;
	//std::map<std::string, HDC>::iterator i = m_Bmp.find(s);
	//if (i == m_Bmp.end())
	//	return false;

	////Alpha���
	//AlphaBlend(
	//	m_MirrorDC,
	//	dx, //Ŀ��������Ͻ�x
	//	dy, //Ŀ��������Ͻ�y
	//	dw, //Ŀ����ο�
	//	dh, //Ŀ����θ�
	//	i->second, //���ͼ
	//	sx, //Ŀ��������Ͻ�x
	//	sy, //Ŀ��������Ͻ�y
	//	dw, //Ŀ����ο�
	//	dh, //Ŀ����θ�
	//	bf);

	////�Ӿ����豸���������豸
	//TransparentBlt(
	//	m_BackDC, //Ŀ���豸
	//	dx, //Ŀ��������Ͻ�x
	//	dy, //Ŀ��������Ͻ�y
	//	dw, //Ŀ����ο�
	//	dh, //Ŀ����θ�
	//	m_MirrorDC, //Դ�豸
	//	sx, //Դ�������Ͻ�x
	//	sy, //Դ�������Ͻ�x
	//	dw, //Դ���ο�
	//	dh, //Դ���θ�
	//	tc); //Ҫ���˵���ɫ

	return true;
}

bool dfsFolder(std::string FolderPath, const char* Extensions, std::vector<std::string>& FileName)//��Ŀ¼����
{
	_finddata_t FileInfo;
	std::string strfind = FolderPath + "\\*";//���������ļ���Ŀ¼
	long Handle = (long)(_findfirst(strfind.c_str(), &FileInfo));

	if (Handle == -1L)//�Ƿ�Ŀ¼
		return false;

	do{
		//�ж��Ƿ�����Ŀ¼
		if (FileInfo.attrib & _A_SUBDIR)    
		{
			//�ж��Ƿ�����Ŀ¼
			if((strcmp(FileInfo.name,".") != 0 ) &&(strcmp(FileInfo.name,"..") != 0))   
			{
				std::string newPath = FolderPath + "\\" + FileInfo.name;
				//OutputDebugStr(newPath.c_str());
				dfsFolder(newPath, Extensions, FileName);
			}
		}
		else 
		{
			if(strstr(FileInfo.name, Extensions))//�ж��ļ�����
			{
				std::string Temp = FolderPath + "\\" + FileInfo.name;
				//OutputDebugStr(Temp.c_str());
				FileName.push_back(Temp);
			}
		}
	}while (_findnext(Handle, &FileInfo) == 0);

	_findclose(Handle);

	return true;
}