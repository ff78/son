#include "UpdateHelper.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#else
#include "MessageInfo.h"
#include "Update_Logic/UpdateData.h"
#include "cocos2d.h"
#include "UI_Interface/UI_UpdateLayer.h"
#include "UpdateManager.h"
#include "Platform_Dependence/Dependence.h"

USING_NS_CC;
#define DOWNLOAD_ZORDER 8000
UpdateHelper* UpdateHelper::instance=NULL;
UpdateHelper* UpdateHelper::sharedInstance()
{
	if(instance==NULL)
	{
		instance=new UpdateHelper();
	}
	return instance;
}
UpdateHelper::UpdateHelper()
{
	messageQueue=new list<MessageInfo*>();
	pthread_mutex_init(&messageQueueMutex,NULL);
	Director::getInstance()->getScheduler()->scheduleUpdateForTarget(this,-25,false);
}
UpdateHelper::~UpdateHelper()
{
	Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
	delete messageQueue;

}
void UpdateHelper::update(float dt)
{
	MessageInfo* msg=NULL;
	pthread_mutex_lock(&messageQueueMutex);
	if(0==messageQueue->size())
	{
		pthread_mutex_unlock(&messageQueueMutex);
		return;
	}
	do 
	{
	
		msg=*(messageQueue->begin());
		messageQueue->pop_front();
	

		if(msg->what==MessageInfo::STARTDOWNLOAD)
		{
	
				UpdateProtocol* up=(UpdateProtocol*)(msg->obj);
				up->beforeProgress();
				//开始更新
				upgradeInfo(1);
				delete msg;
		}
		else if(msg->what==MessageInfo::DOWNLOAD_SUCCEED)
		{
			UpdateProtocol* upds=(UpdateProtocol*)(msg->obj);
			upds->downloadSucceed();
			delete msg;
		}
		else if(msg->what==MessageInfo::DOWNLOAD_PROGRESS)
		{
			UpdateProtocol* updp=(UpdateProtocol*)(msg->obj);
			updp->onProgress(msg->arg1,msg->arg2,msg->arg3);
			delete msg;
		}
		else if(msg->what==MessageInfo::START_GETMESSAGE)
		{
			UpdateProtocol* up=(UpdateProtocol*)(msg->obj);
			up->onGettingDownloadInfo();
			delete msg;
		}
		else if(msg->what==MessageInfo::NET_WORK_ERROR)
		{
			UpdateProtocol* up=(UpdateProtocol*)(msg->obj);
			up->onError(UpdateProtocol::kNetwork);
			CCLog("-----------network error");
			delete msg;
		}
		else if(msg->what==MessageInfo::CREATE_FILE_FAILED)
		{
			UpdateProtocol* up=(UpdateProtocol*)(msg->obj);
			up->onError(UpdateProtocol::kCreateFile);
			delete msg;
		}
		else if(msg->what==MessageInfo::ALL_SUCCEED)
		{
			//更新成功
			upgradeInfo(2);
			UpdateProtocol* up=(UpdateProtocol*)(msg->obj);
			if(msg->arg1==1)
			{
				
				//安装apk
				up->onSuccess(UpdateProtocol::kINSTALL);
				
			}
			else
			{
				if(msg->arg2==1)
				{
					//重启
					up->onSuccess(UpdateProtocol::kREBOOT);
				}
				else
				{
					//直接进入
					up->onSuccess(UpdateProtocol::kGOON);
				}
			}
			
			delete msg;
		}
		else if(msg->what==MessageInfo::UNCOMPRESS_SUCCEED)
		{
			UpdateProtocol* up=(UpdateProtocol*)(msg->obj);
			up->uncompressSucceed();
			delete msg;
		}
		else if(msg->what==MessageInfo::UNCOMPRESS_FAILED)
		{
			UpdateProtocol* up=(UpdateProtocol*)(msg->obj);
			up->onError(UpdateProtocol::kCreateFile);
			delete msg;
		}
		else if(msg->what==MessageInfo::DELETE_SOMETHING)
		{
			UpdateProtocol* up=(UpdateProtocol*)(msg->obj);
			if(msg->arg1==1)
			{
				//删除.so文件
				deleteSO();
			}
			//删除zip文件
			deleteZIP();
			delete msg;
		}
		else if(msg->what==MessageInfo::START_MESSION)
		{

			
			UI_UpdateLayer* updateLayer =UI_UpdateLayer::create();
			updateLayer->setTag(UPDATELAYERTAG);
			Director::getInstance()->getRunningScene()->addChild(updateLayer,DOWNLOAD_ZORDER);
			
			UpdateManager* um=new UpdateManager(updateLayer,3);
			
			um->update();
			delete msg;
		}
		else if(msg->what==MessageInfo::ONE_SUCCEED)
		{

#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	//		Dependence::downloadedFile(msg->respath,msg->md5,msg->filename);
#endif
			delete msg;
		}

	} while(messageQueue->size());
	pthread_mutex_unlock(&messageQueueMutex);

}
void UpdateHelper::deleteZIP()
{
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
//	Dependence::deleteZIP();
#endif
}
void UpdateHelper::deleteSO()
{
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
//	Dependence::deleteSO();
#endif
}
void UpdateHelper::sendMessage(MessageInfo* msg)
{
	pthread_mutex_lock(&messageQueueMutex);
	messageQueue->push_back(msg);
	pthread_mutex_unlock(&messageQueueMutex);
}
void UpdateHelper::upgradeInfo(int state)
{
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
//	Dependence::setUpdateState(state);
#endif
}
#endif // CC_TARGET_PLATFORM != CC_PLATFORM_WIN32