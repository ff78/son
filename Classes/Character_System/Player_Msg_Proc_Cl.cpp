
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
#include "UI_Interface/UI_MainMenu_Layer.h"
#include "Character_System/Player_Logic_Cl.h"

#include "Function_Open_System/Function_Open_Config_Data.h"

#include "cocos2d.h"

//#include "Actor_Mgr.h"
#include "Player_Msg_Proc_Cl.h"
#include "cocos2d.h"

//#include "Game_Utils.h"
//#include "Monster.h"
//#include "Game_Scene.h"
#include "UI/City_Scene.h"

//#include "GameUI_Layer.h"
#include "UI/Message_Layer.h"

//#include "Dynamic_Sprite.h"
//#include "Attack_Cfg_Data_Mgr.h"

#include "Game/Hurt_Utils.h"

#include "Game_Interface/game_event_response.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_element.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Play_System/Instance_Data_Mgr.h"

#include "Item_System/Item_Mgr_Cl.h"

//#include "Game/Monster_Wave_Cfg_Data_Mgr.h"

#include "Character_System/Character_Mgr.h"
#include "Character_System/Character.h"
//#include "Runtime.h"
//#include "UI/GameUI_Layer.h"

//#include "Skill_System/Skill/Skill_Logic.h"
#include "Character_System/Player_Config_Data.h"
#include "ClientLogic/GameScene/ResultLayer.h"
#include "../UI_Interface/UI_ModalDialogue_Layer.h"
#include "../Player_Account/Account_Logic.h"
#include "God_System/God_Client.h"
#include "Pet_System/Pet_Client.h"


Player_Msg_Proc* Player_Msg_Proc::instance_ = 0;
Player_Msg_Proc::Player_Msg_Proc()
{

}

Player_Msg_Proc::~Player_Msg_Proc()
{

}

Player_Msg_Proc* Player_Msg_Proc::instance()
{
    if(NULL == instance_)
        instance_ = new Player_Msg_Proc;

    return instance_;
}

bool Player_Msg_Proc::send_player_move(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 2)
    {
        return false;
    }

    int x = (int)para[0];
    int y = (int)para[1];
    
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_PLAYER_MOVE;
    body_ms << x;
    body_ms << y;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Player_Msg_Proc::send_get_player_info(Game_Logic::Game_Interface& gm_interface)
{
	char body[256] = {0};
	message_stream body_ms(body, sizeof(body));
	body_ms << C2S_GET_PLAYER_INFO;

    CNetManager::GetMe()->send_msg( body_ms );
	return true;
}

bool Player_Msg_Proc::send_chat_msg(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));

    string msg = gm_interface.get_buff();
    string flag = "/gm ";
    int index = msg.find(flag);
    if (index == 0 && msg.length() > flag.length())
    {
        string cmd = msg.substr(flag.length(),msg.size());
        body_ms << C2S_GM_COMMAND;
        body_ms << cmd;
    }
    else
    {
        body_ms << C2S_PLAYER_CHAT;
        body_ms << msg;
    }
    

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Player_Msg_Proc::send_chat_msg(int channel, const char* receiver_name, const char* chat)
{

	char body[MAX_MSG_BODY_LEN] = {0};
	message_stream body_ms(body, sizeof(body));

	string msg = chat;
	string flag = "/gm ";
	int index = msg.find(flag);
	if (index == 0 && msg.length() > flag.length())
	{
		string cmd = msg.substr(flag.length(),msg.size());
		body_ms << C2S_GM_COMMAND;
		body_ms << cmd;
	}
	else
	{
		body_ms << C2S_PLAYER_CHAT;
		body_ms << channel;
		body_ms << receiver_name;
		body_ms << msg;
	}
	CNetManager::GetMe()->send_msg( body_ms );
	
	return true;
}

bool Player_Msg_Proc::send_player_revive(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 1)
    {
        return false;
    }

    int character_id = (int)para[0];
    Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(character_id);
    if (!character)
    {
        return false;
    }
    
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_PLAYER_REVIVE;
    body_ms << character_id;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;

}

bool Player_Msg_Proc::send_player_instance_collided_something(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64> para;
	gm_interface.get_para(para);
	if( para.size() < 1)
	{
		return false;
	}

	int static_id=(int)para[0];

	char body[256] = {0};
	message_stream body_ms(body, sizeof(body));
	body_ms << C2S_COLLIDED_SOMETHING;
	body_ms<<static_id;
	CNetManager::GetMe()->send_msg( body_ms );
	return true;
}

bool Player_Msg_Proc::send_player_useitem_something(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64> para;
	gm_interface.get_para(para);
	if( para.size() < 1)
	{
		return false;
	}

	int itemid=(int)para[0];

	char body[256] = {0};
	message_stream body_ms(body, sizeof(body));
	body_ms << C2S_USEITEM_SOMETHING;
	body_ms<<itemid;
	CNetManager::GetMe()->send_msg( body_ms );
	return true;
}

bool Player_Msg_Proc::send_player_buy_energy(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_PLAYER_BUY_ENERGY;
    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Player_Msg_Proc::send_player_quality_up(Game_Logic::Game_Interface& gm_interface)
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
    body_ms << C2S_PLAYER_QUALITY_UP;
    body_ms << character_id;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Player_Msg_Proc::send_get_main_city_player(Game_Logic::Game_Interface& gm_interface)
{
	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));
	body_ms << C2S_GET_MAIN_CITY_PLAYER;

	CNetManager::GetMe()->send_msg(body_ms);
	return true;
}

bool Player_Msg_Proc::on_get_main_city_player(Game_Logic::Game_Interface& gm_interface)
{
	int count;
	auto players = CHARACTER_MGR::instance()->_other_player_map;
	players->clear();

    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));
	body_ms >> count;

	for (int i = 0; i < count; i++)
	{
		int id, x, y, sex, job, cur_pet_id, cur_god_id;
		std::string name;
		std::string title;
		body_ms >> id;
		body_ms >> x;
		body_ms >> y;
		body_ms >> sex;
		body_ms >> name;
		body_ms >> title;
		body_ms >> job;
		body_ms >> cur_pet_id;
		body_ms >> cur_god_id;

		Game_Data::Player* bot = new Game_Data::Player;
		bot->set_database_character_id(id);
		bot->set_x(x);
		bot->set_y(y);
		bot->set_character_name(name.c_str());
		bot->set_title_name(title);
		bot->set_job(job);
		bot->set_cur_pet_id(cur_pet_id);
		bot->set_cur_god_id(cur_god_id);
		players->insert( make_pair(id, bot) );
	}


    int player_id_1 = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = (Game_Data::Player*)CHARACTER_MGR::instance()->get_character(player_id_1);
	vector<uint64> para;
	para.clear();
	para.push_back(1);

	auto black = new BlackCity();
	black->readFile(player->get_main_city_scene_id(), CITY_FILE);
	bool bEnter = black->canEnter(player->get_character_level(), player->get_camp_tag());
	if (bEnter)
	{
		Game_Logic::Game_Content_Interface::instance()->exec_interface("enterscene", para);
	}
	else
	{
		//const char* exitInfo = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SERVER_DISCONNECT);
		UI_ModalDialogue_Layer::DoModal("", "Error city id", UI_ModalDialogue_Layer::DT_OK, []()
		{
			Account_Logic::releaseData();


			Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			 exit(0);
#endif
		}
		);
		return false;
	}

	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Logic::Game_Event event;
	event.reset();
	event.set_para(para);
	event.set_char_type(Game_Logic::Game_Event::EVENT_TYPE_PLAYER);
	event.set_char_id(player_id);
	event.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_PLAYER);
	event.set_event_owner_id(player_id);
	event.set_event_active_type(Game_Logic::Game_Event::EVENT_FINISH_SCENE_LOAD);
	event.set_event_active_id(0);

	Game_Logic::Game_Event_Mgr::instance()->reg_event("finishi_load_scene", Account_Logic::on_finish_load_scene, event);

    return true;
}

bool Player_Msg_Proc::on_player_move(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));
    
    //ACTOR_MGR::instance()->player_move(body_ms);

    return true;
}

bool Player_Msg_Proc::on_get_player_info(Game_Logic::Game_Interface& gm_interface)
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

	int level = 0;
	int exp = 0;
	int gold = 0;
    int energy = 0;
	body_ms >> level;
	body_ms >> exp;
	body_ms >> gold;
    body_ms >> energy;

    if (player->get_character_level() != level)
    {  
        player->set_character_level(level);
        player->update_level_date();
    }
    
    player->set_exp(exp);
    player->set_gold(gold);
    player->set_energy(energy);
    Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player->get_database_character_id());

	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("eventBackMainCity");

    return true;
}

bool Player_Msg_Proc::on_player_chat(Game_Logic::Game_Interface& gm_interface)
{
	/*if (!Game_Utils::instance()->is_in_city())
	{
		return true;
	}*/

	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	std::string roleName = player->get_character_name();

    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

	int channel = -1;
    std::string sender;
    std::string receiver;
    std::string chat;
    body_ms >> channel;
    body_ms >> sender;
    body_ms >> receiver;
    body_ms >> chat;

	if (CHAT_CHANNEL_ALL == channel)
	{

	}
	else if (CHAT_CHANNEL_FRIEND == channel)
	{

	}
	else if (CHAT_CHANNEL_MENPAI == channel)
	{
	}
	else if (CHAT_CHANNEL_TEAM == channel)
	{
	}
	else if(CHAT_CHANNEL_WORLD == channel)
	{
		chat = "[" + sender + "]:" + chat;  //: ????????
	}
	else if(CHAT_CHANNEL_PRIVATE == channel)
	{
		if( sender == roleName )
		{
			const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SEND_MESSAGE_TO_SB);
			CCString *note_text = CCString::createWithFormat(szString, receiver.c_str());
			std::string temp = note_text->getCString();
			chat = temp + ":" + chat;
		}
		else
		{
			const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(RECEIVE_MESSAGE_FROM_SB);
			CCString *note_text = CCString::createWithFormat(szString, sender.c_str());
			std::string temp = note_text->getCString();
			chat = temp+ ":" + chat;
		}
		
	}

	UI_MainMenu_Layer::get_instance()->addChatContent(chat.c_str(), channel, sender.c_str(), receiver.c_str());
	return true;
}

bool Player_Msg_Proc::on_gm_command(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    std::string op_result;
    int cmd_type = CMDT_NONE;
    GMCResult result;
    result.reset();

    body_ms >> op_result;
    body_ms >> cmd_type;

    if (cmd_type > CMDT_NONE)
    {
        for (int i = 0;i < 4;++i)
        {
            body_ms >> result.data1[i];
            body_ms >> result.data2[i];
        }

        operate_gm_command_reasult(cmd_type,result,op_result);
    }

    UI_MainMenu_Layer::get_instance()->addChatContent(op_result.c_str());
    return true;
}

bool Player_Msg_Proc::on_player_into_main_city(Game_Logic::Game_Interface& gm_interface)
{
	auto players = CHARACTER_MGR::instance()->_other_player_map;
	players->clear();

	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	int count;
	body_ms >> count;
	for (int i = 0; i < count;i++)
	{
		int id, x, y, sex, job, cur_pet_id, cur_god_id;
		std::string name, title;
		body_ms >> id;
		body_ms >> x;
		body_ms >> y;
		body_ms >> sex;
		body_ms >> name;
		body_ms >> title;
		body_ms >> job;
		body_ms >> cur_pet_id;
		body_ms >> cur_god_id;

		Game_Data::Player* bot = new Game_Data::Player;
		bot->set_database_character_id(id);
		bot->set_x(x);
		bot->set_y(y);
		bot->set_character_name(name.c_str());
		bot->set_title_name(title);
		bot->set_job(job);
		bot->set_cur_pet_id(cur_pet_id);
		bot->set_cur_god_id(cur_god_id);
		players->insert(make_pair(id, bot));
	}

	int level, exp, gold, energy, pet_id, god_id;
	body_ms >> level;
	body_ms >> exp;
	body_ms >> gold;
	body_ms >> energy;
	body_ms >> pet_id;
	body_ms >> god_id;

	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)return false;
	player->set_character_level(level);
	player->set_exp(exp);
	player->set_gold(gold);
	player->set_energy(energy);
	player->set_cur_pet_id(pet_id);
	player->set_cur_god_id(god_id);
    
    GOD_MODEL::getInstance()->setCurrentGodId(god_id);
    GOD_MODEL::getInstance()->load();
    //GOD_MODEL::getInstance()->setCurrentGodId(1003);
    
    PET_MODEL::getInstance()->setCurrentPetId(pet_id);
    
	vector<uint64> para;
	para.clear();
	para.push_back(1);
	Game_Logic::Game_Content_Interface::instance()->exec_interface("enterscene", para);

    current_instance_data cid_new;
    cid_new.reset();
    
    INSTANCE_DATA_MGR::instance()->get_player_instance(player_id, cid_new);

	if (cid_new.get_instance_state() == current_instance_data::INSTANCE_STATE_SUC)
	{
    	Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player->get_database_character_id());
	}

    return true;

}

bool Player_Msg_Proc::on_player_quit_main_city(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    //ACTOR_MGR::instance()->player_quit_main_city(body_ms);

    return true;
}

bool Player_Msg_Proc::on_add_recharge_token(Game_Logic::Game_Interface& gm_interface)
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return false;
	}

	int add = 0;
	body_ms >> add;

	player->add_recharge_token((uint)add);
	Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player->get_database_character_id());
	return true;
}

bool Player_Msg_Proc::on_change_token(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    int change = 0;
    body_ms >> change;

    player->change_token(change);
    Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player->get_database_character_id());
    return true;
}

bool Player_Msg_Proc::on_change_energy(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    int change = 0;
    body_ms >>  change;

    player->change_energy(change);
    Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player->get_database_character_id());
    return true;
}

bool Player_Msg_Proc::on_change_prestige(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    int change = 0;
    body_ms >>  change;

    player->change_prestige(change);
    Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player->get_database_character_id());
    return true;
}

bool Player_Msg_Proc::on_change_gold(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    int change = 0;
    body_ms >>  change;

    player->change_gold(change);
    Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player->get_database_character_id());
    return true;
}

bool Player_Msg_Proc::on_change_exp(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    int character_id = 0;
    int change = 0;
    body_ms >>  character_id;
    body_ms >>  change;

    Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(character_id);
    if (!character)
    {
        return false;
    }


    character->change_exp(change);
    Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player_id);
    return true;
}

bool Player_Msg_Proc::on_player_revivie(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    int character_id = 0;
    body_ms >>  character_id;

	/*UI::Actor *actor = Runtime::instance()->get_actor(character_id);
	actor->set_is_dead(false);
	Game_Utils::instance()->reset_character(character_id);

	UI::GameUI_Layer::get_instance()->setHPFull();
	Game_Utils::instance()->close_UI_Tips_Layer();
	Game_Utils::instance()->stop();*/

//	SKILL_LOGIC::instance()->AddBuff(player, player, 4000, false, 1);

	return true;
}

bool Player_Msg_Proc::on_player_buy_energy(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    int count = player->get_buy_energy_count() + 1;
    player->set_buy_energy_count(count);
    //DICTIONARY_CONFIG_MGR::instance()->show_alert(BUY_SUCCEED);
    return true;
}

bool Player_Msg_Proc::on_player_quality_up(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    int character_id = 0;
    body_ms >> character_id;
    Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(character_id);
    if (!character)
    {
        return false;
    }

    ITEM_MGR::instance()->remove_quality_upgrade_need_material(player,Game_Data::QMT_ROLE,character->get_character_quality());

    character->character_quality_up();
    Game_Logic::Game_Event_Response::instance()->on_update_item_ui_info(player->get_database_character_id());
//    Game_Logic::Game_Event_Response::instance()->on_update_role_quality_up(player->get_database_character_id());
    Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player->get_database_character_id());
    //DICTIONARY_CONFIG_MGR::instance()->show_alert(QUALITY_UP_SUCCESS);

    return true;
}

void Player_Msg_Proc::operate_gm_command_reasult(int cmd_type,GMCResult& result,std::string& op_result)
{
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return;
    }

    switch(cmd_type)
    {
    case CMDT_CHANGE_TOKEN:
        {

        }
        break;

    case CMDT_CHANGE_ENERGY:
        {

        }
        break;

    case CMDT_CHANGE_GOLD:
        {

        }
        break;

    case CMDT_CHANGE_PRESTIGE:
        {

        }
        break;

    case CMDT_CHANGE_EXP:
        {

        }
        break;

    case CMDT_CHANGE_LEVEL:
        {
            int changed_level = player->get_character_level() + result.data1[0];
            player->set_character_level(changed_level);
            player->update_level_date();
            Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player->get_database_character_id());
        }
        break;

    case CMDT_ADD_ITEM:
        {
            
        }
        break;

    case CMDT_SHOW_ALL_STAGE:
        {
            Account_Data_Mgr::instance()->set_is_show_all_stage(result.data1[0]);
        }
        break;

    case CMDT_OPEN_ALL_FUNCTION:
        {
//            player->set_function_open_id(ICON_SUM);
//			for (int i=0; i<ICON_SUM; ++i)
//			{
				//UI_MainMenu_Layer::get_instance()->arr[i] = true;
//			}
        }
        break;

    case CMDT_ADD_GENERAL:
        {

        }
        break;

    case CMDT_SHOW_FPS:
        {
            Director* pDirector = Director::getInstance();
            if (pDirector)
            {
                pDirector->setDisplayStats(result.data1[0] == 1);
            }
            
        }
        break;

    case CMDT_SHOW_PLAYER:
        {
            char buff[256] = {0};
            sprintf(buff, "online[%d] in battle[%d]", result.data1[0],result.data1[1]);
            op_result = buff;
        }
        break;

    default:
        {
            op_result = "operate fail,command type error!";
        }

        break;
    }
}

/**************************************** dely *************************************/
/*------------------- send -------------------*/
bool Player_Msg_Proc::send_chat_all_msg(int channel, const char* receiver_name, const char* chat)//区域
{
	//int character_id = (int)para[0];
	//Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(character_id);
	//if (!character)
	//	return false;

	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if (!player_id)
		return false;

	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	int scene_id = player->get_main_city_scene_id();
	if (scene_id <= 0)
		return false;

	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));
	body_ms << C2S_CHAT_AREA_MSG;
	body_ms << player_id;
	body_ms << scene_id;
	body_ms << chat;

	CNetManager::GetMe()->send_msg(body_ms);
	return true;
}

bool Player_Msg_Proc::send_chat_private_msg(int channel, const char* receiver_name, const char* chat)//私密
{
	//vector<uint64> para;
	//gm_interface.get_para(para);
	//if (para.size() < 1)
	//	return false;

	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if (!player_id)
		return false;

	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	int target = 1000001;

	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));
	body_ms << C2S_CHAT_PRIVATE_MSG;
	body_ms << player_id;
	body_ms << target;
	body_ms << chat;

	CNetManager::GetMe()->send_msg(body_ms);
	return true;
}

bool Player_Msg_Proc::send_chat_team_msg(int channel, const char* receiver_name, const char* chat)//组队
{
	return false;

}

bool Player_Msg_Proc::send_chat_friend_msg(int channel, const char* receiver_name, const char* chat)//好友
{
	return false;
}

bool Player_Msg_Proc::send_chat_faction_msg(int channel, const char* receiver_name, const char* chat)//工会
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if (!player_id)
		return false;

	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));

	int faction_id = 1;
	body_ms << C2S_CHAT_FACTION_MSG;
	body_ms << player_id;
	body_ms << faction_id;
	body_ms << chat;

	CNetManager::GetMe()->send_msg(body_ms);
	return true;
}

bool Player_Msg_Proc::send_chat_world_msg(int channel, const char* receiver_name, const char* chat)//世界
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if (!player_id)
		return false;

	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));
	body_ms << C2S_CHAT_WORLD_MSG;
	body_ms << player_id;
	body_ms << chat;

	CNetManager::GetMe()->send_msg(body_ms);
	return true;
}

/*------------------- receive -------------------*/
bool Player_Msg_Proc::receive_chat_all_msg(Game_Logic::Game_Interface& gm_interface)//区域
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	int player_id_received;
	string chat_content_received;
	//body_ms>>player_id_received;
	//body_ms>>chat_content_received

	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	std::string roleName = player->get_character_name();

	//std::vector<uint64> para;
	//para.clear();
	//para.push_back(player_id_received);

	Game_Logic::Game_Event_Response::instance()->on_update_chat(player->get_database_character_id());

	return true;

}

bool Player_Msg_Proc::receive_chat_private_msg(Game_Logic::Game_Interface& gm_interface)//私密
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));
	int player_id_received;
	string chat_content_received;
	body_ms>>player_id_received;
	body_ms >> chat_content_received;

	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return false;
	}
	if (player_id==player_id_received)
		return false;

	Game_Logic::Game_Event_Response::instance()->on_update_chat(player->get_database_character_id());

	return true;
}

bool Player_Msg_Proc::receive_chat_team_msg(Game_Logic::Game_Interface& gm_interface)//组队
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));
	int player_id_received;
	string chat_content_received;
	//body_ms>>player_id_received;
	//body_ms>>chat_content_received

	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return false;
	}
	Game_Logic::Game_Event_Response::instance()->on_update_chat(player->get_database_character_id());

	return true;
}

bool Player_Msg_Proc::receive_chat_friend_msg(Game_Logic::Game_Interface& gm_interface)//好友
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));
	int player_id_received;
	string chat_content_received;
	//body_ms>>player_id_received;
	//body_ms>>chat_content_received

	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return false;
	}
	Game_Logic::Game_Event_Response::instance()->on_update_chat(player->get_database_character_id());

	return true;
}

bool Player_Msg_Proc::receive_chat_faction_msg(Game_Logic::Game_Interface& gm_interface)//工会
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));
	int player_id_received;
	string chat_content_received;
	//body_ms>>player_id_received;
	//body_ms>>chat_content_received

	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
	{
		return false;
	}
	Game_Logic::Game_Event_Response::instance()->on_update_chat(player->get_database_character_id());

	return true;
}

bool Player_Msg_Proc::receive_chat_world_msg(Game_Logic::Game_Interface& gm_interface)//世界
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	int player_id_received;
	std::string chat_content_received;
	body_ms>>player_id_received;
	body_ms>>chat_content_received;

	//if(player_id_received==player_id)
	//	return false;
	player->clear_chat();
	player->set_chat_received(chat_content_received);
	player->set_channel(1);
	Game_Logic::Game_Event_Response::instance()->on_update_chat(player->get_database_character_id());

	return true;
}
/**************************************** dely *************************************/