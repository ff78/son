#include "UpdateProtocol.h"
#include "cocos2d.h"
USING_NS_CC;
void UpdateProtocol::onGettingDownloadInfo()
{
	CCLog("--------------onGettingDownloadInfo��getting download message");
}
void UpdateProtocol::downloadSucceed()
{
	CCLog("-------------------->downloadSucceed��download succeed");
}
void UpdateProtocol::beforeProgress()//���ؿ�ʼ֮ǰ���ã�����ui��״̬label����ʾ�������С�������
{
	CCLog("---------->beforeProgress��get download message succeed��start download");
}
void UpdateProtocol::onProgress(int persent,int current,int all)// ���ؽ��������ȸ��½ӿ�
{
	CCLog("---------------->onProgress %d",persent);
}
void UpdateProtocol::onDecompressing()// ����ui��״̬label����ʾ����ѹ�С�������
{
	CCLog("------------------>onDecompressing");
}
void UpdateProtocol::onSuccess(ErrorCode errorCode) //���ؽ�ѹ�ɹ�����ã�����ui�������Ի�����ʾ�û�����Ӧ��
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



