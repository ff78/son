
#ifndef __DAILY_TASK_MSG_PROC_H__
#define __DAILY_TASK_MSG_PROC_H__

#include "Game_Interface/common.h"
#include "Game_Interface/event_define.h"

namespace Game_Logic
{
    struct Game_Interface;
}

class Daily_Task_Msg_Proc
{

public:
    Daily_Task_Msg_Proc();
    virtual ~Daily_Task_Msg_Proc();
    static Daily_Task_Msg_Proc* instance();

public:
    static bool send_load_daily_task(Game_Logic::Game_Interface& gm_interface);
    static bool send_drop_daily_task(Game_Logic::Game_Interface& gm_interface);
    static bool send_submit_daily_task(Game_Logic::Game_Interface& gm_interface);
    static bool send_refresh_daily_task_star_level(Game_Logic::Game_Interface& gm_interface);
    static bool send_set_daily_task_star_level_max(Game_Logic::Game_Interface& gm_interface);
    static bool send_token_complete_daily_task(Game_Logic::Game_Interface& gm_interface);
    static bool send_get_daily_task_gift_one(Game_Logic::Game_Interface& gm_interface);
    static bool send_get_daily_task_gift_two(Game_Logic::Game_Interface& gm_interface);
    static bool send_get_daily_task_gift_three(Game_Logic::Game_Interface& gm_interface);

	static bool on_load_daily_task(Game_Logic::Game_Interface& gm_interface);
    static bool on_drop_daily_task(Game_Logic::Game_Interface& gm_interface);
    static bool on_submit_daily_task(Game_Logic::Game_Interface& gm_interface);
    static bool on_refresh_daily_task_star_level(Game_Logic::Game_Interface& gm_interface);
    static bool on_set_daily_task_star_level_max(Game_Logic::Game_Interface& gm_interface);
    static bool on_token_complete_daily_task(Game_Logic::Game_Interface& gm_interface);
    static bool on_get_daily_task_gift_one(Game_Logic::Game_Interface& gm_interface);
    static bool on_get_daily_task_gift_two(Game_Logic::Game_Interface& gm_interface);
    static bool on_get_daily_task_gift_three(Game_Logic::Game_Interface& gm_interface);

    static bool on_update_daily_task_progress(Game_Logic::Game_Interface& gm_interface);

private:
    static Daily_Task_Msg_Proc* instance_;
};
#endif // __DAILY_TASK_MSG_PROC_H__

