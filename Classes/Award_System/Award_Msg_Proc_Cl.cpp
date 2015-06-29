
#include "Network_Common/NetManager.h"
#include "Network_Common/message.h"
#include "Network_Common/message_coder.h"
#include "Network_Common/message_stream.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_response.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "UI/Main_City_Scene.h"
#include "Award_Msg_Proc_Cl.h"
#include "Platform_Dependence/Dependence.h"
#include "Common/GameDefine.h"
#include "Award_Common.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "Common/Utils.h"


USING_NS_CC;

Award_Msg_Proc* Award_Msg_Proc::instance_ = 0;
Award_Msg_Proc::Award_Msg_Proc()
{

}

Award_Msg_Proc::~Award_Msg_Proc()
{

}

Award_Msg_Proc* Award_Msg_Proc::instance()
{
    if(NULL == instance_)
        instance_ = new Award_Msg_Proc;

    return instance_;
}

bool Award_Msg_Proc::on_ask_exchange_code_info( Game_Logic::Game_Interface& gm_interface )
{
	int result = EAR_NOT_EXIST;

	message_stream ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size() );
	ms.set_rd_ptr(sizeof(int));
	ms >> result;
	
	std::string result_str = "";

	switch (result)
	{
	case EAR_NOT_EXIST:
		{
			result_str = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ECR_WRONG_CODE);
			break;
		}
	case EAR_BEEN_EXCHANGED:
		{
			result_str = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ECR_EXCHENGED);
			break;
		}
	case EAR_SUCCESS:
		{
			result_str = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ECR_SUCCESS);
			break;
		}
	case EAR_BAG_FULL:
		{
			result_str = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ECR_BAG_FULL);
			break;
		}
	default:
		{
			result_str = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(ECR_WRONG_CODE);
			break;
		}
	}

	Game_Data::Item_Desc_Config_Mgr::instance()->show_alert(result_str.c_str());

	return true;
}

bool Award_Msg_Proc::send_ask_exchange_code_info( Game_Logic::Game_Interface& gm_interface )
{
	vector<uint64> para;
	gm_interface.get_para(para);
	if( para.size() < 0)
	{
		return false;
	}
	std::string exchange_code = gm_interface.get_keyword();
	char body[256] = {0};
	message_stream body_ms(body, sizeof(body));
	body_ms << C2S_ASK_EXCHANGE_CODE_REWARD;
	body_ms << exchange_code;

	CNetManager::GetMe()->send_msg( body_ms );
	return true;
}


