
#include "Cool_Time_Logic_Cl.h"
#include "Cool_Time_System/Cool_Time_Mgr_Cl.h"

#include "Game_Interface/game_content_interface.h"
#include "Character_System/Player.h"
#include "Character_System/Player_Logic_Cl.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Cool_Time_System/Cool_Time_Config_Mgr.h"

#include "Common/GameDefine.h"

namespace Game_Data
{
    Cool_Time_Logic* Cool_Time_Logic::instance_ = NULL;
    Cool_Time_Logic::Cool_Time_Logic()
    {

    }

    Cool_Time_Logic::~Cool_Time_Logic()
    {

    }

    Cool_Time_Logic* Cool_Time_Logic::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Cool_Time_Logic;
        }

        return instance_;
    }

    void Cool_Time_Logic::load_cool_time()
    {
        std::vector<uint64> para;
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_load_cool_time", para);
    }

    bool Cool_Time_Logic::clean_cool_time(int type)
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return false;
        }

        if (type < 0 || type >= CTT_MAX)
        {
            return false;
        }

        Game_Data::Cool_Time* cool_time = COOL_TIME_MGR::instance()->get_cool_time(type);
        if (!cool_time)
        {
            return false;
        }

        int cost = COOL_TIME_MGR::instance()->get_clean_cool_time_cost(cool_time);
        if (cost > player->get_token())
        {
            DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_GOLD_INGOT);
            return false;
        }

        std::vector<uint64> para;
        para.push_back(type);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_clean_cool_time", para);
        return true;
    }
}

