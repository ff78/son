
#ifndef _AWARD_MSG_PROC_H_
#define _AWARD_MSG_PROC_H_

#include "Game_Interface/common.h"
#include "Game_Interface/event_define.h"
#include "Public_Annoucement/Pubilc_Annoucement_Common.h"

//class message_stream;
class Award_Msg_Proc
{

public:
    Award_Msg_Proc();
    virtual ~Award_Msg_Proc();
    static Award_Msg_Proc* instance();

public:
    static bool send_ask_exchange_code_info(Game_Logic::Game_Interface& gm_interface);

public:
	static bool on_ask_exchange_code_info(Game_Logic::Game_Interface& gm_interface);

private:
    static Award_Msg_Proc* instance_;
};
#endif // _AWARD_MSG_PROC_H_

