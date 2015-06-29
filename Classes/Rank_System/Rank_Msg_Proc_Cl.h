
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
    static bool on_load_rank_role_level(Game_Logic::Game_Interface& gm_interface);									// ����ȼ����а�
	static bool on_load_rank_role_fighting_capacity(Game_Logic::Game_Interface& gm_interface);						// ����ս�������а�
	static bool on_load_rank_role_have_gold(Game_Logic::Game_Interface& gm_interface);								// �����Ǯ���а�
	static bool on_load_rank_role_renown(Game_Logic::Game_Interface& gm_interface);									// �����������а�
	static bool on_load_rank_role_pvp(Game_Logic::Game_Interface& gm_interface);									// ���뾺�������а�


private:
    static Rank_Msg_Proc* instance_;

};
#endif // __RANK_MSG_PROC_H__
