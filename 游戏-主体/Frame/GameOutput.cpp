#include "GameOutput.h"
#include <io.h>

CGameOutput::CGameOutput(HWND hWnd)
:
m_hWnd(hWnd) //初始化窗口
{
	//得到客户区宽高
	RECT r;
	GetClientRect(m_hWnd, &r);
	m_ClientW = r.right - r.left;
	m_ClientH = r.bottom - r.top;

	//得到主设备
	m_MainDC = GetDC(m_hWnd);

	//得到后备设备
	//刚创建的兼容设备中也有HBITMAP,只不过这个HBITMAP
	//是1*1且为单色格式,无法与主设备进行BitBlt,所以必
	//须创建颜色格式和主设备兼容的位图选入,那么之后才
	//可以用这个后备设备与主设备、位图设备进行图像传输
	m_BackDC = CreateCompatibleDC(m_MainDC);
	HBITMAP hbmp = CreateCompatibleBitmap(m_MainDC, m_ClientW, m_ClientH);
	DeleteObject(SelectObject(m_BackDC, hbmp));

	m_MirrorDC = CreateCompatibleDC(m_MainDC);
	hbmp = CreateCompatibleBitmap(m_MainDC, m_ClientW, m_ClientH);
	DeleteObject(SelectObject(m_MirrorDC, hbmp));
	//设置文字背景透明
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
	//初始化新、老画笔都为0
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
	//若找到了就返回失败
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
	//若找不到就返回失败
	std::string s = Key;
	std::map<std::string, HDC>::iterator i = m_Bmp.find(s);
	if (i == m_Bmp.end())
		return false;

	BitBlt(m_BackDC, dx, dy, dw, dh, i->second, sx, sy, SRCCOPY);

	return true;
}

//绘制位图(带透明色)
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
	//若找不到就返回失败
	std::string s = bmp;
	std::map<std::string, HDC>::iterator i = m_Bmp.find(s);
	if (i == m_Bmp.end())
		return false;

	TransparentBlt(
		m_BackDC, //目标设备
		dx, //目标矩形左上角x
		dy, //目标矩形左上角y
		dw, //目标矩形宽
		dh, //目标矩形高
		i->second, //源设备
		sx, //源矩形左上角x
		sy, //源矩形左上角x
		dw, //源矩形宽
		dh, //源矩形高
		tc); //要过滤的颜色

	return true;
}

//加载一个目录下面的所有位图
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

//绘制位图(带镜像)
bool CGameOutput::mDrawBmp(int dx, int dy, int dw, int dh, int sx, int sy, const char* bmp, char m)
{
	//若找不到就返回失败
	std::string s = bmp;
	std::map<std::string, HDC>::iterator i = m_Bmp.find(s);
	if (i == m_Bmp.end())
		return false;

	switch(m)
	{
	case _M_N://不镜像
		{
			BitBlt(m_BackDC, dx, dy, dw, dh, i->second, sx, sy, SRCCOPY);
			break;
		}
	case _M_H://水平镜像
		{
			StretchBlt(
				m_BackDC, //目标设备
				dx + dw - 1, //目标矩形左上角x
				dy, //目标矩形左上角y
				-dw, //目标矩形宽
				dh, //目标矩形高
				i->second, //源设备
				sx, //源矩形左上角x
				sy, //源矩形左上角x
				dw, //源矩形宽
				dh, //源矩形高
				SRCCOPY);
			break;
		}
	case _M_V://垂直镜像
		{
			StretchBlt(
				m_BackDC, //目标设备
				dx, //目标矩形左上角x
				dy + dh - 1, //目标矩形左上角y
				dw, //目标矩形宽
				-dh, //目标矩形高
				i->second, //源设备
				sx, //源矩形左上角x
				sy, //源矩形左上角x
				dw, //源矩形宽
				dh, //源矩形高
				SRCCOPY);
			break;
		}
	case _M_HV://水平垂直镜像
		{
			StretchBlt(
				m_BackDC, //目标设备
				dx + dw - 1, //目标矩形左上角x
				dy + dh - 1, //目标矩形左上角y
				-dw, //目标矩形宽
				-dh, //目标矩形高
				i->second, //源设备
				sx, //源矩形左上角x
				sy, //源矩形左上角x
				dw, //源矩形宽
				dh, //源矩形高
				SRCCOPY);
			break;
		}
	}

	return true;
}

//绘制位图(带透明色、镜像)
bool CGameOutput::tmDrawBmp(int dx, int dy, int dw, int dh, int sx, int sy, const char* bmp, unsigned int tc, char m)
{
	//若找不到就返回失败
	std::string s = bmp;
	std::map<std::string, HDC>::iterator i = m_Bmp.find(s);
	if (i == m_Bmp.end())
		return false;

	switch(m)
	{
	case _M_N://不镜像
		{
			BitBlt(m_MirrorDC, 0, 0, dw, dh, i->second, sx, sy, SRCCOPY);
			break;
		}
	case _M_H://水平镜像
		{
			StretchBlt(
				m_MirrorDC, //目标设备
				0 + dw - 1, //目标矩形左上角x
				0, //目标矩形左上角y
				-dw, //目标矩形宽
				dh, //目标矩形高
				i->second, //源设备
				sx, //源矩形左上角x
				sy, //源矩形左上角x
				dw, //源矩形宽
				dh, //源矩形高
				SRCCOPY);
			break;
		}
	case _M_V://垂直镜像
		{
			StretchBlt(
				m_MirrorDC, //目标设备
				0, //目标矩形左上角x
				0 + dh - 1, //目标矩形左上角y
				dw, //目标矩形宽
				-dh, //目标矩形高
				i->second, //源设备
				sx, //源矩形左上角x
				sy, //源矩形左上角x
				dw, //源矩形宽
				dh, //源矩形高
				SRCCOPY);
			break;
		}
	case _M_HV://水平垂直镜像
		{
			StretchBlt(
				m_MirrorDC, //目标设备
				0 + dw - 1, //目标矩形左上角x
				0 + dh - 1, //目标矩形左上角y
				-dw, //目标矩形宽
				-dh, //目标矩形高
				i->second, //源设备
				sx, //源矩形左上角x
				sy, //源矩形左上角x
				dw, //源矩形宽
				dh, //源矩形高
				SRCCOPY);
			break;
		}
	}
	//从镜像设备拷贝到后备设备
	TransparentBlt(
		m_BackDC, //目标设备
		dx, //目标矩形左上角x
		dy, //目标矩形左上角y
		dw, //目标矩形宽
		dh, //目标矩形高
		m_MirrorDC, //源设备
		sx, //源矩形左上角x
		sy, //源矩形左上角x
		dw, //源矩形宽
		dh, //源矩形高
		tc); //要过滤的颜色

	return true;
}

//创建文字字体
bool CGameOutput::CreateFont(int h, const char* n, const char* f)
{
	//若找到了就返回失败
	std::string s = f;
	if (m_Font.find(s) != m_Font.end())
		return false;

	HFONT hfont = ::CreateFont(//必须写上::否则会认成类中的CreateFont
		h, //字体高度(为0则Windows会根选择一个合适的高度)
		0, //字体宽度(为0则Windows会根据高度来设一个合适的宽度)
		0, //字体行的斜度,十分之几,比如900,则字体行倾斜90度,必须设定高级绘图模式
		0, //字体的斜度,十分之几,比如900,则字体倾斜90度,必须设定高级绘图模式
		FW_NORMAL, //字体的粗细
		FALSE, //是否为斜体字
		FALSE, //是否有下划线
		FALSE, //是否有穿越线
		DEFAULT_CHARSET, //字符编码(DEFAULT_CHARSET当前机器的默认编码)
		OUT_DEFAULT_PRECIS, //与Windows实际设定文字的外观匹配选项
		CLIP_DEFAULT_PRECIS, //与Windows实际设定文字的剪切匹配选项
		DEFAULT_QUALITY,  //与Windows实际设定文字的显示质量匹配选项
		DEFAULT_PITCH | FF_DONTCARE, //字体簇选项
		n); //文字字体

	if (!hfont)
		return false;

	m_Font.insert(std::pair<std::string, HFONT>(s, hfont));

	return true;
}

//释放字体
bool CGameOutput::ReleaseFont(const char* f)
{
	//若未找到就返回失败
	std::string s = f;
	std::map<std::string, HFONT>::iterator i = m_Font.find(s);
	if (m_Font.find(s) == m_Font.end())
		return false;

	DeleteObject(i->second);
	i = m_Font.erase(i);
	return true;
}

//绘制单行文字
bool CGameOutput::DrawText(const char* t, int x, int y, unsigned int c, const char* f)
{
	HFONT of = 0;
	//查找字体
	if (f != 0)
	{
		std::string s = f;
		std::map<std::string, HFONT>::iterator i = m_Font.find(s);
		if (i != m_Font.end())
			of = (HFONT)SelectObject(m_BackDC, i->second);
	}

	//设置字体颜色
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

//绘制多行文字
bool CGameOutput::DrawText(const char* t, int x, int y, int w, int h, unsigned int c, const char* f)
{
	HFONT of = 0;
	RECT r = {x, y, x + w, y + h};
	//查找字体
	if (f != 0)
	{
		std::string s = f;
		std::map<std::string, HFONT>::iterator i = m_Font.find(s);
		if (i != m_Font.end())
			of = (HFONT)SelectObject(m_BackDC, i->second);
	}

	//设置字体颜色
	if (c != RGB(0, 0, 0))
		SetTextColor(m_BackDC, c);

	::DrawText(
		m_BackDC,
		t,
		(int)strlen(t),
		&r, //文字绘制所在矩形
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
	//若未找到就返回失败
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
	//设置Alpha混合
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = Alpha; //Alpha值
	bf.AlphaFormat = 0;

	//若找不到就返回失败
	std::string s = bmp;
	std::map<std::string, HDC>::iterator i = m_Bmp.find(s);
	if (i == m_Bmp.end())
		return false;

	//Alpha混合
	AlphaBlend(
		m_BackDC,
		dx, //目标矩形左上角x
		dy, //目标矩形左上角y
		dw, //目标矩形宽
		dh, //目标矩形高
		i->second, //混合图
		sx, //目标矩形左上角x
		sy, //目标矩形左上角y
		dw, //目标矩形宽
		dh, //目标矩形高
		bf);

	return true;
}

bool CGameOutput::tSetAlphaBlend(int dx, int dy, int dw, int dh, int sx, int sy, int Alpha, const char* bmp, unsigned int tc)
{
	////设置Alpha混合
	//BLENDFUNCTION bf;
	//bf.BlendOp = AC_SRC_OVER;
	//bf.BlendFlags = 0;
	//bf.SourceConstantAlpha = Alpha; //Alpha值
	//bf.AlphaFormat = 0;

	////若找不到就返回失败
	//std::string s = bmp;
	//std::map<std::string, HDC>::iterator i = m_Bmp.find(s);
	//if (i == m_Bmp.end())
	//	return false;

	////Alpha混合
	//AlphaBlend(
	//	m_MirrorDC,
	//	dx, //目标矩形左上角x
	//	dy, //目标矩形左上角y
	//	dw, //目标矩形宽
	//	dh, //目标矩形高
	//	i->second, //混合图
	//	sx, //目标矩形左上角x
	//	sy, //目标矩形左上角y
	//	dw, //目标矩形宽
	//	dh, //目标矩形高
	//	bf);

	////从镜像设备拷贝到后备设备
	//TransparentBlt(
	//	m_BackDC, //目标设备
	//	dx, //目标矩形左上角x
	//	dy, //目标矩形左上角y
	//	dw, //目标矩形宽
	//	dh, //目标矩形高
	//	m_MirrorDC, //源设备
	//	sx, //源矩形左上角x
	//	sy, //源矩形左上角x
	//	dw, //源矩形宽
	//	dh, //源矩形高
	//	tc); //要过滤的颜色

	return true;
}

bool dfsFolder(std::string FolderPath, const char* Extensions, std::vector<std::string>& FileName)//子目录搜索
{
	_finddata_t FileInfo;
	std::string strfind = FolderPath + "\\*";//查找所有文件和目录
	long Handle = (long)(_findfirst(strfind.c_str(), &FileInfo));

	if (Handle == -1L)//非法目录
		return false;

	do{
		//判断是否有子目录
		if (FileInfo.attrib & _A_SUBDIR)    
		{
			//判断是否是子目录
			if((strcmp(FileInfo.name,".") != 0 ) &&(strcmp(FileInfo.name,"..") != 0))   
			{
				std::string newPath = FolderPath + "\\" + FileInfo.name;
				//OutputDebugStr(newPath.c_str());
				dfsFolder(newPath, Extensions, FileName);
			}
		}
		else 
		{
			if(strstr(FileInfo.name, Extensions))//判断文件类型
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