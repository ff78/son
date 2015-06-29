
//#include <fstream>
#ifdef YN_LINUX
#include <string.h>
#endif

#include "Daily_Task_Mgr_Cl.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Network_Common/message_stream.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
//#include "Daily_Task_System/Daily_Task_Config_Mgr.h"

namespace Game_Data
{
    Daily_Task_Mgr* Daily_Task_Mgr::instance_ = NULL;
    Daily_Task_Mgr::Daily_Task_Mgr()
    {

    }

    Daily_Task_Mgr::~Daily_Task_Mgr()
    {

    }

    Daily_Task_Mgr* Daily_Task_Mgr::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Daily_Task_Mgr;
        }

        return instance_;
    }

    void Daily_Task_Mgr::release()
    {
        daily_task_.reset();
    }

    void Daily_Task_Mgr::load_daily_task(message_stream& ms)
    {
        daily_task_.reset();

        ms >> daily_task_.role_id_;
        ms >> daily_task_.task_base_id_;
        ms >> daily_task_.star_level_;
        ms >> daily_task_.progress_;
        ms >> daily_task_.complete_count_;
        ms >> daily_task_.exec_count_;
        ms >> daily_task_.got_time_;
        for (int i = 0;i < DAILY_TASK_GIFT_COUNT;++i)
        {
            ms >> daily_task_.got_flag_[i];
        }
    }
}