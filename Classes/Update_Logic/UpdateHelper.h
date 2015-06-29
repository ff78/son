#ifndef __UPDATEHELPER_H__
#define __UPDATEHELPER_H__
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#else
#include "MessageInfo.h"
#include <list>
#include "UpdateProtocol.h"
#include <pthread.h>
USING_NS_CC;
using namespace std;
class UpdateHelper:public Ref
{
public:
	~UpdateHelper();
	static UpdateHelper* sharedInstance();
	virtual void update(float dt);
	void sendMessage(MessageInfo* msg);
	static void deleteZIP();
	static void deleteSO();
	static void upgradeInfo(int state);
private:
	UpdateHelper();
	static UpdateHelper*instance;
	list<MessageInfo*>* messageQueue;
	pthread_mutex_t messageQueueMutex;

};
#endif // CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#endif //__UPDATEHELPER_H__