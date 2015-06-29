

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

#include "Cool_Time_Config_Mgr.h"
#include "Play_System/Container_Mgr.h"
#include "Network_Common/global_macros.h"

#ifdef GAME_CLIENT
#define COOL_TIME_CONFIG_FILE_PATH "game_data/cool_time_system/cool_time_config.json"
#else
#define COOL_TIME_CONFIG_FILE_PATH "../config/cool_time_system/cool_time_config.json"
#endif

namespace Game_Data
{
    Cool_Time_Config_Mgr* Cool_Time_Config_Mgr::instance_ = NULL;
    Cool_Time_Config_Mgr::Cool_Time_Config_Mgr()
    {

    }

    Cool_Time_Config_Mgr::~Cool_Time_Config_Mgr()
    {
        if(instance_)
            delete instance_;
    }

    Cool_Time_Config_Mgr* Cool_Time_Config_Mgr::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Cool_Time_Config_Mgr;
        }

        return instance_;
    }

    int Cool_Time_Config_Mgr::initialize()
    {
        memset(cool_time_config_array_,0,sizeof(cool_time_config_array_));

        load_cool_time_config_data();

        return 0;
    }

    int Cool_Time_Config_Mgr::release()
    {
        for (int i = 0;i < CTT_MAX;++i)
        {
            delete (cool_time_config_array_[i]);
        }

        memset(cool_time_config_array_,0,sizeof(cool_time_config_array_));
        return 0;
    }

    int Cool_Time_Config_Mgr::load_cool_time_config_data()
    {
        Json::Value root_value;
        Container_Mgr::instance()->get_json_value_by_file_name(root_value, COOL_TIME_CONFIG_FILE_PATH);

        cool_time_config* config = NULL;
        //char key[255] = {0};
        for (Json::Value::iterator iter = root_value.begin();iter != root_value.end();++iter)
        {
            config = new cool_time_config;
            Json::Value &v = (*iter)["base_id"];
            if (!v.empty())
            {
                config->base_id_ =  v.asUInt();
            }

            v = (*iter)["type"];
            if (!v.empty())
            {
                config->type_ = v.asUInt();
            }

            v = (*iter)["over"];
            if (!v.empty())
            {
                config->over_ = v.asUInt();
            }

            v = (*iter)["add_time"];
            if (!v.empty())
            {
                config->add_time_ = v.asUInt();
            }

            v = (*iter)["unit_cost"];
            if (!v.empty())
            {
                config->unit_cost_ = v.asUInt();
            }

            v = (*iter)["interval"];
            if (!v.empty())
            {
                config->interval_ = v.asUInt();
            }

           cool_time_config_array_[config->type_] = config;
        }

        return 0;
    }

    cool_time_config* Cool_Time_Config_Mgr::get_cool_time_config(int type)
    {
        return cool_time_config_array_[type%CTT_MAX];
    }
}

