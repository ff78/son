

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
#include "Item_Config_Mgr.h"
#include "Play_System/Container_Mgr.h"
#include "Network_Common/global_macros.h"

#ifdef GAME_CLIENT
#define EQUIPMENT_DEPOT_CONFIG_FILE_PATH "game_data/item_system/equipment_depot_config.json"
#define EQUIPMENT_CONFIG_FILE_PATH "game_data/item_system/equipment_config.json"
#define USABLE_ITEM_CONFIG_FILE_PATH "game_data/item_system/usable_item_config.json"
#define QUEST_ITEM_CONFIG_FILE_PATH "game_data/item_system/quest_item_config.json"
#define MATERIAL_ITEM_CONFIG_FILE_PATH "game_data/item_system/material_item_config.json"
#define MATERIAL_FRAGMENT_CONFIG_FILE_PATH "game_data/item_system/material_fragment_config.json"
#define BOOK_FRAGMENT_CONFIG_FILE_PATH "game_data/item_system/book_fragment_config.json"
#define GIFT_ITEM_CONFIG_FILE_PATH "game_data/item_system/gift_item_config.json"
#define BOOK_CONFIG_FILE_PATH "game_data/item_system/book_config.json"
#define BOOK_ATTR_CONFIG_FILE_PATH "game_data/item_system/book_attr_config.json"
#define GEM_CONFIG_FILE_PATH "game_data/item_system/gem_config.json"
#define ICON_CONFIG_FILE_PATH "game_data/item_system/item_icon_config.json"
#define QUALITY_UPGRADE_CONFIG_FILE_PATH "game_data/item_system/quality_upgrade_config.json"
#else
#define EQUIPMENT_DEPOT_CONFIG_FILE_PATH "../config/item_system/equipment_depot_config.json"
#define EQUIPMENT_CONFIG_FILE_PATH "../config/item_system/equipment_config.json"
#define USABLE_ITEM_CONFIG_FILE_PATH "../config/item_system/usable_item_config.json"
#define QUEST_ITEM_CONFIG_FILE_PATH "../config/item_system/quest_item_config.json"
#define MATERIAL_ITEM_CONFIG_FILE_PATH "../config/item_system/material_item_config.json"
#define MATERIAL_FRAGMENT_CONFIG_FILE_PATH "../config/item_system/material_fragment_config.json"
#define BOOK_FRAGMENT_CONFIG_FILE_PATH "../config/item_system/book_fragment_config.json"
#define GIFT_ITEM_CONFIG_FILE_PATH "../config/item_system/gift_item_config.json"
#define BOOK_CONFIG_FILE_PATH "../config/item_system/book_config.json"
#define BOOK_ATTR_CONFIG_FILE_PATH "../config/item_system/book_attr_config.json"
#define GEM_CONFIG_FILE_PATH "../config/item_system/gem_config.json"
#define QUALITY_UPGRADE_CONFIG_FILE_PATH "../config/item_system/quality_upgrade_config.json"
#endif

#define ICON_PATH "icon.plist"

#include "cocostudio/CocoStudio.h"
#include "ClientLogic/Utils/GameReader.h"

using namespace cocostudio;

namespace Game_Data
{
    Item_Config_Mgr* Item_Config_Mgr::instance_ = NULL;
    Item_Config_Mgr::Item_Config_Mgr()
    {

    }

    Item_Config_Mgr::~Item_Config_Mgr()
    {

    }

    Item_Config_Mgr* Item_Config_Mgr::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Item_Config_Mgr;
        }

        return instance_;
    }

    int Item_Config_Mgr::initialize( void )
    {
        m_map_item_config.clear();
        m_map_equipment_depot_config.clear();
        m_map_item_fragment_config.clear();
        m_map_equipment_config.clear();
        m_map_usable_item_config.clear();
        m_map_book_config.clear();
        m_map_gem_config.clear();
        memset(quality_upgrade_config_array_,0,sizeof(quality_upgrade_config_array_));

        load_equipment_depot_config_data();
        load_equipment_config_data();
        load_usable_item_config_data();
        load_quest_item_config_data();
        load_material_item_config_data();
        load_material_fragment_config_data();
        load_book_fragment_config_data();
        load_gift_item_config_data();
        load_book_config_data();
        load_book_attr_config_data();
        load_gem_config_data();
        //load_icon_config_data();
        load_quality_upgrade_config_data();

        return 0;
    }

    int Item_Config_Mgr::release(void)
    {
        /*Item_Fragment_Config_Map_Iter item_fragment_iter = m_map_item_fragment_config.begin();
        for (;item_fragment_iter != m_map_item_fragment_config.end();++item_fragment_iter)
        {
            delete item_fragment_iter->second;
        }

        Equipment_Config_Map_Iter equipment_iter = m_map_equipment_config.begin();
        for (;equipment_iter != m_map_equipment_config.end();++equipment_iter)
        {
            delete equipment_iter->second;
        }

        Usable_Item_Config_Map_Iter usable_item_iter = m_map_usable_item_config.begin();
        for (;usable_item_iter != m_map_usable_item_config.end();++usable_item_iter)
        {
            delete usable_item_iter->second;
        }

        Book_Config_Map_Iter book_iter = m_map_book_config.begin();
        for (;book_iter != m_map_book_config.end();++book_iter)
        {
            delete book_iter->second;
        }*/

        Item_Config_Map_Iter iter = m_map_item_config.begin();
        for (;iter != m_map_item_config.end();++iter)
        {
            delete iter->second;
        }
        
        quality_upgrade_config* quc = NULL;
        for (int i = 0;i < QMT_MAX;++i)
        {
            for (int j = 0;j < (QT_MAX-1);++j)
            {
                quc = quality_upgrade_config_array_[i][j];
                if (quc)
                {
                    delete quc;
                }
            }
        }

        m_map_item_config.clear();
        m_map_equipment_depot_config.clear();
        m_map_item_fragment_config.clear();
        m_map_equipment_config.clear();
        m_map_usable_item_config.clear();
        m_map_gem_config.clear();
        m_map_book_config.clear();
        memset(quality_upgrade_config_array_,0,sizeof(quality_upgrade_config_array_));

        return 0;
    }

    Item_Config* Item_Config_Mgr::get_item_config(int base_id)
    {
        Item_Config* config = NULL;
        Item_Config_Map_Iter it = m_map_item_config.find(base_id);
        if (it != m_map_item_config.end())
        {
            config = it->second;
        }

        return config;
    }

    Equipment_Depot_Config* Item_Config_Mgr::get_equipment_depot_config(int base_id)
    {
        Equipment_Depot_Config* config = NULL;
        Equipment_Depot_Config_Map_Iter it = m_map_equipment_depot_config.find(base_id);
        if (it != m_map_equipment_depot_config.end())
        {
            config = it->second;
        }

        return config;
    }

    Item_Fragment_Config* Item_Config_Mgr::get_item_fragment_config(int base_id)
    {
        Item_Fragment_Config* config = NULL;
        Item_Fragment_Config_Map_Iter it = m_map_item_fragment_config.find(base_id);
        if (it != m_map_item_fragment_config.end())
        {
            config = it->second;
        }

        return config;
    }

    Equipment_Config* Item_Config_Mgr::get_equipment_config(int base_id)
    {
        Equipment_Config* config = NULL;
        Equipment_Config_Map_Iter it = m_map_equipment_config.find(base_id);
        if (it != m_map_equipment_config.end())
        {
            config = it->second;
        }

        return config;
    }

    Usable_Item_Config* Item_Config_Mgr::get_usable_item_config(int base_id)
    {
        Usable_Item_Config* config = NULL;
        Usable_Item_Config_Map_Iter it = m_map_usable_item_config.find(base_id);
        if (it != m_map_usable_item_config.end())
        {
            config = it->second;
        }

        return config;
    }

    Book_Config* Item_Config_Mgr::get_book_config(int base_id)
    {
        Book_Config* config = NULL;
        Book_Config_Map_Iter it = m_map_book_config.find(base_id);
        if (it != m_map_book_config.end())
        {
            config = it->second;
        }

        return config;
    }

    Gem_Config* Item_Config_Mgr::get_gem_config(int base_id)
    {
        Gem_Config* config = NULL;
        Gem_Config_Map_Iter it = m_map_gem_config.find(base_id);
        if (it != m_map_gem_config.end())
        {
            config = it->second;
        }

        return config;
    }

    int Item_Config_Mgr::get_item_type_by_base_id(int base_id)
    {   
        int type = 0;
        type = base_id / 10000;
        return type;
    }

    int Item_Config_Mgr::get_book_max_level(int base_id,int quality)
    {
        int max_level = 0;
        Book_Config* config = get_book_config(base_id);
        if (config)
        {
            max_level = config->max_level[quality];
        }

        return max_level;
    }

    int Item_Config_Mgr::get_equipment_level_up_cost(int base_id,int level)
    {
        int cost = 0;
        Equipment_Config* config = get_equipment_config(base_id);
        if (config)
        {
            cost = (int)((EQUIPMENT_UPGRADE_BASE_COST + EQUIPMENT_UPGRADE_COST_COEFFICIENT * level) *
                (1 + (level / 10.0f)) / 4.0f * config->upgrade_cost_coefficient / 10000);
        }

        return cost;
    }

    int Item_Config_Mgr::get_book_level_up_need_exp(int base_id,int level,int quality)
    {
        quality = quality % QT_MAX;
        int need = 0;
        Book_Config* config = get_book_config(base_id);
        if (config)
        {
            need = int(config->upgrade_base_exp[quality] * (config->upgrade_exp_grow[quality] / 10000.0f * (level - 1) + 1));
        }

        return need;
    }

    int Item_Config_Mgr::get_equipment_offer_money(int base_id,int level)
    {
        int offer = 0;
        Equipment_Config* config = get_equipment_config(base_id);
        if (config)
        {
            offer = config->sell_income;
            for (int i = 1;i < level;++i)
            {
                offer += (EQUIPMENT_UPGRADE_COST_COEFFICIENT * level + EQUIPMENT_UPGRADE_BASE_COST) * config->upgrade_cost_coefficient / 10000;
            }
        }

        return offer;
    }

    int Item_Config_Mgr::get_book_offer_exp(int base_id,int level,int quality)
    {
        quality = quality % QT_MAX;
        float offer = 0.0f;
        Book_Config* config = get_book_config(base_id);
        if (config)
        {
            offer = float(config->exp);
            if (level > 0)
            {
                int max_level = 0;
                for (int i = QT_WHITE;i < quality;++i)
                {
                    max_level = config->max_level[i];
                    for (int j = 1;j < max_level;++j)
                    {
                        offer += config->upgrade_base_exp[i] * (config->upgrade_exp_grow[i] / 10000.0f * (j- 1) + 1);
                    }
                }

                for (int i = 1;i < level;++i)
                {
                    offer += config->upgrade_base_exp[quality] * (config->upgrade_exp_grow[quality] / 10000.0f * (i- 1) + 1);
                }
            }
        }

        return int(offer);
    }

    int Item_Config_Mgr::get_equipment_attr(int base_id,int level,int quality,int attr_type)
    {
        quality = quality % QT_MAX;
        attr_type = attr_type % MAX_ATTR_COUNT;
        int attr = 0;
        Equipment_Config* config = get_equipment_config(base_id);
        if (config)
        {
            attr = (int)((config->base_attr[attr_type] * 10000.0f + config->attr_level_grow[attr_type] * level) * ( config->attr_quality_grow[quality] / 10000.0f) / 10000.0f);
        }

        return attr;
    }

    int Item_Config_Mgr::get_book_attr(int base_id,int level,int quality,int attr_type)
    {
        quality = quality % QT_MAX;
        attr_type = attr_type % MAX_ATTR_COUNT;
        int attr = 0;
        Book_Config* config = get_book_config(base_id);
        if (config)
        {
            attr = (int)(config->base_attr[quality][attr_type] + config->attr_grow[quality][attr_type] * level);
        }

        return attr;
    }

    int Item_Config_Mgr::get_item_sell_income(int base_id,int level,int count)
    {
        int income = 0;
        Item_Config* config = get_item_config(base_id);
        if (config)
        {
            if (config->type == IT_EQUIPMENT)
            {
                income = get_equipment_offer_money(base_id,level);
            }
            else
            {
                income = config->sell_income;
            }
        }

        return income * count;
    }

    int Item_Config_Mgr::load_equipment_depot_config_data()
    {
        Json::Value root_value;
        Container_Mgr::instance()->get_json_value_by_file_name(root_value, EQUIPMENT_DEPOT_CONFIG_FILE_PATH);

        
        Equipment_Depot_Config* config = NULL;
        //char key[255] = {0};
        for (Json::Value::iterator iter = root_value.begin();  iter != root_value.end();  ++iter)
        {
            config = new Equipment_Depot_Config;
            memset(config, 0, sizeof(Equipment_Depot_Config));

            Json::Value &v = (*iter)["base_id"];
            if (!v.empty())
            {
                config->base_id =  v.asUInt();
            }

            v = (*iter)["quality"];
            if (!v.empty())
            {
                config->quality = v.asUInt();
            }

            v = (*iter)["level"];
            if (!v.empty())
            {
                config->level = v.asUInt();
            }

            v = (*iter)["item_base_id"];
            if (!v.empty())
            {
                config->item_base_id = v.asUInt();
            }

            m_map_equipment_depot_config.insert(make_pair(config->base_id, config));
            m_map_item_config.insert(make_pair(config->base_id, config));
        }

        return 0;
    }

    int Item_Config_Mgr::load_equipment_config_data()
    {
//        auto doc = GameReader::getDocInstance(EQUIPMENT_CONFIG_FILE_PATH);
//        if (doc->IsArray()){
//            int size = doc->Size();
//            Equipment_Config* config = NULL;
//            
//            for (int i = 0; i < size; i++) {
//                const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*doc), i);
//                config = new Equipment_Config;
//                config->base_id = DICTOOL->getIntValue_json(dic, "base_id");
//                config->type = DICTOOL->getIntValue_json(dic, "type");
//                config->name = DICTOOL->getStringValue_json(dic, "name");
//                config->icon = DICTOOL->getStringValue_json(dic, "icon");
//                config->quality = DICTOOL->getIntValue_json(dic, "quality");
//                config->desc = DICTOOL->getStringValue_json(dic, "desc");
//                config->drop_desc = DICTOOL->getStringValue_json(dic, "drop_desc");
//                config->bind = DICTOOL->getIntValue_json(dic, "bind");
//                config->pile_count = DICTOOL->getIntValue_json(dic, "pile_count");
//                config->gold_cost = DICTOOL->getIntValue_json(dic, "gold_cost");
//                config->token_cost = DICTOOL->getIntValue_json(dic, "token_cost");
//                config->sell_income = DICTOOL->getIntValue_json(dic, "sell_income");
//                config->can_sell = DICTOOL->getIntValue_json(dic, "can_sell");
//                config->can_auction = DICTOOL->getIntValue_json(dic, "can_auction");
//                config->can_trade = DICTOOL->getIntValue_json(dic, "can_trade");
//                config->can_store = DICTOOL->getIntValue_json(dic, "can_store");
//                config->can_pile = DICTOOL->getIntValue_json(dic, "can_pile");
//                config->can_destroy = DICTOOL->getIntValue_json(dic, "can_destroy");
//                config->destroy_time = DICTOOL->getIntValue_json(dic, "destroy_time");
//                config->sort = DICTOOL->getIntValue_json(dic, "sort");
//                config->occupation = DICTOOL->getIntValue_json(dic, "occupation");
//                config->pos = DICTOOL->getIntValue_json(dic, "pos");
//                config->upgrade_cost_coefficient = DICTOOL->getIntValue_json(dic, "upgrade_cost_coefficient");
//                
//                for (int i = 0;i < MAX_ATTR_COUNT;++i)
//                {
//                    cocos2d::Value num(i);
//                    if (i < QT_MAX)
//                    {
//                        std::string name("attr_quality_grow_");
//                        config->attr_quality_grow[i] = DICTOOL->getIntValue_json(dic, (name+num.asString()).c_str());
//                    }
//                    
//                    std::string baseAttrName("base_attr_");
//                    config->base_attr[i] = DICTOOL->getIntValue_json(dic, (baseAttrName+num.asString()).c_str());
//                    
//                    std::string lvlAttrName("attr_level_grow_");
//                    config->attr_level_grow[i] = DICTOOL->getIntValue_json(dic, (lvlAttrName+num.asString()).c_str());
//                }
//                
//                m_map_equipment_config.insert(make_pair(config->base_id, config));
//                m_map_item_config.insert(make_pair(config->base_id, config));
//            }
//        }

        Json::Value root_value;
        Container_Mgr::instance()->get_json_value_by_file_name(root_value, EQUIPMENT_CONFIG_FILE_PATH);
        
        Equipment_Config* config = NULL;
        char key[255] = {0};
        for (Json::Value::iterator iter = root_value.begin();  iter != root_value.end();  ++iter)
        {
            config = new Equipment_Config;
            memset(config, 0, sizeof(Equipment_Config));
            
            Json::Value &v = (*iter)["base_id"];
            if (!v.empty())
            {
                config->base_id =  v.asUInt();
            }
            
            v = (*iter)["type"];
            if (!v.empty())
            {
                config->type = v.asUInt();
            }
            
            v = (*iter)["name"];
            if (!v.empty())
            {
                config->name = v.asUInt();
            }
            
            v = (*iter)["icon"];
            if (!v.empty())
            {
                config->icon = v.asUInt();
            }
            
            v = (*iter)["quality"];
            if (!v.empty())
            {
                config->quality = v.asUInt();
            }
            
            v = (*iter)["desc"];
            if (!v.empty())
            {
                config->desc = v.asUInt();
            }
            
            v = (*iter)["drop_desc"];
            if (!v.empty())
            {
                config->drop_desc = v.asUInt();
            }
            
            v = (*iter)["bind"];
            if (!v.empty())
            {
                config->bind = v.asUInt();
            }
            
            v = (*iter)["pile_count"];
            if (!v.empty())
            {
                config->pile_count = v.asUInt();
            }
            
            v = (*iter)["gold_cost"];
            if (!v.empty())
            {
                config->gold_cost = v.asUInt();
            }
            
            v = (*iter)["token_cost"];
            if (!v.empty())
            {
                config->token_cost = v.asUInt();
            }
            
            v = (*iter)["sell_income"];
            if (!v.empty())
            {
                config->sell_income = v.asUInt();
            }
            
            v = (*iter)["can_sell"];
            if (!v.empty())
            {
                config->can_sell = v.asUInt();
            }
            
            v = (*iter)["can_auction"];
            if (!v.empty())
            {
                config->can_auction = v.asUInt();
            }
            
            v = (*iter)["can_trade"];
            if (!v.empty())
            {
                config->can_trade = v.asUInt();
            }
            
            v = (*iter)["can_store"];
            if (!v.empty())
            {
                config->can_store = v.asUInt();
            }
            
            v = (*iter)["can_pile"];
            if (!v.empty())
            {
                config->can_pile = v.asUInt();
            }
            
            v = (*iter)["can_destroy"];
            if (!v.empty())
            {
                config->can_destroy = v.asUInt();
            }
            
            v = (*iter)["destroy_time"];
            if (!v.empty())
            {
                config->destroy_time = v.asUInt();
            }
            
            v = (*iter)["sort"];
            if (!v.empty())
            {
                config->sort = v.asUInt();
            }
            
            v = (*iter)["occupation"];
            if (!v.empty())
            {
                config->occupation = v.asUInt();
            }
            
            v = (*iter)["pos"];
            if (!v.empty())
            {
                config->pos = v.asUInt();
            }
            
            v = (*iter)["upgrade_cost_coefficient"];
            if (!v.empty())
            {
                config->upgrade_cost_coefficient = v.asUInt();
            }
            
            for (int i = 0;i < MAX_ATTR_COUNT;++i)
            {
                if (i < QT_MAX)
                {
                    memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS
                    sprintf_s(key,"attr_quality_grow_%d",i);
#else
                    sprintf(key,"attr_quality_grow_%d",i);
#endif
                    v = (*iter)[key];
                    if (!v.empty())
                    {
                        config->attr_quality_grow[i] = v.asUInt();
                    }
                }
                
                memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS
                sprintf_s(key,"base_attr_%d",i);
#else
                sprintf(key,"base_attr_%d",i);
#endif
                v = (*iter)[key];
                if (!v.empty())
                {
                    config->base_attr[i] = v.asUInt();
                }
                
                memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS
                sprintf_s(key,"attr_level_grow_%d",i);
#else
                sprintf(key,"attr_level_grow_%d",i);
#endif
                v = (*iter)[key];
                if (!v.empty())
                {
                    config->attr_level_grow[i] = v.asUInt();
                }
            }
            
            m_map_equipment_config.insert(make_pair(config->base_id, config));
            m_map_item_config.insert(make_pair(config->base_id, config));
        }

        return 0;
    }

    int Item_Config_Mgr::load_usable_item_config_data()
    {
        Json::Value root_value;
        Container_Mgr::instance()->get_json_value_by_file_name(root_value, USABLE_ITEM_CONFIG_FILE_PATH);
        
        Usable_Item_Config* config = NULL;
        //char key[255] = {0};
        for (Json::Value::iterator iter = root_value.begin();  iter != root_value.end();  ++iter)
        {
            config = new Usable_Item_Config;
            memset(config, 0, sizeof(Usable_Item_Config));
            
            Json::Value &v = (*iter)["base_id"];
            if (!v.empty())
            {
                config->base_id =  v.asUInt();
            }
            
            v = (*iter)["type"];
            if (!v.empty())
            {
                config->type = v.asUInt();
            }
            
            v = (*iter)["name"];
            if (!v.empty())
            {
                config->name = v.asUInt();
            }
            
            v = (*iter)["icon"];
            if (!v.empty())
            {
                config->icon = v.asUInt();
            }
            
            v = (*iter)["quality"];
            if (!v.empty())
            {
                config->quality = v.asUInt();
            }
            
            v = (*iter)["desc"];
            if (!v.empty())
            {
                config->desc = v.asUInt();
            }
            
            v = (*iter)["drop_desc"];
            if (!v.empty())
            {
                config->drop_desc = v.asUInt();
            }
            
            v = (*iter)["bind"];
            if (!v.empty())
            {
                config->bind = v.asUInt();
            }
            
            v = (*iter)["pile_count"];
            if (!v.empty())
            {
                config->pile_count = v.asUInt();
            }
            
            v = (*iter)["gold_cost"];
            if (!v.empty())
            {
                config->gold_cost = v.asUInt();
            }
            
            v = (*iter)["token_cost"];
            if (!v.empty())
            {
                config->token_cost = v.asUInt();
            }
            
            v = (*iter)["sell_income"];
            if (!v.empty())
            {
                config->sell_income = v.asUInt();
            }
            
            v = (*iter)["can_sell"];
            if (!v.empty())
            {
                config->can_sell = v.asUInt();
            }
            
            v = (*iter)["can_auction"];
            if (!v.empty())
            {
                config->can_auction = v.asUInt();
            }
            
            v = (*iter)["can_trade"];
            if (!v.empty())
            {
                config->can_trade = v.asUInt();
            }
            
            v = (*iter)["can_store"];
            if (!v.empty())
            {
                config->can_store = v.asUInt();
            }
            
            v = (*iter)["can_pile"];
            if (!v.empty())
            {
                config->can_pile = v.asUInt();
            }
            
            v = (*iter)["can_destroy"];
            if (!v.empty())
            {
                config->can_destroy = v.asUInt();
            }
            
            v = (*iter)["destroy_time"];
            if (!v.empty())
            {
                config->destroy_time = v.asUInt();
            }
            
            v = (*iter)["sort"];
            if (!v.empty())
            {
                config->sort = v.asUInt();
            }
            
            v = (*iter)["event_id"];
            if (!v.empty())
            {
                config->event_id = v.asUInt();
            }
            
            m_map_usable_item_config.insert(make_pair(config->base_id, config));
            m_map_item_config.insert(make_pair(config->base_id, config));
        }

//        auto doc = GameReader::getDocInstance(USABLE_ITEM_CONFIG_FILE_PATH);
//        if (doc->IsArray()){
//            int size = doc->Size();
//            Usable_Item_Config* config = NULL;
//            
//            for (int i = 0; i < size; i++) {
//                const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*doc), i);
//                config = new Usable_Item_Config;
//                config->base_id = DICTOOL->getIntValue_json(dic, "base_id");
//                config->type = DICTOOL->getIntValue_json(dic, "type");
//                config->name = DICTOOL->getStringValue_json(dic, "name");
//                config->icon = DICTOOL->getStringValue_json(dic, "icon");
//                config->quality = DICTOOL->getIntValue_json(dic, "quality");
//                config->desc = DICTOOL->getStringValue_json(dic, "desc");
//                config->drop_desc = DICTOOL->getStringValue_json(dic, "drop_desc");
//                config->bind = DICTOOL->getIntValue_json(dic, "bind");
//                config->pile_count = DICTOOL->getIntValue_json(dic, "pile_count");
//                config->gold_cost = DICTOOL->getIntValue_json(dic, "gold_cost");
//                config->token_cost = DICTOOL->getIntValue_json(dic, "token_cost");
//                config->sell_income = DICTOOL->getIntValue_json(dic, "sell_income");
//                config->can_sell = DICTOOL->getIntValue_json(dic, "can_sell");
//                config->can_auction = DICTOOL->getIntValue_json(dic, "can_auction");
//                config->can_trade = DICTOOL->getIntValue_json(dic, "can_trade");
//                config->can_store = DICTOOL->getIntValue_json(dic, "can_store");
//                config->can_pile = DICTOOL->getIntValue_json(dic, "can_pile");
//                config->can_destroy = DICTOOL->getIntValue_json(dic, "can_destroy");
//                config->destroy_time = DICTOOL->getIntValue_json(dic, "destroy_time");
//                config->sort = DICTOOL->getIntValue_json(dic, "sort");
//                config->event_id = DICTOOL->getIntValue_json(dic, "event_id");
//                
//                m_map_usable_item_config.insert(make_pair(config->base_id, config));
//                m_map_item_config.insert(make_pair(config->base_id, config));
//            }
//        }
        return 0;
    }

    int Item_Config_Mgr::load_quest_item_config_data()
    {
        Json::Value root_value;
        Container_Mgr::instance()->get_json_value_by_file_name(root_value, QUEST_ITEM_CONFIG_FILE_PATH);
        
        Item_Config* config = NULL;
        //char key[255] = {0};
        for (Json::Value::iterator iter = root_value.begin();  iter != root_value.end();  ++iter)
        {
            config = new Item_Config;
            memset(config, 0, sizeof(Item_Config));
            
            Json::Value &v = (*iter)["base_id"];
            if (!v.empty())
            {
                config->base_id =  v.asUInt();
            }
            
            v = (*iter)["type"];
            if (!v.empty())
            {
                config->type = v.asUInt();
            }
            
            v = (*iter)["name"];
            if (!v.empty())
            {
                config->name = v.asUInt();
            }
            
            v = (*iter)["icon"];
            if (!v.empty())
            {
                config->icon = v.asUInt();
            }
            
            v = (*iter)["quality"];
            if (!v.empty())
            {
                config->quality = v.asUInt();
            }
            
            v = (*iter)["desc"];
            if (!v.empty())
            {
                config->desc = v.asUInt();
            }
            
            v = (*iter)["drop_desc"];
            if (!v.empty())
            {
                config->drop_desc = v.asUInt();
            }
            
            v = (*iter)["bind"];
            if (!v.empty())
            {
                config->bind = v.asUInt();
            }
            
            v = (*iter)["pile_count"];
            if (!v.empty())
            {
                config->pile_count = v.asUInt();
            }
            
            v = (*iter)["gold_cost"];
            if (!v.empty())
            {
                config->gold_cost = v.asUInt();
            }
            
            v = (*iter)["token_cost"];
            if (!v.empty())
            {
                config->token_cost = v.asUInt();
            }
            
            v = (*iter)["sell_income"];
            if (!v.empty())
            {
                config->sell_income = v.asUInt();
            }
            
            v = (*iter)["can_sell"];
            if (!v.empty())
            {
                config->can_sell = v.asUInt();
            }
            
            v = (*iter)["can_auction"];
            if (!v.empty())
            {
                config->can_auction = v.asUInt();
            }
            
            v = (*iter)["can_trade"];
            if (!v.empty())
            {
                config->can_trade = v.asUInt();
            }
            
            v = (*iter)["can_store"];
            if (!v.empty())
            {
                config->can_store = v.asUInt();
            }
            
            v = (*iter)["can_pile"];
            if (!v.empty())
            {
                config->can_pile = v.asUInt();
            }
            
            v = (*iter)["can_destroy"];
            if (!v.empty())
            {
                config->can_destroy = v.asUInt();
            }
            
            v = (*iter)["destroy_time"];
            if (!v.empty())
            {
                config->destroy_time = v.asUInt();
            }
            
            v = (*iter)["sort"];
            if (!v.empty())
            {
                config->sort = v.asUInt();
            }
            
            m_map_item_config.insert(make_pair(config->base_id, config));
        }

//        auto doc = GameReader::getDocInstance(QUEST_ITEM_CONFIG_FILE_PATH);
//        if (doc->IsArray()){
//            int size = doc->Size();
//            Item_Config* config = NULL;
//            
//            for (int i = 0; i < size; i++) {
//                const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*doc), i);
//                config = new Item_Config;
//                config->base_id = DICTOOL->getIntValue_json(dic, "base_id");
//                config->type = DICTOOL->getIntValue_json(dic, "type");
//                config->name = DICTOOL->getStringValue_json(dic, "name");
//                config->icon = DICTOOL->getStringValue_json(dic, "icon");
//                config->quality = DICTOOL->getIntValue_json(dic, "quality");
//                config->desc = DICTOOL->getStringValue_json(dic, "desc");
//                config->drop_desc = DICTOOL->getStringValue_json(dic, "drop_desc");
//                config->bind = DICTOOL->getIntValue_json(dic, "bind");
//                config->pile_count = DICTOOL->getIntValue_json(dic, "pile_count");
//                config->gold_cost = DICTOOL->getIntValue_json(dic, "gold_cost");
//                config->token_cost = DICTOOL->getIntValue_json(dic, "token_cost");
//                config->sell_income = DICTOOL->getIntValue_json(dic, "sell_income");
//                config->can_sell = DICTOOL->getIntValue_json(dic, "can_sell");
//                config->can_auction = DICTOOL->getIntValue_json(dic, "can_auction");
//                config->can_trade = DICTOOL->getIntValue_json(dic, "can_trade");
//                config->can_store = DICTOOL->getIntValue_json(dic, "can_store");
//                config->can_pile = DICTOOL->getIntValue_json(dic, "can_pile");
//                config->can_destroy = DICTOOL->getIntValue_json(dic, "can_destroy");
//                config->destroy_time = DICTOOL->getIntValue_json(dic, "destroy_time");
//                config->sort = DICTOOL->getIntValue_json(dic, "sort");
//                
//                m_map_item_config.insert(make_pair(config->base_id, config));
//            }
//        }
        
        return 0;
    }

    int Item_Config_Mgr::load_material_item_config_data()
    {
        Json::Value root_value;
        Container_Mgr::instance()->get_json_value_by_file_name(root_value, MATERIAL_ITEM_CONFIG_FILE_PATH);
        
        Item_Config* config = NULL;
        // char key[255] = {0};
        for (Json::Value::iterator iter = root_value.begin();  iter != root_value.end();  ++iter)
        {
            config = new Item_Config;
            memset(config, 0, sizeof(Item_Config));
            
            Json::Value &v = (*iter)["base_id"];
            if (!v.empty())
            {
                config->base_id =  v.asUInt();
            }
            
            v = (*iter)["type"];
            if (!v.empty())
            {
                config->type = v.asUInt();
            }
            
            v = (*iter)["name"];
            if (!v.empty())
            {
                config->name = v.asUInt();
            }
            
            v = (*iter)["icon"];
            if (!v.empty())
            {
                config->icon = v.asUInt();
            }
            
            v = (*iter)["quality"];
            if (!v.empty())
            {
                config->quality = v.asUInt();
            }
            
            v = (*iter)["desc"];
            if (!v.empty())
            {
                config->desc = v.asUInt();
            }
            
            v = (*iter)["drop_desc"];
            if (!v.empty())
            {
                config->drop_desc = v.asUInt();
            }
            
            v = (*iter)["bind"];
            if (!v.empty())
            {
                config->bind = v.asUInt();
            }
            
            v = (*iter)["pile_count"];
            if (!v.empty())
            {
                config->pile_count = v.asUInt();
            }
            
            v = (*iter)["gold_cost"];
            if (!v.empty())
            {
                config->gold_cost = v.asUInt();
            }
            
            v = (*iter)["token_cost"];
            if (!v.empty())
            {
                config->token_cost = v.asUInt();
            }
            
            v = (*iter)["sell_income"];
            if (!v.empty())
            {
                config->sell_income = v.asUInt();
            }
            
            v = (*iter)["can_sell"];
            if (!v.empty())
            {
                config->can_sell = v.asUInt();
            }
            
            v = (*iter)["can_auction"];
            if (!v.empty())
            {
                config->can_auction = v.asUInt();
            }
            
            v = (*iter)["can_trade"];
            if (!v.empty())
            {
                config->can_trade = v.asUInt();
            }
            
            v = (*iter)["can_store"];
            if (!v.empty())
            {
                config->can_store = v.asUInt();
            }
            
            v = (*iter)["can_pile"];
            if (!v.empty())
            {
                config->can_pile = v.asUInt();
            }
            
            v = (*iter)["can_destroy"];
            if (!v.empty())
            {
                config->can_destroy = v.asUInt();
            }
            
            v = (*iter)["destroy_time"];
            if (!v.empty())
            {
                config->destroy_time = v.asUInt();
            }
            
            v = (*iter)["sort"];
            if (!v.empty())
            {
                config->sort = v.asUInt();
            }
            
            m_map_item_config.insert(make_pair(config->base_id, config));
        }

//        auto doc = GameReader::getDocInstance(MATERIAL_ITEM_CONFIG_FILE_PATH);
//        if (doc->IsArray()){
//            int size = doc->Size();
//            Item_Config* config = NULL;
//            
//            for (int i = 0; i < size; i++) {
//                const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*doc), i);
//                config = new Item_Config;
//                config->base_id = DICTOOL->getIntValue_json(dic, "base_id");
//                config->type = DICTOOL->getIntValue_json(dic, "type");
//                config->name = DICTOOL->getStringValue_json(dic, "name");
//                config->icon = DICTOOL->getStringValue_json(dic, "icon");
//                config->quality = DICTOOL->getIntValue_json(dic, "quality");
//                config->desc = DICTOOL->getStringValue_json(dic, "desc");
//                config->drop_desc = DICTOOL->getStringValue_json(dic, "drop_desc");
//                config->bind = DICTOOL->getIntValue_json(dic, "bind");
//                config->pile_count = DICTOOL->getIntValue_json(dic, "pile_count");
//                config->gold_cost = DICTOOL->getIntValue_json(dic, "gold_cost");
//                config->token_cost = DICTOOL->getIntValue_json(dic, "token_cost");
//                config->sell_income = DICTOOL->getIntValue_json(dic, "sell_income");
//                config->can_sell = DICTOOL->getIntValue_json(dic, "can_sell");
//                config->can_auction = DICTOOL->getIntValue_json(dic, "can_auction");
//                config->can_trade = DICTOOL->getIntValue_json(dic, "can_trade");
//                config->can_store = DICTOOL->getIntValue_json(dic, "can_store");
//                config->can_pile = DICTOOL->getIntValue_json(dic, "can_pile");
//                config->can_destroy = DICTOOL->getIntValue_json(dic, "can_destroy");
//                config->destroy_time = DICTOOL->getIntValue_json(dic, "destroy_time");
//                config->sort = DICTOOL->getIntValue_json(dic, "sort");
//                
//                m_map_item_config.insert(make_pair(config->base_id, config));
//            }
//        }

        return 0;
    }

    int Item_Config_Mgr::load_material_fragment_config_data()
    {
        Json::Value root_value;
        Container_Mgr::instance()->get_json_value_by_file_name(root_value, MATERIAL_FRAGMENT_CONFIG_FILE_PATH);
        
        Item_Fragment_Config* config = NULL;
        //char key[255] = {0};
        for (Json::Value::iterator iter = root_value.begin();  iter != root_value.end();  ++iter)
        {
            config = new Item_Fragment_Config;
            memset(config, 0, sizeof(Item_Fragment_Config));
            
            Json::Value &v = (*iter)["base_id"];
            if (!v.empty())
            {
                config->base_id =  v.asUInt();
            }
            
            v = (*iter)["type"];
            if (!v.empty())
            {
                config->type = v.asUInt();
            }
            
            v = (*iter)["name"];
            if (!v.empty())
            {
                config->name = v.asUInt();
            }
            
            v = (*iter)["icon"];
            if (!v.empty())
            {
                config->icon = v.asUInt();
            }
            
            v = (*iter)["quality"];
            if (!v.empty())
            {
                config->quality = v.asUInt();
            }
            
            v = (*iter)["desc"];
            if (!v.empty())
            {
                config->desc = v.asUInt();
            }
            
            v = (*iter)["drop_desc"];
            if (!v.empty())
            {
                config->drop_desc = v.asUInt();
            }
            
            v = (*iter)["bind"];
            if (!v.empty())
            {
                config->bind = v.asUInt();
            }
            
            v = (*iter)["pile_count"];
            if (!v.empty())
            {
                config->pile_count = v.asUInt();
            }
            
            v = (*iter)["gold_cost"];
            if (!v.empty())
            {
                config->gold_cost = v.asUInt();
            }
            
            v = (*iter)["token_cost"];
            if (!v.empty())
            {
                config->token_cost = v.asUInt();
            }
            
            v = (*iter)["sell_income"];
            if (!v.empty())
            {
                config->sell_income = v.asUInt();
            }
            
            v = (*iter)["can_sell"];
            if (!v.empty())
            {
                config->can_sell = v.asUInt();
            }
            
            v = (*iter)["can_auction"];
            if (!v.empty())
            {
                config->can_auction = v.asUInt();
            }
            
            v = (*iter)["can_trade"];
            if (!v.empty())
            {
                config->can_trade = v.asUInt();
            }
            
            v = (*iter)["can_store"];
            if (!v.empty())
            {
                config->can_store = v.asUInt();
            }
            
            v = (*iter)["can_pile"];
            if (!v.empty())
            {
                config->can_pile = v.asUInt();
            }
            
            v = (*iter)["can_destroy"];
            if (!v.empty())
            {
                config->can_destroy = v.asUInt();
            }
            
            v = (*iter)["destroy_time"];
            if (!v.empty())
            {
                config->destroy_time = v.asUInt();
            }
            
            v = (*iter)["sort"];
            if (!v.empty())
            {
                config->sort = v.asUInt();
            }
            
            v = (*iter)["need_count"];
            if (!v.empty())
            {
                config->need_count = v.asUInt();
            }
            
            v = (*iter)["compound_id"];
            if (!v.empty())
            {
                config->compound_id = v.asUInt();
            }
            
            m_map_item_fragment_config.insert(make_pair(config->base_id, config));
            m_map_item_config.insert(make_pair(config->base_id, config));
        }

//        auto doc = GameReader::getDocInstance(MATERIAL_FRAGMENT_CONFIG_FILE_PATH);
//        if (doc->IsArray()){
//            int size = doc->Size();
//            Item_Fragment_Config* config = NULL;
//            
//            for (int i = 0; i < size; i++) {
//                const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*doc), i);
//                config = new Item_Fragment_Config;
//                config->base_id = DICTOOL->getIntValue_json(dic, "base_id");
//                config->type = DICTOOL->getIntValue_json(dic, "type");
//                config->name = DICTOOL->getStringValue_json(dic, "name");
//                config->icon = DICTOOL->getStringValue_json(dic, "icon");
//                config->quality = DICTOOL->getIntValue_json(dic, "quality");
//                config->desc = DICTOOL->getStringValue_json(dic, "desc");
//                config->drop_desc = DICTOOL->getStringValue_json(dic, "drop_desc");
//                config->bind = DICTOOL->getIntValue_json(dic, "bind");
//                config->pile_count = DICTOOL->getIntValue_json(dic, "pile_count");
//                config->gold_cost = DICTOOL->getIntValue_json(dic, "gold_cost");
//                config->token_cost = DICTOOL->getIntValue_json(dic, "token_cost");
//                config->sell_income = DICTOOL->getIntValue_json(dic, "sell_income");
//                config->can_sell = DICTOOL->getIntValue_json(dic, "can_sell");
//                config->can_auction = DICTOOL->getIntValue_json(dic, "can_auction");
//                config->can_trade = DICTOOL->getIntValue_json(dic, "can_trade");
//                config->can_store = DICTOOL->getIntValue_json(dic, "can_store");
//                config->can_pile = DICTOOL->getIntValue_json(dic, "can_pile");
//                config->can_destroy = DICTOOL->getIntValue_json(dic, "can_destroy");
//                config->destroy_time = DICTOOL->getIntValue_json(dic, "destroy_time");
//                config->sort = DICTOOL->getIntValue_json(dic, "sort");
//                config->need_count = DICTOOL->getIntValue_json(dic, "need_count");
//                config->compound_id = DICTOOL->getIntValue_json(dic, "compound_id");
//                
//                m_map_item_fragment_config.insert(make_pair(config->base_id, config));
//                m_map_item_config.insert(make_pair(config->base_id, config));
//            }
//        }

        return 0;
    }

    int Item_Config_Mgr::load_book_fragment_config_data()
    {
        Json::Value root_value;
        Container_Mgr::instance()->get_json_value_by_file_name(root_value, BOOK_FRAGMENT_CONFIG_FILE_PATH);
        
        Item_Fragment_Config* config = NULL;
        //char key[255] = {0};
        for (Json::Value::iterator iter = root_value.begin();  iter != root_value.end();  ++iter)
        {
            config = new Item_Fragment_Config;
            memset(config, 0, sizeof(Item_Fragment_Config));
            
            Json::Value &v = (*iter)["base_id"];
            if (!v.empty())
            {
                config->base_id =  v.asUInt();
            }
            
            v = (*iter)["type"];
            if (!v.empty())
            {
                config->type = v.asUInt();
            }
            
            v = (*iter)["name"];
            if (!v.empty())
            {
                config->name = v.asUInt();
            }
            
            v = (*iter)["icon"];
            if (!v.empty())
            {
                config->icon = v.asUInt();
            }
            
            v = (*iter)["quality"];
            if (!v.empty())
            {
                config->quality = v.asUInt();
            }
            
            v = (*iter)["desc"];
            if (!v.empty())
            {
                config->desc = v.asUInt();
            }
            
            v = (*iter)["drop_desc"];
            if (!v.empty())
            {
                config->drop_desc = v.asUInt();
            }
            
            v = (*iter)["bind"];
            if (!v.empty())
            {
                config->bind = v.asUInt();
            }
            
            v = (*iter)["pile_count"];
            if (!v.empty())
            {
                config->pile_count = v.asUInt();
            }
            
            v = (*iter)["gold_cost"];
            if (!v.empty())
            {
                config->gold_cost = v.asUInt();
            }
            
            v = (*iter)["token_cost"];
            if (!v.empty())
            {
                config->token_cost = v.asUInt();
            }
            
            v = (*iter)["sell_income"];
            if (!v.empty())
            {
                config->sell_income = v.asUInt();
            }
            
            v = (*iter)["can_sell"];
            if (!v.empty())
            {
                config->can_sell = v.asUInt();
            }
            
            v = (*iter)["can_auction"];
            if (!v.empty())
            {
                config->can_auction = v.asUInt();
            }
            
            v = (*iter)["can_trade"];
            if (!v.empty())
            {
                config->can_trade = v.asUInt();
            }
            
            v = (*iter)["can_store"];
            if (!v.empty())
            {
                config->can_store = v.asUInt();
            }
            
            v = (*iter)["can_pile"];
            if (!v.empty())
            {
                config->can_pile = v.asUInt();
            }
            
            v = (*iter)["can_destroy"];
            if (!v.empty())
            {
                config->can_destroy = v.asUInt();
            }
            
            v = (*iter)["destroy_time"];
            if (!v.empty())
            {
                config->destroy_time = v.asUInt();
            }
            
            v = (*iter)["sort"];
            if (!v.empty())
            {
                config->sort = v.asUInt();
            }
            
            v = (*iter)["need_count"];
            if (!v.empty())
            {
                config->need_count = v.asUInt();
            }
            
            v = (*iter)["compound_id"];
            if (!v.empty())
            {
                config->compound_id = v.asUInt();
            }
            
            m_map_item_fragment_config.insert(make_pair(config->base_id, config));
            m_map_item_config.insert(make_pair(config->base_id, config));
        }
        
//        auto doc = GameReader::getDocInstance(BOOK_FRAGMENT_CONFIG_FILE_PATH);
//        if (doc->IsArray()){
//            int size = doc->Size();
//            Item_Fragment_Config* config = NULL;
//            
//            for (int i = 0; i < size; i++) {
//                const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*doc), i);
//                config = new Item_Fragment_Config;
//                config->base_id = DICTOOL->getIntValue_json(dic, "base_id");
//                config->type = DICTOOL->getIntValue_json(dic, "type");
//                config->name = DICTOOL->getStringValue_json(dic, "name");
//                config->icon = DICTOOL->getStringValue_json(dic, "icon");
//                config->quality = DICTOOL->getIntValue_json(dic, "quality");
//                config->desc = DICTOOL->getStringValue_json(dic, "desc");
//                config->drop_desc = DICTOOL->getStringValue_json(dic, "drop_desc");
//                config->bind = DICTOOL->getIntValue_json(dic, "bind");
//                config->pile_count = DICTOOL->getIntValue_json(dic, "pile_count");
//                config->gold_cost = DICTOOL->getIntValue_json(dic, "gold_cost");
//                config->token_cost = DICTOOL->getIntValue_json(dic, "token_cost");
//                config->sell_income = DICTOOL->getIntValue_json(dic, "sell_income");
//                config->can_sell = DICTOOL->getIntValue_json(dic, "can_sell");
//                config->can_auction = DICTOOL->getIntValue_json(dic, "can_auction");
//                config->can_trade = DICTOOL->getIntValue_json(dic, "can_trade");
//                config->can_store = DICTOOL->getIntValue_json(dic, "can_store");
//                config->can_pile = DICTOOL->getIntValue_json(dic, "can_pile");
//                config->can_destroy = DICTOOL->getIntValue_json(dic, "can_destroy");
//                config->destroy_time = DICTOOL->getIntValue_json(dic, "destroy_time");
//                config->sort = DICTOOL->getIntValue_json(dic, "sort");
//                config->need_count = DICTOOL->getIntValue_json(dic, "need_count");
//                config->compound_id = DICTOOL->getIntValue_json(dic, "compound_id");
//                
//                m_map_item_fragment_config.insert(make_pair(config->base_id, config));
//                m_map_item_config.insert(make_pair(config->base_id, config));
//            }
//        }

        return 0;
    }

    int Item_Config_Mgr::load_gift_item_config_data()
    {
        Json::Value root_value;
        Container_Mgr::instance()->get_json_value_by_file_name(root_value, GIFT_ITEM_CONFIG_FILE_PATH);
        
        Usable_Item_Config* config = NULL;
        //char key[255] = {0};
        for (Json::Value::iterator iter = root_value.begin();  iter != root_value.end();  ++iter)
        {
            config = new Usable_Item_Config;
            memset(config, 0, sizeof(Usable_Item_Config));
            
            Json::Value &v = (*iter)["base_id"];
            if (!v.empty())
            {
                config->base_id =  v.asUInt();
            }
            
            v = (*iter)["type"];
            if (!v.empty())
            {
                config->type = v.asUInt();
            }
            
            v = (*iter)["name"];
            if (!v.empty())
            {
                config->name = v.asUInt();
            }
            
            v = (*iter)["icon"];
            if (!v.empty())
            {
                config->icon = v.asUInt();
            }
            
            v = (*iter)["quality"];
            if (!v.empty())
            {
                config->quality = v.asUInt();
            }
            
            v = (*iter)["desc"];
            if (!v.empty())
            {
                config->desc = v.asUInt();
            }
            
            v = (*iter)["drop_desc"];
            if (!v.empty())
            {
                config->drop_desc = v.asUInt();
            }
            
            v = (*iter)["bind"];
            if (!v.empty())
            {
                config->bind = v.asUInt();
            }
            
            v = (*iter)["pile_count"];
            if (!v.empty())
            {
                config->pile_count = v.asUInt();
            }
            
            v = (*iter)["gold_cost"];
            if (!v.empty())
            {
                config->gold_cost = v.asUInt();
            }
            
            v = (*iter)["token_cost"];
            if (!v.empty())
            {
                config->token_cost = v.asUInt();
            }
            
            v = (*iter)["sell_income"];
            if (!v.empty())
            {
                config->sell_income = v.asUInt();
            }
            
            v = (*iter)["can_sell"];
            if (!v.empty())
            {
                config->can_sell = v.asUInt();
            }
            
            v = (*iter)["can_auction"];
            if (!v.empty())
            {
                config->can_auction = v.asUInt();
            }
            
            v = (*iter)["can_trade"];
            if (!v.empty())
            {
                config->can_trade = v.asUInt();
            }
            
            v = (*iter)["can_store"];
            if (!v.empty())
            {
                config->can_store = v.asUInt();
            }
            
            v = (*iter)["can_pile"];
            if (!v.empty())
            {
                config->can_pile = v.asUInt();
            }
            
            v = (*iter)["can_destroy"];
            if (!v.empty())
            {
                config->can_destroy = v.asUInt();
            }
            
            v = (*iter)["destroy_time"];
            if (!v.empty())
            {
                config->destroy_time = v.asUInt();
            }
            
            v = (*iter)["sort"];
            if (!v.empty())
            {
                config->sort = v.asUInt();
            }
            
            v = (*iter)["event_id"];
            if (!v.empty())
            {
                config->event_id = v.asUInt();
            }
            
            m_map_usable_item_config.insert(make_pair(config->base_id, config));
            m_map_item_config.insert(make_pair(config->base_id, config));
        }

//        auto doc = GameReader::getDocInstance(GIFT_ITEM_CONFIG_FILE_PATH);
//        if (doc->IsArray()){
//            int size = doc->Size();
//            Usable_Item_Config* config = NULL;
//            
//            for (int i = 0; i < size; i++) {
//                const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*doc), i);
//                config = new Usable_Item_Config;
//                config->base_id = DICTOOL->getIntValue_json(dic, "base_id");
//                config->type = DICTOOL->getIntValue_json(dic, "type");
//                config->name = DICTOOL->getStringValue_json(dic, "name");
//                config->icon = DICTOOL->getStringValue_json(dic, "icon");
//                config->quality = DICTOOL->getIntValue_json(dic, "quality");
//                config->desc = DICTOOL->getStringValue_json(dic, "desc");
//                config->drop_desc = DICTOOL->getStringValue_json(dic, "drop_desc");
//                config->bind = DICTOOL->getIntValue_json(dic, "bind");
//                config->pile_count = DICTOOL->getIntValue_json(dic, "pile_count");
//                config->gold_cost = DICTOOL->getIntValue_json(dic, "gold_cost");
//                config->token_cost = DICTOOL->getIntValue_json(dic, "token_cost");
//                config->sell_income = DICTOOL->getIntValue_json(dic, "sell_income");
//                config->can_sell = DICTOOL->getIntValue_json(dic, "can_sell");
//                config->can_auction = DICTOOL->getIntValue_json(dic, "can_auction");
//                config->can_trade = DICTOOL->getIntValue_json(dic, "can_trade");
//                config->can_store = DICTOOL->getIntValue_json(dic, "can_store");
//                config->can_pile = DICTOOL->getIntValue_json(dic, "can_pile");
//                config->can_destroy = DICTOOL->getIntValue_json(dic, "can_destroy");
//                config->destroy_time = DICTOOL->getIntValue_json(dic, "destroy_time");
//                config->sort = DICTOOL->getIntValue_json(dic, "sort");
//                config->event_id = DICTOOL->getIntValue_json(dic, "event_id");
//
//                
//                m_map_usable_item_config.insert(make_pair(config->base_id, config));
//                m_map_item_config.insert(make_pair(config->base_id, config));
//            }
//        }
        
        return 0;
    }

    int Item_Config_Mgr::load_book_config_data()
    {
        Json::Value root_value;
        Container_Mgr::instance()->get_json_value_by_file_name(root_value, BOOK_CONFIG_FILE_PATH);
        
        Book_Config* config = NULL;
        char key[255] = {0};
        for (Json::Value::iterator iter = root_value.begin();  iter != root_value.end();  ++iter)
        {
            config = new Book_Config;
            memset(config, 0, sizeof(Book_Config));
            
            Json::Value &v = (*iter)["base_id"];
            if (!v.empty())
            {
                config->base_id =  v.asUInt();
            }
            
            v = (*iter)["type"];
            if (!v.empty())
            {
                config->type = v.asUInt();
            }
            
            v = (*iter)["name"];
            if (!v.empty())
            {
                config->name = v.asUInt();
            }
            
            v = (*iter)["icon"];
            if (!v.empty())
            {
                config->icon = v.asUInt();
            }
            
            v = (*iter)["quality"];
            if (!v.empty())
            {
                config->quality = v.asUInt();
            }
            
            v = (*iter)["desc"];
            if (!v.empty())
            {
                config->desc = v.asUInt();
            }
            
            v = (*iter)["drop_desc"];
            if (!v.empty())
            {
                config->drop_desc = v.asUInt();
            }
            
            v = (*iter)["bind"];
            if (!v.empty())
            {
                config->bind = v.asUInt();
            }
            
            v = (*iter)["pile_count"];
            if (!v.empty())
            {
                config->pile_count = v.asUInt();
            }
            
            v = (*iter)["gold_cost"];
            if (!v.empty())
            {
                config->gold_cost = v.asUInt();
            }
            
            v = (*iter)["token_cost"];
            if (!v.empty())
            {
                config->token_cost = v.asUInt();
            }
            
            v = (*iter)["sell_income"];
            if (!v.empty())
            {
                config->sell_income = v.asUInt();
            }
            
            v = (*iter)["can_sell"];
            if (!v.empty())
            {
                config->can_sell = v.asUInt();
            }
            
            v = (*iter)["can_auction"];
            if (!v.empty())
            {
                config->can_auction = v.asUInt();
            }
            
            v = (*iter)["can_trade"];
            if (!v.empty())
            {
                config->can_trade = v.asUInt();
            }
            
            v = (*iter)["can_store"];
            if (!v.empty())
            {
                config->can_store = v.asUInt();
            }
            
            v = (*iter)["can_pile"];
            if (!v.empty())
            {
                config->can_pile = v.asUInt();
            }
            
            v = (*iter)["can_destroy"];
            if (!v.empty())
            {
                config->can_destroy = v.asUInt();
            }
            
            v = (*iter)["destroy_time"];
            if (!v.empty())
            {
                config->destroy_time = v.asUInt();
            }
            
            v = (*iter)["sort"];
            if (!v.empty())
            {
                config->sort = v.asUInt();
            }
            
            v = (*iter)["exp"];
            if (!v.empty())
            {
                config->exp = v.asUInt();
            }
            
            v = (*iter)["need_power"];
            if (!v.empty())
            {
                config->need_power = v.asUInt();
            }
            
            for (int i = 0;i < QT_MAX;++i)
            {
                memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS
                sprintf_s(key,"upgrade_base_exp_%d",i);
#else
                sprintf(key,"upgrade_base_exp_%d",i);
#endif
                
                v = (*iter)[key];
                if (!v.empty())
                {
                    config->upgrade_base_exp[i] = v.asUInt();
                }
                
                for (int j = 0;j < MAX_ATTR_COUNT;++j)
                {
                    memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS
                    sprintf_s(key,"base_attr_%d_%d",i,j);
#else
                    sprintf(key,"base_attr_%d_%d",i,j);
#endif
                    
                    v = (*iter)[key];
                    if (!v.empty())
                    {
                        config->base_attr[i][j] = v.asUInt();
                    }
                }
            }
            
            m_map_book_config.insert(make_pair(config->base_id, config));
            m_map_item_config.insert(make_pair(config->base_id, config));
        }

//        auto doc = GameReader::getDocInstance(BOOK_CONFIG_FILE_PATH);
//        if (doc->IsArray()){
//            int size = doc->Size();
//            Book_Config* config = NULL;
//            
//            for (int i = 0; i < size; i++) {
//                const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*doc), i);
//                config = new Book_Config;
//                config->base_id = DICTOOL->getIntValue_json(dic, "base_id");
//                config->type = DICTOOL->getIntValue_json(dic, "type");
//                config->name = DICTOOL->getStringValue_json(dic, "name");
//                config->icon = DICTOOL->getStringValue_json(dic, "icon");
//                config->quality = DICTOOL->getIntValue_json(dic, "quality");
//                config->desc = DICTOOL->getStringValue_json(dic, "desc");
//                config->drop_desc = DICTOOL->getStringValue_json(dic, "drop_desc");
//                config->bind = DICTOOL->getIntValue_json(dic, "bind");
//                config->pile_count = DICTOOL->getIntValue_json(dic, "pile_count");
//                config->gold_cost = DICTOOL->getIntValue_json(dic, "gold_cost");
//                config->token_cost = DICTOOL->getIntValue_json(dic, "token_cost");
//                config->sell_income = DICTOOL->getIntValue_json(dic, "sell_income");
//                config->can_sell = DICTOOL->getIntValue_json(dic, "can_sell");
//                config->can_auction = DICTOOL->getIntValue_json(dic, "can_auction");
//                config->can_trade = DICTOOL->getIntValue_json(dic, "can_trade");
//                config->can_store = DICTOOL->getIntValue_json(dic, "can_store");
//                config->can_pile = DICTOOL->getIntValue_json(dic, "can_pile");
//                config->can_destroy = DICTOOL->getIntValue_json(dic, "can_destroy");
//                config->destroy_time = DICTOOL->getIntValue_json(dic, "destroy_time");
//                config->sort = DICTOOL->getIntValue_json(dic, "sort");
//                config->exp = DICTOOL->getIntValue_json(dic, "exp");
//                config->need_power = DICTOOL->getIntValue_json(dic, "need_power");
//                for (int i = 0;i < QT_MAX;++i)
//                {
//                    cocos2d::Value num(i);
//                    std::string baseAttrName("upgrade_base_exp_");
//                    config->upgrade_base_exp[i] = DICTOOL->getIntValue_json(dic, (baseAttrName+num.asString()).c_str());
//                    
//                    for (int j = 0; j < MAX_ATTR_COUNT; j++) {
//                        cocos2d::Value idx(j);
//                        config->base_attr[i][j] = DICTOOL->getIntValue_json(dic, (baseAttrName+num.asString()+"_"+idx.asString()).c_str());
//                    }
//                }
//
//                
//                m_map_book_config.insert(make_pair(config->base_id, config));
//                m_map_item_config.insert(make_pair(config->base_id, config));
//            }
//        }

        return 0;
    }

    int Item_Config_Mgr::load_book_attr_config_data(void)
    {
        Json::Value root_value;
        Container_Mgr::instance()->get_json_value_by_file_name(root_value, BOOK_ATTR_CONFIG_FILE_PATH);

        Book_Config* config = NULL;
        int base_id = 0;
        char key[255] = {0};
        for (Json::Value::iterator iter = root_value.begin();  iter != root_value.end();  ++iter)
        {

            Json::Value &v = (*iter)["base_id"];
            if (!v.empty())
            {
                base_id = v.asUInt();
            }

            config = get_book_config(base_id);
            if (!config)
            {
                continue;
            }

            for (int i = 0;i < QT_MAX;++i)
            {     
                memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS
                sprintf_s(key,"max_level_%d",i);
#else
                sprintf(key,"max_level_%d",i);
#endif

                v = (*iter)[key];
                if (!v.empty())
                {
                    config->max_level[i] = v.asUInt();
                }

                memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS
                sprintf_s(key,"upgrade_exp_grow_%d",i);
#else
                sprintf(key,"upgrade_exp_grow_%d",i);
#endif

                v = (*iter)[key];
                if (!v.empty())
                {
                    config->upgrade_exp_grow[i] = v.asUInt();
                }

                for (int j = 0;j < MAX_ATTR_COUNT;++j)
                {
                    memset(key, 0, sizeof(key));
#ifdef YN_WINDOWS
                    sprintf_s(key,"attr_grow_%d_%d",i,j);
#else
                    sprintf(key,"attr_grow_%d_%d",i,j);
#endif

                    v = (*iter)[key];
                    if (!v.empty())
                    {
                        config->attr_grow[i][j] = v.asUInt();
                    }
                }
            }
        }

        return 0;
    }

    int Item_Config_Mgr::load_gem_config_data()
    {
        Json::Value root_value;
        Container_Mgr::instance()->get_json_value_by_file_name(root_value, GEM_CONFIG_FILE_PATH);
        
        Gem_Config* config = NULL;
        char key[255] = {0};
        for (Json::Value::iterator iter = root_value.begin();  iter != root_value.end();  ++iter)
        {
            config = new Gem_Config;
            memset(config, 0, sizeof(Gem_Config));
            
            Json::Value &v = (*iter)["base_id"];
            if (!v.empty())
            {
                config->base_id =  v.asUInt();
            }
            
            v = (*iter)["type"];
            if (!v.empty())
            {
                config->type = v.asUInt();
            }
            
            v = (*iter)["name"];
            if (!v.empty())
            {
                config->name = v.asUInt();
            }
            
            v = (*iter)["icon"];
            if (!v.empty())
            {
                config->icon = v.asUInt();
            }
            
            v = (*iter)["quality"];
            if (!v.empty())
            {
                config->quality = v.asUInt();
            }
            
            v = (*iter)["desc"];
            if (!v.empty())
            {
                config->desc = v.asUInt();
            }
            
            v = (*iter)["drop_desc"];
            if (!v.empty())
            {
                config->drop_desc = v.asUInt();
            }
            
            v = (*iter)["bind"];
            if (!v.empty())
            {
                config->bind = v.asUInt();
            }
            
            v = (*iter)["pile_count"];
            if (!v.empty())
            {
                config->pile_count = v.asUInt();
            }
            
            v = (*iter)["gold_cost"];
            if (!v.empty())
            {
                config->gold_cost = v.asUInt();
            }
            
            v = (*iter)["token_cost"];
            if (!v.empty())
            {
                config->token_cost = v.asUInt();
            }
            
            v = (*iter)["sell_income"];
            if (!v.empty())
            {
                config->sell_income = v.asUInt();
            }
            
            v = (*iter)["can_sell"];
            if (!v.empty())
            {
                config->can_sell = v.asUInt();
            }
            
            v = (*iter)["can_auction"];
            if (!v.empty())
            {
                config->can_auction = v.asUInt();
            }
            
            v = (*iter)["can_trade"];
            if (!v.empty())
            {
                config->can_trade = v.asUInt();
            }
            
            v = (*iter)["can_store"];
            if (!v.empty())
            {
                config->can_store = v.asUInt();
            }
            
            v = (*iter)["can_pile"];
            if (!v.empty())
            {
                config->can_pile = v.asUInt();
            }
            
            v = (*iter)["can_destroy"];
            if (!v.empty())
            {
                config->can_destroy = v.asUInt();
            }
            
            v = (*iter)["destroy_time"];
            if (!v.empty())
            {
                config->destroy_time = v.asUInt();
            }
            
            v = (*iter)["sort"];
            if (!v.empty())
            {
                config->sort = v.asUInt();
            }
            
            v = (*iter)["gem_type"];
            if (!v.empty())
            {
                config->gem_type = v.asUInt();
            }
            
            v = (*iter)["level"];
            if (!v.empty())
            {
                config->level = v.asUInt();
            }
            
            v = (*iter)["upgrade_cost"];
            if (!v.empty())
            {
                config->upgrade_cost = v.asUInt();
            }
            
            v = (*iter)["set_equipment_pos"];
            if (!v.empty())
            {
                config->set_equipment_pos = v.asUInt();
            }
            
            v = (*iter)["attr_type"];
            if (!v.empty())
            {
                config->attr_type = v.asUInt();
            }
            
            v = (*iter)["attr_value"];
            if (!v.empty())
            {
                config->attr_value = v.asUInt();
            }
            
            v = (*iter)["need_count"];
            if (!v.empty())
            {
                config->need_count = v.asUInt();
            }
            
            v = (*iter)["compound_id"];
            if (!v.empty())
            {
                config->compound_id = v.asUInt();
            }
            
            m_map_gem_config.insert(make_pair(config->base_id, config));
            m_map_item_config.insert(make_pair(config->base_id, config));
        }

//        auto doc = GameReader::getDocInstance(GEM_CONFIG_FILE_PATH);
//        if (doc->IsArray()){
//            int size = doc->Size();
//            Gem_Config* config = NULL;
//            
//            for (int i = 0; i < size; i++) {
//                const rapidjson::Value &dic = DICTOOL->getSubDictionary_json((*doc), i);
//                config = new Gem_Config;
//                config->base_id = DICTOOL->getIntValue_json(dic, "base_id");
//                config->type = DICTOOL->getIntValue_json(dic, "type");
//                config->name = DICTOOL->getStringValue_json(dic, "name");
//                config->icon = DICTOOL->getStringValue_json(dic, "icon");
//                config->quality = DICTOOL->getIntValue_json(dic, "quality");
//                config->desc = DICTOOL->getStringValue_json(dic, "desc");
//                config->drop_desc = DICTOOL->getStringValue_json(dic, "drop_desc");
//                config->bind = DICTOOL->getIntValue_json(dic, "bind");
//                config->pile_count = DICTOOL->getIntValue_json(dic, "pile_count");
//                config->gold_cost = DICTOOL->getIntValue_json(dic, "gold_cost");
//                config->token_cost = DICTOOL->getIntValue_json(dic, "token_cost");
//                config->sell_income = DICTOOL->getIntValue_json(dic, "sell_income");
//                config->can_sell = DICTOOL->getIntValue_json(dic, "can_sell");
//                config->can_auction = DICTOOL->getIntValue_json(dic, "can_auction");
//                config->can_trade = DICTOOL->getIntValue_json(dic, "can_trade");
//                config->can_store = DICTOOL->getIntValue_json(dic, "can_store");
//                config->can_pile = DICTOOL->getIntValue_json(dic, "can_pile");
//                config->can_destroy = DICTOOL->getIntValue_json(dic, "can_destroy");
//                config->destroy_time = DICTOOL->getIntValue_json(dic, "destroy_time");
//                config->sort = DICTOOL->getIntValue_json(dic, "sort");
//                config->gem_type = DICTOOL->getIntValue_json(dic, "gem_type");
//                config->level = DICTOOL->getIntValue_json(dic, "level");
//                config->upgrade_cost = DICTOOL->getIntValue_json(dic, "upgrade_cost");
//                config->set_equipment_pos = DICTOOL->getIntValue_json(dic, "set_equipment_pos");
//                config->attr_type = DICTOOL->getIntValue_json(dic, "attr_type");
//                config->attr_value = DICTOOL->getIntValue_json(dic, "attr_value");
//                config->need_count = DICTOOL->getIntValue_json(dic, "need_count");
//                config->compound_id = DICTOOL->getIntValue_json(dic, "compound_id");
//                
//                m_map_gem_config.insert(make_pair(config->base_id, config));
//                m_map_item_config.insert(make_pair(config->base_id, config));
//            }
//        }

        return 0;
    }

    int Item_Config_Mgr::load_icon_config_data(void)
    {
#ifdef GAME_CLIENT
        cocos2d::SpriteFrameCache* cache = cocos2d::SpriteFrameCache::sharedSpriteFrameCache();
        cache->addSpriteFramesWithFile(ICON_PATH);
		//cache->addSpriteFramesWithFile("icon.plist");
        //unsigned long size = 0;
		ssize_t size = 0;
        unsigned char* pData = 0;

        pData = cocos2d::FileUtils::getInstance()->getFileData
            (ICON_CONFIG_FILE_PATH, "rb", &size);

        //         cocos2d::CCFileData data(BOOK_ATTR_CONFIG_FILE_PATH, "rb");
        //         unsigned long nBufSize = data.getSize();
        //         char* pBuffer = (char*) data.getBuffer();	 

        Json::Reader j_reader;
        Json::Value root_value;
        if (!j_reader.parse((const char*) pData,(const char*) (pData+size), root_value))
        {	
            //cout << "parse failed!" << j_reader.getFormatedErrorMessages().c_str() << endl;
            //  exit(0);
            CC_SAFE_DELETE_ARRAY(pData);   
            return -1;
        }

        int base_id = 0;
        //char key[255] = {0};
        for (Json::Value::iterator iter = root_value.begin();iter != root_value.end();++iter)
        {

            Json::Value &v = (*iter)["base_id"];
            if (!v.empty())
            {
                base_id = v.asUInt();
            }

            v = (*iter)["path"];
            m_map_icon[base_id] = v.asString();
        }
		CCLOG("icon");
#endif
        return 0;
    }

    const char* Item_Config_Mgr::get_icon_path(int icon_id)
    {
        Icon_Map_Iter it = m_map_icon.find(icon_id);
        if(it!=m_map_icon.end())
        {
            return (*it).second.c_str();
        }
        return "";
    }

    const char* Item_Config_Mgr::get_lock_grid()
    {
        const char* desc = get_icon_path(5132);
        std::string p("icon/");
        p+=desc;
        return p.c_str();
//        return "icon/pic_kuang_suo.png";
    }

    const char* Item_Config_Mgr::get_gem_pos_not_open_icon()
    {
        const char* path = get_icon_path(6170);
        std::string p("icon/");
        p+=path;
        return p.c_str();
//        return "icon/pic_kongwei_weikaikong.png";
    }

    const char* Item_Config_Mgr::get_gold_icon()
    {
        const char* path = get_icon_path(5046);
        std::string p("icon/");
        p+=path;
        return p.c_str();
//        return "icon/pic_huobi_yinliang.png";
    }

    const char* Item_Config_Mgr::get_token_icon()
    {
        const char* path = get_icon_path(5047);
        std::string p("icon/");
        p+=path;
        return p.c_str();
//        return "icon/pic_huobi_yuanbao.png";
    }

    void Item_Config_Mgr::proc_string(const string& content_str,item_content &ic)
    {
        game_element_list_t game_element_vec;
        game_content_parse::instance()->game_element_parse_cell(content_str, game_element_vec);
        ic.set_element(game_element_vec);
    }

    int Item_Config_Mgr::load_quality_upgrade_config_data(void)
    {
        Json::Value root_value;
        Container_Mgr::instance()->get_json_value_by_file_name(root_value, QUALITY_UPGRADE_CONFIG_FILE_PATH);

        quality_upgrade_config* config = NULL;
        for (Json::Value::iterator iter = root_value.begin();iter != root_value.end();++iter)
        {
            config = new quality_upgrade_config;
            config->reset();

            Json::Value &v = (*iter)["module_type"];
            if (!v.empty())
            {
                config->set_module_type(v.asInt());
            }

            v = (*iter)["quality"];
            if (!v.empty())
            {
                config->set_quality(v.asInt());
            }

            v = (*iter)["token"];
            if (!v.empty())
            {
                config->set_token(v.asInt());
            }
           
            item_content ic;
            v = (*iter)["material_content"];
            if (!v.empty())
            {
                string cell_str = v.asString();
                proc_string(cell_str,ic);
            }
            config->set_material(ic);
           
            quality_upgrade_config_array_[config->get_module_type()][config->get_quality()] = config;
        }

        return 0;
    }

    quality_upgrade_config* Item_Config_Mgr::get_quality_upgrade_config(int module_type,int cur_quality)
    {
        module_type = module_type % QMT_MAX;
        cur_quality = cur_quality % (QT_MAX - 1);
        quality_upgrade_config* config = quality_upgrade_config_array_[module_type][cur_quality];

        return config;
    }

    void Item_Config_Mgr::get_quality_upgrade_need_material(int module_type,int cur_quality,game_element_list_t& material)
    {
        module_type = module_type % QMT_MAX;
        cur_quality = cur_quality % (QT_MAX - 1);
        quality_upgrade_config* config = quality_upgrade_config_array_[module_type][cur_quality];
        if (config)
        {
            Game_Data::item_content ele_cont;
            config->get_material(ele_cont);
            ele_cont.get_element(material);
        }
    }

    void Item_Config_Mgr::get_item_use_level(int base_id,int& level_down,int& level_up)
    {  
        Usable_Item_Config* config = get_usable_item_config(base_id);
        if (!config)
        {
            return;
        }

        Event_Data event_data;
        event_system_data_mgr::sharedInstance()->getEventDataById(config->event_id,event_data);
        if(event_data.getId()==0)
        {
            return;
        }

        Game_Data::game_element_list_t ele_list;
        event_data.getCondition(ele_list);
        Game_Data::game_element_list_t::iterator itg;
        for( itg = ele_list.begin(); itg != ele_list.end(); ++ itg)
        {
            Game_Data::Game_Element& element = (*itg);
            if(strcmp(element.get_command(),"level") == 0)
            {
                vector<uint> para;
                element.get_para_list_in_vector(para);
                if(para.size() > 1)
                {
                    level_down = para[0];
                    level_up = para[1];
                    break;
                }
            }
        }
    }

    int Item_Config_Mgr::get_gift_type(int base_id)
    {
        Usable_Item_Config* config = get_usable_item_config(base_id);
        if (!config)
        {
            return 0;
        }

        Event_Data event_data;
        event_system_data_mgr::sharedInstance()->getEventDataById(config->event_id,event_data);
        if(event_data.getId()==0)
        {
            return 0;
        }

        Game_Data::game_element_list_t ele_list;
        event_data.getFunction(ele_list);
        Game_Data::game_element_list_t::iterator itg;
        for( itg = ele_list.begin(); itg != ele_list.end(); ++ itg)
        {
            Game_Data::Game_Element& element = (*itg);
            if(strcmp(element.get_command(),"random_award_one_bag") == 0 || strcmp(element.get_command(),"random_award_one_book_bag") == 0)
            {
                return GT_RANDOM;
            }
            else if(strcmp(element.get_command(),"awarditem") == 0)
            {
                return GT_ALL;
            }
        }

        return 0;
    }
}

