

#if !defined(EA_59BF942E_2C1A_42c4_9F60_3426306BDF17__INCLUDED_)
#define EA_59BF942E_2C1A_42c4_9F60_3426306BDF17__INCLUDED_


#include "Game_Interface/common.h"

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
class Formula_Function_Instance
{

public:
	Formula_Function_Instance();
	virtual ~Formula_Function_Instance();

    static Formula_Function_Instance* instance();

    // Use to process intance logic
    static bool proc_login( Game_Logic::Game_Interface& gm_interface );
    static bool proc_logout( Game_Logic::Game_Interface& gm_interface );
    static bool process_instance_result(Game_Logic::Game_Interface& gm_interface);



    // Interface to transfer player to the scene by config
	static bool instance_begin(Game_Logic::Game_Interface& gm_interface);

#ifdef GAME_SERVER
    //Interface to create monster wave on scene by config
	//static bool monster_wave(Game_Logic::Game_Interface& gm_interface);
	static bool give_item(Game_Logic::Game_Interface& gm_interface);
	static bool award_money(Game_Logic::Game_Interface& gm_interface);
	static bool award_item(Game_Logic::Game_Interface& gm_interface);
	static bool award_exp_compute(Game_Logic::Game_Interface& gm_interface);
    static bool award_general(Game_Logic::Game_Interface& gm_interface);
    static bool remove_item(Game_Logic::Game_Interface& gm_interface);
    static bool instance_energy_consume(Game_Logic::Game_Interface& gm_interface);
    int instance_check(int player_id, const ACE_Time_Value &now);
#endif

    static bool proc_instance_timer_check(Game_Logic::Game_Interface& gm_interface);
    static bool proc_instance_player_die(Game_Logic::Game_Interface& gm_interface);

    int get_element_list_from_instance_data( int instance_id, const char* table_key, 
                                 const char* conten_key, const char* cmd_key, list<Game_Data::Game_Element>& ele_lst);
    int get_para_list_from_instance_data(  int instance_id, const char* table_key, const char* conten_key, const char* cmd_key, vector<uint>& para);
    int get_string_content_from_instance_data( int instance_id, const char* table_key, const char* conten_key, const char* cmd_key, string& content);

    int get_elite_instance_id( int instance_id );

private:

    int proc_init_time_limit_instance(int player_id, int instance_id);
    //int get_instance_dialog_id(  int player_id, int instance_id, int instance_finish = 0 ); 
    //int get_time_limit( int instance_id, int& type );
    int get_instance_first_state(int player_id, int instance_id, int time_limit);
    int exec_element_list(int player_id, int formula_id, const char* key,Game_Data::Formula_Data& fd );

    static Formula_Function_Instance* instance_;

#ifdef YN_LINUX		
    pthread_mutex_t                     fomula_function_mutex_;
#endif
};

#endif // !defined(EA_59BF942E_2C1A_42c4_9F60_3426306BDF17__INCLUDED_)
