#include "Chat_Client.h"

#include "Network_Common/message_stream.h"
#include "Network_Common/message.h"
#include "Network_Common/NetManager.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"

#include "Game_Interface/game_event_response.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_element.h"

#include "UI_Interface/UI_MainMenu_Layer.h"

Chat_Msg_Proc* Chat_Msg_Proc::instance_ = NULL;

Chat_Msg_Proc::Chat_Msg_Proc(){};

Chat_Msg_Proc::~Chat_Msg_Proc(){};

Chat_Msg_Proc* Chat_Msg_Proc::getInstance()
{
	if (instance_==NULL)
		instance_ = new Chat_Msg_Proc;
	return instance_;
};

bool Chat_Msg_Proc::send_chat_all_msg(int channel, const char* receiver_name, const char* chat)//区域
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

	//int scene_id = player->get_character_scene_id();
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

bool Chat_Msg_Proc::send_chat_private_msg(int channel, const char* receiver_name, const char* chat)//私密
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

bool Chat_Msg_Proc::send_chat_team_msg(int channel, const char* receiver_name, const char* chat)//组队
{
	return false;

}

bool Chat_Msg_Proc::send_chat_friend_msg(int channel, const char* receiver_name, const char* chat)//好友
{
	return false;
}

bool Chat_Msg_Proc::send_chat_faction_msg(int channel, const char* receiver_name, const char* chat)//工会
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

bool Chat_Msg_Proc::send_chat_world_msg(int channel, const char* receiver_name, const char* chat)
{
	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	if (!player_id)
		return false;

	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	char body[256] = { 0 };
	message_stream body_ms(body, sizeof(body));

	string msg = chat;
	string flag = "/gm ";
	int index = msg.find(flag);
	if (index == 0 && msg.length() > flag.length())
	{
		string cmd = msg.substr(flag.length(), msg.size());
		body_ms << C2S_GM_COMMAND;
		body_ms << cmd;
	}
	else
	{
		body_ms << C2S_CHAT_WORLD_MSG;
		body_ms << player_id;
		body_ms << chat;
	}

	CNetManager::GetMe()->send_msg(body_ms);
	return true;
}

bool Chat_Msg_Proc::send_chat_area_msg(int channel, const char* receiver_name, const char* chat)
{
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

	string msg = chat;
	string flag = "/gm ";
	int index = msg.find(flag);
	if (index == 0 && msg.length() > flag.length())
	{
		string cmd = msg.substr(flag.length(), msg.size());
		body_ms << C2S_GM_COMMAND;
		body_ms << cmd;
	}
	else
	{
		body_ms << C2S_CHAT_AREA_MSG;
		body_ms << player_id;
		body_ms << scene_id;
		body_ms << chat;
	}

	CNetManager::GetMe()->send_msg(body_ms);
	return true;
}


bool Chat_Msg_Proc::on_chat_all_msg(Game_Logic::Game_Interface& gm_interface)//区域
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	int player_id_received;
	string chat_content_received;
	body_ms>>player_id_received;
	body_ms>>chat_content_received;

	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	//if (player_id_received == player_id)
	//	return false;

	CHAT_LOGIC::getInstance()->clear_msg();
	CHAT_LOGIC::getInstance()->set_channel(2);//2是all 暂时作为区域聊天
	CHAT_LOGIC::getInstance()->set_msg_received(chat_content_received);

	Game_Logic::Game_Event_Response::instance()->on_update_chat(player->get_database_character_id());

	return true;

}

bool Chat_Msg_Proc::on_chat_private_msg(Game_Logic::Game_Interface& gm_interface)//私密
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));
	int player_id_received;
	string chat_content_received;
	body_ms >> player_id_received;
	body_ms >> chat_content_received;

	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;
	
	//if (player_id == player_id_received)
	//	return false;

	CHAT_LOGIC::getInstance()->clear_msg();
	CHAT_LOGIC::getInstance()->set_channel(3);//3是私密聊天
	CHAT_LOGIC::getInstance()->set_msg_received(chat_content_received);

	Game_Logic::Game_Event_Response::instance()->on_update_chat(player->get_database_character_id());

	return true;
}

bool Chat_Msg_Proc::on_chat_team_msg(Game_Logic::Game_Interface& gm_interface)//组队
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

bool Chat_Msg_Proc::on_chat_friend_msg(Game_Logic::Game_Interface& gm_interface)//好友
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

bool Chat_Msg_Proc::on_chat_faction_msg(Game_Logic::Game_Interface& gm_interface)//工会
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

bool Chat_Msg_Proc::on_chat_world_msg(Game_Logic::Game_Interface& gm_interface)//世界
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

	//player->clear_chat();
	//player->set_chat_received(chat_content_received);
	//player->set_channel(1);

	CHAT_LOGIC::getInstance()->clear_msg();
	CHAT_LOGIC::getInstance()->set_channel(1);//1是世界聊天
	CHAT_LOGIC::getInstance()->set_msg_received(chat_content_received);

	Game_Logic::Game_Event_Response::instance()->on_update_chat(player->get_database_character_id());

	return true;
}

bool Chat_Msg_Proc::on_chat_area_msg(Game_Logic::Game_Interface& gm_interface)	//区域
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	int player_id_received;
	string chat_content_received;
	body_ms >> player_id_received;
	body_ms >> chat_content_received;

	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	if (!player)
		return false;

	if (player_id_received == player_id)
		return false;

	CHAT_LOGIC::getInstance()->clear_msg();
	CHAT_LOGIC::getInstance()->set_channel(2);//2是区域聊天
	CHAT_LOGIC::getInstance()->set_msg_received(chat_content_received);

	Game_Logic::Game_Event_Response::instance()->on_update_chat(player->get_database_character_id());

	return true;

}

namespace Game_Data
{
	void Chat_Logic::send_chat_msg_all(int channel, const char* receiver_name, const char* chat)
	{
		int character_id = Account_Data_Mgr::instance()->get_current_role_id();
		Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(character_id));
		if (!player)		
			return;
	
		Chat_Msg_Proc::send_chat_all_msg(channel, receiver_name, chat);
		//UI_MainMenu_Layer::get_instance()->addChatContent(chat, channel, "", receiver_name);

	}

	void Chat_Logic::send_chat_msg_faction(int channel, const char* receiver_name, const char* chat)
	{
		int character_id = Account_Data_Mgr::instance()->get_current_role_id();
		Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(character_id));
		if (!player)
			return;
		
		Chat_Msg_Proc::send_chat_faction_msg(channel, receiver_name, chat);

	}

	void Chat_Logic::send_chat_msg_world(int channel, const char* receiver_name, const char* chat)
	{
		int character_id = Account_Data_Mgr::instance()->get_current_role_id();
		Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(character_id));
		if (!player)
			return;
		
		Chat_Msg_Proc::send_chat_world_msg(channel, receiver_name, chat);
		//UI_MainMenu_Layer::get_instance()->addChatContent(chat, channel, "", receiver_name);

	}

	void Chat_Logic::send_chat_msg_friend(int channel, const char* receiver_name, const char* chat)
	{
		int character_id = Account_Data_Mgr::instance()->get_current_role_id();
		Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(character_id));
		if (!player)
		{
			return;
		}
		Chat_Msg_Proc::send_chat_friend_msg(channel, receiver_name, chat);

	}

	void Chat_Logic::send_chat_msg_team(int channel, const char* receiver_name, const char* chat)
	{
		int character_id = Account_Data_Mgr::instance()->get_current_role_id();
		Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(character_id));
		if (!player)
			return;
		
		Chat_Msg_Proc::send_chat_team_msg(channel, receiver_name, chat);

	}

	void Chat_Logic::send_chat_msg_private(int channel, const char* receiver_name, const char* chat)
	{
		int character_id = Account_Data_Mgr::instance()->get_current_role_id();
		Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(character_id));
		if (!player)
			return;
		
		Chat_Msg_Proc::send_chat_private_msg(channel, receiver_name, chat);
		//UI_MainMenu_Layer::get_instance()->addChatContent(chat, channel, "", receiver_name);

	}

	void Chat_Logic::send_chat_msg_area(int channel, const char* receiver_name, const char* chat)
	{
		int character_id = Account_Data_Mgr::instance()->get_current_role_id();
		Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character(character_id));
		if (!player)
			return;

		Chat_Msg_Proc::send_chat_area_msg(channel, receiver_name, chat);
		//UI_MainMenu_Layer::get_instance()->addChatContent(chat, channel, "", receiver_name);

	}

	Chat_Logic* Chat_Logic::_instance = NULL;

	Chat_Logic* Chat_Logic::getInstance()
	{
		if (_instance == NULL)
			_instance = new Chat_Logic;
		return _instance;
	}

}