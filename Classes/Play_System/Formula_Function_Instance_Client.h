
#ifndef _FORMULA_FUNCTION_INSTANCE_CLIENT_H
#define	_FORMULA_FUNCTION_INSTANCE_CLIENT_H


#include "Game_Interface/common.h"
#include "cocos2d.h"
#ifdef GAME_SERVER
#include <ace/ACE.h>
#endif

namespace Game_Data
{
    struct Formula_Data;
    struct Game_Element;
#ifdef GAME_CLIENT
    class Player;
#endif
};
namespace Game_Logic
{
    struct Game_Interface;
    struct Game_Event;
}
class Formula_Function_Instance_Client
{

public:
	Formula_Function_Instance_Client();
	virtual ~Formula_Function_Instance_Client();

    static Formula_Function_Instance_Client* instance();

    static bool process_instance_player_back_home(Game_Logic::Game_Interface& gm_interface);
    static bool show_instance_dialog(Game_Logic::Game_Interface& gm_interface);
    static bool show_monster_wave(Game_Logic::Game_Interface& gm_interface);
    static bool reg_monster_die_envent(Game_Logic::Game_Interface& gm_interface);
    static bool proc_enter_instance(Game_Logic::Game_Interface& gm_interface);
    static bool on_finish_load_scene( const Game_Logic::Game_Event& gm_evt );
    static bool proc_player_die_envent( const Game_Logic::Game_Event& gm_evt );
    static bool proc_instance_fail(Game_Logic::Game_Interface& gm_interface);
    static bool proc_instance_finish(Game_Logic::Game_Interface& gm_interface);
    static bool proc_instance_dialog_finish_envent( const Game_Logic::Game_Event& gm_evt );
    
    static bool proc_instance_timer_begin( const Game_Logic::Game_Event& gm_evt );
    void notifyServerTime();
    void notifyServerWin();
    void notifyServerLose();
    void waitPacket();
    void requireSelStage();
    
    static bool remove_instance_data(Game_Logic::Game_Interface& gm_interface);
	int process_instance_dialog( int player_id, int instance_id, int instance_finish = 0 ); 
private:
    int reg_instance_event_when_first_enter( int player_id, int instance_id,int scene_id,  vector<uint64>& para );
    int show_instance_time_limit(int player_id);
    void get_instance_dialog_data( Game_Data::Player* player, int& head_id, int& dic_id, vector<uint>& para );
    
    int proc_monster_wave_when_load_scene( int player_id, int instance_id, int scene_id );
    int to_do_init_monster_wave(int player_id, int instance_id);
    static Formula_Function_Instance_Client* instance_;
#ifdef YN_LINUX		
    pthread_mutex_t                     fomula_function_mutex_;
#endif
};

#endif 
