#ifndef _Game_Content_Interface_H
#define	_Game_Content_Interface_H
#include "common.h"
#include "event_define.h"
#include "game_element.h"
namespace Game_Logic
{

	class Game_Content_Interface
	{
	public:
		Game_Content_Interface	(void);
		~Game_Content_Interface	(void);
				
		void init				( void );

		bool reg_interface		( const char* cmd, game_interface_handler_t handle );
		bool exec_interface		( const char* cmd, const vector<uint64> para_vec, const char* key = "", int len = 0 );
		bool reg_function_callback ( const char* cmd, game_interface_handler_t handle,game_interface_handler_map_t& function_call_list );	
		int exec_function_list(Game_Data::game_element_list_t& elementlst, game_interface_handler_map_t& function_call_list);
		int exec_function(const char* cmd, vector<uint64>  para, game_interface_handler_map_t& function_call_list, const char* key = "");
		static Game_Content_Interface* instance(void);

	private:
		static Game_Content_Interface* instance_p_;
		game_interface_multi_handler_map_t game_interface_handler_map_;
#ifdef LINUX_ENV
		pthread_mutex_t  game_content_mutex_;
#endif

	};

}

#endif
