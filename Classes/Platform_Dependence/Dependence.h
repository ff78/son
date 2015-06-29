#ifndef __DEPENDENCE_H__
#define __DEPENDENCE_H__
#include "cocos2d.h"
#define USESOPATH "/data/data/org.cocos2dx.pa/libs"
USING_NS_CC;
#include <string>
#define USELOGO  1
using namespace std;


class Dependence
{
public:

#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	static void showLogin();
	static string getResourcesSearchPath();
	static void setGameInfoWhenLoginDone(string serverId,string roleName);
	static void showGameCenter();
	static void setUpdateState(int state);
	static void installAPK();
	static void reboot();
	static void downloadedFile(string respath,string md5,string filename);
	static void deleteZIP();
	static void deleteSO();
	static string getTempDir();
	static string getWorkingDir();
	static void removeData();
	static void showNetworkFailed();
	static string getLogoName();
	static void checkUpdate();
	static void showPay();
	static bool isWiFiConnected();
	static void showAd();
#endif

};
#endif //__DEPENDENCE_H__




