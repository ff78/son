

#include "Formula_Function_Instance.h"
 
#include "Game_Interface/event_define.h"
#include "Game_Interface/game_element.h"
#include "Game_Interface/game_condition.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_mgr.h"
#include "Game_Interface/Game_Element_Parse.h"
#include "Game_Interface/game_event_response.h"
#include "Formula_Function_Monster_Wave.h"
#include "Play_System/Instance_Data_Mgr.h"

#include "Formula_Mgr.h"
#include "Formula_Data.h"

#include "Formula_Logic.h"


#include "Item_System/Item_Config_Data.h"
#ifdef GAME_CLIENT
#include "Character_System/Character_Mgr.h"
#include "Character_System/Player.h"
#include "cocos2d.h"
#include "UI_Interface/UI_MainMenu_Layer.h"
//#include "AI_System/Game_Utils.h"
//#include "UI/Actor_Mgr.h"
//#include "Runtime.h"
#include "Player_Account/Account_Data_Mgr.h"
//#include "Game/Monster_Wave_Cfg_Data_Mgr.h"
#include "UI_Interface/UI_FuBenDialog.h"
#include "UI_Interface/UI_TimeLimitedInstance_Layer.h"
//#include "UI_Interface/UI_Settlement_Layer.h"
#include "UI_Interface/UI_ModalDialogue_Layer.h"
#include "UI_Interface/UI_Message.h"
#else
#include "Character_System/Player_Logic.h"
#include "Item_System/Item_Mgr_Sv.h"
#include "Daily_Task_System/Daily_Task_Config_Data.h"
#include "Daily_Task_System/Daily_Task_Mgr_Sv.h"
#include "Common/Tool.h"
#endif

#ifdef GAME_SERVER
#include <ace/ACE.h>
#include <ace/Acceptor.h>
#include "Character_System/Player.h"
#include "Character_System/Character_Mgr.h"
#include "log_common_defines.h"
#include "logger.h"
#include "LoggerFacade.h"
#include "game_interface/game_data_exchange.h"

#endif

Formula_Function_Instance* Formula_Function_Instance::instance_ =0;
Formula_Function_Instance::Formula_Function_Instance()
{
#ifdef YN_LINUX		
        pthread_mutex_init(&fomula_function_mutex_,NULL);
#endif
    
}

Formula_Function_Instance::~Formula_Function_Instance()
{
#ifdef YN_LINUX			
        pthread_mutex_destroy(&fomula_function_mutex_);
#endif
}

Formula_Function_Instance* Formula_Function_Instance::instance()
{
    if( NULL == instance_ )
        instance_ = new Formula_Function_Instance;

    return instance_;
}

///---------------------------------instance function-------------------------------------------------

int Formula_Function_Instance::get_elite_instance_id( int instance_id )
{
	Game_Data::Formula_Data fd;
	if( -1 == Game_Data::Formula_Mgr::instance()->get_formula_data("instance_attribute", instance_id, fd ))
		return -1;

    list<Game_Data::Game_Element> ge_lst;

    ge_lst.clear();
	fd.get_formula_element_list_by_key("began_content", ge_lst);

    vector<uint> para_wave;
    para_wave.clear();
    Game_Data::Game_Element_Parse::instance()->get_para_from_require_element("elite_instance",ge_lst, para_wave);

#ifdef YN_LINUX		
        Game_Logic::map_mutex m(&fomula_function_mutex_);
#endif
    if( para_wave.size() < 1)
        return -1;

    return (int)para_wave[0];
}

bool Formula_Function_Instance::instance_begin(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64>  para;
	gm_interface.get_para(para);
	if( para.size() < 3)
		return false;
    int player_id = (int)para[0];
    int instance_id = (int)para[1];
    int elite_instance = (int)para[2];

    //printf( "player %d scene %d \n", player_id,scene_id );
    if( current_instance_data::INSTANCE_TYPE_ELITE == elite_instance )
    {
        instance_id = instance()->get_elite_instance_id( instance_id );
        if( -1 == instance_id )
            return false;
    }

	Game_Data::Formula_Data fd;
	if( -1 == Game_Data::Formula_Mgr::instance()->get_formula_data("instance_attribute", instance_id, fd ))
		return false;

	list<Game_Data::Game_Element> ge_lst;
    ge_lst.clear();
	fd.get_formula_element_list_by_key("condition", ge_lst);

	if(!Game_Logic::Game_Condition::instance()->analysis_game_condition(player_id, ge_lst))
		return false;

    ge_lst.clear();
	fd.get_formula_element_list_by_key("began_content", ge_lst);

    //get time limit
    int time_limit = 0;

    //is the first time to enter instance and save instance begin time
    int instance_first = instance()->get_instance_first_state(player_id, instance_id, time_limit);

    if( -1 == Game_Data::Formula_Mgr::instance()->get_instance_dialog_id( player_id, instance_id ) || current_instance_data::INSTANCE_FIRST != instance_first )
    {

       //to process time limit instance
       time_limit = instance()->proc_init_time_limit_instance(player_id, instance_id);

    }
    
    vector<uint> para_scene;
    para_scene.clear();
    Game_Data::Game_Element_Parse::instance()->get_para_from_require_element("scene",ge_lst, para_scene);
    if(para_scene.size() < 1 )
        return false;
    int scene_id = (int)para_scene[0];

    //process monster wave
    vector<uint> para_wave;
    para_wave.clear();
    Game_Data::Game_Element_Parse::instance()->get_para_from_require_element("monster_wave",ge_lst, para_wave);
    if(para_wave.size() < 1 )
        return false;
    int monster_wave = para_wave[0];

    para_wave.clear();
    Game_Data::Game_Element_Parse::instance()->get_para_from_require_element("monster_wave_list",ge_lst, para_wave);
    if( (int)para_wave.size() != monster_wave )
        return false;

    if( -1 == Formula_Function_Instance::instance()->exec_element_list(player_id, instance_id, "began_content", fd ) )
    {
         //printf("exec result_content error!\n");
    }

    //send player 
    para.clear();
    para.push_back(player_id);
    para.push_back(instance_id);
    para.push_back(scene_id);
    para.push_back(time_limit);
    para.push_back(instance_first);
    para.push_back(monster_wave);
    vector<uint>::iterator itu;
    for( itu = para_wave.begin(); itu != para_wave.end(); ++ itu )
    {
        para.push_back( (*itu));
    }
    Game_Logic::Game_Content_Interface::instance()->exec_interface("sendinstancereq", para);
#ifdef GAME_SERVER
    Game_Logic::game_data_exchange::instance()->player_enter_battle(player_id);
#endif
	return true;
}

int Formula_Function_Instance::proc_init_time_limit_instance(int player_id, int instance_id)
{
    int instance_type = 0;
    int time_limit = Game_Data::Formula_Mgr::instance()->get_time_limit(instance_id, instance_type);
    if( time_limit <= 0)
        return time_limit;

    current_instance_data cid;
    if( -1 != INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid) )
    {
         if( 0 != time_limit )
         {
 #ifdef GAME_SERVER
             ACE_Time_Value now = ACE_OS::gettimeofday();
             cid.set_instace_check_time(now);
 #endif
             cid.set_instance_current_time_limit(time_limit);

             INSTANCE_DATA_MGR::instance()->modi_player_instance( player_id, cid );
             return time_limit;
         }
     }

    return time_limit;
}



int Formula_Function_Instance::get_instance_first_state(int player_id, int instance_id, int time_limit)
{
#ifdef GAME_SERVER
    ACE_Time_Value now = ACE_OS::gettimeofday();
#endif

    // int instance_first = 0;
    current_instance_data cid;
    cid.set_instance_id( instance_id );

    if( -1 == INSTANCE_DATA_MGR::instance()->get_player_instance_from_list( player_id, cid) )
    {
        cid.reset();
        cid.set_player_id( player_id );
        cid.set_instance_id(instance_id);
        cid.set_saved_instance(0);
#ifdef GAME_SERVER
        cid.set_instance_current_time_limit(time_limit);
        cid.set_instace_check_time(now);
#endif
        INSTANCE_DATA_MGR::instance()->add_player_instance( player_id, cid );
        return current_instance_data::INSTANCE_FIRST;
    }
    else
    {
#ifdef GAME_SERVER
        cid.set_instance_current_time_limit(time_limit);
        cid.set_instace_check_time(now);
#endif
        INSTANCE_DATA_MGR::instance()->add_player_instance( player_id, cid );
        return 0;
    }

    return 0;
}


///---------------------------------instance logic-------------------------------------------------
bool Formula_Function_Instance::proc_login( Game_Logic::Game_Interface& gm_interface )
{
	vector<uint64>  para;
	gm_interface.get_para(para);
	if( para.size() < 1)
		return false;
    int player_id = (int)para[0];

    INSTANCE_DATA_MGR::instance()->remove_player_instance_data( player_id );
    INSTANCE_DATA_MGR::instance()->remove_player_instance_list( player_id );
    INSTANCE_DATA_MGR::instance()->clear_stage_data();

#ifdef GAME_SERVER
    para.clear();
    para.push_back(player_id);
  
    Game_Logic::Game_Content_Interface::instance()->exec_interface( "loadinstancefromdb", para);

    Game_Logic::Game_Content_Interface::instance()->exec_interface( "sendinstanceprogress", para);
#endif
    return false;
}
bool Formula_Function_Instance::proc_logout( Game_Logic::Game_Interface& gm_interface )
{
	vector<uint64>  para;
	gm_interface.get_para(para);
	if( para.size() < 1)
		return false;
    int player_id = (int)para[0];
    INSTANCE_DATA_MGR::instance()->remove_player_instance_data( player_id );
    INSTANCE_DATA_MGR::instance()->remove_player_instance_list( player_id );
    INSTANCE_DATA_MGR::instance()->clear_stage_data();
    return false;
}

bool Formula_Function_Instance::proc_instance_timer_check(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64>  para;
	gm_interface.get_para(para);
	if( para.size() < 2)
		return false;
    int player_id = (int)para[0];
    int instance_id = (int)para[1];

    int instance_type = 0;
    int time_limit = Game_Data::Formula_Mgr::instance()->get_time_limit( instance_id, instance_type );

    current_instance_data cid;
    cid.set_instance_id( instance_id );

    if( -1 != INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid) )
    {
        if( 0 != time_limit )
        {
#ifdef GAME_SERVER
            ACE_Time_Value now = ACE_OS::gettimeofday();
            cid.set_instace_check_time(now);
#endif
            cid.set_instance_current_time_limit(time_limit);
   
            INSTANCE_DATA_MGR::instance()->modi_player_instance( player_id, cid );
            return true;
        }
    }

    return false;
}

bool Formula_Function_Instance::proc_instance_player_die(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64>  para;
	gm_interface.get_para(para);
	if( para.size() < 2)
		return false;
    int player_id = (int)para[0];
    int instance_id = (int)para[1];

    int instance_type = 0;
    int time_limit = Game_Data::Formula_Mgr::instance()->get_time_limit( instance_id, instance_type );

    if( current_instance_data::INSTANCE_STATE_SUC_KEEP_ALIVE == instance_type && time_limit > 0 )
    {
        vector<uint64> para;
        para.push_back(player_id);
        para.push_back(instance_id);
        para.push_back( current_instance_data::INSTANCE_STATE_FAILE );
        Game_Logic::Game_Content_Interface::instance()->exec_interface("sendinstancefinishresult", para);
        INSTANCE_DATA_MGR::instance()->remove_player_instance_data(player_id);
#ifdef GAME_SERVER
        Game_Logic::game_data_exchange::instance()->player_exit_battle( player_id );
#endif
    }

    return false;
}


bool Formula_Function_Instance::process_instance_result(Game_Logic::Game_Interface& gm_interface)
{
    string key = gm_interface.get_keyword();
	vector<uint64>  para;
	gm_interface.get_para(para);
	if( para.size() < 4)
		return false;
    int player_id = (int)para[0];
    int instance_id = (int)para[1];
    int result = (int)para[2];
    int total_player_die = (int)para[3];
    //  1 complete 2 fail 3 give up
#ifdef GAME_SERVER
    Game_Logic::game_data_exchange::instance()->player_exit_battle( player_id );
#endif
    Game_Data::Formula_Data fd;
    if( -1 == Game_Data::Formula_Mgr::instance()->get_formula_data("instance_attribute", instance_id, fd ))
		return false;

    if( current_instance_data::INSTANCE_STATE_SUC != result )
    {
        INSTANCE_DATA_MGR::instance()->remove_player_instance_data( player_id );
 
        return false;
    }

    if( -1 == Formula_Function_Instance::instance()->exec_element_list(player_id,  instance_id,"complete_content", fd ) )
    {
         //printf("exec complete_content error!\n");
    }

    if( -1 == Formula_Function_Instance::instance()->exec_element_list(player_id, instance_id, "result_content", fd ) )
    {
         //printf("exec result_content error!\n");
    }

    int score = 1;
    int total_time_asume = 0;

    current_instance_data cid;
    if( 0 == INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid) )
    {
#ifdef GAME_SERVER
    ACE_Time_Value now = ACE_OS::gettimeofday();

    total_time_asume  = (int)(now -cid.get_instace_check_time()).sec();
#endif
    }

    list<Game_Data::Game_Element> ge_lst;
    ge_lst.clear();
	fd.get_formula_element_list_by_key("result_content", ge_lst);

    int time_value_100 = 0, time_value_0 = 0;
    vector<uint> para_u;
    Game_Data::Game_Element_Parse::instance()->get_para_from_require_element("time_envalue",ge_lst, para_u);
    if(para_u.size() > 1 )
    {
         time_value_100 = para_u[0]; time_value_0 = para_u[1];
    }

    int player_die_envalue = 0;
    para_u.clear();
    Game_Data::Game_Element_Parse::instance()->get_para_from_require_element("player_die_envalue",ge_lst, para_u);
    if(para_u.size() > 0 )
    {
        player_die_envalue = para_u[0];
    }

    if( time_value_0 - time_value_100 != 0)
        score = 100 - ((total_time_asume - time_value_100)/(time_value_0 - time_value_100)*100) - total_player_die*player_die_envalue;
    if( score <= 0)
        score = 1;


    cid.set_instance_id( instance_id);
    if( -1 == INSTANCE_DATA_MGR::instance()->get_player_instance_from_list( player_id, cid) )
    {
        cid.reset();
        cid.set_player_id( player_id );
        cid.set_instance_id(instance_id);
        cid.set_instance_score( score );
        cid.set_instance_state(current_instance_data::INSTANCE_STATE_SUC);
        cid.set_saved_instance(current_instance_data::INSTANCE_FIRST);
        cid.set_time_grad(total_time_asume);
        cid.set_total_player_die(total_player_die);
        INSTANCE_DATA_MGR::instance()->add_player_instance_lst( player_id, cid );
    }
    else
    {
        if( score > cid.get_instance_score())
            cid.set_instance_score( score );
        cid.set_saved_instance(current_instance_data::INSTANCE_SAVED);
        cid.set_time_grad(total_time_asume);
        cid.set_total_player_die(total_player_die);
        INSTANCE_DATA_MGR::instance()->modi_player_instance_list( player_id, cid );
    }

    para.clear();
    para.push_back(player_id);
    para.push_back(instance_id);
    para.push_back( score );
    Game_Logic::Game_Content_Interface::instance()->exec_interface("saveinstanceresult", para);

    para.clear();
    para.push_back(player_id);
    para.push_back(instance_id);
    para.push_back(result);
    Game_Logic::Game_Content_Interface::instance()->exec_interface("sendinstancefinishresult", para);

#ifdef GAME_SERVER
    DAILY_TASK_MGR::instance()->update_daily_task_progress(player_id,Game_Data::DTT_INSTANCE);
#endif
    Game_Logic::Game_Event_Response::instance()->on_instance_suc( player_id, instance_id );

    INSTANCE_DATA_MGR::instance()->remove_player_instance_data( player_id );

    return true;
}


int Formula_Function_Instance::exec_element_list(int player_id, int formula_id, const char* key,Game_Data::Formula_Data& fd )
{
    list<Game_Data::Game_Element> ge_lst;
    ge_lst.clear();
	fd.get_formula_element_list_by_key(key, ge_lst);

	std::list<Game_Data::Game_Element>::iterator itr;
	vector<uint> para_u;
	vector<uint64> para_lst;
	vector<uint>::iterator itu;
	for( itr = ge_lst.begin(); itr != ge_lst.end(); ++ itr )
	{
		para_u.clear();
		para_lst.clear();
        para_lst.push_back(player_id);
        para_lst.push_back(formula_id);
		(*itr).get_para_list_in_vector(para_u);
		for( itu = para_u.begin(); itu != para_u.end(); ++itu)
			para_lst.push_back(*itu);
		Formula_Logic::instance()->exec_formula_function((*itr).get_command(),  para_lst, key);
	}

    return 0;
}





int Formula_Function_Instance::get_element_list_from_instance_data( int instance_id, const char* table_key, 
                                                                   const char* conten_key, const char* /*cmd_key*/, list<Game_Data::Game_Element>& ele_lst)
{
    ele_lst.clear();
	Game_Data::Formula_Data fd;
	if( -1 == Game_Data::Formula_Mgr::instance()->get_formula_data(table_key, instance_id, fd ))
		return -1;

	fd.get_formula_element_list_by_key(conten_key, ele_lst);

    return 0;
}

int Formula_Function_Instance::get_para_list_from_instance_data( int instance_id, const char* table_key, const char* conten_key, const char* cmd_key, vector<uint>& para)
{

	Game_Data::Formula_Data fd;
	if( -1 == Game_Data::Formula_Mgr::instance()->get_formula_data(table_key, instance_id, fd ))
		return -1;

    list<Game_Data::Game_Element> ge_lst;
    ge_lst.clear();
	fd.get_formula_element_list_by_key(conten_key, ge_lst);
    para.clear();
    Game_Data::Game_Element_Parse::instance()->get_para_from_require_element(cmd_key,ge_lst, para);

    return 0;
}

int Formula_Function_Instance::get_string_content_from_instance_data( int instance_id, const char* table_key, const char* conten_key, const char* cmd_key, string& content)
{

	Game_Data::Formula_Data fd;
	if( -1 == Game_Data::Formula_Mgr::instance()->get_formula_data(table_key, instance_id, fd ))
		return -1;

    fd.get_formula_key();

   list<Game_Data::Game_Element> ge_lst;
    ge_lst.clear();
	fd.get_formula_element_list_by_key(conten_key, ge_lst);

    vector<string> para;
    Game_Data::Game_Element_Parse::instance()->get_string_para_from_require_element(cmd_key,ge_lst, para);
    if( para.size() < 1 )
        return -1;

    content = para[0];
    return 0;
}

#ifdef GAME_SERVER
int Formula_Function_Instance::instance_check(int player_id, const ACE_Time_Value &now)
{
    current_instance_data cid;
    if(-1 == INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid) )
    {
        return -1;
    }

    if( 0 == cid.get_instance_current_time_limit() )
        return -1;

    if( (now - cid.get_instace_check_time()).sec() > cid.get_instance_current_time_limit() )
    {
        //proc stop current instance, send current instance fail
        int instance_type = 0;
        Game_Data::Formula_Mgr::instance()->get_time_limit( cid.get_instance_id(), instance_type );

        if( 0 == instance_type )
            return -1;

        if( current_instance_data::INSTANCE_STATE_FAILE_OVER_TIME == instance_type)
        {
            vector<uint64> para;
            para.push_back(player_id);
            para.push_back(cid.get_instance_id());
            para.push_back( instance_type );
            Game_Logic::Game_Content_Interface::instance()->exec_interface("sendinstancefinishresult", para);
            INSTANCE_DATA_MGR::instance()->remove_player_instance_data(player_id);
            Game_Logic::game_data_exchange::instance()->player_exit_battle( player_id );
        }
        else if( current_instance_data::INSTANCE_STATE_SUC_KEEP_ALIVE == instance_type)
        {
            vector<uint64> para;
            para.push_back(player_id);
            para.push_back(cid.get_instance_id());
            para.push_back(current_instance_data::INSTANCE_STATE_SUC);
            para.push_back(0);
            Game_Logic::Game_Content_Interface::instance()->exec_interface("instanceresult", para);

            para.clear();
            para.push_back(player_id);
            Game_Logic::Game_Content_Interface::instance()->exec_interface("send_player_into_main_city", para);
            Game_Logic::game_data_exchange::instance()->player_exit_battle( player_id );
        }
        return 0;

    }
    return -1;
}


bool Formula_Function_Instance::give_item(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64>  para;
	gm_interface.get_para(para);
	if( para.size() < 4)
		return false;
	//int player_id = (int)para[0];
	//int instance_id = (int)para[1];
	//int item_id = (int)para[2];
	//int count = (int)para[3];
    //printf( "player %d give item id %d  count %d \n", player_id, item_id, count );
	return true;
}

bool Formula_Function_Instance::award_money(Game_Logic::Game_Interface& gm_interface)
{

	vector<uint64>  para;
	gm_interface.get_para(para);
	if( para.size() < 3)
		return false;
    int player_id = (int)para[0];
    // int formula_id = (int)para[1];
    int money = (int)para[2];
    //printf( "player %d award money %d \n", player_id, money );

	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	int original_money_value = player->get_gold();

    PLAYER_LOGIC::instance()->change_gold(player_id,money);
    // save db
    para.clear();
    para.push_back(player_id);
    Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_role_gold",para);

	LoggerFacade::instance()->facade_role_money_born(player_id,MONEY_BORN_REASON_PVE_COPY,DETAIL_REASON,MONEY_TYPE_JINBI,original_money_value,money);
	return true;
}
bool Formula_Function_Instance::award_general(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64>  para;
	gm_interface.get_para(para);
	if( para.size() < 3)
		return false;
    int player_id = (int)para[0];
    //int formula_id = (int)para[1];
    int general_id = (int)para[2];
    int rate = (int)para[3];
    if(RandGen::GetRand(1, 10000) < rate)
    {
        Game_Logic::game_data_exchange::instance()->add_deputy_general(player_id, general_id);
    }
    return true;
}
bool Formula_Function_Instance::award_item(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64>  para;
	gm_interface.get_para(para);
	if( para.size() < 5)
		return false;
    int player_id = (int)para[0];
    //int formula_id = (int)para[1];
    int item_id = (int)para[2];
    int count = (int)para[3];
    int rate = (int)para[4];
    if(RandGen::GetRand(1, 10000) < rate)
    {
        //printf( "player %d award item %d count %d \n", player_id, item_id, count );
        ITEM_MGR::instance()->create_item(player_id,item_id, count, 1);
        current_instance_data cid;
        if(0 == INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid) )
        {
            cid.set_item_award_list( item_id, count);
            INSTANCE_DATA_MGR::instance()->modi_player_instance( player_id, cid );
        }
    }
    else
    {
        //printf( "player %d can't get item award \n", player_id );
    }
	return true;
}
bool Formula_Function_Instance::award_exp_compute(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64>  para;
	gm_interface.get_para(para);
	if( para.size() < 3)
		return false;
    int player_id = (int)para[0];
    //int formula_id = (int)para[1];
    int para1 = (int)para[2];
    //printf( "player %d award exp %d \n", player_id, para1);

	Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
	int original_exp_value = player->get_exp();

    PLAYER_LOGIC::instance()->add_instance_exp(player_id, para1 );

	LoggerFacade::instance()->facade_role_exp_born(player_id,EXP_BORN_REASON_PVE_COPY,DETAIL_REASON,original_exp_value,para1);

	return true;
}

bool Formula_Function_Instance::remove_item(Game_Logic::Game_Interface& gm_interface)
{
	vector<uint64>  para;
	gm_interface.get_para(para);
	if( para.size() < 4)
		return false;
	//int player_id = (int)para[0];
	//int formula_id = (int)para[1];
	//int item_id = (int)para[2];
	//int count = (int)para[3];
    //printf( "player %d remove item %d count %d \n", player_id, item_id, count );
	return true;
}


bool Formula_Function_Instance::instance_energy_consume(Game_Logic::Game_Interface& gm_interface)
{

    vector<uint64>  para;
	gm_interface.get_para(para);
	if( para.size() < 3)
		return false;
    int player_id = (int)para[0];
    //int formula_id = (int)para[1];
    int energy_value = (int)para[2];
    PLAYER_LOGIC::instance()->change_energy(player_id, -1 * energy_value );
    // save db
    para.clear();
    para.push_back(player_id);
    Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_role_energy",para);
    return true;
}
#endif

