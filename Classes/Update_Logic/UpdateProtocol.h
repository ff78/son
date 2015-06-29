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
	virtual void onGettingDownloadInfo();//正在获取下载更新的信息
	virtual void downloadSucceed();//下载成功，开始解压
	virtual void beforeProgress();//下载开始之前调用，更新ui的状态label，显示“下载中。。。”,获取下载信息成功，开始下载
	virtual void onProgress(int persent,int current,int all);// 下载进度条进度更新接口
	virtual void onDecompressing();// 更新ui的状态label，显示“解压中。。。”
	virtual void onSuccess(ErrorCode errorCode);//下载解压成功后调用，更新ui，弹出对话框提示用户重启应用
	virtual void onError(UpdateProtocol::ErrorCode errorcode );
	virtual void uncompressSucceed();
	virtual void stopUpdate();
};
#endif //__UPDATEDELEGATE_H__