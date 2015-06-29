
#ifndef __LOGIN_REWARD_MSG_PROC_H__
#define __LOGIN_REWARD_MSG_PROC_H__

#include "Game_Interface/common.h"

namespace Game_Logic
{
    struct Game_Interface;
}

class Login_Reward_Msg_Proc
{

public:
	Login_Reward_Msg_Proc();
	virtual ~Login_Reward_Msg_Proc();

    static Login_Reward_Msg_Proc* instance();

public:
    static bool send_load_login_reward(Game_Logic::Game_Interface& gm_interface);
    static bool send_get_login_reward(Game_Logic::Game_Interface& gm_interface);

    static bool on_load_login_reward(Game_Logic::Game_Interface& gm_interface);
    static bool on_get_login_reward(Game_Logic::Game_Interface& gm_interface);
    
private:
	void showAlart( int type );

private:
    static Login_Reward_Msg_Proc* instance_;

};
#endif // __LOGIN_REWARD_MSG_PROC_H__
