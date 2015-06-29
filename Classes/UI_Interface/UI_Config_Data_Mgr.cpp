
#include "UI_Config_Data_Mgr.h"
#include "cocos2d.h"
//#include "cocos-ext.h"

#include "UI_Config.h"
#include "Game_Interface/Game_Element_Parse.h"
#include "UI_Interface/UI_Json_Manager.h"
#include "UI_Json_Config.h"
#include "json/json_header.h"
//using namespace ui;
namespace Game_Data
{
UI_Config_Data_Mgr* UI_Config_Data_Mgr::instance_p_ = 0;
UI_Config_Data_Mgr::UI_Config_Data_Mgr()
{

}

UI_Config_Data_Mgr::~UI_Config_Data_Mgr()
{

}

UI_Config_Data_Mgr* UI_Config_Data_Mgr::instance()
{
	if (!instance_p_)
		instance_p_ = new UI_Config_Data_Mgr;
	return  instance_p_;
}

void UI_Config_Data_Mgr::init()
{
	ui_config_list_.clear();
	load_ui_config_data();
}

int UI_Config_Data_Mgr::get_ui_config_data_by_id(int id, UI_Config& UIc)
{
	std::map<int, UI_Config>::iterator itc;

	itc = ui_config_list_.find(id);
	if (itc != ui_config_list_.end() )
		UIc = itc->second;
	return 0;
}

void UI_Config_Data_Mgr::load_ui_config_data()
{
	map<int, UI_Json_Config> ui_json_config_map;
	UI_Json_Manager::get_instance()->get_ui_json_list(ui_json_config_map);
	map<int, UI_Json_Config>::iterator it;
	for (it = ui_json_config_map.begin(); it != ui_json_config_map.end(); it++)
	{
		const char* jsonName = it->second.get_json_name();
		ssize_t size = 0;
		unsigned char* pData = 0;
		pData = cocos2d::FileUtils::getInstance()->getFileData(/*"game_data/ui_config.json"*/jsonName, "rb", &size);

		Json::Reader j_reader;
		Json::Value root_value;
		if (!j_reader.parse((const char*) pData,(const char*) (pData+size), root_value))
		{
			CC_SAFE_DELETE_ARRAY(pData);
			return;
		}

		UI_Config UIc;
		std::list<Game_Element> gm_lst;
		for (Json::Value::iterator iter = root_value.begin(); iter != root_value.end(); ++iter)
		{
			UIc.reset();

			Json::Value &v = (*iter)["id"];
			if (!v.empty())
			{
				UIc.set_id( v.asInt() );
			}
			v = (*iter)["name"];
			if (!v.empty())
			{
				UIc.set_ui_name( v.asString().data() );
			}
			v = (*iter)["type"];
			if (!v.empty())
			{
				UIc.set_type( v.asString().data() );
			}
			v = (*iter)["function"];
			if (!v.empty())
			{
				string exec_str = v.asString();
				Game_Element_Parse::instance()->game_element_parse_cell(exec_str.data(), gm_lst/*, "cell"*/);
				UIc.set_func_list( gm_lst );
			}
			ui_config_list_.insert(make_pair(UIc.get_id(), UIc));
		}

		CC_SAFE_DELETE_ARRAY(pData);
	}
}

int UI_Config_Data_Mgr::get_ui_config_list( map<int, UI_Config>& list)
{
	list = ui_config_list_;
	return 0;
}

UI_Config* UI_Config_Data_Mgr::get_ui_config_list_by_id( int id )
{
    map<int, UI_Config>::iterator itu;
    itu = ui_config_list_.find(id);
    if( itu != ui_config_list_.end())
    {
        return & itu->second;
    }
    return NULL;
}
}