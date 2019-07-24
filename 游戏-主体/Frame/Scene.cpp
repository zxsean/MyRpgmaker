#include "Scene.h"

CSoundManage CScene::GameSound;

bool CScene::LoadUI(CUI* pUI, const char* ID)
{
	std::string s = ID;
	if (m_UI.find(s) != m_UI.end())
		return false;

	//将控件的所属场景设置为自己
	pUI->scene = this;

	pUI->Init(); //多态

	m_UI.insert(std::pair<std::string, CUI*>(s, pUI));

	return true;
}

bool CScene::ReleaseUI(const char* ID)
{
	std::string s = ID;
	std::map<std::string, CUI*>::iterator i = m_UI.find(s);
	if (i == m_UI.end())
		return false;

	i->second->End(); //多态
	delete i->second;
	m_UI.erase(i);

	return true;
}

bool CScene::SetKeyInputUI(const char* ID)
{
	if (0 == ID)
		m_KeyInputUI = 0;
	else
	{
		std::string s = ID;
		std::map<std::string, CUI*>::iterator i = m_UI.find(s);
		if (i == m_UI.end())
			return false;

		m_KeyInputUI = i->second;
	}

	return true;
}

CScene::CScene()
:
m_KeyInputUI(0)
{}

CScene::~CScene()
{
	std::map<std::string, CUI*>::iterator i;
	for (i = m_UI.begin(); i != m_UI.end(); ++i)
	{
		i->second->End();
		delete i->second;
	}
}

void CScene::Init(){}
void CScene::Enter(){}
void CScene::Run(){}
void CScene::Quit(){}
void CScene::End(){}