#ifndef AuDIO_MANAGER_H
#define AuDIO_MANAGER_H
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
#include "string"

#include "json/json_header.h"

#define AUDIO_PATH "audio/"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define AUDIO_PATH ""
#endif
#pragma warning(disable:4251) 
USING_NS_CC;
typedef struct Audio_Args{
	Audio_Args(const char* filePath, bool loop){
		pszFilePath = filePath;//std::string(filePath);
		bLoop = loop;
	}
	std::string pszFilePath;
	bool bLoop;
}Audio_Args;


class Audio_Manager: public CocosDenshion::SimpleAudioEngine ,public Node
{
public:
	static Audio_Manager * shared_Audio_Manager(void);
	void play_background_music(const char* pszFilePath, bool bLoop = false);
	unsigned int play_effect(const char* pszFilePath, bool bLoop = false);
	void preload_audio();

private:
	Audio_Manager();
  static Audio_Manager * instance_;
};

#endif
