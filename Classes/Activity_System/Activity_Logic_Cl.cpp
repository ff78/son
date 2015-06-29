

#include "Activity_Logic_Cl.h"

#include "Game_Interface/game_content_interface.h"
#include "Event_System/event_system_data_mgr.h"
#include "Character_System/Player.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Activity_System/Activity_Config_Mgr.h"
#include "Activity_System/Activity_Record_Mgr_Cl.h"
#include "Play_System/Formula_Function_Instance.h"

#include "Common/GameDefine.h"

#include "UI_Interface/UI_ModalDialogue_Layer.h"

namespace Game_Data
{
    Activity_Logic* Activity_Logic::instance_ = NULL;
    Activity_Logic::Activity_Logic()
    {

    }

    Activity_Logic::~Activity_Logic()
    {

    }

    Activity_Logic* Activity_Logic::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Activity_Logic;
        }

        return instance_;
    }

    void Activity_Logic::activity_six_sect(int base_id)
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return;
        }

        if (ACTIVITY_CONFIG_MGR::instance()->get_activity_six_sect_type() == -1)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(UA_TIME_OUT);
            return;
        }

        Game_Data::activity_six_sect_config* activity_six_sect_config = ACTIVITY_CONFIG_MGR::instance()->get_activity_six_sect_config(base_id);
        if (!activity_six_sect_config)
        {
            return;
        }

        if (player->get_character_level() < activity_six_sect_config->get_level_limit())
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_ROLE_LEVEL);
            return;
        }

        int join_count = ACTIVITY_RECORD_MGR::instance()->get_six_sect_join_count(activity_six_sect_config->get_type());
        if (join_count >= activity_six_sect_config->get_join_count())
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(TODAY_CHALLENGE_TIMES_OVER);
            return;
        }

        vector<uint> param;
        Formula_Function_Instance::instance()->get_para_list_from_instance_data(activity_six_sect_config->get_instance_id(),
            "instance_attribute","began_content","energyconsume",param);
        if ( param.size() <= 0)
        {
            return; 
        }

        int need_energy = param[0];
        if (player->get_energy() < need_energy)
        { 
            DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_ENERGY);
            return;
        }

        vector<uint64> para;
        para.push_back(base_id);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_activity_six_sect", para);
    }

    bool Activity_Logic::check_activity(int activity_type)
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return false;
        }

        Game_Data::activity_config* activity_config = ACTIVITY_CONFIG_MGR::instance()->get_activity_config_by_type(activity_type);
        if (!activity_config)
        {
            return false;
        }

        if (player->get_character_level() < activity_config->get_level_limit())
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_ROLE_LEVEL);
            return false;
        }

        if (ACTIVITY_CONFIG_MGR::instance()->check_in_open_time(activity_type) == false)
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(UA_TIME_OUT);
            return false;
        }

        return true;
    }
}