#include "msg_proc.h"
#include "msg_manager.h"
#include "cocos2d.h"
#include "Network_Common/message_coder.h"
#include "Network_Common/message_stream.h"
#include "Network_Common/global_macros.h"
#include "Network_Common/message.h"
#include "Player_Account/Account_Msg_Proc.h"
#include "Character_System/Player_Msg_Proc_Cl.h"
#include "Chat_System/Chat_Client.h"

#include "Item_System/Item_Msg_Proc_Cl.h"
#include "Item_Container_System/Item_Container_Msg_Proc_Cl.h"
//#include "Skill_System/Skill/Skill_Msg_Proc.h"
#include "Play_System/Client_Instance_Msg_Proc.h"
#include "Shop_System/Shop_Msg_Proc_Cl.h"
#include "quest_system/quest_logic/quest_msg_proc_client.h"
//#include "Character_System/Deputy_General_Msg_Proc.h"
#include "Relation_System/Relation_Msg_Proc.h"
//#include "Fight_System/Offline_Fight_Msg_Proc_Cl.h"
//#include "Fight_System/Online_Fight_Msg_Proc_Cl.h"
#include "Acupoint_System/Acupoint_Msg_Proc_Cl.h"
#include "Public_Annoucement/Public_Annoucement_Mgr_Proc_CL.h"
#include "Cool_Time_System/Cool_Time_Msg_Proc_Cl.h"
#include "Partition_System/Partition_Msg_Proc_Cl.h"
#include "Award_System/Award_Msg_Proc_Cl.h"
#include "Banks_System/Banks_Msg_Proc_Cl.h"
#include "Rank_System/Rank_Msg_Proc_Cl.h"
#include "Login_Reward_System/Login_Reward_Msg_Proc_Cl.h"
#include "Activity_System/Activity_Msg_Proc_Cl.h"
#include "Daily_Task_System/Daily_Task_Msg_Proc_Cl.h"
#include "RadiateSystem/Radiate_Msg_Proc.h"

//#include "Job_Skill_System/Job_Skill_Msg_Proc.h"
#include "TouchSkill/SkillMsgProc.h"
#include "../Faction_System/Faction_Client.h"
#include "../Emai_System/Email_Client.h"
#include "../God_System/God_Client.h"
#include "../Pet_System/Pet_Client.h"

Msg_Proc* Msg_Proc::instance_ = 0;

 Msg_Proc::Msg_Proc()
{

}
Msg_Proc::~Msg_Proc()
{
    if( instance_ )
        delete instance_;
}

Msg_Proc* Msg_Proc::instance(void)
{
     if( NULL == instance_ )
          instance_ = new Msg_Proc();

     return instance_;
}

int Msg_Proc::init( void )
{
    //register login msg

	reg_interface(RETURN_AUTH_SESSION,					Account_Msg_Proc::on_player_login);
	reg_interface(RETURN_CREATE_ROLE,					Account_Msg_Proc::on_player_create_role);
	reg_interface(RETURN_START_GAME,					Account_Msg_Proc::on_player_start_game);
	reg_interface(RETURN_ENTER_SCENE,					Account_Msg_Proc::on_player_enter_scene);
	reg_interface(RETURN_ERROR_MESSAGE,					Account_Msg_Proc::on_player_error_msg);

    reg_interface(RETURN_INSTANCE_REQ,					Client_Instance_Msg_Proc::on_player_enter_instance);
    reg_interface(RETURN_INSTANCE_MONSTER,				Client_Instance_Msg_Proc::on_player_instance_monster_wave);
    reg_interface(RETURN_INSTANCE_FINISH,				Client_Instance_Msg_Proc::on_player_instance_finish_result);
    reg_interface(RETURN_INSTANCE_PROGRESS,				Client_Instance_Msg_Proc::on_player_instance_progress);
    reg_interface(RETURN_REQUIRE_STAGE_INSTANCE_STATE,  Client_Instance_Msg_Proc::on_player_stage_instance_state);
	reg_interface(RETURN_INSTANCE_SWEEP,				Client_Instance_Msg_Proc::on_instance_sweep);
	reg_interface(RETURN_REQUIRE_STAGE,					Client_Instance_Msg_Proc::on_player_stage);
	reg_interface(RETURN_REQUIRE_STAGE_ALL,				Client_Instance_Msg_Proc::on_player_stage_instance);			// 接收玩家当前章节的相关信息
	reg_interface(RETURN_INSTANCE_NEXT,					Client_Instance_Msg_Proc::on_player_next_instance);				// 接收玩家无尽塔下一关相关信息

    // player
    reg_interface(S2C_PLAYER_INTO_MAIN_CITY,            Player_Msg_Proc::on_player_into_main_city);
    reg_interface(S2C_PLAYER_QUIT_MAIN_CITY,            Player_Msg_Proc::on_player_quit_main_city);
    reg_interface(S2C_GET_MAIN_CITY_PLAYER,             Player_Msg_Proc::on_get_main_city_player);
    reg_interface(S2C_PLAYER_MOVE,                      Player_Msg_Proc::on_player_move);
    reg_interface(S2C_GET_PLAYER_INFO,                  Player_Msg_Proc::on_get_player_info);
    reg_interface(S2C_PLAYER_CHAT,                      Player_Msg_Proc::on_player_chat);
    reg_interface(S2C_GM_COMMAND,                       Player_Msg_Proc::on_gm_command);
    reg_interface(S2C_CHANGE_TOKEN,                     Player_Msg_Proc::on_change_token);
    reg_interface(S2C_ADD_RECHARGE_TOKEN,               Player_Msg_Proc::on_add_recharge_token);
    reg_interface(S2C_CHANGE_ENERGY,                    Player_Msg_Proc::on_change_energy);
    reg_interface(S2C_CHANGE_PRESTIGE,                  Player_Msg_Proc::on_change_prestige);
    reg_interface(S2C_CHANGE_GOLD,                      Player_Msg_Proc::on_change_gold);
    reg_interface(S2C_CHANGE_EXP,                       Player_Msg_Proc::on_change_exp);
	reg_interface(S2C_PLAYER_REVIVE,	            	Player_Msg_Proc::on_player_revivie);
	reg_interface(S2C_PLAYER_QUALITY_UP,		        Player_Msg_Proc::on_player_quality_up);
    reg_interface(S2C_PLAYER_BUY_ENERGY,                Player_Msg_Proc::on_player_buy_energy);
	/**************************************** dely ******************************************/
	//reg_interface(S2C_CHAT_AREA_MSG,					Player_Msg_Proc::receive_chat_all_msg);
	//reg_interface(S2C_CHAT_PRIVATE_MSG,				Player_Msg_Proc::receive_chat_private_msg);
	//reg_interface(S2C_CHAT_TEAM_MSG,					Player_Msg_Proc::receive_chat_team_msg);
	//reg_interface(S2C_CHAT_FRIEND_MSG,				Player_Msg_Proc::receive_chat_friend_msg);
	//reg_interface(S2C_CHAT_FACTION_MSG,				Player_Msg_Proc::receive_chat_faction_msg);
	//reg_interface(S2C_CHAT_WORLD_MSG,					Player_Msg_Proc::receive_chat_world_msg);

	reg_interface(S2C_CHAT_AREA_MSG,					Chat_Msg_Proc::on_chat_all_msg);
	reg_interface(S2C_CHAT_PRIVATE_MSG,					Chat_Msg_Proc::on_chat_private_msg);
	reg_interface(S2C_CHAT_TEAM_MSG,					Chat_Msg_Proc::on_chat_team_msg);
	reg_interface(S2C_CHAT_FRIEND_MSG,					Chat_Msg_Proc::on_chat_friend_msg);
	reg_interface(S2C_CHAT_FACTION_MSG,					Chat_Msg_Proc::on_chat_faction_msg);
	reg_interface(S2C_CHAT_WORLD_MSG,					Chat_Msg_Proc::on_chat_world_msg);
	//guild
	//reg_interface(S2C_CHAT_WORLD_MSG, SOCIAL_MSG::on_join_msg);

	reg_interface(S2C_GET_FACTION_DATA,						    FACTION_NET::on_get_faction_data);
	//reg_interface(S2C_CREATE_FACTION,							FACTION_NET::on_faction_search);
	reg_interface(S2C_CREATE_FACTION,							FACTION_NET::on_faction_create);
	reg_interface(S2C_JOIN_FACTION,								FACTION_NET::on_faction_join);
	reg_interface(S2C_KICK_MEMBER_FACTION,						FACTION_NET::on_faction_kick_member);
	reg_interface(S2C_SET_JOB_FACTION,							FACTION_NET::on_faction_set_job);
	reg_interface(S2C_SET_MSG_BOARD_FACTION,					FACTION_NET::on_faction_set_notice);
	reg_interface(S2C_SET_JOIN_LINMIT_FACTION,					FACTION_NET::on_faction_join_limit);
	reg_interface(S2C_SET_TOTEMS_UP_FACTION,					FACTION_NET::on_faction_totems_up);
	reg_interface(S2C_FACTION_DIGGIN,							FACTION_NET::on_faction_member_digging);
	reg_interface(S2C_FACTION_WORSHIP,							FACTION_NET::on_faction_member_worship);
	reg_interface(S2C_FACTION_DEKARON_BOSS,						FACTION_NET::on_faction_member_dekaron_boos);
	reg_interface(S2C_FACTION_KILL_BOSS,					    FACTION_NET::on_faction_member_kill_boos);

	reg_interface(S2C_ON_LOAD_EMAIL,							EMAIL_NET::on_load_email);
	reg_interface(S2C_SEND_EMAIL_BY_TARGET,						EMAIL_NET::on_recieve_email);
	reg_interface(S2C_SEND_EMAIL_BY_SELF,						EMAIL_NET::on_send_email);
	reg_interface(S2C_SEND_RECEIVE_EMAIL_ITEM,					EMAIL_NET::on_recieve_system_email);
	reg_interface(S2C_SEND_OPEN_EMAIL,							EMAIL_NET::on_open_email);
	reg_interface(S2C_SEND_DELETE_EMAIL,						EMAIL_NET::on_delete_email);

	reg_interface(S2C_GOD_WEAPON_LEVEL_UP,						GOD_NET::on_upgrade);
	reg_interface(S2C_ADD_GOD_WEAPON,							GOD_NET::on_load);

	reg_interface(S2C_ADD_GUARD_BEAST,							PET_NET::on_load);
	reg_interface(S2C_GUARD_BEAST_LV_UP,						PET_NET::on_upgrade);
	reg_interface(S2C_GUARD_BEAST_STATE_CHANGE,					PET_NET::on_change_state);
	/**************************************** dely ******************************************/
    // item
    reg_interface(S2C_LOAD_ITEM,                    Item_Msg_Proc::on_load_item);
    reg_interface(S2C_TIDY_ITEM,                    Item_Msg_Proc::on_tidy_item);
    reg_interface(S2C_EQUIP_EQUIPMENT,              Item_Msg_Proc::on_equip_equipment);
    reg_interface(S2C_TAKE_OFF_EQUIPMENT,           Item_Msg_Proc::on_take_off_equipmen);
    reg_interface(S2C_EQUIP_BOOK,                   Item_Msg_Proc::on_equip_book);
    reg_interface(S2C_TAKE_OFF_BOOK,                Item_Msg_Proc::on_take_off_book);
    reg_interface(S2C_EQUIPMENT_LEVEL_UP,           Item_Msg_Proc::on_equipment_level_up);
    reg_interface(S2C_EQUIPMENT_QUALITY_UP,         Item_Msg_Proc::on_equipment_quality_up);
    reg_interface(S2C_BOOK_LEVEL_UP,                Item_Msg_Proc::on_book_level_up);
    reg_interface(S2C_BOOK_QUALITY_UP,              Item_Msg_Proc::on_book_quality_up);
    reg_interface(S2C_SELL_ITEM,                    Item_Msg_Proc::on_sell_item);
    reg_interface(S2C_USE_ITEM,                     Item_Msg_Proc::on_use_item);
    reg_interface(S2C_LOAD_MATERIAL_FRAGMENT,       Item_Msg_Proc::on_load_material_fragment);
    reg_interface(S2C_LOAD_BOOK_FRAGMENT,           Item_Msg_Proc::on_load_book_fragment);
    reg_interface(S2C_COMPOUND_MATERIAL_FRAGMENT,   Item_Msg_Proc::on_compound_material_fragment);
    reg_interface(S2C_COMPOUND_BOOK_FRAGMENT,       Item_Msg_Proc::on_compound_book_fragment);
    reg_interface(S2C_SET_ON_GEM,                   Item_Msg_Proc::on_set_on_gem);									  // 装备宝石
    reg_interface(S2C_SET_OFF_GEM,                  Item_Msg_Proc::on_set_off_gem);									  // 卸下宝石
    reg_interface(S2C_GEM_LEVEL_UP,                 Item_Msg_Proc::on_gem_level_up);								  // 合成宝石

    reg_interface(S2C_CREATE_ITEM,                  Item_Msg_Proc::on_create_item);
    reg_interface(S2C_CREATE_MATERIAL_FRAGMENT,     Item_Msg_Proc::on_create_material_fragment);
    reg_interface(S2C_CREATE_BOOK_FRAGMENT,         Item_Msg_Proc::on_create_book_fragment);
    reg_interface(S2C_ITEM_CLIENT_SHOW,             Item_Msg_Proc::on_item_client_show);

    // item_container
    reg_interface(S2C_LOAD_ITEM_CONTAINER,          Item_Container_Msg_Proc::on_load_item_container);
    reg_interface(S2C_ADD_ITEM_CONTAINER,           Item_Container_Msg_Proc::on_add_item_container);
    reg_interface(S2C_UPDATE_ITEM_CONTAINER,        Item_Container_Msg_Proc::on_update_item_container);

	reg_interface(SC_LOAD_SKILL,					SkillMsgProc::on_load_skill);
	reg_interface(SC_UPLEVEL_SKILL,					SkillMsgProc::on_uplevel_skill);
	//reg_interface(SC_CREATE_SKILL,					Job_Skill_Msg_Proc::on_create_skill);
	//reg_interface(SC_CHANGE_SELECT_SKILL,			Job_Skill_Msg_Proc::on_change_select_skill);

    //quest
    reg_interface(RETURN_QUEST_UPDATE,             quest_msg_proc_client::on_quest_update);
    reg_interface(RETURN_NPC_QUEST_BIND_LIST,      quest_msg_proc_client::on_update_npc_quest_bind_list);			  // 更新当前Npc的请求结合列表
    reg_interface(RETURN_QUEST_SUBMIT_RESULT,      quest_msg_proc_client::on_quest_submuit_result);					  // 任务结束弹出任务结束的界面
	
    //shop
    reg_interface(SC_LOAD_SHOPING_RECORD,   Shop_Msg_Proc::on_load_shoping_record);
	reg_interface(SC_BUY_ITEM,              Shop_Msg_Proc::on_buy_item);

	// deputy_general
//	reg_interface(SC_LOAD_DEPUTY_GENERAL,           Deputy_General_Msg_Proc::on_load_deputy_general);
//	reg_interface(SC_DEPUTY_GENERAL_FIGHT,          Deputy_General_Msg_Proc::on_deputy_general_fight);
//    reg_interface(SC_DEPUTY_GENERAL_CANCEL_FIGHT,   Deputy_General_Msg_Proc::on_deputy_general_cancel_fight);
//    reg_interface(SC_CREATE_DEPUTY_GENERAL,         Deputy_General_Msg_Proc::on_create_deputy_general);

	// relation
	reg_interface(SC_ADD_FRIEND,				Relation_Msg_Proc::on_add_friend_from_apply);
	reg_interface(SC_ALLPY_FRIEND_DATA,			Relation_Msg_Proc::on_add_friend);
	reg_interface(SC_DEL_FRIEND,				Relation_Msg_Proc::on_del_friend);
	reg_interface(SC_ASK_FRIEND_INFO,           Relation_Msg_Proc::on_ask_friend_info);
	reg_interface(SC_ASK_FRIEND_LIST,           Relation_Msg_Proc::on_ask_friend_list);

    /*// offline_fight
    reg_interface(S2C_LOAD_OFFLINE_FIGHT,                           Offline_Fight_Msg_Proc::on_load_offline_fight);
    reg_interface(S2C_OFFLINE_FIGHT_START,                          Offline_Fight_Msg_Proc::on_offline_fight_start);
    reg_interface(S2C_OFFLINE_FIGHT_FINISH,                         Offline_Fight_Msg_Proc::on_offline_fight_finish);
    reg_interface(S2C_PLAYER_BUY_OFFLINE_FIGHT_COUNT,               Offline_Fight_Msg_Proc::on_player_buy_offline_fight_count);
    reg_interface(S2C_GET_OFFLINE_FIGHT_RANK_REWARD,                Offline_Fight_Msg_Proc::on_get_offline_fight_rank_reward);
    reg_interface(S2C_GET_OFFLINE_FIGHT_RANK_REWARD_REMAINING_TIME, Offline_Fight_Msg_Proc::on_get_offline_fight_rank_reward_remaining_time);

	// online_fight
	// offline_fight
	reg_interface(S2C_LOAD_ONLINE_FIGHT,                           Online_Fight_Msg_Proc::on_load_online_fight);
	reg_interface(S2C_ONLINE_FIGHT_START,                          Online_Fight_Msg_Proc::on_online_fight_start);
	reg_interface(S2C_ONLINE_FIGHT_FINISH,                         Online_Fight_Msg_Proc::on_online_fight_finish);
	reg_interface(S2C_ONLINE_FIGHT_MOVE,                           Online_Fight_Msg_Proc::on_online_fight_move);
	reg_interface(S2C_ONLINE_FIGHT_USE_SKILL,                      Online_Fight_Msg_Proc::on_online_fight_use_skill);
	reg_interface(S2C_ONLINE_FIGHT_RESULT,                         Online_Fight_Msg_Proc::on_online_fight_result);*/
	

    // acupoint
    reg_interface(S2C_LOAD_ACUPOINT,            Acupoint_Msg_Proc::on_load_acupoint);
    reg_interface(S2C_OPEN_ACUPOINT,            Acupoint_Msg_Proc::on_open_acupoint);

    reg_interface(S2C_CREATE_ACUPOINT,          Acupoint_Msg_Proc::on_create_acupoint);

	// public annoucement
	//reg_interface(S2C_ASK_PUBLIC_ANNOUCEMENT,          Public_Annoucement_Msg_Proc::on_ask_pubilc_annoucement);

    // cool_time
    reg_interface(S2C_LOAD_COOL_TIME,           Cool_Time_Msg_Proc::on_load_cool_time);
    reg_interface(S2C_CLEAN_COOL_TIME,          Cool_Time_Msg_Proc::on_clean_cool_time);
    reg_interface(S2C_CREATE_COOL_TIME,         Cool_Time_Msg_Proc::on_create_cool_time);

	// partition server list
	reg_interface(S2C_ASK_PARTITION_SERVER_LIST,         Partition_Msg_Proc_Cl::on_ask_partition_info);

	//exchange code
	reg_interface(S2C_ASK_EXCHANGE_CODE_INFO,	Award_Msg_Proc::on_ask_exchange_code_info);

	//banks 
	reg_interface(S2C_EXCHANGE_TOKEN_TO_GOLD,	    Banks_Msg_Proc::on_exchange_token_to_gold);

    // rank
    reg_interface(S2C_LOAD_RANK,                            Rank_Msg_Proc::on_load_rank);
    reg_interface(S2C_LOAD_RANK_ROLE_LEVEL,                 Rank_Msg_Proc::on_load_rank_role_level);
    reg_interface(S2C_LOAD_RANK_ROLE_FIGHTING_CAPACITY,     Rank_Msg_Proc::on_load_rank_role_fighting_capacity);
    reg_interface(S2C_LOAD_RANK_ROLE_HAVE_GOLD,             Rank_Msg_Proc::on_load_rank_role_have_gold);

    // login_reward
    reg_interface(S2C_LOAD_LOGIN_REWARD,                    Login_Reward_Msg_Proc::on_load_login_reward);
    reg_interface(S2C_GET_LOGIN_REWARD,                     Login_Reward_Msg_Proc::on_get_login_reward);

	//  radiate
	reg_interface(S2C_RADIATE_SYSTEM,                     Radiate_Msg_Proc::PlaySystemMsgForUI);
	reg_interface(S2C_RADIATE_PLAYER,                     Radiate_Msg_Proc::PlayPlayerMsgForUI);

    //activity
    reg_interface(S2C_LOAD_ACTIVITY_RECORD,          Activity_Msg_Proc::on_load_activity_record);
    reg_interface(S2C_ACTIVITY_SIX_SECT,             Activity_Msg_Proc::on_activity_six_sect);

    // 每日任务
    reg_interface(S2C_LOAD_DAILY_TASK,						Daily_Task_Msg_Proc::on_load_daily_task);
    reg_interface(S2C_DROP_DAILY_TASK,						Daily_Task_Msg_Proc::on_drop_daily_task);
    reg_interface(S2C_SUBMIT_DAILY_TASK,					Daily_Task_Msg_Proc::on_submit_daily_task);
    reg_interface(S2C_REFRESH_DAILY_TASK_STAR_LEVEL,		Daily_Task_Msg_Proc::on_refresh_daily_task_star_level);
    reg_interface(S2C_SET_DAILY_TASK_STAR_LEVEL_MAX,		Daily_Task_Msg_Proc::on_set_daily_task_star_level_max);
    reg_interface(S2C_TOKEN_COMPLETE_DAILY_TASK,			Daily_Task_Msg_Proc::on_token_complete_daily_task);
    reg_interface(S2C_GET_DAILY_TASK_GIFT_ONE,				Daily_Task_Msg_Proc::on_get_daily_task_gift_one);
    reg_interface(S2C_GET_DAILY_TASK_GIFT_TWO,				Daily_Task_Msg_Proc::on_get_daily_task_gift_two);
    reg_interface(S2C_GET_DAILY_TASK_GIFT_THREE,			Daily_Task_Msg_Proc::on_get_daily_task_gift_three);
    reg_interface(S2C_UPDATE_DAILY_TASK_PROGRESS,			Daily_Task_Msg_Proc::on_update_daily_task_progress);

    return 0;
}

int Msg_Proc::process_network_message(message_stream& msg)
{
    int msg_id;

    msg >> msg_id;

    //if( msg_id >= CLIENT_AUTH_SESSION &&  msg_id <= SERVER_KEEP_ALIVE )
    //    cocos2d::CCLog("Msg_Proc::process_message %d\n", msg_id);

    vector<uint64> para; para.clear();
 
    int read_size;
    instance()->exec_interface(msg_id, para, (char*)msg.get_ptr(), msg.length(), read_size);
    return 0;
}

bool Msg_Proc::process_message(Game_Logic::Game_Interface& gm_interface)
{
    Msg_Data md;
    string server_type = gm_interface.get_keyword();
    if( !server_type.compare("gate") )
    {

       do {
        if ( -1 == Msg_Manager::instance()->pop_msg_list(md) )
            return false;

        instance()->do_process_message( (char*)md.get_buff(), md.get_size());
       } while( -1 == Msg_Manager::instance()->is_empty());
    }
    else
    {
        if( 0 == Msg_Manager::instance()->is_engine_empty() )
            return false;
        if ( -1 == Msg_Manager::instance()->pop_engine_msg_list(md) )
            return false;
    }

    return true;
}

int Msg_Proc::do_process_message(char* buff, int size)
{
    message_stream body_ms(buff, size);

    int msg_id;
    uint len = body_ms.length();
    int pak_len = 0;
    body_ms >> pak_len;
    body_ms >> msg_id;
    int read_size = 0;
    char buff_pars[65536];
    memcpy(buff_pars, buff + sizeof(int), pak_len );
   if( msg_id >= CLIENT_AUTH_SESSION &&  msg_id <= SERVER_KEEP_ALIVE )
   {
        vector<uint64> para; para.clear();
 
        instance()->exec_interface(msg_id, para, buff_pars, pak_len, read_size);
   }

    return 0;
}

bool Msg_Proc::reg_interface( int cmd, Game_Logic::game_interface_handler_t handle)
{
	Game_Logic::game_interface_handler_uint_map_t::iterator itgi;
	itgi = msg_hanler_.find(cmd);
	if( itgi == msg_hanler_.end() )
	{
		msg_hanler_.insert(make_pair(cmd, handle));
		return true;
	}
	return false;
}
bool Msg_Proc::exec_interface( int cmd, const vector<uint64>& para, const char* key_word, int size, int& read_size )
{
	Game_Logic::game_interface_handler_uint_map_t::iterator itgi;
	itgi = msg_hanler_.find(cmd);
    bool result = false;
	if( itgi != msg_hanler_.end() )
	{
		Game_Logic::Game_Interface gm_arg;
		gm_arg.set_para( para );
        gm_arg.set_buff(key_word,size);

		result = (*itgi->second)(gm_arg);
        read_size = gm_arg.get_read_size();
        return result;

	}
    return true;
}

