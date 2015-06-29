
#include "Network_Common/message_stream.h"
#include "Network_Common/global_macros.h"
#include "Network_Common/message.h"
#include "Network_Common/NetManager.h"
#include "Game_Interface/Game_Element_Parse.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_response.h"
#include "Game_Interface/event_define.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "Item_System/Item_Desc_Config_Mgr.h"

#include "Rank_Msg_Proc_Cl.h"
#include "Rank_Mgr_Cl.h"
#include "Common/Utils.h"
Rank_Msg_Proc* Rank_Msg_Proc::instance_ = 0;
Rank_Msg_Proc::Rank_Msg_Proc(){

}

Rank_Msg_Proc::~Rank_Msg_Proc(){

}

Rank_Msg_Proc* Rank_Msg_Proc::instance()
{
    if(NULL == instance_)
        instance_ = new Rank_Msg_Proc;

    return instance_;
}

bool Rank_Msg_Proc::send_load_rank(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_LOAD_RANK;
    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Rank_Msg_Proc::send_load_rank_role_level(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_LOAD_RANK_ROLE_LEVEL;
    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Rank_Msg_Proc::send_load_rank_role_fighting_capacity(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_LOAD_RANK_ROLE_FIGHTING_CAPACITY;
    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Rank_Msg_Proc::send_load_rank_role_have_gold(Game_Logic::Game_Interface& gm_interface)
{
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << C2S_LOAD_RANK_ROLE_HAVE_GOLD;
    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool Rank_Msg_Proc::on_load_rank(Game_Logic::Game_Interface& gm_interface)
{
	/*message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	RANK_MGR::instance()->load_rank(body_ms);

	int role_id = Account_Data_Mgr::instance()->get_current_role_id();
	Game_Logic::Game_Event_Response::instance()->on_update_rank(role_id, Game_Data::RT_ROLE_LEVEL);*/

	return true;
}

bool Rank_Msg_Proc::on_load_rank_role_level(Game_Logic::Game_Interface& gm_interface)
{
	/************************************************************************/
	// 载入等级排行榜
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	Rank_Manager::instance()->LoadLevelRankingDataList(body_ms);
	return true;
}

bool Rank_Msg_Proc::on_load_rank_role_fighting_capacity(Game_Logic::Game_Interface& gm_interface)
{
	/************************************************************************/
	// 载入战斗力排行榜
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	Rank_Manager::instance()->LoadFightingPowerRankingDataList(body_ms);
	return true;
}

bool Rank_Msg_Proc::on_load_rank_role_have_gold(Game_Logic::Game_Interface& gm_interface)
{
	/************************************************************************/
	// 载入战斗力排行榜
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	Rank_Manager::instance()->LoadMoneyRankingDataList(body_ms);
	return true;
}

bool Rank_Msg_Proc::on_load_rank_role_renown(Game_Logic::Game_Interface& gm_interface)
{
	/************************************************************************/
	// 载入声望排行榜
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	Rank_Manager::instance()->LoadRenownRankingDataList(body_ms);
	return true;
}

bool Rank_Msg_Proc::on_load_rank_role_pvp(Game_Logic::Game_Interface& gm_interface)
{
	/************************************************************************/
	// 载入竞技场排行榜
	message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
	body_ms.set_rd_ptr(sizeof(int));

	Rank_Manager::instance()->LoadPVPRankingDataList(body_ms);
	return true;
}