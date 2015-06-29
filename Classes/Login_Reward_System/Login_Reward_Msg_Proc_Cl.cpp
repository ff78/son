
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
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Item_System/Item_Config_Mgr.h"
//#include "AI_System/Game_Utils.h"

#include "cocos2d.h"

#include "Login_Reward_Msg_Proc_Cl.h"
#include "Login_Reward_Mgr_Cl.h"
#include "Login_Reward_Config_Mgr.h"
#include "Common/Utils.h"
#include "Common/GameDefine.h"
using namespace cocos2d;


Login_Reward_Msg_Proc* Login_Reward_Msg_Proc::instance_ = 0;
Login_Reward_Msg_Proc::Login_Reward_Msg_Proc(){

}

Login_Reward_Msg_Proc::~Login_Reward_Msg_Proc(){

}

Login_Reward_Msg_Proc* Login_Reward_Msg_Proc::instance()
{
    if(NULL == instance_)
        instance_ = new Login_Reward_Msg_Proc;

    return instance_;
}

bool Login_Reward_Msg_Proc::send_load_login_reward(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_LOAD_LOGIN_REWARD;
    CNetManager::GetMe()->send_msg( body_ms );
    cout << "load login_reward request!----------------------------------"<< endl;
    return true;
}


bool Login_Reward_Msg_Proc::send_get_login_reward(Game_Logic::Game_Interface& gm_interface)
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
    body_ms << C2S_GET_LOGIN_REWARD;
    body_ms << type;
    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Login_Reward_Msg_Proc::on_load_login_reward(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    LOGIN_REWARD_MGR::instance()->load_login_reward(body_ms);
    cout << "load login_reward finish!----------------------------------"<< endl;

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player_id);
    return true;
}

bool Login_Reward_Msg_Proc::on_get_login_reward(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int type = 0;
    body_ms >> type;

	Login_Reward_Msg_Proc::instance()->showAlart(type);

	Game_Data::Login_Reward& login_reward = Game_Data::Login_Reward_Mgr::instance()->get_login_reward();
	login_reward.got_flag_[type] = 1;

	int player_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Logic::Game_Event_Response::instance()->on_update_login_award(player_id);
    Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player_id);
    return true;
}

void Login_Reward_Msg_Proc::showAlart( int type )
{
	if ( type < 0 )
	{
		return;
	}
	
	Game_Data::login_reward_config *lrc = Game_Data::Login_Reward_Config_Mgr::instance()->get_login_reward_config(type);

	int item_id = lrc->reward_id_;
	const int daily_login_award_count = 1;

	std::string reward = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_U_GAIN);
	const char* format = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ALERT_GAIN_INFO);
	Game_Data::Item_Config* item_config = Game_Data::Item_Config_Mgr::instance()->get_item_config(item_id);
	const char* item_name = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(item_config->name);

	reward += CCString::createWithFormat(format,item_name,daily_login_award_count)->getCString();
	//Game_Utils::instance()->show_alert(reward.c_str());
}
