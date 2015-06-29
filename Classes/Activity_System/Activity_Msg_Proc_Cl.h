
#ifndef __ACTIVITY_MSG_PROC_H__
#define __ACTIVITY_MSG_PROC_H__

#include "Game_Interface/common.h"
#include "Game_Interface/event_define.h"

namespace Game_Logic
{
    struct Game_Interface;
}

class Activity_Msg_Proc
{

public:
    Activity_Msg_Proc();
    virtual ~Activity_Msg_Proc();
    static Activity_Msg_Proc* instance();

public:
    static bool send_load_activity_record(Game_Logic::Game_Interface& gm_interface);
    static bool send_activity_six_sect(Game_Logic::Game_Interface& gm_interface);

	static bool on_load_activity_record(Game_Logic::Game_Interface& gm_interface);
    static bool on_activity_six_sect(Game_Logic::Game_Interface& gm_interface);

public:
	//---接收消息---//
	static bool RecMsgEndlessTowerInfo(Game_Logic::Game_Interface& gm_interface);							// 接收无尽塔的信息

private:
    static Activity_Msg_Proc* instance_;
};
#endif // __ACTIVITY_MSG_PROC_H__

