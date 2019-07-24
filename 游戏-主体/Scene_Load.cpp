#include "Scene_Load.h"

void CScene_Load::Init()
{
	pGF = CGameFrame::GetObject();
}

void CScene_Load::Enter()
{
	HeroData = (CScene_Data*)pGF->GetScene("���ݴ��泡��");
}

void CScene_Load::Run()
{
	pGF->GetGO()->DrawBmp(
		0,
		0, 
		pGF->GetW(),
		pGF->GetH(),
		0,
		0,
		"Pic\\System\\Save.bmp");

	if(pGF->GetGI()->Get(_GI_K_ESC) == _KS_DC)
	{
		SaveGame();
		pGF->SetCurScene("����2");
	}
}

void CScene_Load::Quit()
{
}

void CScene_Load::SaveGame()
{
	int DjNum = (int)HeroData->Hero.YxHero.Dj.size(); //Ӣ�۵�����
	int DoneNum = (int)HeroData->Hero._Done_Things.size(); //������������С
	int DoingNum = (int)HeroData->Hero._Doing_Things.size(); //������������С

	int fileSize = 3 * sizeof(int);
	fileSize += DjNum * sizeof(int); //���߱��С
	fileSize += (DoneNum + DoingNum) * sizeof(int); //����id
	fileSize += (14 + 3) * sizeof(int); //Ӣ������
	fileSize += 32 + 4; //Ӣ������

	char* _Save_Data = new char[fileSize];
	int Py = 0;

	memcpy( _Save_Data + Py, &DjNum, sizeof(int)); //д��Ӣ�۵�����
	Py += sizeof(int);
	memcpy( _Save_Data + Py, &DoneNum, sizeof(int)); //д��������������С
	Py += sizeof(int);
	memcpy( _Save_Data + Py, &DoingNum, sizeof(int)); //д��������������С
	Py += sizeof(int);

	//�������ID
	std::vector<Item>::iterator i = HeroData->Hero.YxHero.Dj.begin();
	for (; i != HeroData->Hero.YxHero.Dj.end(); ++i)
	{
		memcpy( _Save_Data + Py, &i->id,sizeof(int)); 
		Py += sizeof(int);

		memcpy( _Save_Data + Py, &i->ItemNum,sizeof(int)); 
		Py += sizeof(int);
	}

	//�����������ID
	std::map<int, Mission>::iterator j = HeroData->Hero._Done_Things.begin();
	for (; j != HeroData->Hero._Done_Things.end(); ++j)
	{
		memcpy( _Save_Data + Py, &j->second.id, sizeof(int)); 
		Py += sizeof(int);
	}

	//��������������ID
	j = HeroData->Hero._Doing_Things.begin();
	for (; j != HeroData->Hero._Doing_Things.end(); ++j)
	{
		memcpy( _Save_Data + Py, &j->second.id, sizeof(int)); 
		Py += sizeof(int);
	}

	//����Ӣ������
	//������
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Atk, sizeof(int)); 
	Py += sizeof(int);
	//������
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Def, sizeof(int)); 
	Py += sizeof(int);
	//����
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Agi, sizeof(int)); 
	Py += sizeof(int);
	//ħ��
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Mag, sizeof(int)); 
	Py += sizeof(int);
	//����
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Miss, sizeof(int)); 
	Py += sizeof(int);
	//����
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Critical, sizeof(int)); 
	Py += sizeof(int);
	//Hp
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Hp, sizeof(int)); 
	Py += sizeof(int);
	//MaxHp
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.MaxHp, sizeof(int)); 
	Py += sizeof(int);
	//Mp
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Mp, sizeof(int)); 
	Py += sizeof(int);
	//MaxMp
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.MaxMp, sizeof(int)); 
	Py += sizeof(int);
	//���
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Money, sizeof(int)); 
	Py += sizeof(int);
	//�ȼ�
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Level, sizeof(int)); 
	Py += sizeof(int);
	//����
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Exp, sizeof(int)); 
	Py += sizeof(int);
	//����
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.MaxExp, sizeof(int)); 
	Py += sizeof(int);
	//װ��
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Equip.weapon, sizeof(int)); 
	Py += sizeof(int);
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Equip.shield, sizeof(int)); 
	Py += sizeof(int);
	memcpy( _Save_Data + Py, &HeroData->Hero.YxHero.Equip.pendant, sizeof(int)); 
	Py += sizeof(int);

	//����
	char* Name = HeroData->Hero.YxHero.getName();
	int Len = (int)strlen(Name);
	//��д���ַ�������
	memcpy( _Save_Data + Py, &Len, sizeof(int)); 
	Py += sizeof(int);
	memcpy( _Save_Data + Py, Name, Len); 
	Py += Len;

	FILE* fp1 = 0;
	fopen_s(&fp1, "Save", "wb");
	fwrite(_Save_Data, 1, fileSize, fp1);
	fclose(fp1);
}

