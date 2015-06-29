#ifndef __EVENT_SYSTEM_LOGIC_H__
#define __EVENT_SYSTEM_LOGIC_H__
#include "Game_Interface/event_define.h"
#include "Game_Interface/game_element.h"

namespace Game_Logic
{
	struct Game_Interface;
	struct Game_Event;
}
class event_system_logic
{
public:
	int init_event_system(int player_id);
	static event_system_logic* sharedInstance();
	static bool load_event_data(Game_Logic::Game_Interface& gm_interface);
	int exec_element_function_list( int event_id, std::list<Game_Data::Game_Element>& ge_lst, const char* key,vector<uint64> para);
	static bool proc_monster_die_envent( const Game_Logic::Game_Event& gm_evt );
	static bool proc_useitem_event( const Game_Logic::Game_Event& gm_evt );
    int reg_function();

private:
	event_system_logic();
	static event_system_logic* instance_;
	Game_Logic::game_interface_handler_map_t event_function_call_map_;
};
#endif //__EVENT_SYSTEM_LOGIC_H__