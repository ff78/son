#ifndef __UPDATEDELEGATE_H__
#define __UPDATEDELEGATE_H__


class UpdateProtocol
{
public:
	enum ErrorCode
    {
        // Error caused by creating a file to store downloaded data
        kCreateFile,
        /** Error caused by Network
         -- Network unavaivable
         -- timeout
         -- ...
         */
        kNetwork,
        /** There is not a new version
         */
        kNoNewVersion,
        /** Error caused in uncompressing stage
         -- can not open zip file
         -- can not read file global information
         -- can not read file information
         -- can not create a directory
         -- ...
         */
        kUncompress,
		kINSTALL,
		kREBOOT,
		kGOON,
    };
	virtual void onGettingDownloadInfo();//���ڻ�ȡ���ظ��µ���Ϣ
	virtual void downloadSucceed();//���سɹ�����ʼ��ѹ
	virtual void beforeProgress();//���ؿ�ʼ֮ǰ���ã�����ui��״̬label����ʾ�������С�������,��ȡ������Ϣ�ɹ�����ʼ����
	virtual void onProgress(int persent,int current,int all);// ���ؽ��������ȸ��½ӿ�
	virtual void onDecompressing();// ����ui��״̬label����ʾ����ѹ�С�������
	virtual void onSuccess(ErrorCode errorCode);//���ؽ�ѹ�ɹ�����ã�����ui�������Ի�����ʾ�û�����Ӧ��
	virtual void onError(UpdateProtocol::ErrorCode errorcode );
	virtual void uncompressSucceed();
	virtual void stopUpdate();
};
#endif //__UPDATEDELEGATE_H__