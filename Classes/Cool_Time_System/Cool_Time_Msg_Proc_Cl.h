
#ifndef __COOL_TIME_MSG_PROC_H__
#define __COOL_TIME_MSG_PROC_H__

#include "Game_Interface/common.h"

namespace Game_Logic
{
    struct Game_Interface;
}

class Cool_Time_Msg_Proc
{

public:
	Cool_Time_Msg_Proc();
	virtual ~Cool_Time_Msg_Proc();

    static Cool_Time_Msg_Proc* instance();

public:
    static bool send_load_cool_time(Game_Logic::Game_Interface& gm_interface);
    static bool send_clean_cool_time(Game_Logic::Game_Interface& gm_interface);
    
    static bool on_load_cool_time(Game_Logic::Game_Interface& gm_interface);
    static bool on_clean_cool_time(Game_Logic::Game_Interface& gm_interface);

    static bool on_create_cool_time(Game_Logic::Game_Interface& gm_interface);
    
private:
    static Cool_Time_Msg_Proc* instance_;

};
#endif // __COOL_TIME_MSG_PROC_H__
