

#include "Activity_Msg_Proc_Cl.h"

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

#include "Activity_System/Activity_Record_Mgr_Cl.h"
#include "Activity_System/Activity_Config_Mgr.h"
#include "Common/Utils.h"

Activity_Msg_Proc* Activity_Msg_Proc::instance_ = 0;
Activity_Msg_Proc::Activity_Msg_Proc()
{

}

Activity_Msg_Proc::~Activity_Msg_Proc()
{

}

Activity_Msg_Proc* Activity_Msg_Proc::instance()
{
    if(NULL == instance_)
        instance_ = new Activity_Msg_Proc;

    return instance_;
}

bool Activity_Msg_Proc::send_load_activity_record(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_LOAD_ACTIVITY_RECORD;
    CNetManager::GetMe()->send_msg( body_ms );
    cout << "load activity_record request!----------------------------------"<< endl;
    return true;
}

bool Activity_Msg_Proc::send_activity_six_sect(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64> para;
	gm_interface.get_para(para);
	if( para.size() < 1)
	{
		return false;
	}

	int base_id = (int)para[0];

	char body[256] = {0};
	message_stream body_ms(body, sizeof(body));
	body_ms << C2S_ACTIVITY_SIX_SECT;
	body_ms << base_id;

    CNetManager::GetMe()->send_msg( body_ms );
	return true;
}

bool Activity_Msg_Proc::on_load_activity_record(Game_Logic::Game_Interface& gm_interface)
{
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        cout << "load activity_record error!----------------------------------"<< endl;
        return false;
    }

    ACTIVITY_RECORD_MGR::instance()->load_activity_record(body_ms);

    cout << "load activity_record finish!----------------------------------"<< endl;
    return true;
}

bool Activity_Msg_Proc::on_activity_six_sect(Game_Logic::Game_Interface& gm_interface)
{
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	int base_id = 0;
	body_ms >> base_id;

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (!player)
    {
        return false;
    }

    Game_Data::activity_six_sect_config* activity_six_sect_config = ACTIVITY_CONFIG_MGR::instance()->get_activity_six_sect_config(base_id);
    if (!activity_six_sect_config)
    {
        return false;
    }

    Game_Data::activity_record& record = ACTIVITY_RECORD_MGR::instance()->get_activity_record();
    record.six_sect_record_[activity_six_sect_config->get_type()] += 1;
   
	return true;
}

bool Activity_Msg_Proc::RecMsgEndlessTowerInfo(Game_Logic::Game_Interface& gm_interface)
{
	/************************************************************************/
	// 接收无尽塔的消息

	// ...
	return true;
}
