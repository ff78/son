#ifndef _Game_Element_PARSE_H
#define	_Game_Element_PARSE_H

#include "Game_Interface/common.h"
#include "game_element.h"

namespace Game_Data
{
	class Game_Element_Parse
	{
	public:
		Game_Element_Parse( void );
		~Game_Element_Parse( void );

		static Game_Element_Parse* instance(void);

		int     game_element_parse_cmd( const string& cmd_str, 
			        game_command_element_vec_t& game_cmd_list,const char* data_type = "");
		int     game_element_parse_cell( const string& cell_str, 
			        game_element_list_t& Game_Element_list,const char* data_type = "");

		int     replace_char_to_char_from_string( string& temp_str, const char* src_char, const char* des_char);
        int     get_content_from_string(vector<string>& str_vec, const char* content, const char* key );
		void    getContentListFromString(list<string>& vecTempStrLst, const char* contentList);
        int     push_msg_para( const int msgid,const char* msg, vector<uint64>& para_vec);
        int     get_para_from_require_element( const char* key, game_element_list_t& Game_Element_list, vector<uint>& para_vec);
        int     get_string_para_from_require_element( const char* key, game_element_list_t& Game_Element_list, vector<string>& para_vec);
	private:

		static Game_Element_Parse* instance_;
#ifdef YN_LINUX				
		pthread_mutex_t  game_element_mutex_; 
#endif
	};
}
#endif
