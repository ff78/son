
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

#include "Cool_Time_System/Cool_Time_Config_Mgr.h"

#include "Cool_Time_Msg_Proc_Cl.h"
#include "Cool_Time_Mgr_Cl.h"
#include "Common/Utils.h"

Cool_Time_Msg_Proc* Cool_Time_Msg_Proc::instance_ = 0;
Cool_Time_Msg_Proc::Cool_Time_Msg_Proc(){

}

Cool_Time_Msg_Proc::~Cool_Time_Msg_Proc(){

}

Cool_Time_Msg_Proc* Cool_Time_Msg_Proc::instance()
{
    if(NULL == instance_)
        instance_ = new Cool_Time_Msg_Proc;

    return instance_;
}

bool Cool_Time_Msg_Proc::send_load_cool_time(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_LOAD_COOL_TIME;
    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Cool_Time_Msg_Proc::send_clean_cool_time(Game_Logic::Game_Interface& gm_interface)
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
    body_ms << C2S_CLEAN_COOL_TIME;
    body_ms << type;
    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Cool_Time_Msg_Proc::on_load_cool_time(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    COOL_TIME_MGR::instance()->load_cool_time(player,body_ms);
    return true;
}

bool Cool_Time_Msg_Proc::on_clean_cool_time(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    int type = 0;
    body_ms >> type;

    Game_Data::Cool_Time* cool_time = COOL_TIME_MGR::instance()->get_cool_time(type);
    if (cool_time)
    {
        COOL_TIME_MGR::instance()->clean_cool_time(cool_time);
    }

    Game_Logic::Game_Event_Response::instance()->on_update_fate(player_id);
    return true;
}

bool Cool_Time_Msg_Proc::on_create_cool_time(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    COOL_TIME_MGR::instance()->create_cool_time(player,body_ms);

    return true;
}