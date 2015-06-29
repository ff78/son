
#include "Network_Common/message_stream.h"
#include "Network_Common/global_macros.h"
#include "Network_Common/message.h"
#include "Network_Common/NetManager.h"
#include "Game_Interface/Game_Element_Parse.h"
#include "UI_Interface/CocoStu_UI_Scene_Interface.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_response.h"
#include "Game_Interface/event_define.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"

#include "cocos2d.h"

#include "Common/GameDefine.h"

#include "Item_Container_Msg_Proc_Cl.h"
#include "Item_Container_Mgr_Cl.h"
#include "Common/Utils.h"

Item_Container_Msg_Proc* Item_Container_Msg_Proc::instance_ = 0;
Item_Container_Msg_Proc::Item_Container_Msg_Proc(){

}

Item_Container_Msg_Proc::~Item_Container_Msg_Proc(){

}

Item_Container_Msg_Proc* Item_Container_Msg_Proc::instance()
{
    if(NULL == instance_)
        instance_ = new Item_Container_Msg_Proc;

    return instance_;
}

bool Item_Container_Msg_Proc::send_load_item_container(Game_Logic::Game_Interface& gm_interface)
{
    if (ITEM_CONTAINER_MGR::instance()->is_load())
    {
        return false;
    }

    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_LOAD_ITEM_CONTAINER;
    CNetManager::GetMe()->send_msg( body_ms );
    cout << "load item_container request!----------------------------------"<< endl;
    return true;
}

bool Item_Container_Msg_Proc::send_add_item_container(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 1)
    {
        return false;
    }

    int bag_type = (int)para[0];

    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_ADD_ITEM_CONTAINER;
    body_ms << bag_type;
    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Item_Container_Msg_Proc::on_load_item_container(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        cout << "load item_container error!----------------------------------"<< endl;
        return false;
    }

    if (ITEM_CONTAINER_MGR::instance()->is_load())
    {
        return false;
    }
    
    ITEM_CONTAINER_MGR::instance()->load_item_container(player,body_ms);
    
    vector<uint64> para;
    para.push_back( player_id );
    Game_Logic::Game_Content_Interface::instance()->exec_interface("sendreqnpcquest",para);

    cout << "load item_container finish!----------------------------------"<< endl;
    return true;
}

bool Item_Container_Msg_Proc::on_add_item_container(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ITEM_CONTAINER_MGR::instance()->create_item_container(player,body_ms);

    return true;
}

bool Item_Container_Msg_Proc::on_update_item_container(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ITEM_CONTAINER_MGR::instance()->update_item_container(player,body_ms);

    return true;
}

bool Item_Container_Msg_Proc::add_item_container(int bag_type)
{
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    if (player->get_token() < ADD_ITEM_CONTAINER_COST)
    {
        DICTIONARY_CONFIG_MGR::instance()->show_alert(LACK_GOLD_INGOT);
        return false;
    }
    
    std::vector<uint64> para;
    para.push_back(bag_type);
    Game_Logic::Game_Content_Interface::instance()->exec_interface("send_add_item_container", para);
    return true;
}