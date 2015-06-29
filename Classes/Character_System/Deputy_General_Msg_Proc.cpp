
#include "Skill_System/Skill/Skill_Logic.h"
#include "Network_Common/message.h"
#include "Network_Common/message_coder.h"
#include "Network_Common/message_stream.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_response.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Deputy_General_Msg_Proc.h"
#include "Network_Common/NetManager.h"
//#include "Runtime.h"
#include "Common/Utils.h"

using namespace Game_Data;

Deputy_General_Msg_Proc* Deputy_General_Msg_Proc::instance_ = 0;
Deputy_General_Msg_Proc::Deputy_General_Msg_Proc()
{

}

Deputy_General_Msg_Proc::~Deputy_General_Msg_Proc()
{

}

Deputy_General_Msg_Proc* Deputy_General_Msg_Proc::instance()
{
    if(NULL == instance_)
        instance_ = new Deputy_General_Msg_Proc;

    return instance_;
}

bool Deputy_General_Msg_Proc::send_load_deputy_general(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64> para;
	gm_interface.get_para(para);
	if( para.size() < 1)
	{
		return false;
	}
	int character_id = (int)para[0];

	char body[256] = {0};
	message_stream body_ms(body, sizeof(body));
	body_ms << CS_LOAD_DEPUTY_GENERAL << character_id;


	//Client_Network::instance()->send_msg_to_game(body_ms);
    CNetManager::GetMe()->send_msg( body_ms );

	return true;
}

bool Deputy_General_Msg_Proc::send_deputy_general_fight(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64> para;
	gm_interface.get_para(para);
	if( para.size() < 1)
	{
		return false;
	}
	int character_id = (int)para[0];

	char body[256] = {0};
	message_stream body_ms(body, sizeof(body));
	body_ms << CS_DEPUTY_GENERAL_FIGHT << character_id;
//	Client_Network::instance()->send_msg_to_game(body_ms);
    CNetManager::GetMe()->send_msg( body_ms );
	return true;
}

bool Deputy_General_Msg_Proc::send_deputy_general_cancel_fight(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
	message_stream body_ms(body, sizeof(body));
	body_ms << CS_DEPUTY_GENERAL_CANCEL_FIGHT;
//	Client_Network::instance()->send_msg_to_game(body_ms);
    CNetManager::GetMe()->send_msg( body_ms );
	return true;
}

bool Deputy_General_Msg_Proc::on_load_deputy_general(Game_Logic::Game_Interface& gm_interface)
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return false;
	}

	int deputy_general_count = 0;
	body_ms >> deputy_general_count;

	int database_id = 0;
	int static_id = 0;
	int level = 0; 
    int quality = 0;
	int exp = 0;
	for (int i = 0; i < deputy_general_count; ++i)
	{
		DeputyGeneral* deputy_general = new DeputyGeneral;
		body_ms >> database_id;
		body_ms >> static_id;
		body_ms >> level;
        body_ms >> quality;
		body_ms >> exp;
		
        deputy_general->set_owner(player);
		deputy_general->set_database_character_id(database_id);
        deputy_general->set_character_type(Game_Logic::Game_Event::EVENT_TYPE_DEPUTY_GENERAL);
		deputy_general->init_attr_data(static_id, level);
        deputy_general->set_character_quality(quality);
        deputy_general->set_exp(exp);
		CHARACTER_MGR::instance()->insert_character(deputy_general);

		player->insert_deputy_general(deputy_general);

		//Runtime::instance()->create_actor(database_id);
	}

	return true;
}

bool Deputy_General_Msg_Proc::on_deputy_general_fight(Game_Logic::Game_Interface& gm_interface)
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return false;
	}

	int fight_general_id = 0;
	body_ms >> fight_general_id;

	DeputyGeneral* deputy_general = player->get_deputy_general(fight_general_id);
	if (!deputy_general)
	{
		return false;
	}
	
	player->set_fight_general_id(fight_general_id);

    Game_Logic::Game_Event_Response::instance()->on_update_item_ui_info(player->get_database_character_id());
	Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player->get_database_character_id());
	return true;
}

bool Deputy_General_Msg_Proc::on_deputy_general_cancel_fight(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    player->set_fight_general_id(0);

    Game_Logic::Game_Event_Response::instance()->on_update_item_ui_info(player->get_database_character_id());
    Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player->get_database_character_id());
	return true;
}

bool Deputy_General_Msg_Proc::on_create_deputy_general(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    int database_id = 0;
    int static_id = 0;
    int level = 0; 
    int quality = 0;
    int exp = 0;
    
    DeputyGeneral* deputy_general = new DeputyGeneral;
    body_ms >> database_id;
    body_ms >> static_id;
    body_ms >> level;
    body_ms >> quality;
    body_ms >> exp;

    deputy_general->set_owner(player);
    deputy_general->set_database_character_id(database_id);
    deputy_general->set_character_type(Game_Logic::Game_Event::EVENT_TYPE_DEPUTY_GENERAL);
    deputy_general->init_attr_data(static_id, level);
    deputy_general->set_character_quality(quality);
    deputy_general->set_exp(exp);
    CHARACTER_MGR::instance()->insert_character(deputy_general);

    player->insert_deputy_general(deputy_general);

    //Runtime::instance()->create_actor(database_id);

    return true;
}

int Deputy_General_Msg_Proc::get_message_stream_body(int& player_id, message_stream& ms, Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64> para;
	gm_interface.get_para(para);
	if( para.size() < 1)
	{
		return -1;
	}

	player_id = (int)para[0];
	ms = message_stream((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	ms.set_rd_ptr(sizeof(int));

	return 0;
}