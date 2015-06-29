#include "event_system_data_mgr.h"
#include "Game_Interface/Game_Element_Parse.h"
#ifdef GAME_CLIENT
#include "json/json_header.h"
#include "cocos2d.h"
USING_NS_CC;
#define EVENT_DATA_FILE_NAME "game_data/Event_System/event_data_config.json"
#else
#include "json/json.h"
#define EVENT_DATA_FILE_NAME "../config/Event_System/event_data_config.json"
#endif
event_system_data_mgr::event_system_data_mgr()
{

}
event_system_data_mgr* event_system_data_mgr::sharedInstance()
{
	if(instance_==NULL)
	{
		instance_=new event_system_data_mgr();
	}
	return instance_;
}
event_system_data_mgr* event_system_data_mgr::instance_=NULL;
int event_system_data_mgr::init()
{
	event_data_map_t.clear();
#ifdef GAME_CLIENT
	//unsigned long size=0;
	ssize_t size = 0;
	unsigned char* pData=NULL;
	pData=FileUtils::getInstance()->getFileData(EVENT_DATA_FILE_NAME,"rb",&size);
	Json::Reader j_reader;
	Json::Value  root_value;
	if(!j_reader.parse((const char*)pData,(const char*)(pData+size),root_value))
	{
		CCLOG("paser JSON FILE FAILED event_data_config.json failed");
		CC_SAFE_DELETE_ARRAY(pData);
		return -1;
	}
#else
	std::ifstream fin(EVENT_DATA_FILE_NAME);
	if(!fin)
	{
		cout<<"reader event_data_config.json failed"<<endl;
		return -1;
	}
	Json::Reader j_reader;
	Json::Value root_value;
	if(!j_reader.parse(fin,root_value))
	{
		cout<<"reader event_data_config.json failed"<<endl;
		fin.close();
		return -1;
	}
	fin.close();
#endif

	
	for(Json::Value::iterator iter=root_value.begin();iter!=root_value.end();++iter)
	{
		Json::Value v=(*iter)["filename"];
		if(!v.empty())
		{
			load_data(v.asCString());
		}
	}

	return 0;
}
void event_system_data_mgr::load_data(const char* filename)
{
#ifdef GAME_CLIENT
	//unsigned long size=0;
	ssize_t size = 0;
	unsigned char* pData=NULL;
	pData=FileUtils::getInstance()->getFileData(filename,"rb",&size);
	Json::Reader j_reader;
	Json::Value  root_value;
	if(!j_reader.parse((const char*)pData,(const char*)(pData+size),root_value))
	{
		CCLOG("paser JSON FILE FAILED %s failed",filename);
		CC_SAFE_DELETE_ARRAY(pData);
		return ;
	}
#else
	std::ifstream fin(filename);
	if(!fin)
	{
		cout<<"reader "<<filename<<" failed"<<endl;
		return;
	}
	Json::Reader j_reader;
	Json::Value root_value;
	if(!j_reader.parse(fin,root_value))
	{
		cout<<"paser "<<filename<<" failed"<<endl;
		fin.close();
		return;
	}
	fin.close();
#endif

	Event_Data event_data;

	std::list<Game_Element> ge_lst;
	for(Json::Value::iterator iter=root_value.begin();iter!=root_value.end();++iter)
	{
		//memset(&event_data,0,sizeof(event_data));
		Json::Value v=(*iter)["id"];
		if(!v.empty())
		{

			event_data.setId(v.asInt());
		}
		v=(*iter)["condition"];
		if(!v.empty())
		{
			//ge_lst.clear();
			string str=v.asString();
			Game_Element_Parse::instance()->game_element_parse_cell(str.data(), ge_lst, "cell");
			event_data.setCondition(ge_lst);
		}
		v=(*iter)["trigger"];
		if(!v.empty())
		{
			ge_lst.clear();
			string str=v.asString();
			Game_Element_Parse::instance()->game_element_parse_cell(str.data(), ge_lst, "cell");
			event_data.setTrigger(ge_lst);
		}

		v=(*iter)["function"];
		if(!v.empty())
		{
			ge_lst.clear();
			string str=v.asString();
			Game_Element_Parse::instance()->game_element_parse_cell(str.data(), ge_lst, "cell");
			event_data.setFunction(ge_lst);
		}
		event_data_map_t.insert(make_pair(event_data.getId(),event_data));


	}
}
void event_system_data_mgr::getEventDataMap(map<int,Event_Data> &map_t)
{
	map_t=this->event_data_map_t;
}
void event_system_data_mgr::getEventDataById(int id,Event_Data& event_data)
{
	map<int,Event_Data>::iterator iter=event_data_map_t.find(id);
	if(iter!=event_data_map_t.end())
	{
		event_data=iter->second;
	}
	else
	{
		event_data.setId(0);
	}
}