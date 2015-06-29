
#include "Network_Common/message_stream.h"
#include "Network_Common/global_macros.h"
#include "Network_Common/message.h"
#include "Network_Common/NetManager.h"
#include "Game_Interface/Game_Element_Parse.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_response.h"
#include "Game_Interface/event_define.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Cool_Time_System/Cool_Time_Mgr_Cl.h"

#include "Acupoint_System/Acupoint_Config_Mgr.h"
#include "Common/Utils.h"

#include "Acupoint_Msg_Proc_Cl.h"
#include "Acupoint_Mgr_Cl.h"

Acupoint_Msg_Proc* Acupoint_Msg_Proc::instance_ = 0;
Acupoint_Msg_Proc::Acupoint_Msg_Proc(){

}

Acupoint_Msg_Proc::~Acupoint_Msg_Proc(){

}

Acupoint_Msg_Proc* Acupoint_Msg_Proc::instance()
{
    if(NULL == instance_)
        instance_ = new Acupoint_Msg_Proc;

    return instance_;
}

bool Acupoint_Msg_Proc::send_load_acupoint(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_LOAD_ACUPOINT;
    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Acupoint_Msg_Proc::send_open_acupoint(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 1)
    {
        return false;
    }

    int type = (int)para[0];
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_OPEN_ACUPOINT;
    body_ms << type;
    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Acupoint_Msg_Proc::on_load_acupoint(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ACUPOINT_MGR::instance()->load_acupoint(player,body_ms);
    return true;
}

bool Acupoint_Msg_Proc::on_open_acupoint(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ACUPOINT_MGR::instance()->open_acupoint(player,body_ms);
    Game_Data::Cool_Time* cool_time = COOL_TIME_MGR::instance()->get_cool_time(CTT_OPEN_ACUPOINT);
    if (cool_time)
    {
        COOL_TIME_MGR::instance()->add_length(cool_time);
    }

    Game_Logic::Game_Event_Response::instance()->on_update_fate(player_id);
    return true;
}

bool Acupoint_Msg_Proc::on_create_acupoint(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ACUPOINT_MGR::instance()->create_acupoint(player,body_ms);

    return true;
}