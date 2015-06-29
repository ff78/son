#ifndef _QUEST_GAME_OBJ_PARSE_H
#define _QUEST_GAME_OBJ_PARSE_H

#include "Game_Interface/common.h"
#include "quest_data_mgr.h"
#include "Game_Interface/game_element.h"

namespace Game_Data
{
	class game_content_parse
	{
	public:
		game_content_parse(void);
		~game_content_parse(void);
		static game_content_parse* instance(void);
		int game_element_parse_cmd( const string& cmd_str, 
								game_command_element_vec_t& game_cmd_vec);
		int game_element_parse_cell( const string& cell_str, 
								game_element_list_t& game_element_vec);
		void getContentListFromString(list<string>& vecTempStrLst, const char* contentList);
	private:
		static game_content_parse* instance_;
	};

	class quest_config
	{
	public:
		quest_config(void) {}
		~quest_config(void)
		{
			if (instance_)
				delete instance_;
		}
		static quest_config* instance(void);
		int load_config(quest_data::quest_one_data_map_t &qd, const char * root);
	private:
		void proc_string(const string& content_str, game_quest_content &gqc);
		static quest_config* instance_;
	};

}
#endif 
