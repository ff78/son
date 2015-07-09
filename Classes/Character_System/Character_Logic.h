

#pragma once

#include "Game_Interface/event_define.h"
#include "Game_Interface/game_element.h"

namespace Game_Logic
{
	struct Game_Interface;
}
class Character_Logic
{

public:
	Character_Logic();
	virtual ~Character_Logic();
    static Character_Logic* instance();
	int init_Character_system( void );

//	static bool init_character_skill_list(Game_Logic::Game_Interface& gm_interface);

//	static bool  init_skill_list(int character_id);

	int exec_Character_function(const char* cmd, std::vector<uint64> para, const char* key);
	int reg_Character_function();
	void exec_Character_function();
private:
    int exec_element_function_list( int player_id, std::list<Game_Data::Game_Element>& ge_lst, const char* key );

    int exec_Character_interface(const char* cmd, std::vector<uint64> para, const char* key);

private:
    static Character_Logic*                     instance_;
	Game_Logic::game_interface_handler_map_t    Character_function_call_list_;
};
typedef Character_Logic CHARACTER_LOGIC;

