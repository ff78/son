#include "game_content_interface.h"
#include "event_define.h"

#include "Play_System/Container_Logic.h"
#include "Play_System/Formula_Logic.h"

#ifdef GAME_CLIENT
#include "UI_Interface/UI_MainMenu_Layer.h"
#include "UI_Interface/UI_Logic.h"
#include "UI_Interface/CocoStu_UI_Scene_Logic.h"
#include "Network/msg_proc.h"
#include "Player_Account/Account_Msg_Proc.h"
#include "Player_Account/Account_Logic.h"
#include "UI_Interface/Select_Server_UI.h"
#include "Network_Common/NetManager.h"
#include "Character_System/Character_Logic.h"
#include "UI_Interface/UI_Function_Instance.h"
#include "Play_System/Client_Instance_Msg_Proc.h"
#include "Character_System/Player_Msg_Proc_Cl.h"
#include "Item_System/Item_Msg_Proc_Cl.h"
#include "Item_Container_System/Item_Container_Msg_Proc_Cl.h"
//#include "Skill_System/Skill/Skill_Msg_Proc.h"
#include "Play_System/Formula_Function_Instance.h"
#include "Play_System/Formula_Function_Instance_Client.h"
#include "Play_System/Formula_Function_Monster_Wave.h"
#include "Shop_System/Shop_Msg_Proc_Cl.h"
#include "quest_system/quest_logic/quest_logic_client.h"
#include "quest_system/quest_logic/quest_msg_proc_client.h"
#include "quest_system/quest_logic/quest_npc_logic.h"
#include "quest_system/quest_logic/quest_logic.h"
//#include "Character_System/Deputy_General_Msg_Proc.h"
#include "Relation_System/Relation_Msg_Proc.h"
#include "Event_System/event_system_logic.h"
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
#include "RadiateSystem/Radiate_Msg_Proc.h"
#include "Activity_System/Activity_Msg_Proc_Cl.h"
#include "Daily_Task_System/Daily_Task_Msg_Proc_Cl.h"
#else //for game server
#include "message_proc/message_proc.h"
#include "Play_System/Formula_Function_Instance.h"
#include "Play_System/Instance_DB_Proc.h"
#include "Play_System/Instance_Msg_proc.h"
#include "Item_System/Item_Msg_Proc_Sv.h"
#include "Item_System/Item_DB_Proc.h"
#include "Item_Container_System/Item_Container_Msg_Proc_Sv.h"
#include "Item_Container_System/Item_Container_DB_Proc.h"
#include "Skill_System/Skill_DB_Proc.h"
#include "Skill_System/Skill_Msg_Proc_Sv.h"
#include "Character_System/MainCityPlayer_Mgr.h"
#include "Character_System/Player_Msg_Proc_Sv.h"
#include "quest_system/quest_logic/quest_msg_proc.h"
#include "quest_system/quest_logic/quest_logic.h"
#include "quest_system/quest_logic/quest_db_proc.h"
#include "Character_System/Role_DB_Proc_Attr.h"
#include "Character_System/Role_DB_Proc_Info.h"
#include "quest_system/quest_logic/quest_npc_logic.h"
#include "Character_System/Character_Logic.h"
#include "Character_System/Deputy_General_DB_Proc.h"
#include "Character_System/Deputy_General_Msg_Proc_Sv.h"
#include "Relation_System/Relation_Msg_Proc_Sv.h"
#include "Relation_System/Relation_DB_Proc.h"
#include "Fight_System/Offline_Fight_Record_DB_Proc.h"
#include "Fight_System/Offline_Fight_Msg_Proc_Sv.h"
#include "Acupoint_System/Acupoint_DB_Proc.h"
#include "Acupoint_System/Acupoint_Msg_Proc_Sv.h"
#include "Cool_Time_System/Cool_Time_DB_Proc.h"
#include "Cool_Time_System/Cool_Time_Msg_Proc_Sv.h"
#include "game_interface/game_data_exchange.h"
#include "Event_System/Event_Function_Instance.h"
#include "Scene_System/scene_logic.h"
#include "Award_System/Award_DB_Proc.h"
#include "Banks_System/Banks_Msg_Proc_Srv.h"
#include "Rank_System/Rank_Msg_Proc_Sv.h"
#include "Login_Reward_System/Login_Reward_Msg_Proc_Sv.h"
#include "Login_Reward_System/Login_Reward_DB_Proc.h"
#include "Shop_System/Shop_Msg_Proc_Sv.h"
#include "Shop_System/Shoping_Record_DB_Proc.h"
#include "RadiateSystem/Radiate_Msg_Proc.h"
#include "Activity_System/Activity_Msg_Proc_Sv.h"
#include "Activity_System/Activity_Record_DB_Proc.h"
#include "Daily_Task_System/Daily_Task_Msg_Proc_Sv.h"
#include "Daily_Task_System/Daily_Task_DB_Proc.h"

#endif
/************************************* dely ***********************************/
#include "ClientLogic/GameScene/ResultLayer.h"
#include "../Character_System/Player_Msg_Proc_Cl.h"
#include "../Faction_System/Faction_Client.h"
#include "../Emai_System/Email_Client.h"
#include "../Pet_System/Pet_Client.h"
#include "../God_System/God_Client.h"
/************************************* dely ***********************************/
namespace Game_Logic
{

	Game_Content_Interface* Game_Content_Interface::instance_p_ = 0;

	Game_Content_Interface::Game_Content_Interface(void)
	{

	}

	Game_Content_Interface::~Game_Content_Interface(void)
	{
		if( instance_p_ )
			delete instance_p_;
	}

	Game_Content_Interface* Game_Content_Interface::instance(void)
	{
		if( NULL == instance_p_ )
		{
			instance_p_ = new Game_Content_Interface;
		}
		
		return instance_p_;
	}
#ifdef GAME_CLIENT
	void Game_Content_Interface::init( void )
	{


        // UI
		reg_interface("execUI",										UI_Logic::exec_UI);
		reg_interface("cocostudioUI",								CocoStu_UI_Scene_Logic::exec_UI_Scene);
        reg_interface("createbuttonlist",							Select_Server_UI::create_button_list);
        reg_interface("setbuttonname",								Select_Server_UI::set_button_name);
        reg_interface("shownextui",									Select_Server_UI::show_next_ui);

        // Network process
        reg_interface("procmsg",									Msg_Proc::process_message);
        reg_interface("doconnectgate",								 CNetManager::connetect_to_gate);

        //player account
        reg_interface("save_player",                                Account_Msg_Proc::on_save_player);
        reg_interface("send_player_login",							Account_Msg_Proc::send_player_login);
        reg_interface("send_player_start_game",						Account_Msg_Proc::send_player_start_game);
        reg_interface("connecttogate",								Account_Logic::connect_to_gate_server);
        reg_interface("connecttogame",								CNetManager::connetect_to_game_server);
		reg_interface("closeserver",								CNetManager::close_server);

        reg_interface("sendkeepalive",								Account_Msg_Proc::send_keep_alive);
		reg_interface("send_create_role",							Account_Msg_Proc::send_create_role);

        //scene
        reg_interface("enterscene",									UI_Function_Instance::enter_scene);
		//event system
		reg_interface("loadeventsystemdata",						event_system_logic::load_event_data);

        //instance proc
		reg_interface("createcontainer",							Container_Logic::create_container);
		reg_interface("loadformuladata",							Formula_Logic::load_formula_data);
        reg_interface("enterinstance",								Client_Instance_Msg_Proc::enter_instance);
        reg_interface("selectinstance",								Client_Instance_Msg_Proc::select_instance);
        reg_interface("regmonsterdie",								Formula_Function_Instance_Client::reg_monster_die_envent);
        reg_interface("procenterinstance",							Formula_Function_Instance_Client::proc_enter_instance);
        reg_interface("finishmonstercreate",						Formula_Function_Monster_Wave::on_finish_create_monster);
        reg_interface("nextmonsterwave",							Formula_Function_Monster_Wave::process_next_wave_monster);

        reg_interface("sendfinishinstance",							Client_Instance_Msg_Proc::send_instance_finish);
        reg_interface("sendmonsterkill",							Client_Instance_Msg_Proc::send_monster_kill);
        reg_interface("send_instance_sweep",						Client_Instance_Msg_Proc::send_instance_sweep);

        reg_interface("playerinstancebackhome",						Formula_Function_Instance_Client::process_instance_player_back_home);
        reg_interface("showinstancedialog",							Formula_Function_Instance_Client::show_instance_dialog);
        reg_interface("showmonsterwave",							Formula_Function_Instance_Client::show_monster_wave);
        reg_interface("remvoeinstancedata",							Formula_Function_Instance_Client::remove_instance_data);
        reg_interface("processinstancefail",						Formula_Function_Instance_Client::proc_instance_fail );
        reg_interface("processinstancefinish",						Formula_Function_Instance_Client::proc_instance_finish );
        reg_interface("oninstancefinish",							Formula_Function_Monster_Wave::on_instance_finish);
        /************************************* dely ***********************************/
		reg_interface("waiting",									ResultLayer::waiting);
//        reg_interface("pop_result",									ResultLayer::popResult);
//		reg_interface("on_recieved next",							ResultLayer::onReceivedNext);
		reg_interface("sendbackmaincity",							Client_Instance_Msg_Proc::send_back_main_city);
		/*-------------- email ---------------*/
		reg_interface(EVENT_EMAIL_SEND_LOAD,						EMAIL_NET::send_load_email);
		reg_interface(EVENT_EMAIL_SEND_SEND,						EMAIL_NET::send_send_email);
		reg_interface(EVENT_EMAIL_SEND_OPEN,						EMAIL_NET::send_open_email);
		//reg_interface(EVENT_EMAIL_SEND_DELETE,					Game_Net::send_delete_email);
		reg_interface(EVENT_EMAIL_SEND_DELETE,						EMAIL_NET::send_delete_email);

		/*-------------- faction ---------------*/
		reg_interface(EVENT_FACTION_SEND_LIMIT,						FACTION_NET::send_faction_join_limit);
		//reg_interface(EVENT_FACTION_SEND_SEARCH,					FACTION_NET::send_faction_search);
		reg_interface(EVENT_FACTION_SEND_CREATE,					FACTION_NET::send_faction_create);
		//reg_interface(EVENT_FACTION_SEND_JOIN,					FACTION_NET::send_faction_join);
		reg_interface(EVENT_FACTION_SEND_GET_DATA,					FACTION_NET::send_get_faction_data);
		reg_interface(EVENT_FACTION_SEND_CHALLENGE,					FACTION_NET::send_faction_member_dekaron_boos);
		reg_interface(EVENT_FACTION_SEND_RENOTICE,					FACTION_NET::send_faction_set_notice);
		reg_interface(EVENT_FACTION_SEND_REJOB,						FACTION_NET::send_faction_set_job);
		reg_interface(EVENT_FACTION_SEND_DONATE,					FACTION_NET::send_faction_member_donation);	
		reg_interface(EVENT_FACTION_SEND_KICK,					    FACTION_NET::send_faction_kick_member);
		reg_interface(EVENT_FACTION_SEND_DIG,						FACTION_NET::send_faction_member_digging);
		reg_interface(EVENT_FACTION_SEND_TOTEMUP,					FACTION_NET::send_faction_totems_up);
		reg_interface(EVENT_FACTION_SEND_WORSHIP,					FACTION_NET::send_faction_member_worship);
		reg_interface("sendmemberkillboss",							FACTION_NET::send_faction_member_kill_boos);

		reg_interface(EVENT_PET_SEND_UPGRADE,						PET_NET::send_upgrade);
		reg_interface(EVENT_PET_SEND_CHANGE,						PET_NET::send_change_state);

		reg_interface(EVENT_GOD_SEND_UPGRADE,						GOD_NET::send_upgrade);
        /************************************* dely ***********************************/
        
		reg_interface("sendrequirestagestate",						Client_Instance_Msg_Proc::send_require_stage_instance_list);
		reg_interface("sendrequirestage",							Client_Instance_Msg_Proc::send_reuqire_stage);
        reg_interface("sendrequireallstage",						Client_Instance_Msg_Proc::send_require_all_stage);
        reg_interface("sendbegininstancetimer",						Client_Instance_Msg_Proc::send_begin_instance_timer);
        reg_interface("sendinstanceplayerdie",						Client_Instance_Msg_Proc::send_instance_player_die );
		reg_interface("sendrequirechallengenext",					Client_Instance_Msg_Proc::send_require_challenge_next_instance);// 玩家请求挑战下一关
		reg_interface("next_instance_msg_been_received",			ResultLayer::NextInstanceDataBeenReceived);// 玩家进入副本的消息已经被接收

        // player

        reg_interface("send_get_main_city_player",                  Player_Msg_Proc::send_get_main_city_player);
        reg_interface("send_player_move",                           Player_Msg_Proc::send_player_move);
		reg_interface("send_get_player_info",                       Player_Msg_Proc::send_get_player_info);
        reg_interface("send_chat_msg",                              Player_Msg_Proc::send_chat_msg);
		reg_interface("send_player_revive",                         Player_Msg_Proc::send_player_revive);
        reg_interface("send_player_buy_energy",                     Player_Msg_Proc::send_player_buy_energy);
		reg_interface("send_player_quality_up",                     Player_Msg_Proc::send_player_quality_up);
		reg_interface("send_player_instance_collided_something",    Player_Msg_Proc::send_player_instance_collided_something);
		reg_interface("send_player_useitem_something",			    Player_Msg_Proc::send_player_useitem_something);

        // item_container
        reg_interface("send_load_item_container",					Item_Container_Msg_Proc::send_load_item_container);
        reg_interface("send_add_item_container",					Item_Container_Msg_Proc::send_add_item_container);

        // item
        reg_interface("send_load_item",								Item_Msg_Proc::send_load_item);
        reg_interface("send_load_material_fragment",				Item_Msg_Proc::send_load_material_fragment);
        reg_interface("send_load_book_fragment",					Item_Msg_Proc::send_load_book_fragment);
        reg_interface("send_tidy_item",								Item_Msg_Proc::send_tidy_item);
        reg_interface("send_equip_equipment",						Item_Msg_Proc::send_equip_equipment);
        reg_interface("send_take_off_equipmen",						Item_Msg_Proc::send_take_off_equipmen);
        reg_interface("send_equip_book",							Item_Msg_Proc::send_equip_book);
        reg_interface("send_take_off_book",							Item_Msg_Proc::send_take_off_book);
        reg_interface("send_equipment_level_up",					Item_Msg_Proc::send_equipment_level_up);
        reg_interface("send_equipment_quality_up",					Item_Msg_Proc::send_equipment_quality_up);
        reg_interface("send_book_level_up",							Item_Msg_Proc::send_book_level_up);
        reg_interface("send_book_quality_up",						Item_Msg_Proc::send_book_quality_up);
        reg_interface("send_sell_item",								Item_Msg_Proc::send_sell_item);
        reg_interface("send_use_item",								Item_Msg_Proc::send_use_item);
        reg_interface("send_compound_material_fragment",			Item_Msg_Proc::send_compound_material_fragment);
        reg_interface("send_compound_book_fragment",				Item_Msg_Proc::send_compound_book_fragment);
        reg_interface("send_set_on_gem",							Item_Msg_Proc::send_set_on_gem);
        reg_interface("send_set_off_gem",							Item_Msg_Proc::send_set_off_gem);
        reg_interface("send_gem_level_up",							Item_Msg_Proc::send_gem_level_up);
		
        // skill
		/*reg_interface("send_load_skill",							Skill_Msg_Proc::send_load_skill);
		reg_interface("send_uplevel_skill",							Skill_Msg_Proc::send_uplevel_skill);*/

//		reg_interface("send_load_skill",							Job_Skill_Msg_Proc::send_load_skill);
//		reg_interface("send_uplevel_skill",							Job_Skill_Msg_Proc::send_uplevel_skill);	
//#if 1//yypp			
//		reg_interface("change_select_skill", 						Job_Skill_Msg_Proc::send_change_select_skill);
//#endif		

		// shop
        reg_interface("send_load_shoping_record",					Shop_Msg_Proc::send_load_shoping_record);
		reg_interface("send_buy_item",								Shop_Msg_Proc::send_buy_item);

        //quest
        reg_interface("procupdatequest",							quest_logic_client::proc_update_quest);					  // 玩家点击接受任务,服务器返回消息之后注册的方法
        reg_interface("isquestdone",								quest_logic_client::is_quest_done);
        reg_interface("sendacceptquest",							quest_msg_proc_client::send_accept_quest);
        reg_interface("sendsubmitquest",							quest_msg_proc_client::send_submit_quest);
        reg_interface("sendreqnpcquest",							quest_msg_proc_client::send_require_npc_quest_bind);
        reg_interface("sendreqquestlist",							quest_msg_proc_client::send_require_quest_list);
        reg_interface("procnpcquestbind",							quest_npc_logic::proc_npc_quest_bind);
		reg_interface("iscanacceptquest",							quest_logic::is_can_accept_quest);
		reg_interface("iscansubmitquest",							quest_logic::is_can_submit_quest);
		reg_interface("isquestinprocess",							quest_logic::is_quest_in_process);

		//character system
//        reg_interface("initcharacterskilllist",             Character_Logic::init_character_skill_list);
//		reg_interface("send_load_deputy_general",           Deputy_General_Msg_Proc::send_load_deputy_general);
//		reg_interface("send_deputy_general_fight",          Deputy_General_Msg_Proc::send_deputy_general_fight);
//		reg_interface("send_deputy_general_cancel_fight",   Deputy_General_Msg_Proc::send_deputy_general_cancel_fight);
		
		// relation
		reg_interface("send_add_friend",            Relation_Msg_Proc::send_add_friend);
		reg_interface("send_del_friend",            Relation_Msg_Proc::send_del_friend);
		reg_interface("send_ask_friend_info",       Relation_Msg_Proc::send_ask_friend_info);
		reg_interface("send_ask_friend_list",       Relation_Msg_Proc::send_ask_friend_list);

       /* // offline_fight
        reg_interface("send_load_offline_fight",                    Offline_Fight_Msg_Proc::send_load_offline_fight);
        reg_interface("send_offline_fight_start",                   Offline_Fight_Msg_Proc::send_offline_fight_start);
        reg_interface("send_offline_fight_finish",                  Offline_Fight_Msg_Proc::send_offline_fight_finish);
        reg_interface("send_player_buy_offline_fight_count",        Offline_Fight_Msg_Proc::send_player_buy_offline_fight_count);
        reg_interface("send_get_offline_fight_rank_reward",         Offline_Fight_Msg_Proc::send_get_offline_fight_rank_reward);

		// online_fight
		reg_interface("send_load_online_fight",                    Online_Fight_Msg_Proc::send_load_online_fight);
		reg_interface("send_online_fight_start",                   Online_Fight_Msg_Proc::send_online_fight_start);
		reg_interface("send_online_fight_finish",                  Online_Fight_Msg_Proc::send_online_fight_finish);
		reg_interface("send_online_fight_move",                    Online_Fight_Msg_Proc::send_online_fight_move);
		reg_interface("send_online_fight_use_skill",               Online_Fight_Msg_Proc::send_online_fight_use_skill);
		reg_interface("send_online_fight_result",                  Online_Fight_Msg_Proc::send_online_fight_result);*/

        // acupoint
        reg_interface("send_load_acupoint",                 Acupoint_Msg_Proc::send_load_acupoint);
        reg_interface("send_open_acupoint",                 Acupoint_Msg_Proc::send_open_acupoint);

		// public annoucement
		reg_interface("send_ask_pubilc_annoucement",                 Public_Annoucement_Msg_Proc::send_ask_pubilc_annoucement);

        // cool_time
        reg_interface("send_load_cool_time",                Cool_Time_Msg_Proc::send_load_cool_time);
        reg_interface("send_clean_cool_time",               Cool_Time_Msg_Proc::send_clean_cool_time);

		// partition server list
		reg_interface("send_ask_partition_info",                 Partition_Msg_Proc_Cl::send_ask_partition_info);

		// exchange code
		reg_interface("send_ask_exchange_code_info",                 Award_Msg_Proc::send_ask_exchange_code_info);

		// banks exchange token to gold
		reg_interface("send_exchange_token_to_gold",			    Banks_Msg_Proc::send_exchange_token_to_gold);

        // rank
        reg_interface("send_load_rank",                         Rank_Msg_Proc::send_load_rank);
        reg_interface("send_load_rank_role_level",              Rank_Msg_Proc::send_load_rank_role_level);
        reg_interface("send_load_rank_role_fighting_capacity",  Rank_Msg_Proc::send_load_rank_role_fighting_capacity);
        reg_interface("send_load_rank_role_have_gold",          Rank_Msg_Proc::send_load_rank_role_have_gold);

        // login_reward
        reg_interface("send_load_login_reward",                 Login_Reward_Msg_Proc::send_load_login_reward);
        reg_interface("send_get_login_reward",                  Login_Reward_Msg_Proc::send_get_login_reward);

        // activity
        reg_interface("send_load_activity_record",  Activity_Msg_Proc::send_load_activity_record);
        reg_interface("send_activity_six_sect",     Activity_Msg_Proc::send_activity_six_sect);

        // daily_task
        reg_interface("send_load_daily_task",               Daily_Task_Msg_Proc::send_load_daily_task);
        reg_interface("send_drop_daily_task",               Daily_Task_Msg_Proc::send_drop_daily_task);
        reg_interface("send_submit_daily_task",             Daily_Task_Msg_Proc::send_submit_daily_task);
        reg_interface("send_refresh_daily_task_star_level", Daily_Task_Msg_Proc::send_refresh_daily_task_star_level);
        reg_interface("send_set_daily_task_star_level_max", Daily_Task_Msg_Proc::send_set_daily_task_star_level_max);
        reg_interface("send_token_complete_daily_task",     Daily_Task_Msg_Proc::send_token_complete_daily_task);
        reg_interface("send_get_daily_task_gift_one",       Daily_Task_Msg_Proc::send_get_daily_task_gift_one);
        reg_interface("send_get_daily_task_gift_two",       Daily_Task_Msg_Proc::send_get_daily_task_gift_two);
        reg_interface("send_get_daily_task_gift_three",     Daily_Task_Msg_Proc::send_get_daily_task_gift_three);

	}
#else  //for game server
	void Game_Content_Interface::init( void )
	{
         //scene system
        reg_interface("procplayerlogout",           Game_Logic::scene_logic::proc_logout);
        reg_interface("procplayermove",             Game_Logic::scene_logic::proc_player_move);

        reg_interface("procplayerlogin",            game_data_exchange::on_player_login);
        reg_interface("procplayerlogout",           game_data_exchange::on_player_logout);

        // Network process
        reg_interface("procmsg",                    Message_Proc::process_message);

        //formula system
		reg_interface("createcontainer",            Container_Logic::create_container);
		reg_interface("loadformuladata",            Formula_Logic::load_formula_data);
		reg_interface("execformula",                Formula_Logic::exec_formula);

        //instance logic
        reg_interface("sendinstancereq",            Instance_Msg_Proc::send_player_enter_instance );
        reg_interface("sendinstancemonster",        Instance_Msg_Proc::send_player_instance_monster_wave );
        reg_interface("sendinstancefinishresult",   Instance_Msg_Proc::send_player_instance_finsish_result );
        reg_interface("sendinstanceprogress",       Instance_Msg_Proc::send_player_instance_progress);
        reg_interface("send_instance_sweep",        Instance_Msg_Proc::send_instance_sweep);

        reg_interface("instancebegin",              Formula_Function_Instance::instance_begin );
        reg_interface("instanceresult",             Formula_Function_Instance::process_instance_result );
        reg_interface("procplayerlogin",            Formula_Function_Instance::proc_login );
        reg_interface("procplayerlogout",           Formula_Function_Instance::proc_logout );
        reg_interface("processintancetimercheck",   Formula_Function_Instance::proc_instance_timer_check );
        reg_interface("processintanceplayerdie",   Formula_Function_Instance::proc_instance_player_die );
        reg_interface("saveinstanceresult",         Instance_DB_Proc::save_instance_result );
        reg_interface("loadinstancefromdb",          Instance_DB_Proc::load_player_instance );
        // player
        reg_interface("send_player_into_main_city", MainCityPlayer_Mgr::send_player_into_main_city);
        reg_interface("send_player_quit_main_city", MainCityPlayer_Mgr::send_player_quit_main_city);
        reg_interface("send_get_main_city_player",  MainCityPlayer_Mgr::send_get_main_city_player);
        reg_interface("send_player_move",           MainCityPlayer_Mgr::send_player_move);

        reg_interface("send_change_token",              Player_Msg_Proc::send_change_token);
		reg_interface("send_add_recharge_token",        Player_Msg_Proc::send_add_recharge_token);
        reg_interface("send_change_energy",             Player_Msg_Proc::send_change_energy);
        reg_interface("send_change_prestige",           Player_Msg_Proc::send_change_prestige);
        reg_interface("send_change_gold",               Player_Msg_Proc::send_change_gold);
        reg_interface("send_change_exp",                Player_Msg_Proc::send_change_exp);
		reg_interface("send_get_player_info",           Player_Msg_Proc::send_get_player_info);
		reg_interface("send_player_revivie",		    Player_Msg_Proc::send_player_revivie);
        reg_interface("send_player_buy_energy",		    Player_Msg_Proc::send_player_buy_energy);
        reg_interface("send_player_quality_up",		    Player_Msg_Proc::send_player_quality_up);

        //character system
        reg_interface("sql_insert_deputy_general",              Deputy_General_DB_Proc::sql_insert_deputy_general);
        reg_interface("sql_select_deputy_general",              Deputy_General_DB_Proc::sql_select_deputy_general);
        reg_interface("sql_update_deputy_general",              Deputy_General_DB_Proc::sql_update_deputy_general);
        reg_interface("sql_update_deputy_general_quality_up",   Deputy_General_DB_Proc::sql_update_deputy_general_quality_up);
        reg_interface("sql_update_deputy_general_exp",          Deputy_General_DB_Proc::sql_update_deputy_general_exp);
        reg_interface("sql_update_deputy_general_level",        Deputy_General_DB_Proc::sql_update_deputy_general_level);
        reg_interface("create_default_deputy_general",          Deputy_General_DB_Proc::create_default_deputy_general);

        reg_interface("send_load_deputy_general",           Deputy_General_Msg_Proc::send_load_deputy_general);
        reg_interface("send_deputy_general_fight",          Deputy_General_Msg_Proc::send_deputy_general_fight);
        reg_interface("send_deputy_general_cancel_fight",   Deputy_General_Msg_Proc::send_deputy_general_cancel_fight);
        reg_interface("send_create_deputy_general",         Deputy_General_Msg_Proc::send_create_deputy_general);
        reg_interface("procplayerlogin",                    Deputy_General_Msg_Proc::send_load_deputy_general);

        // item
        reg_interface("send_load_item",                 Item_Msg_Proc::send_load_item);
        reg_interface("send_load_material_fragment",    Item_Msg_Proc::send_load_material_fragment);
        reg_interface("send_load_book_fragment",        Item_Msg_Proc::send_load_book_fragment);
        reg_interface("send_tidy_item",                 Item_Msg_Proc::send_tidy_item);
        reg_interface("send_equip_equipment",           Item_Msg_Proc::send_equip_equipment);
        reg_interface("send_take_off_equipmen",         Item_Msg_Proc::send_take_off_equipmen);
        reg_interface("send_equip_book",                Item_Msg_Proc::send_equip_book);
        reg_interface("send_take_off_book",             Item_Msg_Proc::send_take_off_book);
        reg_interface("send_equipment_level_up",        Item_Msg_Proc::send_equipment_level_up);
        reg_interface("send_equipment_quality_up",      Item_Msg_Proc::send_equipment_quality_up);
        reg_interface("send_book_level_up",             Item_Msg_Proc::send_book_level_up);
        reg_interface("send_book_quality_up",           Item_Msg_Proc::send_book_quality_up);
        reg_interface("send_sell_item",                 Item_Msg_Proc::send_sell_item);
        reg_interface("send_use_item",                  Item_Msg_Proc::send_use_item);
        reg_interface("send_compound_material_fragment",Item_Msg_Proc::send_compound_material_fragment);
        reg_interface("send_compound_book_fragment",    Item_Msg_Proc::send_compound_book_fragment);
        reg_interface("send_set_on_gem",                Item_Msg_Proc::send_set_on_gem);
        reg_interface("send_set_off_gem",               Item_Msg_Proc::send_set_off_gem);
        reg_interface("send_gem_level_up",              Item_Msg_Proc::send_gem_level_up);

        reg_interface("send_create_item",               Item_Msg_Proc::send_create_item);
        reg_interface("send_create_material_fragment",  Item_Msg_Proc::send_create_material_fragment);
        reg_interface("send_create_book_fragment",      Item_Msg_Proc::send_create_book_fragment);
        reg_interface("send_item_client_show",          Item_Msg_Proc::send_item_client_show);
        reg_interface("sql_insert_item",                Item_DB_Proc::sql_insert_item);
        reg_interface("sql_select_item",                Item_DB_Proc::sql_select_item);
        reg_interface("sql_update_item",                Item_DB_Proc::sql_update_item);
        reg_interface("sql_update_item_pos",            Item_DB_Proc::sql_update_item_pos);
        reg_interface("sql_update_item_level",          Item_DB_Proc::sql_update_item_level);
        reg_interface("sql_update_item_quality",        Item_DB_Proc::sql_update_item_quality);
        reg_interface("sql_update_item_count",          Item_DB_Proc::sql_update_item_count);
        reg_interface("sql_update_item_destroy_way",    Item_DB_Proc::sql_update_item_destroy_way);
        reg_interface("sql_update_item_gem",            Item_DB_Proc::sql_update_item_gem);
        reg_interface("create_default_item",            Item_DB_Proc::create_default_item);
        reg_interface("procplayerlogin",                Item_Msg_Proc::send_load_item);
        reg_interface("procplayerlogin",                Item_Msg_Proc::send_load_material_fragment);
        reg_interface("procplayerlogin",                Item_Msg_Proc::send_load_book_fragment);

        //quest
		reg_interface("updatenpcquestlist",	        quest_msg_proc::update_npc_quest_list );
        reg_interface("procplayerlogin",            quest_logic::proc_login );
        reg_interface("procplayerlogout",           quest_logic::proc_logout );
        reg_interface("sendsubmitquestresult",      quest_msg_proc::send_submit_quest_result);

		reg_interface("updatequestcontent",	        quest_msg_proc::update_quest_content );
		reg_interface("updatequestcontent",	        quest_db_proc::update_quest_content_to_db );
        reg_interface("insternewquesttodb",	        quest_db_proc::insert_new_quest_content_to_db );
		reg_interface("updatenpcquestopr",	        quest_msg_proc::update_npc_quest_operate );
		reg_interface("sendsavedquest",		        quest_msg_proc::send_saved_quest );

		reg_interface("acceptquest",		        quest_logic::accept_quest);
		reg_interface("completequest",		        quest_logic::complete_quest);
		reg_interface("giveupquest",		        quest_logic::giveup_quest);
		reg_interface("submitquest",		        quest_logic::submit_quest);
		reg_interface("iscanacceptquest",	        quest_logic::is_can_accept_quest);
		reg_interface("iscansubmitquest",	        quest_logic::is_can_submit_quest);
		reg_interface("isquestinprocess",	        quest_logic::is_quest_in_process);
		reg_interface("questcontentcount",          quest_logic::proc_quest_content_cout );
		reg_interface("questcontentcmdanalysis",    quest_logic::proc_quest_content_cmd_analysis );
		reg_interface("questcontentcounterfull",    quest_logic::is_quest_content_counter_full );

		reg_interface("procnpcquestbind",	        quest_npc_logic::proc_npc_quest_bind);
		reg_interface("procnpclistquestbind",	    quest_npc_logic::proc_npc_list_quest_bind);
		reg_interface("playerlevelup",		        quest_npc_logic::proc_npc_quest_bind );
		reg_interface("loadallquestdb",		        quest_db_proc::load_all_quest_from_db);

		//role
		reg_interface("sql_insert_role_attr",	                    Role_DB_Proc_Attr::sql_insert_role_attr);
		reg_interface("sql_select_role_attr",		                Role_DB_Proc_Attr::sql_select_role_attr );
		reg_interface("sql_update_role_attr",		                Role_DB_Proc_Attr::sql_update_role_attr);
        reg_interface("sql_update_role_token",                      Role_DB_Proc_Attr::sql_update_role_token);
        reg_interface("sql_update_role_recharge_token",             Role_DB_Proc_Attr::sql_update_role_recharge_token);
        reg_interface("sql_update_role_gold",                       Role_DB_Proc_Attr::sql_update_role_gold);
        reg_interface("sql_update_role_prestige",                   Role_DB_Proc_Attr::sql_update_role_prestige);
        reg_interface("sql_update_role_open_acupoint",              Role_DB_Proc_Attr::sql_update_role_open_acupoint);
        reg_interface("sql_update_role_exp",		                Role_DB_Proc_Attr::sql_update_role_exp);
        reg_interface("sql_update_role_energy",		                Role_DB_Proc_Attr::sql_update_role_energy);
        reg_interface("sql_update_role_buy_energy",		            Role_DB_Proc_Attr::sql_update_role_buy_energy);
        reg_interface("sql_update_role_offline_fight_finish",       Role_DB_Proc_Attr::sql_update_role_offline_fight_finish);
        reg_interface("sql_update_role_offline_fight_rank_reward",  Role_DB_Proc_Attr::sql_update_role_offline_fight_rank_reward);
        reg_interface("sql_update_role_buy_offline_fight_count",    Role_DB_Proc_Attr::sql_update_role_buy_offline_fight_count);
        reg_interface("sql_update_role_daily_data",                 Role_DB_Proc_Attr::sql_update_role_daily_data);
        reg_interface("sql_update_role_fight_general_id",		    Role_DB_Proc_Attr::sql_update_role_fight_general_id);
        reg_interface("sql_update_role_exchange_token_to_gold",     Role_DB_Proc_Attr::sql_update_role_exchange_token_to_gold);
        reg_interface("sql_update_role_function_open_id",           Role_DB_Proc_Attr::sql_update_role_function_open_id);

		reg_interface("sql_insert_role_info",	        Role_DB_Proc_Info::sql_insert_role_info);
		reg_interface("sql_select_role_info",		    Role_DB_Proc_Info::sql_select_role_info);
        reg_interface("sql_update_role_info",		    Role_DB_Proc_Info::sql_update_role_info);
        reg_interface("sql_update_role_level",		    Role_DB_Proc_Info::sql_update_role_level);
		reg_interface("sql_update_role_quality_up",		Role_DB_Proc_Info::sql_update_role_quality_up);
        reg_interface("sql_update_role_login",		    Role_DB_Proc_Info::sql_update_role_login);
        reg_interface("sql_update_role_logout",		    Role_DB_Proc_Info::sql_update_role_logout);

        // item_container
        reg_interface("send_load_item_container",           Item_Container_Msg_Proc::send_load_item_container);

        reg_interface("sql_insert_item_container",          Item_Container_DB_Proc::sql_insert_item_container);
        reg_interface("sql_select_item_container",          Item_Container_DB_Proc::sql_select_item_container);
        reg_interface("sql_update_item_container",          Item_Container_DB_Proc::sql_update_item_container);
        reg_interface("sql_update_item_container_data",     Item_Container_DB_Proc::sql_update_item_container_data);
        reg_interface("create_default_item_container",      Item_Container_DB_Proc::create_default_item_container);
        //reg_interface("procplayerlogin",                    Item_Container_Msg_Proc::send_load_item_container);
        reg_interface("send_update_item_container",         Item_Container_Msg_Proc::send_update_item_container);
        reg_interface("send_add_item_container",            Item_Container_Msg_Proc::send_add_item_container);

        // skill

        reg_interface("sql_select_skill",           Skill_DB_Proc::sql_select_skill);
        reg_interface("sql_update_skill",           Skill_DB_Proc::sql_update_skill);
        reg_interface("create_character_skill",     Skill_DB_Proc::create_character_skill);
        
        //reg_interface("procplayerlogin",            Skill_Msg_Proc::send_load_skill);
        reg_interface("send_load_skill",            Skill_Msg_Proc::send_load_skill);
        reg_interface("send_uplevel_skill",         Skill_Msg_Proc::send_uplevel_skill);
        reg_interface("send_create_skill",          Skill_Msg_Proc::send_create_skill);

        // shop
        reg_interface("send_load_shoping_record",   Shop_Msg_Proc::send_load_shoping_record);
        reg_interface("send_buy_item",              Shop_Msg_Proc::send_buy_item);
        reg_interface("procplayerlogin",            Shop_Msg_Proc::send_load_shoping_record);
        // shoping_record
        reg_interface("sql_insert_shoping_record",          Shoping_Record_DB_Proc::sql_insert_shoping_record);
        reg_interface("sql_select_shoping_record",          Shoping_Record_DB_Proc::sql_select_shoping_record);
        reg_interface("sql_update_shoping_record",          Shoping_Record_DB_Proc::sql_update_shoping_record);

		//relation system
		reg_interface("send_add_friend",            Relation_Msg_Proc::send_add_friend);
		reg_interface("send_del_friend",            Relation_Msg_Proc::send_del_friend);
		reg_interface("send_ask_friend_info",       Relation_Msg_Proc::send_ask_friend_info);
		reg_interface("send_ask_friend_list",       Relation_Msg_Proc::send_ask_friend_list);
		reg_interface("sql_insert_relation",		Relation_DB_Proc::sql_insert_relation);
		reg_interface("sql_select_relation",		Relation_DB_Proc::sql_select_relation);
		reg_interface("sql_update_relation",		Relation_DB_Proc::sql_update_relation);
		reg_interface("sql_del_relation",			Relation_DB_Proc::sql_delete_relation);

        // offline_fight
        reg_interface("send_player_buy_offline_fight_count",		Offline_Fight_Msg_Proc::send_player_buy_offline_fight_count);
        reg_interface("procplayerlogin",                            Offline_Fight_Msg_Proc::get_offline_fight_rank_reward_remaining_time);

        reg_interface("sql_insert_offline_fight_record",        Offline_Fight_Record_DB_Proc::sql_insert_offline_fight_record);
        reg_interface("sql_select_offline_fight_record",        Offline_Fight_Record_DB_Proc::sql_select_offline_fight_record);

        //Acupoint system
        reg_interface("send_load_acupoint",                     Acupoint_Msg_Proc::send_load_acupoint);
        reg_interface("send_open_acupoint",                     Acupoint_Msg_Proc::send_open_acupoint);
        reg_interface("send_create_acupoint",                   Acupoint_Msg_Proc::send_create_acupoint);
       
        reg_interface("sql_insert_acupoint",                    Acupoint_DB_Proc::sql_insert_acupoint);
        reg_interface("sql_select_acupoint",                    Acupoint_DB_Proc::sql_select_acupoint);
        reg_interface("sql_update_acupoint",                    Acupoint_DB_Proc::sql_update_acupoint);
        reg_interface("procplayerlogin",                        Acupoint_Msg_Proc::send_load_acupoint);

        //Cool_Time system
        reg_interface("send_load_cool_time",                    Cool_Time_Msg_Proc::send_load_cool_time);
        reg_interface("send_clean_cool_time",                   Cool_Time_Msg_Proc::send_clean_cool_time);
        reg_interface("send_create_cool_time",                  Cool_Time_Msg_Proc::send_create_cool_time);

        reg_interface("sql_insert_cool_time",                   Cool_Time_DB_Proc::sql_insert_cool_time);
        reg_interface("sql_select_cool_time",                   Cool_Time_DB_Proc::sql_select_cool_time);
        reg_interface("sql_update_cool_time",                   Cool_Time_DB_Proc::sql_update_cool_time);
        reg_interface("procplayerlogin",                        Cool_Time_Msg_Proc::send_load_cool_time);

		//Event system
		 reg_interface("procplayerlogin",						Event_Function_Instance::on_login);
		 reg_interface("procplayerlogout",						Event_Function_Instance::on_logout );

                  //scene system
        reg_interface("procplayerlogin",            Game_Logic::scene_logic::proc_login);

		//exchanged code
		reg_interface("sql_update_is_exchanged",            Award_DB_Proc::sql_update_exchanged_code);

		// banks exchange token to gold
		reg_interface("send_exchange_token_to_gold",                Banks_Msg_Proc::send_exchange_token_to_gold);

        // rank
        reg_interface("on_role_level_changed",                      Rank_Msg_Proc::on_role_level_changed);

        // login_reward
        reg_interface("sql_insert_login_reward",            Login_Reward_DB_Proc::sql_insert_login_reward);
        reg_interface("sql_select_login_reward",            Login_Reward_DB_Proc::sql_select_login_reward);
        reg_interface("sql_update_login_reward",            Login_Reward_DB_Proc::sql_update_login_reward);
        reg_interface("sql_update_login_reward_got_flag",   Login_Reward_DB_Proc::sql_update_login_reward_got_flag);
        reg_interface("create_default_login_reward",        Login_Reward_DB_Proc::create_default_login_reward);

        reg_interface("send_load_login_reward",                 Login_Reward_Msg_Proc::send_load_login_reward);
        reg_interface("send_get_login_reward",                  Login_Reward_Msg_Proc::send_get_login_reward);
        reg_interface("procplayerlogin",                        Login_Reward_Msg_Proc::send_load_login_reward);

        // activity
        reg_interface("sql_insert_activity_record",         Activity_Record_DB_Proc::sql_insert_activity_record);
        reg_interface("sql_select_activity_record",         Activity_Record_DB_Proc::sql_select_activity_record);
        reg_interface("sql_update_activity_record",         Activity_Record_DB_Proc::sql_update_activity_record);
        reg_interface("sql_update_six_sect_record",         Activity_Record_DB_Proc::sql_update_six_sect_record);
        reg_interface("create_default_activity_record",     Activity_Record_DB_Proc::create_default_activity_record);

        reg_interface("send_load_activity_record",  Activity_Msg_Proc::send_load_activity_record);
        reg_interface("send_activity_six_sect",     Activity_Msg_Proc::send_activity_six_sect);
        reg_interface("procplayerlogin",            Activity_Msg_Proc::send_load_activity_record);

        // daily_task
        reg_interface("sql_insert_daily_task",                  Daily_Task_DB_Proc::sql_insert_daily_task);
        reg_interface("sql_select_daily_task",                  Daily_Task_DB_Proc::sql_select_daily_task);
        reg_interface("sql_update_daily_task",                  Daily_Task_DB_Proc::sql_update_daily_task);
        reg_interface("sql_update_daily_task_star_level",       Daily_Task_DB_Proc::sql_update_daily_task_star_level);
        reg_interface("sql_update_daily_task_progress",         Daily_Task_DB_Proc::sql_update_daily_task_progress);
        reg_interface("sql_update_daily_task_gift_got_flag",    Daily_Task_DB_Proc::sql_update_daily_task_gift_got_flag);
        reg_interface("create_default_daily_task",              Daily_Task_DB_Proc::create_default_daily_task);

        reg_interface("send_load_daily_task",               Daily_Task_Msg_Proc::send_load_daily_task);
        reg_interface("send_drop_daily_task",               Daily_Task_Msg_Proc::send_drop_daily_task);
        reg_interface("send_submit_daily_task",             Daily_Task_Msg_Proc::send_submit_daily_task);
        reg_interface("send_refresh_daily_task_star_level", Daily_Task_Msg_Proc::send_refresh_daily_task_star_level);
        reg_interface("send_set_daily_task_star_level_max", Daily_Task_Msg_Proc::send_set_daily_task_star_level_max);
        reg_interface("send_token_complete_daily_task",     Daily_Task_Msg_Proc::send_token_complete_daily_task);
        reg_interface("send_get_daily_task_gift_one",       Daily_Task_Msg_Proc::send_get_daily_task_gift_one);
        reg_interface("send_get_daily_task_gift_two",       Daily_Task_Msg_Proc::send_get_daily_task_gift_two);
        reg_interface("send_get_daily_task_gift_three",     Daily_Task_Msg_Proc::send_get_daily_task_gift_three);
        reg_interface("send_update_daily_task_progress",    Daily_Task_Msg_Proc::send_update_daily_task_progress);
        reg_interface("procplayerlogin",                    Daily_Task_Msg_Proc::send_load_daily_task);
    }
#endif

	bool Game_Content_Interface::reg_interface( const char* cmd, game_interface_handler_t handle )
	{

		game_interface_multi_handler_map_t::iterator itgm;
		itgm = game_interface_handler_map_.find( cmd );
		if( itgm != game_interface_handler_map_.end() )
		{
			itgm->second.push_back(handle); 
		}
		else
		{
			game_interface_handler_vec_t tmp_hdl_vec;
			tmp_hdl_vec.clear();
			tmp_hdl_vec.push_back(handle);
			game_interface_handler_map_.insert(make_pair(cmd, tmp_hdl_vec));
		}	
		return true;
	}
	bool Game_Content_Interface::exec_interface( const char* cmd, const vector<uint64> para_vec, const char* key , int len)
	{

		game_interface_multi_handler_map_t::iterator itgm;
		itgm = game_interface_handler_map_.find( cmd );
		if( itgm != game_interface_handler_map_.end() )
		{
			Game_Interface gm_arg;
			gm_arg.set_para( para_vec );
			gm_arg.set_keyword(key);
            gm_arg.set_buff( key,len);
			game_interface_handler_vec_t::iterator itgi;
			bool ret_b = false;
			for( itgi = itgm->second.begin(); itgi != itgm->second.end(); ++ itgi )
			{
 			  ret_b = (*itgi)(gm_arg);
			}
			return ret_b;
		}
		return true;
	}
	bool Game_Content_Interface::reg_function_callback( const char* cmd, game_interface_handler_t handle,game_interface_handler_map_t& function_call_list )
	{
		game_interface_handler_map_t::iterator itgm;
		itgm = function_call_list.find( cmd );
		if( itgm == function_call_list.end() )
		{
			function_call_list.insert( make_pair(cmd, handle));
		}

		return true;

	}

	int Game_Content_Interface::exec_function_list( Game_Data::game_element_list_t& elementlst, game_interface_handler_map_t& function_call_list )
	{
		Game_Data::game_element_list_t::iterator itgv;

		int result_b = 0;
		for( itgv = elementlst.begin(); itgv != elementlst.end(); itgv++  )
		{
			game_interface_handler_map_t::iterator itgm;
			itgm = function_call_list.find( (*itgv).get_command() );
			if( itgm != function_call_list.end() )
			{
				vector<uint64>  para;
				list<uint> para_vec;
				para_vec = (*itgv).get_para_list();
				list<uint>::iterator itvi;
				for( itvi = para_vec.begin(); itvi != para_vec.end(); itvi++  )
				{
					para.push_back( *itvi );
				}
				//callback the function
				Game_Interface gm_arg;

				gm_arg.set_para(para );
				if(!(*itgm->second)(gm_arg))
					result_b = -1;
			}
		}

		return result_b;
	}

	int Game_Content_Interface::exec_function( const char* cmd, vector<uint64>  para, game_interface_handler_map_t& function_call_list, const char* key  )
	{
		game_interface_handler_map_t::iterator itgm;	
		itgm = function_call_list.find( cmd );
		if( itgm == function_call_list.end() )
			return -1;


		//callback the function
		Game_Interface gm_arg;

		gm_arg.set_para(para );
        gm_arg.set_keyword(key);

		return (!(*itgm->second)(gm_arg)) ? -1 : 0;

	}
}
