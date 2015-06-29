
#ifndef __RANK_MSG_PROC_H__
#define __RANK_MSG_PROC_H__

#include "Game_Interface/common.h"

namespace Game_Logic
{
    struct Game_Interface;
}

class Rank_Msg_Proc
{

public:
	Rank_Msg_Proc();
	virtual ~Rank_Msg_Proc();

    static Rank_Msg_Proc* instance();

public:
    static bool send_load_rank(Game_Logic::Game_Interface& gm_interface);
    static bool send_load_rank_role_level(Game_Logic::Game_Interface& gm_interface);
    static bool send_load_rank_role_fighting_capacity(Game_Logic::Game_Interface& gm_interface);
    static bool send_load_rank_role_have_gold(Game_Logic::Game_Interface& gm_interface);
    
    static bool on_load_rank(Game_Logic::Game_Interface& gm_interface);
    static bool on_load_rank_role_level(Game_Logic::Game_Interface& gm_interface);									// 载入等级排行榜
	static bool on_load_rank_role_fighting_capacity(Game_Logic::Game_Interface& gm_interface);						// 载入战斗力排行榜
	static bool on_load_rank_role_have_gold(Game_Logic::Game_Interface& gm_interface);								// 载入金钱排行榜
	static bool on_load_rank_role_renown(Game_Logic::Game_Interface& gm_interface);									// 载入声望排行榜
	static bool on_load_rank_role_pvp(Game_Logic::Game_Interface& gm_interface);									// 载入竞技场排行榜


private:
    static Rank_Msg_Proc* instance_;

};
#endif // __RANK_MSG_PROC_H__
