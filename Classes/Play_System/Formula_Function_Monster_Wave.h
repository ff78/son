
#if !defined(EA_F207A884_139F_4f64_B4AD_8E39FAFB73BE__INCLUDED_)
#define EA_F207A884_139F_4f64_B4AD_8E39FAFB73BE__INCLUDED_

#include "Game_Interface/common.h"

namespace Game_Logic
{
    struct Game_Interface;
    struct Game_Event;
}

struct  current_instance_data;
class Formula_Function_Monster_Wave
{

public:
	Formula_Function_Monster_Wave();
	virtual ~Formula_Function_Monster_Wave();
    static Formula_Function_Monster_Wave* instance();
    static bool  process_next_wave_monster( Game_Logic::Game_Interface& gm_interface );
    static bool  on_instance_finish( Game_Logic::Game_Interface& gm_interface );

    static bool on_finish_create_monster( Game_Logic::Game_Interface& gm_interface );
    static bool proc_monster_die_envent(const Game_Logic::Game_Event& gm_evt);
    static void on_finish_move_to_next_scene( void );
private:
    int to_send_monster_kill(int player_id, current_instance_data &cid);
    int proc_next_monster_wave( int player_id, current_instance_data& cid );
    int get_current_locked_screen(current_instance_data& cid);
    int proc_monster_wave(int player_id, current_instance_data& cid,bool is_end);
    int proc_finish_instance(int player_id, current_instance_data &cid, int state);
    static Formula_Function_Monster_Wave* instance_;
};


#endif // !defined(EA_F207A884_139F_4f64_B4AD_8E39FAFB73BE__INCLUDED_)

