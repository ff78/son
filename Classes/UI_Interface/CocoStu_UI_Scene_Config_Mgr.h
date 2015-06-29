#ifndef _UI_JSON_CONFIG_MGR_CLASS_
#define _UI_JSON_CONFIG_MGR_CLASS_

#include "Game_Interface/common.h"
#include "CocoStu_UI_Scene_Config.h"
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
USING_NS_CC;
using namespace ui;
namespace CocoStudio
{
	struct CocoStu_Config;

	class CocoStu_UI_Scene_Config_Mgr
	{
	public:
		CocoStu_UI_Scene_Config_Mgr(void);
		virtual ~CocoStu_UI_Scene_Config_Mgr(void);

		static CocoStu_UI_Scene_Config_Mgr* get_instance();
		void init();
		int get_ui_json_config_by_id(int id, CocoStu_UI_Scene_Config& UJC);
		void load_ui_json_config();
		int get_ui_json_config_map(map<int,CocoStu_UI_Scene_Config>& i_ujc_map);

	private:
		static CocoStu_UI_Scene_Config_Mgr* instance_;
		map<int,CocoStu_UI_Scene_Config> ui_json_config_map_;
	};
}


#endif //_UI_JSON_CONFIG_MGR_CLASS_
