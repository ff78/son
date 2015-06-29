#include "UpdateManager.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#else
#include "UpdateData.h"
#include "Common/GameMacro.h"
#include "unzip.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#else
//#include <stdio.h> 
//#include <process.h> 
//#include <dir.h> 
#include "C:/Program Files (x86)/Windows Kits/8.0/Include/um/fileapi.h"
//#include <fileapi.h>
#endif
#include "Platform_Dependence/Dependence.h"

#define DOWNSOPATH "data/lib/libgame.so"
#define APKPATH      "/temp"


#include "UpdateHelper.h"
#include <stdio.h>
#define BUFFER_SIZE 8*1024
#define MAX_FILENAME   512
UpdateManager* UpdateManager::instance=0;
string UpdateManager::downloadTempPath;
string UpdateManager::resourcesPath;
int assetsManagerProgressFunc(void *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded)
{
	/*
	AssetsManager* manager = (AssetsManager*)ptr;
	AssetsManager::Message *msg = new AssetsManager::Message();
	msg->what = ASSETSMANAGER_MESSAGE_PROGRESS;

	ProgressMessage *progressData = new ProgressMessage();
	progressData->percent = (int)(nowDownloaded/totalToDownload*100);
	progressData->manager = manager;
	msg->obj = progressData;

	manager->_schedule->sendMessage(msg);*/
	UpdateManager* mgr = (UpdateManager*)ptr;
	double  current=0;
	for(unsigned int i=0;i<mgr->downloadIndex;++i)
	{

		VersionInfo vi=mgr->downloadInfo[i];
		current+=vi.getFileLength();
	}
	current+=nowDownloaded;
	double persent=current*100.0/(mgr->allToBeDownload);


	
	MessageInfo *msg=new MessageInfo();
	msg->what=MessageInfo::DOWNLOAD_PROGRESS;
	msg->obj=mgr->protocol;
	msg->arg1=(unsigned int)persent;
	msg->arg2=current;
	msg->arg3=mgr->allToBeDownload;
	mgr->helper->sendMessage(msg);
	CCLog("downloading... %f%%", persent);

	return 0;
}
UpdateManager::UpdateManager(UpdateProtocol* protocol,unsigned int timeOut)
{
	this->protocol=protocol;
	this->timeOut=timeOut;
	helper=UpdateHelper::sharedInstance();
	init();
	haveApk=false;
	haveSo=false;
	instance=this;
}
UpdateManager::~UpdateManager()
{
	
	if(helper)
	{
		Director::getInstance()->getScheduler()->unscheduleAllForTarget(helper);
	}}
void UpdateManager::init()
{
	downloadIndex=0;
	allToBeDownload=1;

}
void UpdateManager::update()
{
	downloadTempPath=string("/mnt/sdcard");
	resourcesPath=string("/mnt/sdcard");
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
//	downloadTempPath=Dependence::getTempDir();
//	resourcesPath=Dependence::getWorkingDir();
#endif
	 CCLog("temppath---------------------->%s",downloadTempPath.c_str());
	 CCLog("downloadRes------------------------%s",resourcesPath.c_str());
	



	getDownloadInfo();
	CCLog("	--------------------getDownloadInfo();");
	pthread_create(&pid,NULL,downloadUncompressCopy,this);
	CCLog("	--------------------pthread_create(&pid,NULL,downloadUncompressCopy,this);");

}
void UpdateManager::getDownloadInfo()
{
	//string currentVersion,newVersion;
	//currentVersion=UpDateData::sharedInstance()->getVersion();
	//newVersion=UpDateData::sharedInstance()->getNewVersion();
	vector<VersionInfo> data;
	VersionInfo vi;
	UpDateData::sharedInstance()->getVersionDataVector(data);
	for(unsigned int i=0;i<data.size();++i)
	{
		vi=data[i];
		CCLog("getDownloadInfo-------------------------------------------name is %s,path is %s",vi.getName(),vi.getPath());
		
		
			if(getFileExtention(vi.getPath())==string("apk"))
			{
				downloadInfo.clear();
				haveApk=true;
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
//				Dependence::removeData();
#endif
			}
			downloadInfo.push_back(vi);
		
			
		
	}
	for(unsigned int i=0;i<downloadInfo.size();i++)
	{
		vi=downloadInfo[i];
		CCLog("really download is %s",vi.getName());
	}
	

}
void* UpdateManager::downloadUncompressCopy(void* args)
{
	CCLog("---------------------->UpdateManager::downloadUncompressCopy");
	UpdateManager* mgr=(UpdateManager*)(args);
	//获取下载的路径
	for(unsigned int i=0;i<mgr->downloadInfo.size();++i)
	{
		string url=string(mgr->downloadInfo[i].getPath());
		if(mgr->getFileExtention(url)==string("apk"))
		{
			mgr->downloadInfo[i].setResPath(APKPATH);
			string respath=mgr->downloadInfo[i].getRespath();
			mgr->downloadInfo[i].setFullpath(resourcesPath+respath+"/jieji.apk");
		}
		else
		{
			mgr->downloadInfo[i].setResPath(getFileResName(url));
			string respath=mgr->downloadInfo[i].getRespath();
			mgr->downloadInfo[i].setFullpath(resourcesPath+respath);
		}
		
	}

	for(int i=0;i<(int)(mgr->downloadInfo.size());++i)
	{
		VersionInfo vi=mgr->downloadInfo[i];
		CCLog("name is %s,path is %s,respath is %s,fullpath is %s",vi.getName(),vi.getPath(),vi.getRespath().c_str(),vi.getFullpath().c_str());
	}


	mgr->curl = curl_easy_init();
	//开始获取下载的大小
	   
	MessageInfo * startGetMessage=new MessageInfo();
	startGetMessage->what=MessageInfo::START_GETMESSAGE;
	startGetMessage->obj=mgr->protocol;
	mgr->helper->sendMessage(startGetMessage);

	for(unsigned int i=0;i<mgr->downloadInfo.size();++i)
	{
		long remoteFileLength=getRemoteFileLength(mgr->downloadInfo[i].getPath(),mgr->curl);
		if(-1==remoteFileLength)
		{
			MessageInfo *networkerror=new MessageInfo();
			networkerror->obj=mgr->protocol;
			networkerror->what=MessageInfo::NET_WORK_ERROR;
			mgr->helper->sendMessage(networkerror);
			curl_easy_cleanup(mgr->curl);
			CCLog("------downloadUncompressCopy---get download message failed!");
			return NULL;
		}
		mgr->downloadInfo[i].setFileLength(remoteFileLength);
	}
	for(unsigned int i=0;i<mgr->downloadInfo.size();++i)
	{
		VersionInfo vi=mgr->downloadInfo[i];
		mgr->allToBeDownload+=vi.getFileLength();
	}
	curl_easy_cleanup(mgr->curl);
	
	MessageInfo* msg=new MessageInfo();
	msg->what=MessageInfo::STARTDOWNLOAD;
	msg->obj=mgr->protocol;
	mgr->helper->sendMessage(msg);

	
	mgr->curl = curl_easy_init();
	if (! mgr->curl)
	{
		CCLog("can not init curl");
		return NULL;
	}
	for(unsigned int i=0;i<mgr->downloadInfo.size();++i)
	{
		bool state=mgr->downloadFile(i);
		if(!state)
		{
			curl_easy_cleanup(mgr->curl);
				CCLog("------downloadUncompressCopy---download file failed!");
			return NULL;
		}
		
	}
	curl_easy_cleanup(mgr->curl);


	MessageInfo *msgdownloadsucceed=new MessageInfo();
	msgdownloadsucceed->what=MessageInfo::DOWNLOAD_SUCCEED;
	msgdownloadsucceed->obj=mgr->protocol;
	mgr->helper->sendMessage(msgdownloadsucceed);
	/*
	for(unsigned int i=0;i<mgr->downloadInfo.size();++i)
	{
		bool re=mgr->uncompressFile(i);
		if(!re)
		{
			MessageInfo *compress=new MessageInfo();
			compress->what=MessageInfo::UNCOMPRESS_FAILED;
			compress->obj=mgr->protocol;
			mgr->helper->sendMessage(compress);

			CCLog("------------>uncompressed file failed");
			return NULL;
		}
	}*/

	MessageInfo * uncompresssucceed=new MessageInfo();
	uncompresssucceed->obj=mgr->protocol;
	uncompresssucceed->what=MessageInfo::UNCOMPRESS_SUCCEED;
	mgr->helper->sendMessage(uncompresssucceed);


	////////开始复制文件了
	string sopath=resourcesPath+"/"+DOWNSOPATH;
	CCLog("--------->so de path is %s",sopath.c_str());
	FILE *fso=fopen(sopath.c_str(),"rb");
	

	string usepath=USESOPATH;
	bool createfolder=createDirectory(usepath.c_str());
	string sotouse(USESOPATH);
	sotouse=sotouse+"/libgame.so";
	CCLog("write path is %s",sotouse.c_str());


	FILE *writeso=fopen(sotouse.c_str(),"wb");
	if(fso&&writeso)
	{
		int len=getFileLength(sopath);
		int times=len/(8192);
		int last=len%(8192);
		char buffer[8192]={0};
		for(int i=0;i<times;i++)
		{
			fread(buffer,1,8192,fso);
			fwrite(buffer,1,8192,writeso);
		}
		fread(buffer,1,last,fso);
		fwrite(buffer,1,last,writeso);
		fclose(writeso);
		fclose(fso);
		mgr->haveSo=true;
		CCLog("-----------------copy succeed ");
	}
	else
	{
		CCLog("not have the file");
	}

	/***********************************************************/
	//删除文件吧1.下载的temp文件的zip文件，2..so文件
	MessageInfo *deleteSomething=new MessageInfo();
	deleteSomething->what=MessageInfo::DELETE_SOMETHING;
	deleteSomething->arg1=mgr->haveSo;
	mgr->helper->sendMessage(deleteSomething);






	MessageInfo* allsucceed=new MessageInfo();
	allsucceed->what=MessageInfo::ALL_SUCCEED;
	allsucceed->obj=mgr->protocol;
	allsucceed->arg1=mgr->haveApk;
	allsucceed->arg2=mgr->haveSo;
	mgr->helper->sendMessage(allsucceed);
	



	return NULL;
}
bool UpdateManager::downloadFile(int index)
{
	

	this->downloadIndex=index;
	VersionInfo vi=downloadInfo[index];
	string filename=vi.getFullpath();//getFileFullName(vi.getPath());
	createDirForFile(filename);
	long sourcesLength=vi.getFileLength();
	int fileLength=getFileLength(filename);
	if(sourcesLength==fileLength)
		return true;
	CCLog("downloadFile name is %s,path is %s",vi.getName(),vi.getPath());
	CCLog("filename is %s",filename.c_str());
	
	FILE* f;
	if(fileLength&&getFileExtention(filename)==string("apk"))
	{
		f=fopen(filename.c_str(),"ab+");
		
	}
	else
	{
		f=fopen(filename.c_str(),"wb");
	}
	if(!f)
	{
		MessageInfo *networkerror=new MessageInfo();
		networkerror->obj=this->protocol;
		networkerror->what=MessageInfo::CREATE_FILE_FAILED;
		this->helper->sendMessage(networkerror);
		CCLog("file pointer create failed");
		return false;
	}
	CURLcode res;
	curl_easy_setopt(curl, CURLOPT_URL,vi.getPath());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFile);
	//curl_easy_setopt(curl,CURLOPT_RESUME_FROM_LARGE,fileLength?fileLength:0);
	if(getFileExtention(filename)==string("apk"))
	{
		char temp[64]={0};
		SPRINTF(temp,"%d-",fileLength);
		curl_easy_setopt(curl, CURLOPT_RANGE,temp);
	}
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, f);
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
	curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, assetsManagerProgressFunc);
	curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, this);
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, timeOut);
	res = curl_easy_perform(curl);
	if (res != 0)
	{
		CCLog("error when download package");
		fclose(f);
		MessageInfo *networkerror=new MessageInfo();
		networkerror->obj=this->protocol;
		networkerror->what=MessageInfo::NET_WORK_ERROR;
		this->helper->sendMessage(networkerror);
		CCLog("downloadFile fialed network error");
		return false;
	}
	
	CCLog("succeed downloading file %s",filename.c_str());

	fclose(f);
	//发送消息，下载成功
	MessageInfo *msg=new MessageInfo();
	msg->what=MessageInfo::ONE_SUCCEED;
	msg->obj=this->protocol;
	msg->filename=string(vi.getName());
	msg->md5=vi.getMd5();
	msg->respath=vi.getRespath();
	helper->sendMessage(msg);
	
	return true;
}

bool UpdateManager::uncompressFile(int index)
{
	VersionInfo vi=downloadInfo[index];
	CCLog("start to uncompressed name %s",vi.getName());
	string outFileName=getFileFullName(vi.getPath());
	if(getFileExtention(vi.getPath())==string("apk"))
	{
		haveApk=true;
		return true;
	}

	// Open the zip file
	unzFile zipfile = unzOpen(outFileName.c_str());
	if (! zipfile)
	{
		CCLog("can not open downloaded zip file %s", outFileName.c_str());
		return false;
	}

	// Get info about the zip file
	unz_global_info global_info;
	if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
	{
		CCLog("can not read file global info of %s", outFileName.c_str());
		unzClose(zipfile);
		return false;
	}

	// Buffer to hold data read from the zip file
	char readBuffer[BUFFER_SIZE];

	CCLog("start uncompressing");

	// Loop to extract all files.
	uLong i;
	for (i = 0; i < global_info.number_entry; ++i)
	{
		// Get info about current file.
		unz_file_info fileInfo;
		char fileName[MAX_FILENAME];
		if (unzGetCurrentFileInfo(zipfile,
			&fileInfo,
			fileName,
			MAX_FILENAME,
			NULL,
			0,
			NULL,
			0) != UNZ_OK)
		{
			CCLog("can not read file info");
			unzClose(zipfile);
			return false;
		}

		string fullPath = resourcesPath +"/"+ fileName;
		CCLog("uncompressed dir is %s",fullPath.c_str());

		// Check if this entry is a directory or a file.
		const size_t filenameLength = strlen(fileName);
		if (fileName[filenameLength-1] == '/')
		{
			// Entry is a direcotry, so create it.
			// If the directory exists, it will failed scilently.
			if (!createDirectory(fullPath.c_str()))
			{
				CCLog("can not create directory %s", fullPath.c_str());
				unzClose(zipfile);
				return false;
			}
		}
		else
		{
			// Entry is a file, so extract it.

			// Open current file.
			if (unzOpenCurrentFile(zipfile) != UNZ_OK)
			{
				CCLog("can not open file %s", fileName);
				unzClose(zipfile);
				return false;
			}

			// Create a file to store current file.
			FILE *out = fopen(fullPath.c_str(), "wb");
			if (! out)
			{
				CCLog("can not open destination file %s", fullPath.c_str());
				unzCloseCurrentFile(zipfile);
				unzClose(zipfile);
				return false;
			}

			// Write current file content to destinate file.
			int error = UNZ_OK;
			do
			{
				error = unzReadCurrentFile(zipfile, readBuffer, BUFFER_SIZE);
				if (error < 0)
				{
					CCLog("can not read zip file %s, error code is %d", fileName, error);
					unzCloseCurrentFile(zipfile);
					unzClose(zipfile);
					return false;
				}

				if (error > 0)
				{
					fwrite(readBuffer, error, 1, out);
				}
			} while(error > 0);

			fclose(out);
		}

		unzCloseCurrentFile(zipfile);

		// Goto next entry listed in the zip file.
		if ((i+1) < global_info.number_entry)
		{
			if (unzGoToNextFile(zipfile) != UNZ_OK)
			{
				CCLog("can not read next file");
				unzClose(zipfile);
				return false;
			}
		}
	}

	CCLog("end uncompressing");

	return true;
}
string UpdateManager::getFileFullName(string url)
{
	string ret;
	int pos=url.find_last_of('/');
	ret=url.substr(pos+1,url.size()-pos);
	ret=downloadTempPath+"/"+ret;
	return ret;
}
string UpdateManager::getFileResName(string url)
{
	string ret;
	int pos=url.find("/data");
	ret=url.substr(pos,url.size()+1-pos);
	return ret;
}
string UpdateManager::getFileExtention(string url)
{
	string ret;
	int pos=url.find_last_of('.');
	ret=url.substr(pos+1,url.size()-pos);
	return ret;
}
int UpdateManager::getFileLength(string fileFullName)
{
	int length=0;
	FILE* f=fopen(fileFullName.c_str(),"rb");
	if(!f)
	{
		return 0;
	}
	fseek(f,0,SEEK_END);
	length=ftell(f);
	fclose(f);
	return length;
}
size_t UpdateManager::writeFile(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	FILE *fp = (FILE*)userdata;
	size_t written = fwrite(ptr, size, nmemb, fp);
	return written;
}
bool UpdateManager::createDirForFile(string str)
{
	int worklength=resourcesPath.length()+1;
	for(int i=worklength;i<(int)(str.length());++i)
	{
		if(str[i]=='/')
		{
			string sub=str.substr(0,i);
			createDirectory(sub.c_str());
		}
	}
	return true;

}
bool UpdateManager::createDirectory(const char *path)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	mode_t processMask = umask(0);
	int ret = mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO);
	umask(processMask);
	if (ret != 0 && (errno != EEXIST))
	{
		return false;
	}

	return true;
#else
	BOOL ret = CreateDirectoryA(path, NULL);
	if (!ret && ERROR_ALREADY_EXISTS != GetLastError())
	{
		return false;
	}
	return true;
#endif
}
long UpdateManager::getRemoteFileLength(string url,CURL* curl)
{
	double fileLength=0;
	curl_easy_setopt(curl,CURLOPT_URL,url.c_str());
	curl_easy_setopt(curl,CURLOPT_NOBODY,1);
	curl_easy_setopt(curl, CURLOPT_HEADER,1);
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
	if(curl_easy_perform(curl)==CURLE_OK)
	{
		curl_easy_getinfo(curl,CURLINFO_CONTENT_LENGTH_DOWNLOAD,&fileLength);
	}
	else
	{
		//出错了
		fileLength=-1;
	}
	return (long)fileLength;
}
#endif // CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
