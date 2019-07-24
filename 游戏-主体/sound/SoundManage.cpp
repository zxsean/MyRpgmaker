#include "soundmanage.h"

CSoundManage::CSoundManage(void):
pSystem(NULL),
isMute(false)
{
	Init();
}	

CSoundManage::~CSoundManage(void)
{
	//---------------------------------
	//释放所有声音资源
	list< SOUND_BUFFER* >::iterator itSndBuffer,itBufNext;
	for(itSndBuffer = m_listSoundBuffer.begin(); itSndBuffer!=m_listSoundBuffer.end(); itSndBuffer=itBufNext)
	{
		itBufNext = itSndBuffer; itBufNext++;
		SOUND_BUFFER* sndBuffer = *itSndBuffer;
		if (sndBuffer)
		{
			//释放声音资源
			if(sndBuffer->pSound)
			{
				sndBuffer->pSound->release();
				sndBuffer->pSound = NULL;
			}
			delete sndBuffer;
			sndBuffer = NULL;
			m_listSoundBuffer.erase(itSndBuffer);
		}
	}

	list< SOUND_SOURCE* >::iterator itSndSource,itSouNext;
	for(itSndSource = m_listSoundSource.begin(); itSndSource!=m_listSoundSource.end(); itSndSource=itSouNext)
	{
		itSouNext = itSndSource; itSouNext++;
		SOUND_SOURCE* sndSource = *itSndSource;

		if(sndSource)
		{
			delete sndSource;
			sndSource = NULL;
			m_listSoundSource.erase(itSndSource);
		}
	}
	m_listSoundSource.clear();
	m_listSoundBuffer.clear();
	m_mapSoundID.clear();
	if(pSystem)
	{
		pSystem->close();
		pSystem->release();
	}
}
void CSoundManage::Init()
{
	FMOD::System_Create(&pSystem);
	pSystem->init(32,FMOD_INIT_NORMAL,NULL);
	m_listSoundSource.clear();
	m_listSoundBuffer.clear();
	m_mapSoundID.clear();
}
void CSoundManage::ReadFile(int Id,char * FileName,SoundType Type)
{
	SOUND_BUFFER* newSound = new SOUND_BUFFER; 
	newSound->Loop = Type;
	newSound->FileName = FileName;
	newSound->pSound = NULL;
	
	//加入列表
	m_listSoundBuffer.push_back(newSound);
	//加入索引
	m_mapSoundID[Id] = m_listSoundBuffer.back();
}

void CSoundManage::play(int Id)
{
	if (!isMute)
	{
		
		map< int, SOUND_BUFFER* >::iterator it;
		it = m_mapSoundID.find(Id);
		//非法ID
		if(it == m_mapSoundID.end())
		{
			MessageBox(NULL,"错误的ID号码",NULL,NULL);
			
		}else
		{
			SOUND_BUFFER& sndBuffer = *(it->second);
			if(sndBuffer.pSound == NULL)
			{
				FMOD::Sound   *pSound;
				if (pSystem->createSound(sndBuffer.FileName.c_str(),FMOD_HARDWARE,NULL,&pSound))
				{
					MessageBox(NULL,"声音文件加载失败:可能是路径错误",NULL,MB_OK);
					return;
				}
				sndBuffer.pSound = pSound;
				//Stop();
				FMOD::Channel		*pChannel;
				pSystem->playSound(FMOD_CHANNEL_FREE,pSound,false,&pChannel);
				SOUND_SOURCE * newSource = new SOUND_SOURCE;
				newSource->pChannel = pChannel;
				newSource->bAutoPlay = sndBuffer.Loop;
				newSource->Id = Id;
				m_listSoundSource.push_back(newSource);
			}else
			{
				Stop(Id);
				FMOD::Channel		*pChannel;
				pSystem->playSound(FMOD_CHANNEL_FREE,sndBuffer.pSound,false,&pChannel);
				SOUND_SOURCE * newSource = new SOUND_SOURCE;
				newSource->pChannel = pChannel;
				newSource->bAutoPlay = sndBuffer.Loop;
				newSource->Id = Id;
				m_listSoundSource.push_back(newSource);
			}
		}		
	}
}
void CSoundManage::SetVolume(float Volume)
{
	list< SOUND_SOURCE* >::iterator it, itNext;
	for(it = m_listSoundSource.begin(); it!=m_listSoundSource.end(); it=itNext)
	{
		itNext = it; itNext++;
		SOUND_SOURCE* theSnd = *it;
		theSnd->pChannel->setVolume(Volume);
	}
}
void CSoundManage::SetVolume(int state)
{
	list< SOUND_SOURCE* >::iterator it, itNext;
	for(it = m_listSoundSource.begin(); it!=m_listSoundSource.end(); it=itNext)
	{
		itNext = it; itNext++;
		SOUND_SOURCE* theSnd = *it;

		float Volume = VOLUME_MIN_VALUE;
		theSnd->pChannel->getVolume(&Volume);
		if (state > 0)
		{
			Volume += VOLUME_CHANGE_ONCE_VALUE;
			if (Volume >= VOLUME_MAX_VALUE) Volume = VOLUME_MAX_VALUE;
		}else if (state < 0)
		{
			Volume -= VOLUME_CHANGE_ONCE_VALUE;
			if (Volume <= VOLUME_MIN_VALUE) Volume = VOLUME_MIN_VALUE;
		}
		theSnd->pChannel->setVolume(Volume);
	}
}
void CSoundManage::Tick()
{
	list< SOUND_SOURCE* >::iterator it, itNext;
	for(it = m_listSoundSource.begin(); it!=m_listSoundSource.end(); it=itNext)
	{
		bool isPlay = false;
		float Volume = 0.0f;

		itNext = it; itNext++;
		SOUND_SOURCE* theSnd = *it;
		
		theSnd->pChannel->isPlaying(&isPlay);
		if (!isPlay)
		{
			if (theSnd->bAutoPlay)
			{
				map< int, SOUND_BUFFER* >::iterator it;
				it = m_mapSoundID.find(theSnd->Id);
				if(it != m_mapSoundID.end())
				{
					theSnd->pChannel->getVolume(&Volume);
					SOUND_BUFFER& sndBuffer = *(it->second);
					FMOD::Channel		*pChannel;
					pSystem->playSound(FMOD_CHANNEL_FREE,sndBuffer.pSound,false,&pChannel);
					theSnd->pChannel = pChannel;
					theSnd->pChannel->setVolume(Volume);
				}
			}else
			{
				theSnd->pChannel->stop();
				delete theSnd;
				theSnd = NULL;
				m_listSoundSource.erase(it);
			}
		}
	}
}
void CSoundManage::Stop(int Id)
{
	list< SOUND_SOURCE* >::iterator it, itNext;
	for(it = m_listSoundSource.begin(); it!=m_listSoundSource.end(); it=itNext)
	{
		itNext = it; itNext++;
		SOUND_SOURCE* theSnd = *it;
		if (theSnd->Id == Id)
		{
			theSnd->pChannel->stop();
			delete theSnd;
			theSnd = NULL;
			m_listSoundSource.erase(it);
		}
	}
}
void CSoundManage::SetIsMute(bool Mute)
{
	isMute = Mute;
}