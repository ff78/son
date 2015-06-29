
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

#include "Event_System/event_system_data_mgr.h"
#include "quest_system/quest_data/quest_json_config.h"
#include "Activity_Config_Mgr.h"
#include "Play_System/Container_Mgr.h"
#include "Network_Common/global_macros.h"

#ifdef GAME_CLIENT
#define ACTIVITY_CONFIG_FILE_PATH "game_data/activity_system/activity_config.json"
#define ACTIVITY_SIX_SECT_CONFIG_FILE_PATH "game_data/activity_system/activity_six_sect_config.json"
#else
#define ACTIVITY_CONFIG_FILE_PATH "../config/activity_system/activity_config.json"
#define ACTIVITY_SIX_SECT_CONFIG_FILE_PATH "../config/activity_system/activity_six_sect_config.json"
#endif

namespace Game_Data
{
    Activity_Config_Mgr* Activity_Config_Mgr::instance_ = NULL;
    Activity_Config_Mgr::Activity_Config_Mgr()
    {

    }

    Activity_Config_Mgr::~Activity_Config_Mgr()
    {

    }

    Activity_Config_Mgr* Activity_Config_Mgr::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Activity_Config_Mgr;
        }

        return instance_;
    }

    int Activity_Config_Mgr::initialize( void )
    {
        activity_config_map_.clear();
        activity_six_sect_config_map_.clear();
        activity_six_sect_am_config_map_.clear();
        activity_six_sect_pm_config_map_.clear();

        load_activity_config_data();
        load_activity_six_sect_config_data();

        return 0;
    }

    int Activity_Config_Mgr::release(void)
    {
        activity_config_map_iter iter = activity_config_map_.begin();
        for (;iter != activity_config_map_.end();++iter)
        {
            delete iter->second;
        }

        activity_six_sect_config_map_iter iter_six_sect = activity_six_sect_config_map_.begin();
        for (;iter_six_sect != activity_six_sect_config_map_.end();++iter)
        {
            delete iter_six_sect->second;
        }

        activity_config_map_.clear();
        activity_six_sect_config_map_.clear();
        activity_six_sect_am_config_map_.clear();
        activity_six_sect_pm_config_map_.clear();

        return 0;
    }

    activity_config* Activity_Config_Mgr::get_activity_config_by_type(int type)
    {
        activity_config* config = NULL;
        activity_config_map_iter it = activity_config_map_.find(type);
        if (it != activity_config_map_.end())
        {
            config = it->second;
        }

        return config;
    }

    activity_six_sect_config* Activity_Config_Mgr::get_activity_six_sect_config(int base_id)
    {
        activity_six_sect_config* config = NULL;
        activity_six_sect_config_map_iter it = activity_six_sect_config_map_.find(base_id);
        if (it != activity_six_sect_config_map_.end())
        {
            config = it->second;
        }

        return config;
    }

    activity_six_sect_config_map& Activity_Config_Mgr::get_activity_six_sect_config_map_by_type(int type)
    {
        if (type == 0)
        {
            return activity_six_sect_am_config_map_;
        }
        else
        {
            return activity_six_sect_pm_config_map_;
        }
    }

    int Activity_Config_Mgr::get_activity_six_sect_type()
    {
        activity_config* config = get_activity_config_by_type(AT_SIX_SECT);
        if (!config)
        {
            return -1;                                                                                  
        }

        cute::date_time cur_time;
        int hour = cur_time.hour();
        int minute = cur_time.minute();

        Game_Data::item_content ele_cont;
        config->get_open_time(ele_cont);

        game_element_list_t ele_list;
        ele_cont.get_element(ele_list);

        int type = 0;
        Game_Data::game_element_list_t::iterator itg = ele_list.begin();
        for(;itg != ele_list.end();++itg)
        {
            Game_Data::Game_Element& element = (*itg);
            if(strcmp(element.get_command(),"time") == 0)
            {
                vector<uint> para;
                element.get_para_list_in_vector(para);
                if (para.size() == 4)
                {
                    if ((hour > (int)para[0] || hour == (int)para[0] && minute >= (int)para[1]) &&
                        (hour < (int)para[2] || hour == (int)para[2] && minute < (int)para[3]))
                    {
                        return type;
                    }

                     ++type;
                }
            }
        }

        return -1;
    }

    void Activity_Config_Mgr::proc_string(const string& content_str,item_content &ic)
    {
        game_element_list_t game_element_vec;
        game_content_parse::instance()->game_element_parse_cell(content_str, game_element_vec);
        ic.set_element(game_element_vec);
    }

    int Activity_Config_Mgr::load_activity_config_data(void)
    {
        Json::Value root_value;
        Container_Mgr::instance()->get_json_value_by_file_name(root_value, ACTIVITY_CONFIG_FILE_PATH);

        activity_config* config = NULL;
        for (Json::Value::iterator iter = root_value.begin();iter != root_value.end();++iter)
        {
            config = new activity_config;
            config->reset();

            Json::Value &v = (*iter)["base_id"];
            if (!v.empty())
            {
                config->set_base_id(v.asInt());
            }

            v = (*iter)["type"];
            if (!v.empty())
            {
                config->set_type(v.asInt());
            }

            v = (*iter)["level_limit"];
            if (!v.empty())
            {
                config->set_level_limit(v.asInt());
            }
           
            item_content ic;
            v = (*iter)["week_open_day_content"];
            if (!v.empty())
            {
                string cell_str = v.asString();
                proc_string(cell_str,ic);
            }
            config->set_week_open_day(ic);

            ic.reset();
            v = (*iter)["open_time_content"];
            if (!v.empty())
            {
                string cell_str = v.asString();
                proc_string(cell_str,ic);
            }
            config->set_open_time(ic);

            v = (*iter)["name"];
            if (!v.empty())
            {
                config->set_name(v.asInt());
            }

            v = (*iter)["icon"];
            if (!v.empty())
            {
                config->set_icon(v.asInt());
            }

            v = (*iter)["week_open_day_desc"];
            if (!v.empty())
            {
                config->set_week_open_day_desc(v.asInt());
            }

            v = (*iter)["open_time_desc"];
            if (!v.empty())
            {
                config->set_open_time_desc(v.asInt());
            }

            v = (*iter)["activity_desc"];
            if (!v.empty())
            {
                config->set_activity_desc(v.asInt());
            }

            v = (*iter)["reward_desc"];
            if (!v.empty())
            {
                config->set_reward_desc(v.asInt());
            }
            
            v = (*iter)["check_effect_show"];
            if (!v.empty())
            {
                config->set_check_effect_show(v.asInt());
            }
           
            activity_config_map_.insert(make_pair(config->get_type(),config));
        }

        return 0;
    }

    int Activity_Config_Mgr::load_activity_six_sect_config_data(void)
    {
        Json::Value root_value;
        Container_Mgr::instance()->get_json_value_by_file_name(root_value, ACTIVITY_SIX_SECT_CONFIG_FILE_PATH);

        activity_six_sect_config* config = NULL;
        for (Json::Value::iterator iter = root_value.begin();iter != root_value.end();++iter)
        {
            config = new activity_six_sect_config;
            config->reset();

            Json::Value &v = (*iter)["base_id"];
            if (!v.empty())
            {
                config->set_base_id(v.asInt());
            }

            v = (*iter)["type"];
            if (!v.empty())
            {
                config->set_type(v.asInt());
            }

            v = (*iter)["level_limit"];
            if (!v.empty())
            {
                config->set_level_limit(v.asInt());
            }

            item_content ic;
            v = (*iter)["open_time_content"];
            if (!v.empty())
            {
                string cell_str = v.asString();
                proc_string(cell_str,ic);
            }
            config->set_open_time(ic);

            v = (*iter)["name"];
            if (!v.empty())
            {
                config->set_name(v.asInt());
            }

            v = (*iter)["icon"];
            if (!v.empty())
            {
                config->set_icon(v.asInt());
            }

            v = (*iter)["open_time_desc"];
            if (!v.empty())
            {
                config->set_open_time_desc(v.asInt());
            }

            v = (*iter)["reward_desc"];
            if (!v.empty())
            {
                config->set_reward_desc(v.asInt());
            }

            v = (*iter)["join_count"];
            if (!v.empty())
            {
                config->set_join_count(v.asInt());
            }

            v = (*iter)["instance_id"];
            if (!v.empty())
            {
                config->set_instance_id(v.asInt());
            }

            activity_six_sect_config_map_.insert(make_pair(config->get_base_id(),config));
            if (config->get_type() < 3)
            {
                activity_six_sect_am_config_map_.insert(make_pair(config->get_base_id(),config));
            }
            else
            {
                activity_six_sect_pm_config_map_.insert(make_pair(config->get_base_id(),config));
            }
        }

        return 0;
    }

    bool Activity_Config_Mgr::check_in_open_time(int type)
    {
        activity_config* config = get_activity_config_by_type(type);
        if (!config)
        {
            return false;                                                                                  
        }

        cute::date_time cur_time;
        int week_day = cur_time.wday();
        
        Game_Data::item_content ele_cont;
        config->get_week_open_day(ele_cont);

        game_element_list_t ele_list;
        ele_cont.get_element(ele_list);

        bool is_week_open_day = false;
        Game_Data::game_element_list_t::iterator itg = ele_list.begin();
        for(;itg != ele_list.end();++itg)
        {
            Game_Data::Game_Element& element = (*itg);
            if(strcmp(element.get_command(),"week") == 0)
            {
                vector<uint> para;
                element.get_para_list_in_vector(para);
                vector<uint>::iterator iter = para.begin(); 
                for(;iter != para.end();++iter)
                {
                    if ((*iter) == week_day)
                    {
                        is_week_open_day = true;
                        break;
                    }
                }
            }
        }

        if (is_week_open_day)
        {
            int hour = cur_time.hour();
            int minute = cur_time.minute();

            ele_cont.reset();
            config->get_open_time(ele_cont);

            ele_list.clear();
            ele_cont.get_element(ele_list);

            Game_Data::game_element_list_t::iterator itg = ele_list.begin();
            for(;itg != ele_list.end();++itg)
            {
                Game_Data::Game_Element& element = (*itg);
                if(strcmp(element.get_command(),"time") == 0)
                {
                    vector<uint> para;
                    element.get_para_list_in_vector(para);
                    if (para.size() == 4)
                    {
                        if ((hour > (int)para[0] || hour == (int)para[0] && minute >= (int)para[1]) &&
                            (hour < (int)para[2] || hour == (int)para[2] && minute < (int)para[3]))
                        {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

    bool Activity_Config_Mgr::check_activity_effect_show()
    {
        activity_config* config = NULL;
        activity_config_map_iter iter = activity_config_map_.begin();
        for (;iter != activity_config_map_.end();++iter)
        {
            config = iter->second;
            if (config && config->get_check_effect_show())
            {
                if (check_in_open_time(config->get_type()))
                {
                    return true;
                }
            }
        }

        return false;
    }
}

