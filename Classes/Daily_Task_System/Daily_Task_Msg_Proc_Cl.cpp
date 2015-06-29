
#include "Daily_Task_Msg_Proc_Cl.h"

#include "Network_Common/NetManager.h"
#include "Network_Common/message.h"
#include "Network_Common/message_coder.h"
#include "Network_Common/message_stream.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_response.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"

#include "Item_System/Item_Desc_Config_Mgr.h"

#include "Daily_Task_System/Daily_Task_Mgr_Cl.h"
#include "Daily_Task_System/Daily_Task_Config_Mgr.h"

#include "Common/Utils.h"
#include "Common/GameDefine.h"

Daily_Task_Msg_Proc* Daily_Task_Msg_Proc::instance_ = 0;
Daily_Task_Msg_Proc::Daily_Task_Msg_Proc()
{

}

Daily_Task_Msg_Proc::~Daily_Task_Msg_Proc()
{

}

Daily_Task_Msg_Proc* Daily_Task_Msg_Proc::instance()
{
    if(NULL == instance_)
        instance_ = new Daily_Task_Msg_Proc;

    return instance_;
}

bool Daily_Task_Msg_Proc::send_load_daily_task(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_LOAD_DAILY_TASK;
    CNetManager::GetMe()->send_msg( body_ms );
    cout << "load daily_task request!----------------------------------"<< endl;
    return true;
}

bool Daily_Task_Msg_Proc::send_drop_daily_task(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_DROP_DAILY_TASK;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Daily_Task_Msg_Proc::send_submit_daily_task(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_SUBMIT_DAILY_TASK;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Daily_Task_Msg_Proc::send_refresh_daily_task_star_level(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_REFRESH_DAILY_TASK_STAR_LEVEL;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Daily_Task_Msg_Proc::send_set_daily_task_star_level_max(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_SET_DAILY_TASK_STAR_LEVEL_MAX;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Daily_Task_Msg_Proc::send_token_complete_daily_task(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_TOKEN_COMPLETE_DAILY_TASK;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Daily_Task_Msg_Proc::send_get_daily_task_gift_one(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_GET_DAILY_TASK_GIFT_ONE;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Daily_Task_Msg_Proc::send_get_daily_task_gift_two(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_GET_DAILY_TASK_GIFT_TWO;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Daily_Task_Msg_Proc::send_get_daily_task_gift_three(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_GET_DAILY_TASK_GIFT_THREE;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Daily_Task_Msg_Proc::on_load_daily_task(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        cout << "load daily_task error!----------------------------------"<< endl;
        return false;
    }

    DAILY_TASK_MGR::instance()->load_daily_task(body_ms);

    cout << "load daily_task finish!----------------------------------"<< endl;
    return true;
}

bool Daily_Task_Msg_Proc::on_drop_daily_task(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int task_base_id = 0;
    int star_level = 0;
    int got_time = 0;
    body_ms >> task_base_id;
    body_ms >> star_level;
    body_ms >> got_time;

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    Game_Data::daily_task& data = DAILY_TASK_MGR::instance()->get_daily_task();
    if (data.exec_count_ == DAILY_TASK_COUNT_MAX)
    {
        data.task_base_id_ = 0;
        data.star_level_ = 0;
        data.progress_ = 0;
    } 
    else
    {
        data.task_base_id_ = task_base_id;
        data.star_level_ = star_level;
        data.progress_ = 0;
        data.exec_count_ += 1;
        data.got_time_ = got_time;
    }

    Game_Logic::Game_Event_Response::instance()->on_update_daily_task(player_id);
    return true;
}

bool Daily_Task_Msg_Proc::on_submit_daily_task(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int task_base_id = 0;
    int star_level = 0;
    int got_time = 0;
    body_ms >> task_base_id;
    body_ms >> star_level;
    body_ms >> got_time;

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    Game_Data::daily_task& data = DAILY_TASK_MGR::instance()->get_daily_task();
    if (data.exec_count_ == DAILY_TASK_COUNT_MAX)
    {
        data.task_base_id_ = 0;
        data.star_level_ = 0;
        data.progress_ = 0;
    } 
    else
    {
        data.task_base_id_ = task_base_id;
        data.star_level_ = star_level;
        data.progress_ = 0;
        data.complete_count_ += 1;
        data.exec_count_ += 1;
        data.got_time_ = got_time;
    }

    Game_Logic::Game_Event_Response::instance()->on_update_daily_task(player_id);
    return true;
}

bool Daily_Task_Msg_Proc::on_refresh_daily_task_star_level(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int star_level = 0;
    body_ms >> star_level;

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    Game_Data::daily_task& data = DAILY_TASK_MGR::instance()->get_daily_task();
    data.star_level_ = star_level;

    Game_Logic::Game_Event_Response::instance()->on_update_daily_task(player_id);
    return true;
}

bool Daily_Task_Msg_Proc::on_set_daily_task_star_level_max(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int star_level = 0;
    body_ms >> star_level;

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    Game_Data::daily_task& data = DAILY_TASK_MGR::instance()->get_daily_task();
    data.star_level_ = star_level;

    Game_Logic::Game_Event_Response::instance()->on_update_daily_task(player_id);
    return true;
}

bool Daily_Task_Msg_Proc::on_token_complete_daily_task(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int task_base_id = 0;
    int star_level = 0;
    int got_time = 0;
    body_ms >> task_base_id;
    body_ms >> star_level;
    body_ms >> got_time;

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    Game_Data::daily_task& data = DAILY_TASK_MGR::instance()->get_daily_task();
    if (data.exec_count_ == DAILY_TASK_COUNT_MAX)
    {
        data.task_base_id_ = 0;
        data.star_level_ = 0;
        data.progress_ = 0;
    } 
    else
    {
        data.task_base_id_ = task_base_id;
        data.star_level_ = star_level;
        data.progress_ = 0;
        data.complete_count_ += 1;
        data.exec_count_ += 1;
        data.got_time_ = got_time;
    }

    Game_Logic::Game_Event_Response::instance()->on_update_daily_task(player_id);
    return true;
}

bool Daily_Task_Msg_Proc::on_get_daily_task_gift_one(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    Game_Data::daily_task& data = DAILY_TASK_MGR::instance()->get_daily_task();
    data.got_flag_[Game_Data::DTGT_ONE] = 1;

    Game_Logic::Game_Event_Response::instance()->on_update_daily_task(player_id);

    Game_Data::Item_Config* item_config = ITEM_CONFIG_MGR::instance()->get_item_config(DAILY_TASK_GIFT_ONE_ITEM_ID);
    if (item_config)
    {
        const char* format = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_GAIN_INFO);
        const char* name = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(item_config->name);
        const char* item = CCString::createWithFormat(format,name,1)->getCString();
        const char* head = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_U_GAIN);
        //Game_Utils::instance()->show_alert(CCString::createWithFormat("%s%s",head,item)->getCString());
    }

    return true;
}

bool Daily_Task_Msg_Proc::on_get_daily_task_gift_two(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    Game_Data::daily_task& data = DAILY_TASK_MGR::instance()->get_daily_task();
    data.got_flag_[Game_Data::DTGT_TWO] = 1;

    Game_Logic::Game_Event_Response::instance()->on_update_daily_task(player_id);

    Game_Data::Item_Config* item_config = ITEM_CONFIG_MGR::instance()->get_item_config(DAILY_TASK_GIFT_TWO_ITEM_ID);
    if (item_config)
    {
        const char* format = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_GAIN_INFO);
        const char* name = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(item_config->name);
        const char* item = CCString::createWithFormat(format,name,1)->getCString();
        const char* head = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_U_GAIN);
       // Game_Utils::instance()->show_alert(CCString::createWithFormat("%s%s",head,item)->getCString());
    }

    return true;
}

bool Daily_Task_Msg_Proc::on_get_daily_task_gift_three(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    Game_Data::daily_task& data = DAILY_TASK_MGR::instance()->get_daily_task();
    data.got_flag_[Game_Data::DTGT_THREE] = 1;

    Game_Logic::Game_Event_Response::instance()->on_update_daily_task(player_id);

    Game_Data::Item_Config* item_config = ITEM_CONFIG_MGR::instance()->get_item_config(DAILY_TASK_GIFT_THREE_ITEM_ID);
    if (item_config)
    {
        const char* format = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_GAIN_INFO);
        const char* name = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(item_config->name);
        const char* item = CCString::createWithFormat(format,name,1)->getCString();
        const char* head = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_U_GAIN);
        //Game_Utils::instance()->show_alert(CCString::createWithFormat("%s%s",head,item)->getCString());
    }

    return true;
}

bool Daily_Task_Msg_Proc::on_update_daily_task_progress(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int progress = 0;
    body_ms >> progress;

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    Game_Data::daily_task& data = DAILY_TASK_MGR::instance()->get_daily_task();
    data.progress_ = progress;

    Game_Logic::Game_Event_Response::instance()->on_update_daily_task(player_id);
    return true;
}