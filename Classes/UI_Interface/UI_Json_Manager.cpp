#include "UI_Json_Manager.h"
#include "cocos2d.h"
//#include "cocos-ext.h"
#include "UI_Json_Config.h"
#include "json/json_header.h"
using namespace ui;
UI_Json_Manager::UI_Json_Manager(void)
{
}


UI_Json_Manager::~UI_Json_Manager(void)
{
}

UI_Json_Manager* UI_Json_Manager::instance_ = 0;
UI_Json_Manager* UI_Json_Manager::get_instance()
{
	if( !instance_ )
		instance_ = new UI_Json_Manager;
	return instance_;
}

void UI_Json_Manager::init()
{
	ui_json_config_map_.clear();
	load_ui_json_config_data();
}

void UI_Json_Manager::load_ui_json_config_data()
{
	ssize_t size = 0;
	unsigned char* pData = 0;

	pData = cocos2d::FileUtils::getInstance()->getFileData("game_data/UI/ui_manager.json","rb",&size);

	Json::Reader j_reader;
	Json::Value j_value;
	if( !j_reader.parse((const char*)pData, (const char*)(pData+size), j_value) )
	{
		CC_SAFE_DELETE_ARRAY(pData);
		return;
	}

	UI_Json_Config UJC;
	for (Json::Value::iterator iter = j_value.begin(); iter!=j_value.end(); ++iter)
	{
		UJC.reset();

		Json::Value &v = (*iter)["id"];
		if( !v.empty() )
		{
			UJC.set_json_id( v.asInt() );
		}
		v = (*iter)["name"];
		if ( !v.empty() )
		{
			UJC.set_json_name( v.asString().data() );
		}
		ui_json_config_map_.insert(make_pair(UJC.get_json_id(),UJC));
	}
	CC_SAFE_DELETE_ARRAY(pData);
}

int UI_Json_Manager::get_ui_json_list( map<int,UI_Json_Config>& r_map )
{
	r_map = ui_json_config_map_;
	return 0;
}

UI_Json_Config* UI_Json_Manager::get_ui_json_info_by_id( int id )
{
	map<int,UI_Json_Config>::iterator iter;
	iter = ui_json_config_map_.find(id);
	if( iter != ui_json_config_map_.end() )
	{
		return & iter->second;
	}
	return NULL;
}
