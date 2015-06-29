#ifndef _GAME_CONDITION_H_
#define	_GAME_CONDITION_H_

#include "common.h"
#include "event_define.h"

namespace Game_Logic
{
	struct Game_Interface;
	class Game_Condition
	{
	public:
		Game_Condition(void);
		~Game_Condition(void);
		
		static Game_Condition* instance(void);
		void init(void);

		bool	reg_game_condition_function_callback ( const char* cmd, game_interface_handler_t handle );

		bool analysis_game_condition( const int player_id, const list<Game_Data::Game_Element>& game_ele_vec );
		
		static bool player_level	( Game_Interface& gm_interface );
		static bool player_gender	( Game_Interface& gm_interface );
		static bool player_vigour	( Game_Interface& gm_interface );
		
		static bool player_money	( Game_Interface& gm_interface );
		static bool player_item		( Game_Interface& gm_interface );
		static bool player_levelrange( Game_Interface& gm_interface );
		static bool player_title	( Game_Interface& gm_interface );
		static bool player_team		( Game_Interface& gm_interface );		
		static bool player_guilddevote( Game_Interface& gm_interface );
		static bool player_guild	( Game_Interface& gm_interface );
		static bool player_honor	( Game_Interface& gm_interface );
		static bool player_country	( Game_Interface& gm_interface );
		static bool player_bind		( Game_Interface& gm_interface );
		static bool player_vip		( Game_Interface& gm_interface );
        static bool player_energy   ( Game_Interface& gm_interface );
	private:
		static Game_Condition* m_pInstance;

		
		game_interface_handler_map_t game_condition_interface_map_;
	};

}

#endif

