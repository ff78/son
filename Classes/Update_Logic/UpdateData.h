#ifndef __UPDATEDATA_H__
#define __UPDATEDATA_H__
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#else
#define VERSIONPATH "http://sdk.9961.cn/sdkbus/client/cp/verify/token"
#include "VersionInfo.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <string>
#include <map>

using namespace std;
USING_NS_CC;
class UpDateData
{

public:
	enum RESULTVALUE
	{
		HAVE_NEW_VERSION,
		NO_NEW_VERSION,
		NETWORK_ERROR,
		PARSER_FILE_FAILED,
		PARSER_FILE_OK,
	};
	static UpDateData* sharedInstance();
	void getVersionDataVector(vector<VersionInfo>& versionData);
	string getVersion();
	string getNewVersion();
	int init(string str);
protected:
private:
	
	static UpDateData* instance_;
	UpDateData();
	vector<VersionInfo> versionData;
	static size_t getVersionData(uint8_t *ptr, size_t size, size_t nmemb, void *userdata);
	int parserJson(string data);
	CURL* curl;

};
#endif //(CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#endif //__UPDATEDATA_H__