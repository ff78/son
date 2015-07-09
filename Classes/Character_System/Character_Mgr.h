

#ifndef __CHARACTER_MGR_H__
#define __CHARACTER_MGR_H__

#ifdef GAME_CLIENT
#include "cocos2d.h"
#endif

#include <list>
#include <map>

#include "Game_Interface/game_element.h"

#ifdef GAME_CLIENT
USING_NS_CC;
#endif

namespace Game_Data
{
	class Player;
    class DeputyGeneral;
	class FightNpc;
	class CommonNpc;
	class Character;
#ifdef GAME_CLIENT
    class Character_Mgr : public CCNode
#else
    class Character_Mgr
#endif
	{

	public:
		Character_Mgr();
		virtual ~Character_Mgr();
        static Character_Mgr* instance();
        void release();

	public:
		void insert_character(Character* character);
		void remove_character_from_list(int player_id);
        void remove_character(int character_id);
		Character* get_character(int id);
		CommonNpc* get_common_npc_by_static_id(int static_id);
#ifdef GAME_CLIENT
		virtual void update(float delta);
#endif
	    void update_buff(float delta);
		void update_gangqi(float delta);

//        DeputyGeneral* create_deputy_general(Player* player,int character_base_id,int character_type,int level);
		int create_general_id(int role_id);
        void refresh_player_daily_data();

        void save_deputy_general(int role_id);

		//inline std::map<int, Player*>& get_other_players(){ return _other_player_map;};

		std::map<int, Player*>*      _other_player_map;
	private:
        static Character_Mgr*       instance_;
		std::map<int, Character*>   character_map_;
		std::map<int, Player*>      player_map_;
		std::map<int, FightNpc*>    fightnpc_map_;
		std::map<int, CommonNpc*>   commonnpc_map_;
		int							m_last_general_id;
#ifdef YN_LINUX		
        pthread_mutex_t                     character_mutex_;
#endif
	};
}
typedef Game_Data::Character_Mgr CHARACTER_MGR;
#endif // __CHARACTER_MGR_H__

