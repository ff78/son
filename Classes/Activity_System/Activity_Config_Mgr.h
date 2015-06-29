
#ifndef __ACTIVITY_CONFIG_MGR_H__
#define __ACTIVITY_CONFIG_MGR_H__

#include "Game_Interface/common.h"
#include "Activity_Config_Data.h"

namespace Game_Data
{
    class Activity_Config_Mgr
    {
    public:
        Activity_Config_Mgr();
        virtual ~Activity_Config_Mgr();

        static Activity_Config_Mgr* instance();

        int initialize(void);
        int release(void);

        activity_config* get_activity_config_by_type(int type);
        activity_config_map& get_activity_config_map(){return activity_config_map_;}

        activity_six_sect_config* get_activity_six_sect_config(int base_id);
        activity_six_sect_config_map& get_activity_six_sect_config_map_by_type(int type);

        int get_activity_six_sect_type();

        bool check_in_open_time(int type);

        bool check_activity_effect_show();

    private:
        int load_activity_config_data();
        int load_activity_six_sect_config_data();
        void proc_string(const string& content_str, item_content &ic);

    private:
        static Activity_Config_Mgr*         instance_;

        activity_config_map                 activity_config_map_;
        activity_six_sect_config_map        activity_six_sect_config_map_;
        activity_six_sect_config_map        activity_six_sect_am_config_map_;
        activity_six_sect_config_map        activity_six_sect_pm_config_map_;
    };
}


typedef Game_Data::Activity_Config_Mgr ACTIVITY_CONFIG_MGR;


#endif /* __ACTIVITY_CONFIG_MGR_H__ */
