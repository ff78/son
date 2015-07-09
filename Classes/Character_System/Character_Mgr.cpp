
#ifdef GAME_SERVER
#include "player_manager.h"
#include "Login_Reward_System/Login_Reward_Mgr_Sv.h"
#include "Daily_Task_System/Daily_Task_Mgr_Sv.h"
#include "Activity_System/Activity_Record_Mgr_Sv.h"
#endif // GAME_SEVER

#include "Player.h"
//#include "DeputyGeneral.h"
#include "FightNpc.h"
#include "Character.h"
#include "Character_Mgr.h"
#include "Common/Tool.h"
//#include "Skill_System/Buff/Buff_Mgr.h"
//#include "Fight_System/Fight_Config_Data.h"

#include <fstream>
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_response.h"
#include "Game_Interface/game_event_mgr.h"
#include "Game_Interface/Game_Element_Parse.h"



namespace Game_Data
{
    Character_Mgr* Character_Mgr::instance_ = NULL;
	Character_Mgr::Character_Mgr()
	{
		_other_player_map = new std::map<int, Player*>;
		_other_player_map->clear();
#ifdef YN_LINUX		
        pthread_mutex_init(&character_mutex_,NULL);
#endif
		m_last_general_id = 1000000000;
		//  2.2.1  与 3.2的区别。。3.2的CCBNode没有m_pScheduler
/*#ifdef GAME_CLIENT    
		m_pScheduler->scheduleSelector(schedule_selector(Character_Mgr::update), this, 0.1f, kCCRepeatForever, 0, false);
		m_pScheduler->scheduleSelector(schedule_selector(Character_Mgr::update_buff), this, 1, kCCRepeatForever, 0, false);
		m_pScheduler->scheduleSelector(schedule_selector(Character_Mgr::update_gangqi), this, 1, kCCRepeatForever, 0, false);
#endif*/
	}

	Character_Mgr::~Character_Mgr()
	{
		delete _other_player_map;
		_other_player_map = nullptr;
#ifdef YN_LINUX			
        pthread_mutex_destroy(&character_mutex_);
#endif
	}

    Character_Mgr* Character_Mgr::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Character_Mgr;
        }

        return instance_;
    }

    void Character_Mgr::release()
    {
        Character* character = NULL; 
        std::map<int, Character*>::iterator iter = character_map_.begin();
        for (;iter != character_map_.end();++iter)
        {      
            character = iter->second;
            if (character)
            {
                delete character;
            }
        }

        character_map_.clear();
        player_map_.clear();
		_other_player_map->clear();
    }

	void Character_Mgr::insert_character(Character* character)
	{
#ifdef YN_LINUX		
        Game_Logic::map_mutex m(&character_mutex_);
#endif
		if (!character)
		{
			return;
		}

		character_map_.insert(make_pair(character->get_database_character_id(), character));
        if (character->get_character_type() == Game_Logic::Game_Event::EVENT_TYPE_PLAYER)
        {
            Player* player = dynamic_cast<Player*>(character);
            if (player)
            {
                player_map_.insert(make_pair(player->get_database_character_id(), player));
            }
        }
	}
		
	void Character_Mgr::remove_character_from_list(int player_id)
	{
#ifdef YN_LINUX		
        Game_Logic::map_mutex m(&character_mutex_);
#endif
		std::map<int, Character*>::iterator it_character = character_map_.find(player_id);
		if (it_character == character_map_.end())
        {
			return;
        }

        if (it_character->second->get_character_type() == Game_Logic::Game_Event::EVENT_TYPE_PLAYER)
        {
            std::map<int, Player*>::iterator it_player = player_map_.find(player_id);
            if (it_player != player_map_.end())
            {
                player_map_.erase(it_player);
            }
        }

		if ( NULL != it_character->second )
		{
			delete it_character->second;
			it_character->second = NULL;
		}
		
		character_map_.erase(it_character);
     
	}

    void Character_Mgr::remove_character(int character_id)
    {
#ifdef YN_LINUX		
        Game_Logic::map_mutex m(&character_mutex_);
#endif
        Character* character = get_character(character_id);
        if (!character)
        {
            return;
        }

        std::map<int, Character*>::iterator it = character_map_.find(character_id);
        if (it == character_map_.end())
        {
            return;
        }

        character_map_.erase(it);
        if (character->get_character_type() == Game_Logic::Game_Event::EVENT_TYPE_PLAYER)
        {
            std::map<int, Player*>::iterator it = player_map_.find(character->get_database_character_id());
            if (it != player_map_.end())
            {
                player_map_.erase(it);
            }
        }

        delete character;
    }

	Character* Character_Mgr::get_character(int id)
	{
		std::map<int, Character*>::iterator it = character_map_.find(id);
		if ( it == character_map_.end() )
			return NULL;

		return (*it).second;
	}

	CommonNpc* Character_Mgr::get_common_npc_by_static_id(int static_id)
	{
		CommonNpc* common_npc = NULL;
		std::map<int, Character*>::iterator it = character_map_.begin();
		for (; it != character_map_.end(); it++)
		{
			Character* character = (*it).second;
			if ( character->get_character_type() == Game_Logic::Game_Event::EVENT_TYPE_NPC && character->get_static_character_id() == static_id)
			{
				common_npc = (CommonNpc*)character;
			}
		}

		return common_npc;
	}

#ifdef GAME_CLIENT
	void Character_Mgr::update(float delta)
	{
		std::map<int, Character*>::iterator it = character_map_.begin();
		for (; it != character_map_.end(); it++)
		{
			Character* character = (*it).second;
			if (character)
			{
				character->update(delta);
			}
		}
	}
#endif

	//void Character_Mgr::update_buff(float /*delta*/)
	//{
	//	std::map<int, Character*>::iterator it = character_map_.begin();
	//	for (; it != character_map_.end(); it++)
	//	{
	//		Character* character = (*it).second;
	//		for (int i = 0; i < character->get_buff_size(); i++)
	//		{
	//			Buff_Logic* buff_logic= character->get_buff_logic_by_index(i);
	//			if ( NULL == buff_logic )
	//				continue;
	//			
	//			int buff_id = buff_logic->GetBuffData(CBA_ID);
 //               Buff_Data* buff_data = BUFF_MGR::instance()->GetBuffData( buff_id );
	//			if ( NULL == buff_data )
	//				continue;
	//			
	//			int  config_last_time = buff_data->m_Attr[BA_LAST_TIME];
	//			int  buff_last_time   = buff_logic->GetBuffData(CBA_LAST_TIME);
	//			int  config_last_interval = buff_data->m_Attr[BA_LAST_INTERVAL];
	//			if ( buff_last_time > 0 )
	//			{
	//				if ( config_last_interval != 0 && (config_last_time - buff_last_time)%config_last_interval == 0 )
	//				{
	//					buff_logic->Active();
	//					buff_logic->SetBuffData(CBA_LAST_TIME, buff_last_time - 1);
	//				}
	//			}
	//			else
	//			{
	//				character->remove_buff( buff_id );
	//			}
	//		}
	//	}
	//}

	void Character_Mgr::update_gangqi(float /*delta*/)
	{
		std::map<int, Character*>::iterator it = character_map_.begin();
		for (; it != character_map_.end(); it++)
		{
			Character* character = (*it).second;
			if ( Game_Logic::Game_Event::EVENT_TYPE_PLAYER == character->get_character_type() || Game_Logic::Game_Event::EVENT_TYPE_MONSTER == character->get_character_type() )
			{
				if ( GetCurTime() - character->get_character_no_hurt_time() >= character->get_character_gp_behit_time()/1000 )
				{
					if ( character->get_character_cur_gp() < character->get_character_max_gp() )
					{
						int add_gp = character->get_character_gp_recover_speed();
						if ( character->get_character_cur_gp() + add_gp > character->get_character_max_gp() )
						{
							add_gp = character->get_character_max_gp() - character->get_character_cur_gp();
						}

						character->set_character_cur_gp(character->get_character_cur_gp() + add_gp);
					}
				}
			}
		}
	}

	int Character_Mgr::create_general_id(int role_id)
	{
#ifdef GAME_SERVER
        player_ptr player = PLAYER_MANAGER::instance()->find(role_id);
        if(player)
        {
            m_last_general_id = player->worker_->db()->get_last_deputy_general_id();
            if (m_last_general_id <= 0)
            {
                m_last_general_id = 1000000000;
            }
        }

        ++m_last_general_id;
#endif
        return m_last_general_id;
	}

//    DeputyGeneral* Character_Mgr::create_deputy_general(Player* player,int character_base_id,int character_type,int level)
//    {
//        DeputyGeneral* general = new DeputyGeneral;
//        general->set_owner(player);
//        general->set_database_character_id(create_general_id(player->get_database_character_id()));
//        general->set_character_type(character_type);
//        general->init_attr_data(character_base_id, level);
//        general->set_exp(0);
//
//        player->insert_deputy_general(general);
//        insert_character(general);
//
//        vector<uint64> para;
//        para.push_back(general->get_database_character_id());
//        Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_insert_deputy_general", para);
//
//        return general;
//    }

    void Character_Mgr::refresh_player_daily_data()
    {
#ifdef GAME_SERVER
        cute::date_time curTime;
        Player* player = NULL; 
        std::map<int, Player*>::iterator iter = player_map_.begin();
        for (;iter != player_map_.end();++iter)
        {      
            player = iter->second;
            if (player)
            {
                player->set_buy_energy_count(0);
                player->set_offline_fight_count(PLAYER_DAILY_OFFLINE_FIGHT_COUNT);
                player->set_buy_offline_fight_count(1);
                player->set_offline_fight_rank_reward_count(1);
				player->set_banks_exchange_count(0);
                player->refresh_shop_record();

                LOGIN_REWARD_MGR::instance()->update_daily_data((curTime.wday() == 1),player->get_database_character_id());
                DAILY_TASK_MGR::instance()->update_daily_data(player->get_database_character_id());
                ACTIVITY_RECORD_MGR::instance()->update_daily_data(player->get_database_character_id());
            }
        }
#endif // GAME_SERVER
    }

//    void Character_Mgr::save_deputy_general(int role_id)
//    {
//        Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(role_id));
//        if (!player)
//        {
//            return;
//        }
//
//        Deputy_General_Map& map_deputy_general = player->get_deputy_general();
//
//        DeputyGeneral* deputy_general = NULL;
//        Deputy_General_Map_Iter iter = map_deputy_general.begin();
//        for (;iter != map_deputy_general.end();++iter)
//        {
//            deputy_general = iter->second;
//            if (deputy_general)
//            {
//                vector<uint64> para;
//                para.push_back(deputy_general->get_database_character_id());
//                Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_deputy_general", para);
//            }
//
//        }
//    }
}