
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

#include "Function_Open_Config_Mgr.h"
#include "Play_System/Container_Mgr.h"
#include "Network_Common/global_macros.h"

#ifdef GAME_CLIENT
#define FUNCTION_OPEN_CONFIG_FILE_PATH "game_data/function_open_system/function_open_config.json"
#else
#define FUNCTION_OPEN_CONFIG_FILE_PATH "../config/function_open_system/function_open_config.json"
#endif

namespace Game_Data
{
    function_open_config_mgr* function_open_config_mgr::instance_ = NULL;
    function_open_config_mgr::function_open_config_mgr()
    {

    }

    function_open_config_mgr::~function_open_config_mgr()
    {

    }

    function_open_config_mgr* function_open_config_mgr::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new function_open_config_mgr;
        }

        return instance_;
    }

    int function_open_config_mgr::initialize()
    {
        load_function_open_config_data();

        return 0;
    }

    int function_open_config_mgr::load_function_open_config_data()
    {
        Json::Value root_value;
        Container_Mgr::instance()->get_json_value_by_file_name(root_value, FUNCTION_OPEN_CONFIG_FILE_PATH);

        function_open_config* config = NULL;
        for (Json::Value::iterator iter = root_value.begin();iter != root_value.end();++iter)
        {
            config = new function_open_config;
            Json::Value &v = (*iter)["index"];
            if (!v.empty())
            {
                config->index_ =  v.asInt();
            }

            v = (*iter)["quest_id"];
            if (!v.empty())
            {
                config->quest_id_ = v.asInt();
            }
			function_open_config_map_.insert(make_pair(config->index_, config));
        }

        return 0;
    }

	int function_open_config_mgr::get_map_size()
	{
		return function_open_config_map_.size();
	}

	int function_open_config_mgr::get_cur_index_point_quest_id( int index )
	{
		if( index < 0 )
			return -1;

		function_open_config_map_iter iter = function_open_config_map_.find( index );
		if (iter != function_open_config_map_.end())
		{
			return iter->second->quest_id_;
		}

		return -1;
	}

	function_open_config* function_open_config_mgr::get_cur_index_point_config( int index )
	{
		if( index < 0 )
			return NULL;

		function_open_config_map_iter iter = function_open_config_map_.find( index );
		if (iter != function_open_config_map_.end())
		{
			return iter->second;
		}

		return NULL;
	}



}

