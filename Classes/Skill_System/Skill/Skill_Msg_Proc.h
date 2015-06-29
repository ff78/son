
#ifndef __Skill_MSG_PROC_H__
#define __Skill_MSG_PROC_H__

#include "Game_Interface/common.h"
#include "Game_Interface/event_define.h"

class message_stream;
class Skill_Msg_Proc
{

public:
    Skill_Msg_Proc();
    virtual ~Skill_Msg_Proc();
    static Skill_Msg_Proc* instance();

public:
    static bool send_load_skill(Game_Logic::Game_Interface& gm_interface);
	static bool send_uplevel_skill(Game_Logic::Game_Interface& gm_interface);

	static bool on_load_skill(Game_Logic::Game_Interface& gm_interface);
	static bool on_uplevel_skill(Game_Logic::Game_Interface& gm_interface);

    static bool on_create_skill(Game_Logic::Game_Interface& gm_interface);

private:
    static Skill_Msg_Proc* instance_;
};
#endif // __Skill_MSG_PROC_H__

