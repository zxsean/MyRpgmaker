#ifndef _Item_H_
#define _Item_H_

Item* ItemData;

int LoadItemini()
{
	char acSectionName[256];//模块名
	int iSectionLen = 0;//读取长度
	char acItemNum[32];
	int iItemNumShow;


	GetPrivateProfileSectionNamesA(
		acSectionName, 
		256, 
		".\\Data\\Item.ini");
	strcpy_s(acItemNum,32,acSectionName + iSectionLen);
	iSectionLen += int(strlen(acItemNum) + 1);

	//读取数量
	iItemNumShow = GetPrivateProfileIntA(
		acItemNum, //指定的模块
		"道具数量", //指定的键
		-1, //当找不到指定的数据返回的值
		".\\Data\\Item.ini"); //指定的ini文件

	//std::cout <<iTalkNumShow<<std::endl;
	ItemData = new Item[iItemNumShow * sizeof(Item)];
	char *TempName = new char[32 * iItemNumShow];

	for (int i = 0;i < iItemNumShow;++i)
	{
		strcpy_s(TempName,32,acSectionName + iSectionLen);
		iSectionLen += int(strlen(TempName) + 1);

		GetPrivateProfileStringA(
			TempName,
			"Name",
			"!?", //当找不到指定的数据返回的字符串
			ItemData[i].name, //用于得到字符串的字符数组
			256, //用于得到字符串的字符数组长度
			".\\Data\\Item.ini");

		GetPrivateProfileStringA(
			TempName,
			"Text",
			"!?", //当找不到指定的数据返回的字符串
			ItemData[i].ItemText, //用于得到字符串的字符数组
			256, //用于得到字符串的字符数组长度
			".\\Data\\Item.ini");
		//Num
		ItemData[i].ItemNum = GetPrivateProfileIntA(
			TempName, //指定的模块
			"ItemNum", //指定的键
			-1, //当找不到指定的数据返回的值
			".\\Data\\Item.ini"); //指定的ini文件
		//ID
		ItemData[i].id = GetPrivateProfileIntA(
			TempName, //指定的模块
			"Id", //指定的键
			-1, //当找不到指定的数据返回的值
			".\\Data\\Item.ini"); //指定的ini文件
		//生命值
		ItemData[i].HpAdd = GetPrivateProfileIntA(
			TempName, //指定的模块
			"Hp", //指定的键
			-1, //当找不到指定的数据返回的值
			".\\Data\\Item.ini"); //指定的ini文件
		//魔力值
		ItemData[i].MpAdd = GetPrivateProfileIntA(
			TempName, //指定的模块
			"Mp", //指定的键
			-1, //当找不到指定的数据返回的值
			".\\Data\\Item.ini"); //指定的ini文件
		//攻击力
		ItemData[i].AtkAdd = GetPrivateProfileIntA(
			TempName, //指定的模块
			"Atk", //指定的键
			-1, //当找不到指定的数据返回的值
			".\\Data\\Item.ini"); //指定的ini文件
		//防御力
		ItemData[i].DefAdd = GetPrivateProfileIntA(
			TempName, //指定的模块
			"Def", //指定的键
			-1, //当找不到指定的数据返回的值
			".\\Data\\Item.ini"); //指定的ini文件
		//敏捷	
		ItemData[i].AgiAdd = GetPrivateProfileIntA(
			TempName, //指定的模块
			"Agi", //指定的键
			-1, //当找不到指定的数据返回的值
			".\\Data\\Item.ini"); //指定的ini文件
		//魔力
		ItemData[i].MagAdd = GetPrivateProfileIntA(
			TempName, //指定的模块
			"Mag", //指定的键
			-1, //当找不到指定的数据返回的值
			".\\Data\\Item.ini"); //指定的ini文件
		//价格
		ItemData[i].Price = GetPrivateProfileIntA(
			TempName, //指定的模块
			"Price", //指定的键
			-1, //当找不到指定的数据返回的值
			".\\Data\\Item.ini"); //指定的ini文件
		//类型
		ItemData[i].Type = GetPrivateProfileIntA(
			TempName, //指定的模块
			"Type", //指定的键
			-1, //当找不到指定的数据返回的值
			".\\Data\\Item.ini"); //指定的ini文件
	}
	return iItemNumShow;
}

#endif