#pragma once
#include <list>
#include <windows.h>
#include <map>
#include <string>
#include "include/fmod.hpp"
#pragma comment(lib, "Sound/lib/fmodex_vc.lib")
using namespace std;
// �������ֵ
#define VOLUME_MAX_VALUE            1.0f

// ������Сֵ
#define VOLUME_MIN_VALUE            0.0f

// ÿ�θı�������ֵ
#define VOLUME_CHANGE_ONCE_VALUE    0.05f

//��Ƶ����
enum SoundType
{
	DOSOUND,		//��Ч
	BACKMUSIC		//����
};

class CSoundManage
{
public:
	CSoundManage(void);
	~CSoundManage(void);
	//�����ӿڳ�ʼ��
	void	Init();
	//��ȡ�����ļ�
	void	ReadFile(int Id,char * FileName,SoundType Type = BACKMUSIC);
	//��������
	void	play(int Id);
	//��������
	void	SetVolume(float Volume);//[0.0-1.0]
	void	SetVolume(int state);//state>0�� state<0��
	//��ͣ����
	//void	setPaused(bool Paused){pChannel->setPaused(Paused);}
	//����ѭ��
	void	Tick();
	//ֹͣ����
	void	Stop(int Id);
	//���þ���
	void	SetIsMute(bool Mute);




protected:
	FMOD::System  *pSystem; 
	bool	isMute;							//������־
	//------------------------------------------
	//���ڲ��ŵ�����Դ
	struct SOUND_SOURCE
	{
		int					Id;
		SoundType				bAutoPlay;	//�Զ�����
		FMOD::Channel		*pChannel;		//����������
	};
	//Ԥ�����ֽṹ��
	struct SOUND_BUFFER
	{
		string				FileName;		//�ļ���
		SoundType			Loop;			//�Ƿ�ѭ��
		FMOD::Sound			*pSound;		//����
	};
	list< SOUND_SOURCE* >	m_listSoundSource;

	//����������Դ�б�
	list< SOUND_BUFFER* >			m_listSoundBuffer;
	//����ID����
	map< INT, SOUND_BUFFER* >		m_mapSoundID;
};
