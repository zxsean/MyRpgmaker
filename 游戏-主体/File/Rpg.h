#ifndef _Rpg_H_
#define _Rpg_H_

#include "Mission.h"
#include "Hero.h"
#include <map>

class CRpg
{
public:
	Hero YxHero;//Ӣ��
	std::map<int, Mission> _Done_Things;//��������
	std::map<int, Mission> _CanDo_Things;//����������
	std::map<int, Mission> _Doing_Things;//����������
};

#endif
