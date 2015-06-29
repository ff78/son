#include "ShieldManager.h"
#define SHIELD_DATA_FILE_NAME "game_data/Shield_Word/shieldword.json"
ShieldManager* ShieldManager::instance_=0;
ShieldManager::ShieldManager()
{

}
ShieldManager::~ShieldManager()
{

}
ShieldManager* ShieldManager::sharedShieldManager()
{
	if(instance_==0)
	{
		instance_=new ShieldManager();
	}
	return instance_;
}
void ShieldManager::init()
{
	data.clear();
	//unsigned long size=0;
	ssize_t size = 0;
	unsigned char* pData=NULL;
	pData=CCFileUtils::sharedFileUtils()->getFileData(SHIELD_DATA_FILE_NAME,"rb",&size);
	Json::Reader j_reader;
	Json::Value  root_value;
	if(!j_reader.parse((const char*)pData,(const char*)(pData+size),root_value))
	{
		CCLOG("paser JSON FILE FAILED shieldword.json failed");
		CC_SAFE_DELETE_ARRAY(pData);
		return;
	}
	for(Json::Value::iterator iter=root_value.begin();iter!=root_value.end();++iter)
	{
		Json::Value v=(*iter)["name"];
		if(!v.empty())
		{
			data.insert(v.asString()); 
		}
	}
	CC_SAFE_DELETE_ARRAY(pData);
}
bool ShieldManager::isNameContainShield(const string& name)
{
	bool ret=false;
	for(set<string>::iterator iter=data.begin();iter!=data.end();iter++)
	{
		if(name.find(*iter)!=string::npos)
		{
			ret=true;
			break;
		}
	}
	return ret;
}
string ShieldManager::transferChatMessage(const string& message)
{
	string ret=message;
	while (isNameContainShield(ret))
	{
		for(set<string>::iterator iter=data.begin();iter!=data.end();iter++)
		{
			string::size_type pos=ret.find(*iter);
			if(pos!=string::npos)
			{
				int strlength=strlen(iter->c_str());
				ret.replace(pos,strlength,string(strlength,'*'));
				break;
			}
		}
	}
	return ret;

}
