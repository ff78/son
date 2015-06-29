#ifndef _UI_JSON_MANAGER_CLASS_
#define _UI_JSON_MANAGER_CLASS_ 
#include "ui/CocosGUI.h"

#include "Game_Interface/common.h"
USING_NS_CC;
using namespace ui;
class UI_Json_Config;

class UI_Json_Manager
{
public:
	UI_Json_Manager(void);
	virtual ~UI_Json_Manager(void);

	static UI_Json_Manager* get_instance();
	void init();

	void load_ui_json_config_data();
	int get_ui_json_list(map<int,UI_Json_Config>& list);
	UI_Json_Config* get_ui_json_info_by_id(int id);

private:
	static UI_Json_Manager* instance_;
	map<int, UI_Json_Config> ui_json_config_map_;
};

#endif //_UI_JSON_MANAGER_CLASS_
