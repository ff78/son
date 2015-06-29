
#include "Network_Common/NetManager.h"
#include "Network_Common/message.h"
#include "Network_Common/message_coder.h"
#include "Network_Common/message_stream.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_response.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"

#include "UI/Main_City_Scene.h"
#include "Banks_Msg_Proc_Cl.h"
#include "Platform_Dependence/Dependence.h"
#include "Common/GameDefine.h"
#include "Banks_Common.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Banks_System/Banks_Common.h"
#include "Common/Utils.h"
USING_NS_CC;

Banks_Msg_Proc* Banks_Msg_Proc::instance_ = 0;
Banks_Msg_Proc::Banks_Msg_Proc()
{

}

Banks_Msg_Proc::~Banks_Msg_Proc()
{

}

Banks_Msg_Proc* Banks_Msg_Proc::instance()
{
    if(NULL == instance_)
        instance_ = new Banks_Msg_Proc;

    return instance_;
}

bool Banks_Msg_Proc::on_exchange_token_to_gold( Game_Logic::Game_Interface& gm_interface )
{

	int result = BER_FAILED;
	int gold = 0;

	message_stream ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size() );
	ms.set_rd_ptr(sizeof(int));

	ms >> result;
	ms >> gold;


/*
	BANK_SUCCEED						= 90389, //获得银两%d
		BANK_NOT_ENOUGH_TOKEN				= 90390, //元宝不足，无法兑换！
		BANK_HAVE_NO_CHANCE					= 90391, //兑换次数已达上限*/

	do 
	{
		if (BER_NOT_ENOUGH_TOKEN == result)
		{
			DICTIONARY_CONFIG_MGR::instance()->show_alert(BANK_NOT_ENOUGH_TOKEN);
			break;
		}
		if (BER_HAVE_NO_CHANCE == result)
		{
			DICTIONARY_CONFIG_MGR::instance()->show_alert(BANK_HAVE_NO_CHANCE);
			break;
		}
		if (BER_SUCCEED == result)
		{
			int player_id = Account_Data_Mgr::instance()->get_current_role_id();
			Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
			if (!player)
			{
				return false;
			}
			int count = player->get_banks_exchange_count();
			player->set_banks_exchange_count(count+1);
			Game_Logic::Game_Event_Response::instance()->on_update_banks(player_id);

			const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(BANK_SUCCEED);
			CCLOG("%s",szString);
			CCString* note_text = CCString::createWithFormat(szString,gold);	
			//Game_Utils::instance()->show_alert(note_text->getCString());
			break;
		}

	} while (false);

	return true;
}

bool Banks_Msg_Proc::send_exchange_token_to_gold( Game_Logic::Game_Interface& gm_interface )
{
	vector<uint64> para;
	gm_interface.get_para(para);
	if( para.size() < 0)
	{
		return false;
	}
	char body[64] = {0};
	message_stream body_ms(body, sizeof(body));
	body_ms << C2S_EXCHANGE_TOKEN_TO_GOLD;

	CNetManager::GetMe()->send_msg( body_ms );
	return true;
}