

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
#include "Shop_Config_Mgr.h"
#include "Network_Common/global_macros.h"

#ifdef GAME_CLIENT
#define SHOP_CONFIG_FILE_PATH "game_data/shop_system/shop_config.json"
#else
#define SHOP_CONFIG_FILE_PATH "../config/shop_system/shop_config.json"
#endif

namespace Game_Data
{
    Shop_Config_Mgr* Shop_Config_Mgr::instance_ = NULL;
    Shop_Config_Mgr::Shop_Config_Mgr()
    {

    }

    Shop_Config_Mgr::~Shop_Config_Mgr()
    {

    }

    Shop_Config_Mgr* Shop_Config_Mgr::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Shop_Config_Mgr;
        }

        return instance_;
    }

    int Shop_Config_Mgr::initialize()
    {
        shop_config_map_.clear();
        gold_shop_config_map_.clear();
        token_shop_config_map_.clear();
        special_shop_config_map_.clear();

        load_shop_config();
        return 0;
    }

    int Shop_Config_Mgr::release()
    {
        shop_config* config = NULL;
        shop_config_map_iter iter = shop_config_map_.begin();
        for (;iter != shop_config_map_.end();++iter)
        {
            config = iter->second;
            if (config)
            {
                delete config;
            }
        }

        shop_config_map_.clear();
        gold_shop_config_map_.clear();
        token_shop_config_map_.clear();
        special_shop_config_map_.clear();
        return 0;
    }

    int Shop_Config_Mgr::load_shop_config()
    {
        Json::Value root_value;
        Container_Mgr::instance()->get_json_value_by_file_name(root_value, SHOP_CONFIG_FILE_PATH);

        shop_config* config = NULL;
        for (Json::Value::iterator iter = root_value.begin();iter != root_value.end();++iter)
        {
            config = new shop_config;
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

            v = (*iter)["item_base_id"];
            if (!v.empty())
            {
                config->item_base_id_ = v.asUInt();
            }

            v = (*iter)["money_type"];
            if (!v.empty())
            {
                config->money_type_ = v.asUInt();
            }

            v = (*iter)["cost"];
            if (!v.empty())
            {
                config->cost_ = v.asUInt();
            }

            v = (*iter)["discount"];
            if (!v.empty())
            {
                config->discount_ = v.asUInt();
            }

            v = (*iter)["buy_count"];
            if (!v.empty())
            {
                config->buy_count_ = v.asUInt();
            }

            shop_config_map_.insert(make_pair(config->base_id_,config));
            if (config->type_ == ST_GOLD_SHOP)
            {
                gold_shop_config_map_.insert(make_pair(config->base_id_,config));
            }
            else if (config->type_ == ST_TOKEN_SHOP)
            {
                token_shop_config_map_.insert(make_pair(config->base_id_,config));
            }
            else if (config->type_ == ST_SPECIAL_SHOP)
            {
                special_shop_config_map_.insert(make_pair(config->base_id_,config));
            }
        }

        return 0;
    }

    shop_config* Shop_Config_Mgr::get_shop_config(int goods_id)
    {
        shop_config* config = NULL;
        shop_config_map_iter iter = shop_config_map_.find(goods_id);
        if (iter != shop_config_map_.end())
        {
            config = iter->second;
        }

        return config;
    }

    shop_config_map& Shop_Config_Mgr::get_shop_config_map_by_shop_type(int shop_type)
    {
        if (shop_type == ST_GOLD_SHOP)
        {
            return gold_shop_config_map_;
        }
        else if (shop_type == ST_TOKEN_SHOP)
        {
            return token_shop_config_map_;
        }
        else if (shop_type == ST_SPECIAL_SHOP)
        {
            return special_shop_config_map_;
        }
        else
        {
            return shop_config_map_;
        }
    }
}