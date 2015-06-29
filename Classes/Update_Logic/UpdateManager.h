#ifndef __UPDATEMANAGER_H__
#define __UPDATEMANAGER_H__
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#else
#include "UpdateProtocol.h"
#include <curl/curl.h>
#include <pthread.h>
#include "VersionInfo.h"
#include <vector>
USING_NS_CC;
using namespace std;
class UpdateHelper;
class UpdateManager
{
public:
	
	UpdateManager(UpdateProtocol* protocol,unsigned int timeOut);
	~UpdateManager();
	void init();
	void update();
	static long getRemoteFileLength(string url,CURL* curl);
	static int getFileLength(string fileName);
	friend int assetsManagerProgressFunc(void *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded);
public :
	static UpdateManager* instance;

private:
	static bool createDirectory(const char *path);
	string getFileFullName(string url);
	static string getFileResName(string url);
	void getDownloadInfo();
	static  void* downloadUncompressCopy(void* args);
	bool downloadFile(int index);
	bool uncompressFile(int index);
	static size_t writeFile(void *ptr, size_t size, size_t nmemb, void *userdata);
	string getFileExtention(string url);
	static bool createDirForFile(string str);

private:
	static string downloadTempPath;
	static string resourcesPath;
	UpdateProtocol* protocol;
	CURL* curl;
	UpdateHelper* helper;
	pthread_t pid;
	unsigned int timeOut;
	vector<VersionInfo> downloadInfo;
	unsigned int downloadIndex;
	unsigned int allToBeDownload;
	bool haveApk;
	bool haveSo;
	

	
};
#endif // CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#endif //__UPDATEMANAGER_H__