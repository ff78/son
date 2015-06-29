#include "UpdateProtocol.h"
#include "cocos2d.h"
USING_NS_CC;
void UpdateProtocol::onGettingDownloadInfo()
{
	CCLog("--------------onGettingDownloadInfo，getting download message");
}
void UpdateProtocol::downloadSucceed()
{
	CCLog("-------------------->downloadSucceed，download succeed");
}
void UpdateProtocol::beforeProgress()//下载开始之前调用，更新ui的状态label，显示“下载中。。。”
{
	CCLog("---------->beforeProgress，get download message succeed，start download");
}
void UpdateProtocol::onProgress(int persent,int current,int all)// 下载进度条进度更新接口
{
	CCLog("---------------->onProgress %d",persent);
}
void UpdateProtocol::onDecompressing()// 更新ui的状态label，显示“解压中。。。”
{
	CCLog("------------------>onDecompressing");
}
void UpdateProtocol::onSuccess(ErrorCode errorCode) //下载解压成功后调用，更新ui，弹出对话框提示用户重启应用
{
	CCLog("------------------->onSuccess");
}
void UpdateProtocol::onError(UpdateProtocol::ErrorCode errorcode )
{
	CCLOG("-------------------->onError");
}
void UpdateProtocol::uncompressSucceed()
{
	CCLog("------------------------->uncompressSucceed");
}
void UpdateProtocol::stopUpdate()
{
	CCLog("------------------------->stop update");
}



