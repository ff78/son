

#ifndef __MONSTER_MGR_H__
#define __MONSTER_MGR_H__

#include <list>
#include <map>
#include <string>

#include "Game_Interface/game_element.h"
#include "Player_Config_Data.h"
namespace Game_Data
{
	struct Player_Base_Attr_Config_Data;
	struct Player_Data;
	
	class Player_Mgr
	{
	public:
		Player_Mgr();
		virtual ~Player_Mgr();

        static Player_Mgr* instance();

		int initialize( void );

		Player_Base_Attr_Config_Data* get_player_base_attr(int id);
		Player_Level_Attr_Config_Data* get_player_level_attr(int level_id, int level);
		const char* get_player_portrait(int id);
        int get_name_id(int base_id);
	private:

		int load_player_base_attr_config_data(void);
		int load_player_level_attr_config_data(void);
		int load_player_portrait_config(void);

    private:
        static Player_Mgr*                              instance_;

        std::map<int, Player_Base_Attr_Config_Data>     player_base_attr_data_map_;
		list<Player_Level_Attr_Config_Data>             player_level_attr_data_list_;
		std::map<int,std::string>                       player_portrait_config;
	};
}


typedef Game_Data::Player_Mgr PLAYER_MGR;


#endif /* __MONSTER_MGR_H__ */
