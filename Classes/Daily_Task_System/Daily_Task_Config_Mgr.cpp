
//#include <fstream>
#ifdef YN_LINUX
#include <string.h>
#endif

#include "Common/date_time.h"

#ifdef GAME_CLIENT
#include "json/json_header.h"
#include "cocos2d.h"
#else
#include "json/json.h"
#endif

#include "Daily_Task_Config_Mgr.h"
#include "Play_System/Container_Mgr.h"
#include "Network_Common/global_macros.h"

#ifdef GAME_CLIENT
#define DAILY_TASK_CONFIG_FILE_PATH "game_data/daily_task_system/daily_task_config.json"
#else
#define DAILY_TASK_CONFIG_FILE_PATH "../config/daily_task_system/daily_task_config.json"
#endif

namespace Game_Data
{
    Daily_Task_Config_Mgr* Daily_Task_Config_Mgr::instance_ = NULL;
    Daily_Task_Config_Mgr::Daily_Task_Config_Mgr()
    {
        
    }

    Daily_Task_Config_Mgr::~Daily_Task_Config_Mgr()
    {

    }

    Daily_Task_Config_Mgr* Daily_Task_Config_Mgr::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Daily_Task_Config_Mgr;
        }

        return instance_;
    }

    int Daily_Task_Config_Mgr::initialize( void )
    {
        daily_task_config_map_.clear();

        load_daily_task_config_data();
        return 0;
    }

    int Daily_Task_Config_Mgr::release(void)
    {
        daily_task_config_map_iter iter = daily_task_config_map_.begin();
        for (;iter != daily_task_config_map_.end();++iter)
        {
            delete iter->second;
        }

        daily_task_config_map_.clear();
        return 0;
    }

    daily_task_config* Daily_Task_Config_Mgr::get_daily_task_config(int base_id)
    {
        daily_task_config* config = NULL;
        daily_task_config_map_iter it = daily_task_config_map_.find(base_id);
        if (it != daily_task_config_map_.end())
        {
            config = it->second;
        }

        return config;
    }

    int Daily_Task_Config_Mgr::load_daily_task_config_data(void)
    {
        Json::Value root_value;
        Container_Mgr::instance()->get_json_value_by_file_name(root_value, DAILY_TASK_CONFIG_FILE_PATH);

        daily_task_config* config = NULL;
        for (Json::Value::iterator iter = root_value.begin();iter != root_value.end();++iter)
        {
            config = new daily_task_config;
            config->reset();

            Json::Value &v = (*iter)["base_id"];
            if (!v.empty())
            {
                config->base_id_ = v.asInt();
            }

            v = (*iter)["type"];
            if (!v.empty())
            {
                config->type_ = v.asInt();
            }

            v = (*iter)["count"];
            if (!v.empty())
            {
                config->count_ = v.asInt();
            }

            v = (*iter)["exp"];
            if (!v.empty())
            {
                config->exp_ = v.asInt();
            }

            v = (*iter)["money"];
            if (!v.empty())
            {
                config->money_ = v.asInt();
            }
           
            v = (*iter)["name"];
            if (!v.empty())
            {
                config->name_ = v.asInt();
            }

            v = (*iter)["icon"];
            if (!v.empty())
            {
                config->icon_ = v.asInt();
            }

            v = (*iter)["desc"];
            if (!v.empty())
            {
                config->desc_ = v.asInt();
            }

            daily_task_config_map_.insert(make_pair(config->base_id_,config));
        }

        return 0;
    }
}

