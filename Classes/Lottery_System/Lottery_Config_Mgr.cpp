
//#include <fstream>
#ifdef YN_LINUX
#include <string.h>
#endif

#ifdef GAME_CLIENT
#include "json/json_header.h"
#include "cocos2d.h"
#else
#include "json/json.h"
#endif

#include "Event_System/event_system_data_mgr.h"
#include "quest_system/quest_data/quest_json_config.h"
#include "Lottery_Config_Mgr.h"
#include "Play_System/Container_Mgr.h"
#include "Network_Common/global_macros.h"

#ifdef GAME_CLIENT
#define LOTTERY_CATEGORY_CONFIG_FILE_PATH "game_data/Lottery_System/lottery_category.json"

#else
#define LOTTERY_CATEGORY_CONFIG_FILE_PATH "../config/Lottery_System/lottery_category.json"

#endif

namespace Game_Data
{
    Lottery_Config_Mgr* Lottery_Config_Mgr::instance_ = NULL;
    Lottery_Config_Mgr::Lottery_Config_Mgr()
    {

    }

    Lottery_Config_Mgr::~Lottery_Config_Mgr()
    {

    }

    Lottery_Config_Mgr* Lottery_Config_Mgr::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Lottery_Config_Mgr;
        }

        return instance_;
    }

    int Lottery_Config_Mgr::initialize( void )
    {
        map_lottery_category_config_.clear();
		load_lottery_category_config_data();

        return 0;
    }

    int Lottery_Config_Mgr::release(void)
    {

        LotteryCategory_Map_Iter iter = map_lottery_category_config_.begin();
        for (;iter != map_lottery_category_config_.end();++iter)
        {
            delete iter->second;
        }

        map_lottery_category_config_.clear();

        return 0;
    }


    void Lottery_Config_Mgr::proc_string(const string& content_str,item_content &ic)
    {
        game_element_list_t game_element_vec;
        game_content_parse::instance()->game_element_parse_cell(content_str, game_element_vec);
        ic.set_element(game_element_vec);
    }

	int Lottery_Config_Mgr::load_lottery_category_config_data()
	{
		Json::Value root_value;
		Container_Mgr::instance()->get_json_value_by_file_name(root_value, LOTTERY_CATEGORY_CONFIG_FILE_PATH);
		LotteryCategory* LC_Config = NULL;
		for (Json::Value::iterator iter = root_value.begin(); iter != root_value.end(); ++iter)
		{
			LC_Config = new LotteryCategory;
			memset(LC_Config, 0, sizeof(LotteryCategory));

			Json::Value &v = (*iter)["base_id"];
		}


		//map_lottery_category_config_
		return 0;
	}


   
}

