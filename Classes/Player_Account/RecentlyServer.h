#ifndef RECENTLYSERVER_H_H
#define RECENTLYSERVER_H_H
#include "cocos2d.h"
#include "Player_Account/Account_Data.h"
#include "Common/GameMacro.h"

#include "SimpleAudioEngine.h"
USING_NS_CC;

class RecentlyServer
{
public:
	RecentlyServer(void);
	~RecentlyServer(void);
	/************************************************************************/
	/* 从0开始
	//获取后首先判断id，id为0的话就不存在
	/************************************************************************/
	static Server_List_Data getRecentlyServerInfomation(int index);
	static void addServer(Server_List_Data sld);
	static void setServerData(int index,Server_List_Data sld);

	static bool getBackgroundMusicState();
	static void setBackgroundMusicStateAndBehavior(bool value);
	static bool getEffectState();
	static void setEffectStateAndBehavior(bool value);
	static bool getShieldState();
	static void setShieldState(bool value);
	static int getBackgroundMusicValue();
	static void setBackgroundMusicValue(int value);
	static int getEffectValue();
	static void setEffectValue(int value);
	static int musicvalue;
	static int effectvalue;
	static bool music,effect;

};
#endif //RECENTLYSERVER_H_H

