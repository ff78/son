
#ifndef _PUBLIC_ANNOUCEMENT_MSG_PROC_CL_H_
#define _PUBLIC_ANNOUCEMENT_MSG_PROC_CL_H_

#include "Game_Interface/common.h"
#include "Game_Interface/event_define.h"
#include "Public_Annoucement/Pubilc_Annoucement_Common.h"

//class message_stream;
class Public_Annoucement_Msg_Proc
{

public:
    Public_Annoucement_Msg_Proc();
    virtual ~Public_Annoucement_Msg_Proc();
    static Public_Annoucement_Msg_Proc* instance();

public:
    static bool send_ask_pubilc_annoucement(Game_Logic::Game_Interface& gm_interface);

public:
	static bool on_ask_pubilc_annoucement(Game_Logic::Game_Interface& gm_interface);


private:
    static Public_Annoucement_Msg_Proc* instance_;
	static bool showed;
};
#endif // _PUBLIC_ANNOUCEMENT_MSG_PROC_CL_H_

