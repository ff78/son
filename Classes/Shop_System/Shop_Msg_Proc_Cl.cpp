
#include "Shop_Msg_Proc_Cl.h"

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
#include "Item_System/Item_Config_Mgr.h"
#include "Shop_System/Shop_Config_Mgr.h"
#include "Shop_System/Shoping_Record_Mgr_Cl.h"

#include "Common/GameDefine.h"
#include "Common/Utils.h"
Shop_Msg_Proc* Shop_Msg_Proc::instance_ = 0;
Shop_Msg_Proc::Shop_Msg_Proc()
{

}

Shop_Msg_Proc::~Shop_Msg_Proc()
{

}

Shop_Msg_Proc* Shop_Msg_Proc::instance()
{
    if(NULL == instance_)
        instance_ = new Shop_Msg_Proc;

    return instance_;
}

bool Shop_Msg_Proc::send_load_shoping_record(Game_Logic::Game_Interface& gm_interface)
{

    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << CS_LOAD_SHOPING_RECORD;
    CNetManager::GetMe()->send_msg( body_ms );
    cout << "load shoping_record request!----------------------------------"<< endl;
    return true;
}

bool Shop_Msg_Proc::send_buy_item(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64> para;
	gm_interface.get_para(para);
	if( para.size() < 2)
	{
		return false;
	}

	int goods_id = (int)para[0];
	int count = (int)para[1];

	char body[256] = {0};
	message_stream body_ms(body, sizeof(body));
	body_ms << CS_BUY_ITEM;
	body_ms << goods_id;
	body_ms << count;


    CNetManager::GetMe()->send_msg( body_ms );
	return true;
}

bool Shop_Msg_Proc::on_load_shoping_record(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        cout << "load shoping_record error!----------------------------------"<< endl;
        return false;
    }

    SHOPING_RECORD_MGR::instance()->load_shoping_record(player,body_ms);

    cout << "load shoping_record finish!----------------------------------"<< endl;
    return true;
}

bool Shop_Msg_Proc::on_buy_item(Game_Logic::Game_Interface& gm_interface)
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	int goods_id = 0;
	int count = 0;

	body_ms >> goods_id;
	body_ms >> count;

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    Game_Data::shop_config* shop_config = SHOP_CONFIG_MGR::instance()->get_shop_config(goods_id);
    if (!shop_config)
    {
        return false;
    }

    Game_Data::Item_Config* item_config = ITEM_CONFIG_MGR::instance()->get_item_config(shop_config->item_base_id_);
    if (!item_config)
    {
        return false;
    }

    if (shop_config->buy_count_ > 0)
    {
        Game_Data::shoping_record* record = SHOPING_RECORD_MGR::instance()->get_shoping_record(goods_id);
        if (record)
        {
            record->buy_count_ += count;
        } 
        else
        {
            SHOPING_RECORD_MGR::instance()->create_shoping_record(player,goods_id,count);
        }
    }
    
    const char* format = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_GAIN_INFO);
    const char* name = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(item_config->name);
    const char* item = CCString::createWithFormat(format,name,count)->getCString();
    const char* head = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_U_GAIN);
    //Game_Utils::instance()->show_alert(CCString::createWithFormat("%s%s",head,item)->getCString());

    Game_Logic::Game_Event_Response::instance()->on_update_shop(player_id);
	return true;
}