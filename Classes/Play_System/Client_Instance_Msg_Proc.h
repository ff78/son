
#if !defined(EA_9E9DED21_276A_4d66_A93D_83D92315F6F7__INCLUDED_)
#define EA_9E9DED21_276A_4d66_A93D_83D92315F6F7__INCLUDED_

#include "Game_Interface/common.h"

namespace Game_Logic
{
    struct Game_Interface;
    struct Game_Event;
}

class Client_Instance_Msg_Proc
{

public:
	Client_Instance_Msg_Proc();
	virtual ~Client_Instance_Msg_Proc();

    static Client_Instance_Msg_Proc* instance();
    static bool on_player_enter_instance( Game_Logic::Game_Interface& gm_interface );
    static bool on_player_instance_finish_result( Game_Logic::Game_Interface& gm_interface );
    static bool on_player_instance_monster_wave( Game_Logic::Game_Interface& gm_interface );

    static bool on_player_instance_progress( Game_Logic::Game_Interface& gm_interface );
    static bool on_player_stage_instance_state( Game_Logic::Game_Interface& gm_interface );
    static bool on_instance_sweep( Game_Logic::Game_Interface& gm_interface );
    static bool on_player_stage( Game_Logic::Game_Interface& gm_interface );
    static bool on_player_stage_instance(Game_Logic::Game_Interface &gm_interface);

    static bool enter_instance( Game_Logic::Game_Interface& gm_interface );
    static bool select_instance( Game_Logic::Game_Interface& gm_interface );
    static bool send_instance_finish( Game_Logic::Game_Interface& gm_interface );
    static bool send_monster_kill( Game_Logic::Game_Interface& gm_interface );
    static bool send_require_stage_instance_list( Game_Logic::Game_Interface& gm_interface );
    static bool send_reuqire_stage( Game_Logic::Game_Interface& gm_interface );
    static bool send_begin_instance_timer( Game_Logic::Game_Interface& gm_interface );
    static bool send_instance_player_die( Game_Logic::Game_Interface& gm_interface );
    static bool send_instance_sweep( Game_Logic::Game_Interface& gm_interface );
    static bool send_require_all_stage(Game_Logic::Game_Interface &gm_interface);
	
	static bool send_back_main_city(Game_Logic::Game_Interface& gm_interface);
	static bool send_require_challenge_next_instance(Game_Logic::Game_Interface &gm_interface);				// 发送消息请求挑战下一关
	static bool on_player_next_instance(Game_Logic::Game_Interface &gm_interface);							// 服务器返回消息挑战下一关
private:


    static Client_Instance_Msg_Proc* instance_;
};
#endif // !defined(EA_9E9DED21_276A_4d66_A93D_83D92315F6F7__INCLUDED_)
