

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

#include "Play_System/Container_Mgr.h"
#include "Login_Reward_Config_Mgr.h"
#include "Network_Common/global_macros.h"

#ifdef GAME_CLIENT
#define LOGIN_REWARD_CONFIG_FILE_PATH "game_data/login_reward_system/login_reward_config.json"
#else
#define LOGIN_REWARD_CONFIG_FILE_PATH "../config/login_reward_system/login_reward_config.json"
#endif

namespace Game_Data
{
    Login_Reward_Config_Mgr* Login_Reward_Config_Mgr::instance_ = NULL;
    Login_Reward_Config_Mgr::Login_Reward_Config_Mgr()
    {

    }

    Login_Reward_Config_Mgr::~Login_Reward_Config_Mgr()
    {

    }

    Login_Reward_Config_Mgr* Login_Reward_Config_Mgr::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Login_Reward_Config_Mgr;
        }

        return instance_;
    }

    int Login_Reward_Config_Mgr::initialize()
    {
        login_reward_config_map_.clear();

        load_login_reward_config();
        return 0;
    }

    int Login_Reward_Config_Mgr::release()
    {
        login_reward_config* config = NULL;
        login_reward_config_map_iter iter = login_reward_config_map_.begin();
        for (;iter != login_reward_config_map_.end();++iter)
        {
            config = iter->second;
            if (config)
            {
                delete config;
            }
        }

        login_reward_config_map_.clear();
        return 0;
    }

    int Login_Reward_Config_Mgr::load_login_reward_config()
    {
        Json::Value root_value;
        Container_Mgr::instance()->get_json_value_by_file_name(root_value, LOGIN_REWARD_CONFIG_FILE_PATH);

        login_reward_config* config = NULL;
        for (Json::Value::iterator iter = root_value.begin();iter != root_value.end();++iter)
        {
            config = new login_reward_config;
            Json::Value &v = (*iter)["base_id"];
            if (!v.empty())
            {
                config->base_id_ =  v.asUInt();
            }

            v = (*iter)["reward_id"];
            if (!v.empty())
            {
                config->reward_id_ = v.asUInt();
            }

            login_reward_config_map_.insert(make_pair(config->base_id_,config));
        }

        return 0;
    }

    login_reward_config* Login_Reward_Config_Mgr::get_login_reward_config(int type)
    {
        int base_id = type+1;
        login_reward_config* config = NULL;
        login_reward_config_map_iter iter = login_reward_config_map_.find(base_id);
        if (iter != login_reward_config_map_.end())
        {
            config = iter->second;
        }

        return config;
    }
}

