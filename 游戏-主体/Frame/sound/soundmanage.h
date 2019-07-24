#pragma once
#include <list>
#include <windows.h>
#include <map>
#include <string>
#include "include/fmod.hpp"
#pragma comment(lib, "Sound/lib/fmodex_vc.lib")
using namespace std;
// 音量最大值
#define VOLUME_MAX_VALUE            1.0f

// 音量最小值
#define VOLUME_MIN_VALUE            0.0f

// 每次改变音量的值
#define VOLUME_CHANGE_ONCE_VALUE    0.05f

//音频类型
enum SoundType
{
	DOSOUND,		//音效
	BACKMUSIC		//音乐
};

class CSoundManage
{
public:
	CSoundManage(void);
	~CSoundManage(void);
	//声音接口初始化
	void	Init();
	//读取声音文件
	void	ReadFile(int Id,char * FileName,SoundType Type = BACKMUSIC);
	//播放音乐
	void	play(int Id);
	//设置音量
	void	SetVolume(float Volume);//[0.0-1.0]
	void	SetVolume(int state);//state>0增 state<0减
	//暂停音乐
	//void	setPaused(bool Paused){pChannel->setPaused(Paused);}
	//音乐循环
	void	Tick();
	//停止音乐
	void	Stop(int Id);
	//设置静音
	void	SetIsMute(bool Mute);




protected:
	FMOD::System  *pSystem; 
	bool	isMute;							//静音标志
	//------------------------------------------
	//正在播放的声音源
	struct SOUND_SOURCE
	{
		int					Id;
		SoundType				bAutoPlay;	//自动播放
		FMOD::Channel		*pChannel;		//声音控制器
	};
	//预读音乐结构体
	struct SOUND_BUFFER
	{
		string				FileName;		//文件名
		SoundType			Loop;			//是否循环
		FMOD::Sound			*pSound;		//声音
	};
	list< SOUND_SOURCE* >	m_listSoundSource;

	//所有声音资源列表
	list< SOUND_BUFFER* >			m_listSoundBuffer;
	//按照ID查找
	map< INT, SOUND_BUFFER* >		m_mapSoundID;
};
