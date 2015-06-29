
#ifndef __ACUPOINT_MSG_PROC_H__
#define __ACUPOINT_MSG_PROC_H__

#include "Game_Interface/common.h"

namespace Game_Logic
{
    struct Game_Interface;
}

class Acupoint_Msg_Proc
{

public:
	Acupoint_Msg_Proc();
	virtual ~Acupoint_Msg_Proc();

    static Acupoint_Msg_Proc* instance();

public:
    static bool send_load_acupoint(Game_Logic::Game_Interface& gm_interface);
    static bool send_open_acupoint(Game_Logic::Game_Interface& gm_interface);
    
    static bool on_load_acupoint(Game_Logic::Game_Interface& gm_interface);
    static bool on_open_acupoint(Game_Logic::Game_Interface& gm_interface);

    static bool on_create_acupoint(Game_Logic::Game_Interface& gm_interface);
    
private:
    static Acupoint_Msg_Proc* instance_;

};
#endif // __ACUPOINT_MSG_PROC_H__
