
#ifndef __DAILY_TASK_MGR_H__
#define __DAILY_TASK_MGR_H__

#include "Game_Interface/common.h"
#include "Daily_Task_Data.h"

class message_stream;
namespace Game_Data
{
    class Player;
    class Daily_Task_Mgr
    {
    public:
        Daily_Task_Mgr();
        virtual ~Daily_Task_Mgr();

        static Daily_Task_Mgr* instance();

        void release();

        void load_daily_task(message_stream& ms);
        daily_task& get_daily_task(){return daily_task_;}
        
    private:
        static Daily_Task_Mgr*          instance_;

        daily_task                      daily_task_;
    };
}


typedef Game_Data::Daily_Task_Mgr DAILY_TASK_MGR;


#endif /* __DAILY_TASK_MGR_H__ */
