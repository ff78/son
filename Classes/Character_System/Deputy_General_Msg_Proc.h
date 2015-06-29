
#ifndef __DEPUTY_GENERAL_MSG_PROC_H__
#define __DEPUTY_GENERAL_MSG_PROC_H__

#include "Game_Interface/common.h"
#include "Game_Interface/event_define.h"

class message_stream;
class Deputy_General_Msg_Proc
{

public:
    Deputy_General_Msg_Proc();
    virtual ~Deputy_General_Msg_Proc();
    static Deputy_General_Msg_Proc* instance();

public:
	static bool send_load_deputy_general(Game_Logic::Game_Interface& gm_interface);
	static bool send_deputy_general_fight(Game_Logic::Game_Interface& gm_interface);
	static bool send_deputy_general_cancel_fight(Game_Logic::Game_Interface& gm_interface);

	static bool on_load_deputy_general(Game_Logic::Game_Interface& gm_interface);
	static bool on_deputy_general_fight(Game_Logic::Game_Interface& gm_interface);
	static bool on_deputy_general_cancel_fight(Game_Logic::Game_Interface& gm_interface);

    static bool on_create_deputy_general(Game_Logic::Game_Interface& gm_interface);

private:
    static Deputy_General_Msg_Proc* instance_;
	int get_message_stream_body(int& player_id,message_stream& ms, Game_Logic::Game_Interface& gm_interface);
};
#endif // __DEPUTY_GENERAL_MSG_PROC_H__

