
#ifndef __ACTIVITY_CONFIG_DATA_H__
#define __ACTIVITY_CONFIG_DATA_H__

#include <string>
#include <map>
#include <list>

#include "Item_System/Item_Config_Data.h"

using namespace std;
namespace Game_Data
{
    enum Activity_Type
    {
        AT_SIX_SECT = 1,        // ¡˘¥Û√≈≈…
    };

    struct activity_config
    {
        activity_config()
        {
            reset();
        }

        ~activity_config() {}

        void reset()
        {
            base_id_ = 0;
            type_ = 0;
            level_limit_ = 0;
            week_open_day_.reset();
            open_time_.reset();
            name_ = 0;
            icon_ = 0;
            week_open_day_desc_ = 0;
            open_time_desc_ = 0;
            activity_desc_ = 0;
            reward_desc_ = 0;
            check_effect_show_ = 0;
        }

        activity_config & operator = (const activity_config& ac)
        {
            base_id_ = ac.get_base_id();
            type_ = ac.get_type();
            level_limit_ = ac.get_level_limit();
            week_open_day_ = ac.get_week_open_day();
            open_time_ = ac.get_open_time();
            name_ = ac.get_name();
            icon_ = ac.get_icon();
            week_open_day_desc_ = ac.get_week_open_day_desc();
            open_time_desc_ = ac.get_open_time_desc();
            activity_desc_ = ac.get_activity_desc();
            reward_desc_ = ac.get_reward_desc();
            check_effect_show_ = ac.get_check_effect_show();
            
            return *this;
        }
        
        void set_base_id(int base_id){base_id_ = base_id;}
        int get_base_id() const { return base_id_; } 
        
        void set_type(int type){type_ = type;}
        int get_type() const { return type_; }

        void set_level_limit(int level_limit){level_limit_ = level_limit;}
        int get_level_limit() const { return level_limit_; }

        void set_week_open_day(const item_content& ic){week_open_day_ = ic;}
        void get_week_open_day(item_content& ic){ic = week_open_day_;}
        const item_content get_week_open_day() const {return week_open_day_;}

        void set_open_time(const item_content& ic){open_time_ = ic;}
        void get_open_time(item_content& ic){ic = open_time_;}
        const item_content get_open_time() const {return open_time_;}

        void set_name(int name){name_ = name;}
        int get_name() const { return name_; }

        void set_icon(int icon){icon_ = icon;}
        int get_icon() const { return icon_; }
        
        void set_week_open_day_desc(int week_open_day_desc){week_open_day_desc_ = week_open_day_desc;}
        int get_week_open_day_desc() const { return week_open_day_desc_; }
       
        void set_open_time_desc(int open_time_desc){open_time_desc_ = open_time_desc;}
        int get_open_time_desc() const { return open_time_desc_; }

        void set_activity_desc(int activity_desc){activity_desc_ = activity_desc;}
        int get_activity_desc() const { return activity_desc_; }

        void set_reward_desc(int reward_desc){reward_desc_ = reward_desc;}
        int get_reward_desc() const { return reward_desc_; }
        
        void set_check_effect_show(int check_effect_show){check_effect_show_ = check_effect_show;}
        int get_check_effect_show() const { return check_effect_show_; }

    private:
        int base_id_;
        int type_;
        int level_limit_;
        item_content week_open_day_;
        item_content open_time_;
        int name_;
        int icon_;
        int week_open_day_desc_;
        int open_time_desc_;
        int activity_desc_;
        int reward_desc_;
        int check_effect_show_;
    };

    struct activity_six_sect_config
    {
        activity_six_sect_config()
        {
            reset();
        }

        ~activity_six_sect_config() {}

        void reset()
        {
            base_id_ = 0;
            type_ = 0;
            level_limit_ = 0;
            open_time_.reset();
            name_ = 0;
            icon_ = 0;
            open_time_desc_ = 0;
            reward_desc_ = 0;
            join_count_ = 0;
            instance_id_ = 0;
        }

        activity_six_sect_config & operator = (const activity_six_sect_config& ac)
        {
            base_id_ = ac.get_base_id();
            type_ = ac.get_type();
            level_limit_ = ac.get_level_limit();
            open_time_ = ac.get_open_time();
            name_ = ac.get_name();
            icon_ = ac.get_icon();
            open_time_desc_ = ac.get_open_time_desc();
            reward_desc_ = ac.get_reward_desc();
            join_count_ = ac.get_join_count();
            instance_id_ = ac.get_instance_id();

            return *this;
        }

        void set_base_id(int base_id){base_id_ = base_id;}
        int get_base_id() const { return base_id_; } 

        void set_type(int type){type_ = type;}
        int get_type() const { return type_; }

        void set_level_limit(int level_limit){level_limit_ = level_limit;}
        int get_level_limit() const { return level_limit_; }

        void set_open_time(const item_content& ic){open_time_ = ic;}
        void get_open_time(item_content& ic){ic = open_time_;}
        const item_content get_open_time() const {return open_time_;}

        void set_name(int name){name_ = name;}
        int get_name() const { return name_; }

        void set_icon(int icon){icon_ = icon;}
        int get_icon() const { return icon_; }

        void set_open_time_desc(int open_time_desc){open_time_desc_ = open_time_desc;}
        int get_open_time_desc() const { return open_time_desc_; }

        void set_reward_desc(int reward_desc){reward_desc_ = reward_desc;}
        int get_reward_desc() const { return reward_desc_; }

        void set_join_count(int join_count){join_count_ = join_count;}
        int get_join_count() const { return join_count_; }

        void set_instance_id(int instance_id){instance_id_ = instance_id;}
        int get_instance_id() const { return instance_id_; }

    private:
        int base_id_;
        int type_;
        int level_limit_;
        item_content open_time_;
        int name_;
        int icon_;
        int open_time_desc_;
        int reward_desc_;
        int join_count_;
        int instance_id_;
    };

    typedef map<int, activity_config*>                  activity_config_map;
    typedef activity_config_map::iterator		        activity_config_map_iter;
    
    typedef map<int, activity_six_sect_config*>         activity_six_sect_config_map;
    typedef activity_six_sect_config_map::iterator      activity_six_sect_config_map_iter;
}

#endif /* __ACTIVITY_CONFIG_DATA_H__ */

