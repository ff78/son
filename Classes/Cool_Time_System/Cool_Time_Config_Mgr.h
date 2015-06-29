
#ifndef __COOL_TIME_CONFIG_MGR_H__
#define __COOL_TIME_CONFIG_MGR_H__

#include "Cool_Time_Config_Data.h"

namespace Game_Data
{
    class Cool_Time_Config_Mgr
    {
    public:
        Cool_Time_Config_Mgr();
        virtual ~Cool_Time_Config_Mgr();

        static Cool_Time_Config_Mgr* instance();

        int initialize();
        int release();

        cool_time_config* get_cool_time_config(int type);

    private:
        int load_cool_time_config_data();

    private:
        static Cool_Time_Config_Mgr*            instance_;

        cool_time_config*                       cool_time_config_array_[CTT_MAX];
    };
}


typedef Game_Data::Cool_Time_Config_Mgr COOL_TIME_CONFIG_MGR;


#endif /* __COOL_TIME_CONFIG_MGR_H__ */
