
#include "Player_Logic_Cl.h"
#include "Game_Interface/game_content_interface.h"
#include "Character_System/Player.h"
#include "Character_System/Player_Config_Data.h"
#include "Character_System/Player_Msg_Proc_Cl.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Item_System/Item_Mgr_Cl.h"

#include "Common/GameDefine.h"

//#include "Actor_Mgr.h"
//#include "Actor.h"
//#include "Game_Utils.h"

namespace Game_Data
{
    Player_Logic* Player_Logic::instance_ = NULL;
    Player_Logic::Player_Logic()
    {
        check_x = 400;
        check_y = 200;
        start_update();
    }

    Player_Logic::~Player_Logic()
    {

    }

    Player_Logic* Player_Logic::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Player_Logic;
        }

        return instance_;
    }

    void Player_Logic::start_update()
    {
        //m_pScheduler->scheduleSelector(schedule_selector(Player_Logic::update), this, 1.0f, kCCRepeatForever, 0.f, false);	
    }

    void Player_Logic::update(float delta)
    {
        player_move();
    }

    void Player_Logic::get_main_city_player()
    {
        std::vector<uint64> para;
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_get_main_city_player", para);
    }

    void Player_Logic::get_player_info()
    {
        std::vector<uint64> para;
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_get_player_info", para);
    }

    void Player_Logic::player_move()
    {
        //if (!Game_Utils::instance()->is_in_city())
        //{
        //    return;
        //}

        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return;
        }

        //UI::Actor* actor = Game_Utils::instance()->get_primary_actor();
        //if (!actor)
        //{
        //    return;
        //}

        float x = 0;
        float y = 0;
        //actor->get_logic_postion(x,y);
        if ((int)x == check_x && (int)y == check_y)
        {
            return;
        }

        check_x = (int)x;
        check_y = (int)y;

        std::vector<uint64> para;
        para.push_back((uint64)x);
        para.push_back((uint64)y);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_player_move", para);
    }

    void Player_Logic::send_chat_msg(const char* chat)
    {
        int character_id = Account_Data_Mgr::instance()->get_current_role_id();
        Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(character_id));
        if (!player)
        {
            return;
        }

        std::vector<uint64> para;
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_chat_msg", para , chat ,strlen(chat));
    }

	void Player_Logic::send_chat_msg(int channel, const char* receiver_name, const char* chat)
	{
		int character_id = Account_Data_Mgr::instance()->get_current_role_id();
        Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(character_id));
        if (!player)
        {
            return;
        }
		Player_Msg_Proc::send_chat_msg(channel, receiver_name, chat);
	}
	/******************************* dely *******************************/
	void Player_Logic::send_chat_msg_all(int channel, const char* receiver_name, const char* chat)
	{
		int character_id = Account_Data_Mgr::instance()->get_current_role_id();
		Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(character_id));
		if (!player)
		{
			return;
		}
		Player_Msg_Proc::send_chat_all_msg(channel, receiver_name, chat);
	}

	void Player_Logic::send_chat_msg_private(int channel, const char* receiver_name, const char* chat)
	{
		int character_id = Account_Data_Mgr::instance()->get_current_role_id();
		Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(character_id));
		if (!player)
		{
			return;
		}
		Player_Msg_Proc::send_chat_private_msg(channel, receiver_name, chat);
	}

	void Player_Logic::send_chat_msg_team(int channel, const char* receiver_name, const char* chat)
	{
		int character_id = Account_Data_Mgr::instance()->get_current_role_id();
		Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(character_id));
		if (!player)
		{
			return;
		}
		Player_Msg_Proc::send_chat_team_msg(channel, receiver_name, chat);
	}

	void Player_Logic::send_chat_msg_friend(int channel, const char* receiver_name, const char* chat)
	{
		int character_id = Account_Data_Mgr::instance()->get_current_role_id();
		Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(character_id));
		if (!player)
		{
			return;
		}
		Player_Msg_Proc::send_chat_friend_msg(channel, receiver_name, chat);
	}

	void Player_Logic::send_chat_msg_faction(int channel, const char* receiver_name, const char* chat)
	{
		int character_id = Account_Data_Mgr::instance()->get_current_role_id();
		Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(character_id));
		if (!player)
		{
			return;
		}
		Player_Msg_Proc::send_chat_faction_msg(channel, receiver_name, chat);
	}

	void Player_Logic::send_chat_msg_world(int channel, const char* receiver_name, const char* chat)
	{
		int character_id = Account_Data_Mgr::instance()->get_current_role_id();
		Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(character_id));
		if (!player)
		{
			return;
		}
		Player_Msg_Proc::send_chat_world_msg(channel, receiver_name, chat);
	}
	/******************************* dely *******************************/

    void Player_Logic::player_buy_energy()
    {
        int character_id = Account_Data_Mgr::instance()->get_current_role_id();
        Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(character_id));
        if (!player)
        {
            return;
        }

        if (player->get_buy_energy_count() >= PLAYER_BUY_ENERGY_MAX_COUNT)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(BUY_ENERGY_COUNT_LIMIT);
            return;
        }

        if (player->get_token() < player->get_buy_energy_cost())
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_GOLD_INGOT);
            return;
        }

        std::vector<uint64> para;
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_player_buy_energy", para);
    }

    void Player_Logic::player_callup_deputy_general(int character_id)
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        if (player_id == character_id)
        {
            return;
        }

        Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return;
        }

        Character* character = CHARACTER_MGR::instance()->get_character(character_id);
        if (!character)
        {
            return;
        }

        if (character_id == player->get_fight_general_id())
        {
            std::vector<uint64> para;
            Game_Logic::Game_Content_Interface::instance()->exec_interface("send_deputy_general_cancel_fight", para);
        } 
        else
        {
            std::vector<uint64> para;
            para.push_back(character_id);
            Game_Logic::Game_Content_Interface::instance()->exec_interface("send_deputy_general_fight", para);
        }
    }

    void Player_Logic::player_quality_up(int character_id)
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return;
        }

        Character* character = CHARACTER_MGR::instance()->get_character(character_id);
        if (!player)
        {
            return;
        }    

        if(character->get_character_quality() >= Game_Data::QT_ORANGE)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(QUALITY_MAX_LIMIT);
            return;
        }

        if (ITEM_MGR::instance()->check_quality_upgrade_need_material(player,Game_Data::QMT_ROLE,character->get_character_quality()) == false)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_MATERIAL);
            return;
        }

        std::vector<uint64> para;
        para.push_back(character_id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_player_quality_up", para);
    }

    bool Player_Logic::check_bag_room(int player_id,game_element_list_t& ele_list)
    {
        Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return false;
        }

        int need_bag_count = 0;
        vector<uint> para;
        Game_Data::game_element_list_t::iterator itg;
        for( itg = ele_list.begin(); itg != ele_list.end(); ++ itg)
        {
            para.clear();
            Game_Data::Game_Element& element = (*itg);
            if(strcmp(element.get_command(),"item") == 0 || strcmp(element.get_command(),"awarditem") == 0)
            {
                
                element.get_para_list_in_vector(para);
                if(para.size() > 1)
                {
                    int item_base_id = para[0];
                    int count = para[1];
                    calc_need_bag_room(player,item_base_id,count,need_bag_count);
                }
            }
            else if (strcmp(element.get_command(),"random_award_one_bag") == 0 || 
                strcmp(element.get_command(),"random_award_one_book_bag") == 0)
            {
                need_bag_count += 1;
            }
        }

        bool is_bag_full = true;
        if (need_bag_count > 0)
        {
            int empty = 0;
            Item_Container_Map& container_map = player->get_bag_item_container_map();
            Item_Container* container = NULL;
            Item_Container_Map_Iter iter = container_map.begin();
            for (;iter != container_map.end();++iter)
            {
                container = iter->second;
                if (container && container->item_id == 0)
                {
                    ++empty;
                    if (empty == need_bag_count)
                    {
                        is_bag_full = false;
                        break;
                    }
                }
            }

            if (is_bag_full)
            {
                return false;
            }
        }

        return true;
    }

    bool Player_Logic::check_bag_room(int player_id,int item_base_id,int count)
    {
        Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return false;
        }

        int need_bag_count = 0;
        calc_need_bag_room(player,item_base_id,count,need_bag_count);

        bool is_bag_full = true;
        if (need_bag_count > 0)
        {
            int empty = 0;
            Item_Container_Map& container_map = player->get_bag_item_container_map();
            Item_Container* container = NULL;
            Item_Container_Map_Iter iter = container_map.begin();
            for (;iter != container_map.end();++iter)
            {
                container = iter->second;
                if (container && container->item_id == 0)
                {
                    ++empty;
                    if (empty == need_bag_count)
                    {
                        is_bag_full = false;
                        break;
                    }
                }
            }

            if (is_bag_full)
            {
                return false;
            }
        }

        return true;
    }

    bool Player_Logic::check_can_use(int player_id,game_element_list_t& ele_list)
    {
        Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return false;
        }

        vector<uint> para;
        Game_Data::game_element_list_t::iterator itg;
        for( itg = ele_list.begin(); itg != ele_list.end(); ++ itg)
        {
            para.clear();
            Game_Data::Game_Element& element = (*itg);
            if(strcmp(element.get_command(),"award_general_exp") == 0)
            {
                DeputyGeneral* general = player->get_fight_general();
                if (general)
                {
                    if (general->get_character_level() >= MAX_LEVEL)
                    {
                        DICTIONARY_CONFIG_MGR::instance()->show_alert(ROLE_REACH_LEVEL_LIMIT);
                        return false;
                    }
                }
                else
                {
                    DICTIONARY_CONFIG_MGR::instance()->show_alert(GENERAL_USE_EXP_ITEM);
                    return false;
                }
            }
            else if (strcmp(element.get_command(),"award_deputy_general") == 0)
            {
                if (player->get_deputy_general_count() > 2)
                {
                    DICTIONARY_CONFIG_MGR::instance()->show_alert(GENERAL_FULL);
                    return false;
                }
            }
        }

        return true;
    }

    void Player_Logic::calc_need_bag_room(Player* player,int item_base_id,int count,int& need_bag_count)
    {
        Item_Config* config = ITEM_CONFIG_MGR::instance()->get_item_config(item_base_id);
        if (config)
        {
            if (config->type == IT_EQUIPMENT_DEPOT)
            {
                Equipment_Depot_Config* equipment_depot_config = reinterpret_cast<Equipment_Depot_Config*>(config);
                config = ITEM_CONFIG_MGR::instance()->get_item_config(equipment_depot_config->item_base_id);
                if (config->type == IT_EQUIPMENT || config->type == IT_BOOK)
                {
                    need_bag_count += count;
                } 
            }
            else if (config->type == IT_EQUIPMENT || config->type == IT_BOOK)
            {
                need_bag_count += count;
            }
            else if (config->type == IT_USABLE_ITEM || config->type == IT_MATERIAL_ITEM || 
                config->type == IT_QUEST_ITEM || config->type == IT_GIFT_ITEM ||
                config->type == Game_Data::IT_GEM)
            {
                Item_Container* pile_container = player->get_bag_can_pile_item_container(config);
                if (pile_container == NULL || (pile_container->item_count + count) > config->pile_count)
                {
                    need_bag_count += 1;
                }
            }
        }
    }
}

