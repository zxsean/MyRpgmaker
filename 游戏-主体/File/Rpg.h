#ifndef _Rpg_H_
#define _Rpg_H_

#include "Mission.h"
#include "Hero.h"
#include <map>

class CRpg
{
public:
	Hero YxHero;//英雄
	std::map<int, Mission> _Done_Things;//做过的事
	std::map<int, Mission> _CanDo_Things;//可以做的事
	std::map<int, Mission> _Doing_Things;//正在做的事
};

#endif
