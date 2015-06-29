#ifndef _GAME_EVENT_MGR_H
#define	_GAME_EVENT_MGR_H
#include "common.h"
#include "event_define.h"
namespace Game_Logic
{

	class Game_Event_Mgr
	{
	public:
		Game_Event_Mgr			( void );
		~Game_Event_Mgr			( void );
		
		static Game_Event_Mgr* instance(void);

		void proc_event			( const int player_id_n, const char* cmd, const Game_Event& gm_evt );

		void reg_event			( const char* cmd, const game_event_handler_t handle, const Game_Event& gm_evt );

		void remove_event		( const int player_id_n, const Game_Event& gm_evt );

		void remove_event_by_player_id( const int player_id_n );

		void get_org_quest_command_para( const int quest_id_n, const char* command_c, vector< unsigned int >& para_vec );

	private:
		static Game_Event_Mgr* instance_p_;

		void reg_player_event	( const int player_id_n, const char* cmd, const game_event_handler_t handle, const Game_Event& gm_evt );
		void reg_player_event_when_null	( const char* cmd, const game_event_handler_t handle, const Game_Event& gm_evt, game_event_handler_multi_map_t& tmp_game_event_handler_multi_map );
		
		void proc_player_event_by_command(const game_event_handler_vec_t& gm_evt_list, const char* cmd, const Game_Event& gm_evt);
	
		void proc_common_event_by_command(const game_event_handler_vec_t& gm_evt_list);
	
		game_event_handler_multi_map_t game_event_handler_multi_map_; //handle event for common
		game_event_handler_multi_player_map_t game_event_handler_multi_player_map_; //handle event for player
		
#ifdef YN_LINUX				
		pthread_mutex_t  game_event_mutex_; 
#endif
	};
}


#endif

