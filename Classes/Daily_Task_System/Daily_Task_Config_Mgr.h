
#ifndef __DAILY_TASK_CONFIG_MGR_H__
#define __DAILY_TASK_CONFIG_MGR_H__

#include "Game_Interface/common.h"
#include "Daily_Task_Config_Data.h"

namespace Game_Data
{
    class Daily_Task_Config_Mgr
    {
    public:
        Daily_Task_Config_Mgr();
        virtual ~Daily_Task_Config_Mgr();

        static Daily_Task_Config_Mgr* instance();

        int initialize(void);
        int release(void);

        daily_task_config* get_daily_task_config(int base_id);
        daily_task_config_map& get_daily_task_config_map(){return daily_task_config_map_;}

    private:
        int load_daily_task_config_data();

    private:
        static Daily_Task_Config_Mgr*       instance_;

        daily_task_config_map               daily_task_config_map_;
    };
}


typedef Game_Data::Daily_Task_Config_Mgr DAILY_TASK_CONFIG_MGR;


#endif /* __ACTIVITY_CONFIG_MGR_H__ */
