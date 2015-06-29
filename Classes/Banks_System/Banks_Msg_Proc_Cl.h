
#ifndef _BANKS_MSG_PROC_CL_H_
#define _BANKS_MSG_PROC_CL_H_

#include "Game_Interface/common.h"
#include "Game_Interface/event_define.h"

//class message_stream;
class Banks_Msg_Proc
{

public:
    Banks_Msg_Proc();
    virtual ~Banks_Msg_Proc();
    static Banks_Msg_Proc* instance();

public:
	static bool send_exchange_token_to_gold(Game_Logic::Game_Interface& gm_interface);

public:
	static bool on_exchange_token_to_gold(Game_Logic::Game_Interface& gm_interface);

private:
    static Banks_Msg_Proc* instance_;
};
#endif // _BANKS_MSG_PROC_CL_H_

