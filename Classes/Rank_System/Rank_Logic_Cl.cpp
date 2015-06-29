
#include "Rank_Logic_Cl.h"
#include "Rank_System/Rank_Mgr_Cl.h"

#include "Game_Interface/game_content_interface.h"
#include "Character_System/Player.h"
#include "Character_System/Player_Logic_Cl.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"

namespace Game_Data
{
    Rank_Logic* Rank_Logic::instance_ = NULL;
    Rank_Logic::Rank_Logic()
    {

    }

    Rank_Logic::~Rank_Logic()
    {

    }

    Rank_Logic* Rank_Logic::instance()
    {
        if(instance_ == NULL)
        {
            instance_ = new Rank_Logic;
        }

        return instance_;
    }

    void Rank_Logic::load_rank()
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return;
        }

        std::vector<uint64> para;
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_load_rank", para);
    }

    void Rank_Logic::load_rank_role_level()
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return;
        }

        std::vector<uint64> para;
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_load_rank_role_level", para);
    }

    void Rank_Logic::load_rank_role_fighting_capacity()
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return;
        }

        std::vector<uint64> para;
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_load_rank_role_fighting_capacity", para);
    }
    void Rank_Logic::load_rank_role_have_gold()
    {
        int player_id = Account_Data_Mgr::instance()->get_current_role_id();
        Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
        if (!player)
        {
            return;
        }

        std::vector<uint64> para;
        Game_Logic::Game_Content_Interface::instance()->exec_interface("send_load_rank_role_have_gold", para);
    }
}

