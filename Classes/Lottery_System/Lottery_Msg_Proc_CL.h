
#ifndef _LOTTERY_MSG_PROC_CL_H_
#define _LOTTERY_MSG_PROC_CL_H_

#include "Game_Interface/common.h"
#include "Game_Interface/event_define.h"

//class message_stream;
class Lottery_Msg_Proc
{

public:
    Lottery_Msg_Proc();
    virtual ~Lottery_Msg_Proc();
    static Lottery_Msg_Proc* instance();

public:
	static bool send_request_lottery(Game_Logic::Game_Interface& gm_interface);
	static bool send_request_lottery_category_info(Game_Logic::Game_Interface& gm_interface);
	static bool send_request_reward_house_info(Game_Logic::Game_Interface& gm_interface);
	static bool send_request_get_reward(Game_Logic::Game_Interface& gm_interface);

public:
	static bool on_ask_pubilc_annoucement(Game_Logic::Game_Interface& gm_interface);


private:
    static Lottery_Msg_Proc* instance_;
};
#endif // _LOTTERY_MSG_PROC_CL_H_

