
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
#include "Item_Container_System/Item_Container_Mgr_Cl.h"
#include "Item_System/Item_Desc_Config_Mgr.h"

#include "cocos2d.h"

#include "Item_Msg_Proc_Cl.h"
#include "Item_Mgr_Cl.h"
#include "Common/Utils.h"

Item_Msg_Proc* Item_Msg_Proc::instance_ = 0;
Item_Msg_Proc::Item_Msg_Proc(){

}

Item_Msg_Proc::~Item_Msg_Proc(){

}

Item_Msg_Proc* Item_Msg_Proc::instance()
{
    if(NULL == instance_)
        instance_ = new Item_Msg_Proc;

    return instance_;
}

bool Item_Msg_Proc::send_load_item(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_LOAD_ITEM;
    CNetManager::GetMe()->send_msg( body_ms );
    cout << "load item request!----------------------------------"<< endl;
    return true;
}

bool Item_Msg_Proc::send_load_material_fragment(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_LOAD_MATERIAL_FRAGMENT;
    CNetManager::GetMe()->send_msg( body_ms );
    cout << "load material_fragment request!----------------------------------"<< endl;
    return true;
}

bool Item_Msg_Proc::send_load_book_fragment(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_LOAD_BOOK_FRAGMENT;
    CNetManager::GetMe()->send_msg( body_ms );
    cout << "load book_fragment request!----------------------------------"<< endl;
    return true;
}

bool Item_Msg_Proc::send_tidy_item(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_TIDY_ITEM;
    CNetManager::GetMe()->send_msg( body_ms );
    cout << "tidy item request!----------------------------------"<< endl;
    return true;
}

bool Item_Msg_Proc::send_equip_equipment(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 2)
    {
        return false;
    }

    int character_id = (int)para[0];
    int index = (int)para[1];
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_EQUIP_EQUIPMENT;
    body_ms << character_id;
    body_ms << index;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Item_Msg_Proc::send_take_off_equipmen(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 2)
    {
        return false;
    }

    int character_id = (int)para[0];
    int index = (int)para[1];
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_TAKE_OFF_EQUIPMENT;
    body_ms << character_id;
    body_ms << index;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Item_Msg_Proc::send_equip_book(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 3)
    {
        return false;
    }

    int character_id = (int)para[0];
    int index = (int)para[1];
    int pos = (int)para[2];
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_EQUIP_BOOK;
    body_ms << character_id;
    body_ms << index;
    body_ms << pos;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Item_Msg_Proc::send_take_off_book(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 2)
    {
        return false;
    }

    int character_id = (int)para[0];
    int index = (int)para[1];
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_TAKE_OFF_BOOK;
    body_ms << character_id;
    body_ms << index;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Item_Msg_Proc::send_equipment_level_up(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 1)
    {
        return false;
    }

    uint64 item_id = para[0];
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_EQUIPMENT_LEVEL_UP;
    body_ms << item_id;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Item_Msg_Proc::send_equipment_quality_up(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 1)
    {
        return false;
    }

    uint64 item_id = para[0];
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_EQUIPMENT_QUALITY_UP;
    body_ms << item_id;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Item_Msg_Proc::send_book_level_up(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 2)
    {
        return false;
    }

    uint64 item_id = para[0];
    int count = para.size() - 1;
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_BOOK_LEVEL_UP;
    body_ms << item_id;
    body_ms << count;
    for (int i = 0;i < count;++i)
    {
        body_ms << para[i + 1];
    }
    
    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Item_Msg_Proc::send_book_quality_up(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 1)
    {
        return false;
    }

    uint64 item_id = para[0];
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_BOOK_QUALITY_UP;
    body_ms << item_id;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Item_Msg_Proc::send_sell_item(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 2)
    {
        return false;
    }

    uint64 container_id = para[0];
    int sell_count = (int)para[1];
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_SELL_ITEM;
    body_ms << container_id;
    body_ms << sell_count;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Item_Msg_Proc::send_use_item(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 1)
    {
        return false;
    }

    uint64 container_id = para[0];
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_USE_ITEM;
    body_ms << container_id;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Item_Msg_Proc::send_compound_material_fragment(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 2)
    {
        return false;
    }

    int item_base_id = (int)para[0];
    int compound_count = (int)para[1];
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_COMPOUND_MATERIAL_FRAGMENT;
    body_ms << item_base_id;
    body_ms << compound_count;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Item_Msg_Proc::send_compound_book_fragment(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 2)
    {
        return false;
    }

    int item_base_id = (int)para[0];
    int compound_count = (int)para[1];
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_COMPOUND_BOOK_FRAGMENT;
    body_ms << item_base_id;
    body_ms << compound_count;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Item_Msg_Proc::send_set_on_gem(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 2)
    {
        return false;
    }

    int character_id = (int)para[0];
    uint64 container_id = para[1];
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_SET_ON_GEM;
    body_ms << character_id;
    body_ms << container_id;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Item_Msg_Proc::send_set_off_gem(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 2)
    {
        return false;
    }

    uint64 item_id = para[0];
    int gem_pos = (int)para[1];
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_SET_OFF_GEM;
    body_ms << item_id;
    body_ms << gem_pos;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Item_Msg_Proc::send_gem_level_up(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 2)
    {
        return false;
    }

    int gem_id = (int)para[0];
    int time = (int)para[1];
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_GEM_LEVEL_UP;
    body_ms << gem_id;
    body_ms << time;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Item_Msg_Proc::on_load_item(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        cout << "load item error!----------------------------------"<< endl;
        return false;
    }
    
    ITEM_MGR::instance()->load_item(player,body_ms);

    cout << "load item finish!----------------------------------"<< endl;
    return true;
}

bool Item_Msg_Proc::on_load_material_fragment(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        cout << "load material_fragment error!----------------------------------"<< endl;
        return false;
    }

    ITEM_MGR::instance()->load_material_fragment(player,body_ms);

    cout << "load material_fragment finish!----------------------------------"<< endl;
    return true;
}

bool Item_Msg_Proc::on_load_book_fragment(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        cout << "load book_fragment error!----------------------------------"<< endl;
        return false;
    }

    ITEM_MGR::instance()->load_book_fragment(player,body_ms);

    cout << "load book_fragment finish!----------------------------------"<< endl;
    return true;
}

bool Item_Msg_Proc::on_tidy_item(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ITEM_CONTAINER_MGR::instance()->tidy_item_container(player,body_ms);
    cout << "tidy item finish!----------------------------------"<< endl;

    return true;
}

bool Item_Msg_Proc::on_equip_equipment(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ITEM_MGR::instance()->equip_equipment(player,body_ms);


    return true;
}

bool Item_Msg_Proc::on_take_off_equipmen(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ITEM_MGR::instance()->take_off_equipmen(player,body_ms);

    return true;
}

bool Item_Msg_Proc::on_equip_book(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ITEM_MGR::instance()->equip_book(player,body_ms);

    return true;
}

bool Item_Msg_Proc::on_take_off_book(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ITEM_MGR::instance()->take_off_book(player,body_ms);

    return true;
}

bool Item_Msg_Proc::on_equipment_level_up(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ITEM_MGR::instance()->equipment_level_up(player,body_ms);

    return true;
}

bool Item_Msg_Proc::on_equipment_quality_up(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ITEM_MGR::instance()->equipment_quality_up(player,body_ms);

    return true;
}

bool Item_Msg_Proc::on_book_level_up(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ITEM_MGR::instance()->book_level_up(player,body_ms);

    return true;
}

bool Item_Msg_Proc::on_book_quality_up(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ITEM_MGR::instance()->book_quality_up(player,body_ms);

    return true;
}

bool Item_Msg_Proc::on_sell_item(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ITEM_MGR::instance()->sell_item(player,body_ms);
   
    return true;
}

bool Item_Msg_Proc::on_use_item(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ITEM_MGR::instance()->use_item(player,body_ms);

    return true;
}

bool Item_Msg_Proc::on_compound_material_fragment(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ITEM_MGR::instance()->compound_material_fragment(player,body_ms);

    return true;
}

bool Item_Msg_Proc::on_compound_book_fragment(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ITEM_MGR::instance()->compound_book_fragment(player,body_ms);

    return true;
}

bool Item_Msg_Proc::on_set_on_gem(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ITEM_MGR::instance()->set_on_gem(player,body_ms);

    return true;
}

bool Item_Msg_Proc::on_set_off_gem(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ITEM_MGR::instance()->set_off_gem(player,body_ms);

    return true;
}

bool Item_Msg_Proc::on_gem_level_up(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ITEM_MGR::instance()->item_client_show(player,body_ms);

    Game_Logic::Game_Event_Response::instance()->on_update_gem_level_up(player_id);

    //DICTIONARY_CONFIG_MGR::instance()->show_alert(COMBINE_SUCCESS);

    //Game_Utils::instance()->add_effect_to_scene("3015");//合成成功
    return true;
}

bool Item_Msg_Proc::on_create_item(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ITEM_MGR::instance()->create_item(player,body_ms);

    return true;
}

bool Item_Msg_Proc::on_create_material_fragment(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ITEM_MGR::instance()->create_material_fragment(player,body_ms);

    return true;
}

bool Item_Msg_Proc::on_create_book_fragment(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ITEM_MGR::instance()->create_book_fragment(player,body_ms);

    return true;
}

bool Item_Msg_Proc::on_item_client_show(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    ITEM_MGR::instance()->item_client_show(player,body_ms);

    return true;
}