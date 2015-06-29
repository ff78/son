
#include "Daily_Task_Logic_Cl.h"

#include "Game_Interface/game_content_interface.h"
#include "Event_System/event_system_data_mgr.h"
#include "Character_System/Player.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Player_Logic_Cl.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Daily_Task_System/Daily_Task_Config_Mgr.h"
#include "Daily_Task_System/Daily_Task_Mgr_Cl.h"

#include "Common/GameDefine.h"

#include "UI_Interface/UI_ModalDialogue_Layer.h"

namespace Game_Data
{
    Daily_Task_Logic* Daily_Task_Logic::instance_ = NULL;
    Daily_Task_Logic::Daily_Task_Logic()
    {

    }

    Daily_Task_Logic::~Daily_Task_Logic()
    {

    }

    Daily_Task_Logic* Daily_Task_Logic::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Daily_Task_Logic;
        }

        return instance_;
    }

    void Daily_Task_Logic::load_daily_task()
    {
        vector<uint64> para;
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_load_daily_task", para);
    }

    void Daily_Task_Logic::op_daily_task()
    {
        Game_Data::daily_task& data = DAILY_TASK_MGR::instance()->get_daily_task();
        if (data.task_base_id_ == 0)
        {
            return;
        }

        Game_Data::daily_task_config* config = DAILY_TASK_CONFIG_MGR::instance()->get_daily_task_config(data.task_base_id_);
        if (!config)
        {
            return;
        }

        if (data.progress_ == config->count_)
        {
            submit_daily_task();
        }
        else
        {
            drop_daily_task();
        }
    }

    void Daily_Task_Logic::drop_daily_task()
    {
        vector<uint64> para;
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_drop_daily_task", para);
    }

    void Daily_Task_Logic::submit_daily_task()
    {
        vector<uint64> para;
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_submit_daily_task", para);
    }

    void Daily_Task_Logic::refresh_daily_task_star_level()
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return;
        }

        Game_Data::daily_task& data = DAILY_TASK_MGR::instance()->get_daily_task();
        if (data.task_base_id_ == 0)
        {
            return;
        }

        if (data.star_level_ == STAR_LEVEL_MAX)
        {
            return;
        }

        if (player->get_token() < REFRESH_DAILY_TASK_STAR_LEVEL_COST)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_GOLD_INGOT);
            return;
        }

        vector<uint64> para;
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_refresh_daily_task_star_level", para);
    }

    void Daily_Task_Logic::set_daily_task_star_level_max()
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return;
        }

        Game_Data::daily_task& data = DAILY_TASK_MGR::instance()->get_daily_task();
        if (data.task_base_id_ == 0)
        {
            return;
        }

        if (data.star_level_ == STAR_LEVEL_MAX)
        {
            return;
        }

        if (player->get_token() < SET_DAILY_TASK_STAR_LEVEL_MAX_COST)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_GOLD_INGOT);
            return;
        }

        vector<uint64> para;
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_set_daily_task_star_level_max", para);
    }

    void Daily_Task_Logic::token_complete_daily_task()
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return;
        }

        Game_Data::daily_task& data = DAILY_TASK_MGR::instance()->get_daily_task();
        if (data.task_base_id_ == 0)
        {
            return;
        }

        Game_Data::daily_task_config* config = DAILY_TASK_CONFIG_MGR::instance()->get_daily_task_config(data.task_base_id_);
        if (!config)
        {
            return;
        }

        if (data.progress_ == config->count_)
        {
            return;
        }

        if (player->get_token() < TOKEN_COMPLETE_DAILY_TASK_COST)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_GOLD_INGOT);
            return;
        }

        vector<uint64> para;
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_token_complete_daily_task", para);
    }

    void Daily_Task_Logic::get_daily_task_gift_one()
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return;
        }

        Game_Data::daily_task& data = DAILY_TASK_MGR::instance()->get_daily_task();
        if (data.complete_count_ < GET_DAILY_TASK_GIFT_ONE_NEED_COMPLETE_COUNT)
        {
            return;
        }

        if (data.got_flag_[Game_Data::DTGT_ONE] == 1)
        {
            return;
        }

        if (PLAYER_LOGIC::instance()->check_bag_room(player_id,DAILY_TASK_GIFT_ONE_ITEM_ID,1) == false)
        {
            DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ECR_BAG_FULL);
            return;
        }

        vector<uint64> para;
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_get_daily_task_gift_one", para);
    }

    void Daily_Task_Logic::get_daily_task_gift_two()
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return;
        }

        Game_Data::daily_task& data = DAILY_TASK_MGR::instance()->get_daily_task();
        if (data.complete_count_ < GET_DAILY_TASK_GIFT_TWO_NEED_COMPLETE_COUNT)
        {
            return;
        }

        if (data.got_flag_[Game_Data::DTGT_TWO] == 1)
        {
            return;
        }

        if (PLAYER_LOGIC::instance()->check_bag_room(player_id,DAILY_TASK_GIFT_TWO_ITEM_ID,1) == false)
        {
            DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ECR_BAG_FULL);
            return;
        }

        vector<uint64> para;
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_get_daily_task_gift_two", para);
    }

    void Daily_Task_Logic::get_daily_task_gift_three()
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return;
        }

        Game_Data::daily_task& data = DAILY_TASK_MGR::instance()->get_daily_task();
        if (data.complete_count_ < GET_DAILY_TASK_GIFT_THREE_NEED_COMPLETE_COUNT)
        {
            return;
        }

        if (data.got_flag_[Game_Data::DTGT_THREE] == 1)
        {
            return;
        }

        if (PLAYER_LOGIC::instance()->check_bag_room(player_id,DAILY_TASK_GIFT_THREE_ITEM_ID,1) == false)
        {
            DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ECR_BAG_FULL);
            return;
        }

        vector<uint64> para;
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_get_daily_task_gift_three", para);
    }
}