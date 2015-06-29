
#include "Acupoint_Logic_Cl.h"
#include "Acupoint_System/Acupoint_Mgr_Cl.h"

#include "Game_Interface/game_content_interface.h"
#include "Character_System/Player.h"
#include "Character_System/Player_Logic_Cl.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Acupoint_System/Acupoint_Config_Mgr.h"
#include "common/GameDefine.h"
namespace Game_Data
{
    Acupoint_Logic* Acupoint_Logic::instance_ = NULL;
    Acupoint_Logic::Acupoint_Logic()
    {

    }

    Acupoint_Logic::~Acupoint_Logic()
    {

    }

    Acupoint_Logic* Acupoint_Logic::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Acupoint_Logic;
        }

        return instance_;
    }

    void Acupoint_Logic::load_acupoint()
    {
        std::vector<uint64> para;
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_load_acupoint", para);
    }

    bool Acupoint_Logic::open_acupoint(int type)
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return false;
        }

        if (type < 0 || type >= VEIN_COUNT_MAX)
        {
            return false;
        }

        Game_Data::vein_config* config_vein = ACUPOINT_CONFIG_MGR::instance()->get_vein_config(type);
        if (!config_vein)
        {
            return false;
        }

        int pos = 0;
        int level = 0;
        Game_Data::acupoint_config* config_acupoint = NULL;
        Game_Data::Acupoint* acupoint = ACUPOINT_MGR::instance()->get_acupoint(type);
        if (acupoint)
        {
            if (acupoint->pos_ == (ACUPOINT_POS_MAX-1))
            {
                if (acupoint->level_ == (VEIN_LEVEL_MAX-1))
                {
                    return false;
                }

                if (config_vein->level_data_[acupoint->level_+1].open_level_ > player->get_character_level())
                {
                    const char* str = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(TIPS_OPEN_NEXT_LEVEL);
                    //Game_Utils::instance()->show_alert(CCString::createWithFormat(str,config_vein->level_data_[acupoint->level_+1].open_level_)->getCString());
                    return false;
                } 

                level = acupoint->level_+1;
            }
            else
            {
                level = acupoint->level_;
                pos = acupoint->pos_+1;
            }
        }
        else
        { 
            if (config_vein->level_data_[0].open_level_ > player->get_character_level())
            {   
                const char* str = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(TIPS_OPEN_FOR_LEVEL);
                //Game_Utils::instance()->show_alert(CCString::createWithFormat(str,config_vein->level_data_[0].open_level_)->getCString());
                return false;
            }
        }

        config_acupoint = ACUPOINT_CONFIG_MGR::instance()->get_acupoint_config(type,pos);
        if (!config_acupoint)
        {
            return false;
        }

        int prestige_cost = config_acupoint->level_data_[level].prestige_cost_;
        if (prestige_cost > player->get_prestige())
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(TIPS_LACK_REPUTATION);
            return false;
        }

        int gold_cost = config_acupoint->level_data_[level].gold_cost_;
        if (gold_cost > player->get_gold())
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_GOLD_COIN);
            return false;
        }

        std::vector<uint64> para;
        para.push_back(type);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_open_acupoint", para);
        return true;
    }
}

