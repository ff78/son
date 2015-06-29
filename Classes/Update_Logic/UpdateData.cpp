#include "UpdateData.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#else
#include "Player_Account/Account_Data_Mgr.h"
#include "json/json_header.h"
#include "UpdateManager.h"
#include "UpdateProtocol.h"
UpDateData* UpDateData::instance_=0;
UpDateData::UpDateData()
{

}
UpDateData* UpDateData::sharedInstance()
{
	if(instance_==NULL)
	{
		instance_=new UpDateData();
	}
	return instance_;
}
int UpDateData::init(string str)
{
	versionData.clear();
	CCLog("--------------------->UpdateData::init json is %s",str.c_str());


	int ret=NO_NEW_VERSION;

	do 
	{
		/*
		curl=curl_easy_init();
		CC_BREAK_IF(!curl);
		std::string _version;				//使用getVersionCode作为回调函数地话，所有的数据都放在这个string中
		CURLcode res;
		curl_easy_setopt(curl, CURLOPT_URL,VERSIONPATH);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getVersionData);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &_version);
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
		res = curl_easy_perform(curl);

		if (res != 0)
		{
			CCLOG("can not get version file content, error code is %d", res);
			curl_easy_cleanup(curl);
			ret=NETWORK_ERROR;
			break;
		}
		curl_easy_cleanup(curl);
		*/


		if(parserJson(str)!=PARSER_FILE_OK)
		{
			//curl_easy_cleanup(curl);
			CCLog("-------------------->paser JSON FAILED");
			ret=PARSER_FILE_FAILED;
			break;
		}
		CCLog("-------------------->paser JSON succeed!");
		/*
		string v=getVersion();
		CCLog("current version is %s",v.c_str());
		string strnew=getNewVersion();
		if(strnew!="NULL")
		{
			if(strnew!=v)
			{
				ret=HAVE_NEW_VERSION;
			}
		}
		else
		{
			ret=NO_NEW_VERSION;
		}*/

		CCLog("--------------------------->paser JSON succeed");
		ret=HAVE_NEW_VERSION;
		//string ss=UpdateManager::getFileName("http://192.168.8.56:8080/versiontable/0.62.zip");
		//int length=UpdateManager::getFileLength(ss);
		//CCLog("%d",length);

		//UpdateManager* um=new UpdateManager(new UpdateProtocol(),3);
		//um->update();
	} while (0);

	
	return ret;
}
size_t UpDateData::getVersionData(uint8_t *ptr, size_t size, size_t nmemb, void *userdata)
{
	string *version = (string*)userdata;
	CCLog("%s",ptr);
	version->append((char*)ptr, size * nmemb);

	return (size * nmemb);
}
int UpDateData::parserJson(string data)
{
	versionData.clear();
	
	const  char* pdata=data.c_str();
	unsigned long size=strlen(pdata);
	Json::Reader reader;
	Json::Value root;
	if(!reader.parse((const char*)pdata,(const char*)(pdata+size),root))
	{
		CCLOG("paser JSON FILE FAILED verioninfo.json");
		return PARSER_FILE_FAILED;
	}
	VersionInfo vi;
	for(Json::Value::iterator it=root.begin();it!=root.end();++it)
	{
		Json::Value v=(*it)["name"];
		if(!v.empty())
		{
			vi.setName(v.asCString());
		}
		v=(*it)["path"];
		if(!v.empty())
		{
			vi.setPath(v.asCString());
		}
		v=(*it)["md5"];
		if(!v.empty())
		{
			vi.setMd5(v.asString());
		}
		versionData.push_back(vi);
	}
	return PARSER_FILE_OK;
}
void UpDateData::getVersionDataVector( vector<VersionInfo>& versionData) 
{
	versionData=this->versionData;
}
string UpDateData::getVersion()
{

	string ver=UserDefault::getInstance()->getStringForKey("VERSION","NULL");
	if(ver=="NULL")
	{
		ver=Account_Data_Mgr::instance()->get_version();
		UserDefault::getInstance()->setStringForKey("VERSION",ver);
		UserDefault::getInstance()->flush();
	}
	return ver;
}
string UpDateData::getNewVersion()
{
	string str="NULL";
	if(versionData.size()!=0)
	{
		VersionInfo vi=versionData[versionData.size()-1];
		str=vi.getName();
	}
	return str;
}
#endif // CC_TARGET_PLATFORM != CC_PLATFORM_WIN32