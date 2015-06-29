
#ifndef _PARTITION_MSG_PROC_CL_CL_H_
#define _PARTITION_MSG_PROC_CL_CL_H_

#include "Game_Interface/common.h"
#include "Game_Interface/event_define.h"
#include "Public_Annoucement/Pubilc_Annoucement_Common.h"

//class message_stream;
class Partition_Msg_Proc_Cl
{

public:
    Partition_Msg_Proc_Cl();
    virtual ~Partition_Msg_Proc_Cl();
    static Partition_Msg_Proc_Cl* instance();

public:
    static bool send_ask_partition_info(Game_Logic::Game_Interface& gm_interface);

public:
	static bool on_ask_partition_info(Game_Logic::Game_Interface& gm_interface);

private:
    static Partition_Msg_Proc_Cl* instance_;
};
#endif // _PARTITION_MSG_PROC_CL_CL_H_

