
#if !defined(EA_CFE47F27_82BA_40f0_BA2C_D82B31488A5B__INCLUDED_)
#define EA_CFE47F27_82BA_40f0_BA2C_D82B31488A5B__INCLUDED_

#include "Game_Interface/common.h"
#include "Game_Interface/event_define.h"

namespace Game_Data
{
    struct npc_bind_quest;
}

class message_stream;
class quest_msg_proc_client
{

public:
	quest_msg_proc_client();
	virtual ~quest_msg_proc_client();

    static quest_msg_proc_client* instance();

    static bool on_quest_update(Game_Logic::Game_Interface& gm_interface);

    static bool send_accept_quest(Game_Logic::Game_Interface& gm_interface);

    static bool send_submit_quest(Game_Logic::Game_Interface& gm_interface);

    static bool send_require_npc_quest_bind(Game_Logic::Game_Interface& gm_interface);

    static bool on_update_npc_quest_bind_list(Game_Logic::Game_Interface& gm_interface);

    static bool on_quest_submuit_result(Game_Logic::Game_Interface& gm_interface);

    static bool send_require_quest_list(Game_Logic::Game_Interface& gm_interface);

    int update_player_act_data( int quest_id, int act_count, int act_total_count );
private:
    int get_npc_quest_data(int npc_id, message_stream& ms,vector<uint32>& accept_qst_lst,vector<uint32>& submit_qst_lst,vector<uint32>& inprocess_qst_lst);

    int process_npc_quest_bind_state(vector<Game_Data::npc_bind_quest>& npc_bind_old, vector<Game_Data::npc_bind_quest>& npc_bind_new );

    int get_npc_quest_bind_state( int npc_id, vector<Game_Data::npc_bind_quest>& npc_bind );

    int display_npc_quest_state( int instance_npc_id, int state);

    static quest_msg_proc_client* instance_;

};
#endif // !defined(EA_CFE47F27_82BA_40f0_BA2C_D82B31488A5B__INCLUDED_)
