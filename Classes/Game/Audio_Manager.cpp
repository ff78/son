
#include "Audio_Manager.h"



Audio_Manager * Audio_Manager::instance_ = NULL;

Audio_Manager::Audio_Manager():SimpleAudioEngine()
{
	_running = true;
}

Audio_Manager * Audio_Manager::shared_Audio_Manager(void){
	if(!instance_){
		instance_ = new Audio_Manager;
	}
	return instance_;
}

void Audio_Manager::play_background_music( const char* pszFilePath, bool bLoop /*= false*/ )
{
	if(strlen(pszFilePath) < 4){
		return;
	}
	if(!UserDefault::getInstance()->getBoolForKey("BACKGROUNDMUSICSTATE",true))
	{
		return;
	}
	else
	{
		int value=UserDefault::getInstance()->getIntegerForKey("BACKGROUNDMUSICVALUE",100);
		setBackgroundMusicVolume(value/100.0f);
	}
	char path[80];
	sprintf(path,"%s%s", AUDIO_PATH, pszFilePath);
	playBackgroundMusic(path, bLoop);
}

unsigned int Audio_Manager::play_effect( const char* pszFilePath, bool bLoop /*= false*/ )
{
	if(strlen(pszFilePath) < 4){
		return 0;
	}
	if(!UserDefault::getInstance()->getBoolForKey("EFFECTSTATE",true))
	{
		return 0;
	}else
	{
		int value=UserDefault::getInstance()->getIntegerForKey("EFFECTVALUE",100);
		setEffectsVolume(value/100.0f);
	}
	char path[80];
	sprintf(path,"%s%s", AUDIO_PATH, pszFilePath);
	return playEffect(path, bLoop);
}

void Audio_Manager::preload_audio()
{
	preloadEffect("audio/avoidance.mp3");
	preloadEffect("audio/bomb01.mp3");
	preloadEffect("audio/finish.mp3");
	preloadEffect("audio/bomb02.mp3");
	preloadEffect("audio/charge01.mp3");
	preloadEffect("audio/gangqi.mp3");
	preloadEffect("audio/gangqi_jipo.mp3");
	preloadEffect("audio/invincible.mp3");
	preloadEffect("audio/jump01.mp3");
	preloadEffect("audio/manhurt01.mp3");
	preloadEffect("audio/runing10F.mp3");
	preloadEffect("audio/wing-blade01.mp3");
	preloadEffect("audio/wing-blade02.mp3");
	preloadEffect("audio/wing-blade03.mp3");
	preloadEffect("audio/wing-blow01.mp3");
	preloadEffect("audio/wing-fist01.mp3");
	preloadEffect("audio/wing-fist02.mp3");
	preloadEffect("audio/wing-fist03.mp3");
}



