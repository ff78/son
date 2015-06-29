
#include "quest_msg_proc_client.h"

#include "Network_Common/message.h"
#include "Network_Common/message_stream.h"
#include "Network_Common/NetManager.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_response.h"
#include "UI_Interface/UI_MainMenu_Layer.h"
#include "quest_system/quest_data/quest_data_mgr.h"

#ifdef GAME_CLIENT
#include "Common/Game_Utils.h"
#include "Character_System/Character_Mgr.h"
#include "Item_System/Item_Config_Mgr.h"
#include "Player_Account/Account_Data_Mgr.h"
//#include "UI/NPC.h"
#include "game_play_controler/game_play_controler_data/gameplay_ctrl_data_mgr.h"
#endif

#include "Common/GameDefine.h"
#include "Common/Utils.h"
quest_msg_proc_client* quest_msg_proc_client::instance_ = 0;
quest_msg_proc_client::quest_msg_proc_client(){

}



quest_msg_proc_client::~quest_msg_proc_client(){

}

quest_msg_proc_client* quest_msg_proc_client::instance()
{
    if ( NULL == instance_ )
        instance_ = new quest_msg_proc_client;

    return instance_;
}

bool quest_msg_proc_client::on_update_npc_quest_bind_list(Game_Logic::Game_Interface& gm_interface)
{
	/************************************************************************/
	// 更新当前Npc的请求结合列表
	// 1. 解析玩家ID
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));
    int player_id = 0;
    int size = 0;

    body_ms >> player_id  >> size;

	// 2. 
    Game_Data::quest_data_mgr::instance()->remove_player_acceptable_quest(player_id);

	// 3. 
    vector<uint32> accept_qst_lst;				  // 已接受的请求列表
    vector<uint32> submit_qst_lst;				  // 已提交的请求列表
    vector<uint32> challenge_qst_lst;
    vector<uint32> dialog_qst_lst;				  // 对话列表
    vector<uint32> give_item_to_npc_qst_lst;
    vector<uint32> inprocess_qst_lst;			  // 在进行中的请求列表
    vector<uint32>::iterator itu;

    Game_Data::npc_bind_quest nbq_temp;
    nbq_temp.reset();
    int quest_size = 0,npc_id = 0;

    Game_Data::npc_bind_quest::npc_bind_quest_vec_t npc_bind_list_old;
    npc_bind_list_old.clear();
    Game_Data::quest_data_mgr::instance()->get_player_npc_quest_bind_data(player_id, npc_bind_list_old);
    Game_Data::quest_data_mgr::instance()->remove_player_npc_quest_bind_data(player_id);
    for( uint i = 0; i < (uint)size; i ++ )
    {
        quest_size ; npc_id = 0;
        accept_qst_lst.clear(); submit_qst_lst.clear(); inprocess_qst_lst.clear();
        body_ms >> npc_id >> quest_size;
        for( uint j = 0; j < (uint)quest_size; j++)
        {
            instance()->get_npc_quest_data(npc_id, body_ms, accept_qst_lst, submit_qst_lst, inprocess_qst_lst );
        }

        nbq_temp.reset();
        nbq_temp.set_npc_id(npc_id);
        nbq_temp.set_accept_quest_list(accept_qst_lst);
        for( itu = accept_qst_lst.begin(); itu != accept_qst_lst.end(); ++ itu )
        {
            Game_Data::quest_data_mgr::instance()->add_acceptable_quest_id( player_id, (*itu));
        }
        nbq_temp.set_submit_quest_list(submit_qst_lst);
        nbq_temp.set_inprocess_quest_list( inprocess_qst_lst );

        Game_Data::quest_data_mgr::instance()->add_player_npc_quest_bind_data(player_id, nbq_temp);

    }

    Game_Data::npc_bind_quest::npc_bind_quest_vec_t npc_bind_list_new;
    npc_bind_list_new.clear();
    Game_Data::quest_data_mgr::instance()->get_player_npc_quest_bind_data(player_id, npc_bind_list_new);

    instance()->process_npc_quest_bind_state(npc_bind_list_old, npc_bind_list_new);

    vector<uint64> para;
    para.push_back( player_id );
    Game_Logic::Game_Content_Interface::instance()->exec_interface("sendreqquestlist",para);

    Game_Logic::Game_Event_Response::instance()->on_update_npcdialog(player_id);
	Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player_id);
    return true;
}

int quest_msg_proc_client::process_npc_quest_bind_state(vector<Game_Data::npc_bind_quest>& npc_bind_old, vector<Game_Data::npc_bind_quest>& npc_bind_new )
{
    map<int,int> npc_map;
    Game_Utils::instance()->get_npc_list( npc_map );
 
    map<int,int>::iterator iti;
    int old_npc_quest_state = Game_Data::quest_data::QUEST_STATE_NONE;
    int new_npc_quest_state = Game_Data::quest_data::QUEST_STATE_NONE;
    for( iti = npc_map.begin(); iti != npc_map.end(); ++ iti )
    {
        old_npc_quest_state = get_npc_quest_bind_state(iti->first, npc_bind_old);
        new_npc_quest_state = get_npc_quest_bind_state(iti->first, npc_bind_new);

        if( old_npc_quest_state == Game_Data::quest_data::QUEST_STATE_NONE && new_npc_quest_state == Game_Data::quest_data::QUEST_STATE_NONE )
        {
            continue;
        }

        display_npc_quest_state( iti->second, new_npc_quest_state);

    }

    return 0;
}

int quest_msg_proc_client::get_npc_quest_bind_state( int npc_id, vector<Game_Data::npc_bind_quest>& npc_bind )
{
    int state = Game_Data::quest_data::QUEST_STATE_NONE;
    vector<Game_Data::npc_bind_quest>:: iterator itn;
    vector<uint32> qst_lst;

    itn= find_if( npc_bind.begin(), npc_bind.end(), bind2nd( equal_to<Game_Data::npc_bind_quest>(), Game_Data::npc_bind_quest(npc_id) ));

    if(  itn != npc_bind.end() )
    {

        qst_lst.clear();
        (*itn).get_inprocess_quest_list(qst_lst);
        if(qst_lst.size() > 0)
        {
            state = Game_Data::quest_data::QUEST_STATE_INPROCESS;
        }
        qst_lst.clear();
        (*itn).get_accept_quest_list(qst_lst);
        if(qst_lst.size() > 0)
        {
            state = Game_Data::quest_data::QUEST_STATE_ACCEPTABLE;
        }
        qst_lst.clear();
        (*itn).get_submit_quest_list(qst_lst);

        if(qst_lst.size() > 0)
        {
            state = Game_Data::quest_data::QUEST_STATE_SUBMITABLE;
        }
    }

    return state;
}

int quest_msg_proc_client::display_npc_quest_state( int instance_npc_id, int state)
{

    bool changed = false;
    if (Game_Data::quest_data::QUEST_STATE_INPROCESS == state)
    {
        const char* szPath = ITEM_CONFIG_MGR::instance()->get_icon_path(II_REQUEST_2);
        Game_Utils::instance()->set_sprite_info(instance_npc_id , szPath,true);

        changed = true;
    }
    else if (Game_Data::quest_data::QUEST_STATE_ACCEPTABLE == state)
    {
        const char* szPath = ITEM_CONFIG_MGR::instance()->get_icon_path(II_REQUEST_3);
        Game_Utils::instance()->set_sprite_info(instance_npc_id , szPath,true);

        changed = true;
    }
    else  if (Game_Data::quest_data::QUEST_STATE_SUBMITABLE == state)
    {
        const char* szPath = ITEM_CONFIG_MGR::instance()->get_icon_path(II_REQUEST_1);
        Game_Utils::instance()->set_sprite_info(instance_npc_id , szPath,true);
        changed = true;
    }
 
    if( !changed )
        Game_Utils::instance()->set_sprite_info(instance_npc_id , "",true);

    return 0;
}

int quest_msg_proc_client::update_player_act_data( int quest_id, int act_count, int act_total_count )
{
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();

	int act_id = 0;
	vector<uint> req_para;
	Game_Data::quest_data_mgr::instance()->get_org_quest_command_para( quest_id, "actbind", req_para);
	if( 0 != req_para.size() )
	{
		act_id = req_para[0];			

        gameplay_ctrl_data_mgr::instance()->add_player_act_data_client( player_id, act_id, act_count, act_total_count );
        return 0;
	}

	return -1;
}

int quest_msg_proc_client::get_npc_quest_data(int npc_id, message_stream& ms,vector<uint32>& accept_qst_lst,vector<uint32>& submit_qst_lst,vector<uint32>& inprocess_qst_lst)
{

    int quest_id = 0; int state = 0, act_count = 0, act_total_count = 0;
    ms >> quest_id >> state >> act_count >> act_total_count;

    update_player_act_data( quest_id, act_count, act_total_count );
    
    map<int,int> npc_map;
    map<int,int>::iterator iti;

    Game_Utils::instance()->get_npc_list( npc_map );
    iti = npc_map.find(npc_id);
    int instance_npc_id = 0;
    if( iti != npc_map.end() )
        instance_npc_id = iti->second;

    bool changed = false;
    if (Game_Data::quest_data::QUEST_STATE_INPROCESS == state)
    {
        inprocess_qst_lst.push_back(quest_id);
        changed = true;
    }
    else if (Game_Data::quest_data::QUEST_STATE_ACCEPTABLE == state)
    {
        accept_qst_lst.push_back(quest_id);
        changed = true;
    }
    else  if (Game_Data::quest_data::QUEST_STATE_SUBMITABLE == state)
    {
        submit_qst_lst.push_back(quest_id);
        changed = true;
    }
 

    return 0;
}
bool quest_msg_proc_client::on_quest_update(Game_Logic::Game_Interface& gm_interface)
{
	// 点击接受任务回的消息
	// 下面字段分别是什么意思？
	// 潘杰（02.03）
    //CCLog("-------------------->quest_msg_proc_client::on_quest_update ---to game");
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));
    int player_id = 0;
    int quest_id = 0;
    int quest_state = 0;
    string counter_str = "";

    body_ms >> player_id >> quest_id >> quest_state >> counter_str;

    int act_bind = 0;
    int act_count = 0;
    int act_total_count = 0;
    body_ms >> act_bind;
    if( 1 == act_bind )
    {
        body_ms >> act_count >> act_total_count;
        instance()->update_player_act_data( quest_id, act_count, act_total_count );
    }

    vector<uint64> para;
    para.push_back(player_id);
    para.push_back(quest_id);
    para.push_back(quest_state);
    para.push_back(act_count);
    para.push_back(act_total_count);
    Game_Logic::Game_Content_Interface::instance()->exec_interface("procupdatequest",para, counter_str.data());
	Game_Logic::Game_Event_Response::instance()->on_update_main_ui_info(player_id);
	
    return true;
}
bool quest_msg_proc_client::on_quest_submuit_result(Game_Logic::Game_Interface& gm_interface)
{
    //CCLog("-------------------->quest_msg_proc_client::on_quest_submuit_result ---to game");
    message_stream body_ms((char*)gm_interface.get_buff(), gm_interface.get_buff_size());
    body_ms.set_rd_ptr(sizeof(int));
    int player_id = 0;
    int quest_id = 0;


    body_ms >> player_id >> quest_id;
    Game_Data::quest_data_mgr::instance()->removequest( player_id, quest_id );

    

    vector<uint64> para;
    para.push_back( player_id );

  //  Game_Logic::Game_Content_Interface::instance()->exec_interface("sendreqnpcquest",para);
#if 1//MISSION_DIALOG
		Game_Logic::Game_Event_Response::instance()->on_update_mission_dialog(player_id, quest_id);
#endif

    return true;
}
bool quest_msg_proc_client::send_accept_quest(Game_Logic::Game_Interface& gm_interface)
{
    //CCLog("-------------------->quest_msg_proc_client::send_accept_quest ---to game");
	//Game_Utils::instance()->add_effect_to_scene("3019");  //任务接收特效
    vector<uint64> para;
    gm_interface.get_para(para);
    if(para.size() < 2 )
        return false;

    int player_id = (int)para[0];
    int quest_id = (int)para[1];
    //send msg to server
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << CLIENT_QUEST_ACCEPT_QUEST << player_id << quest_id;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}

bool quest_msg_proc_client::send_submit_quest(Game_Logic::Game_Interface& gm_interface)
{
    //CCLog("-------------------->quest_msg_proc_client::send_submit_quest ---to game");
	//Game_Utils::instance()->add_effect_to_scene("2014");  //任务完成特效
    vector<uint64> para;
    gm_interface.get_para(para);
    if(para.size() < 2 )
        return false;

    int player_id = (int)para[0];
    int quest_id = (int)para[1];
    //send msg to server
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << CLIENT_QUEST_SUBMIT_QUEST << player_id << quest_id;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}
bool quest_msg_proc_client::send_require_quest_list(Game_Logic::Game_Interface& gm_interface)
{
    //CCLog("-------------------->quest_msg_proc_client::send_require_quest_list ---to game");
    vector<uint64> para;
    gm_interface.get_para(para);
    if(para.size() < 1 )
        return false;

    int player_id = (int)para[0];

    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << CLIENT_REQUIRE_QUEST_LIST << player_id;

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}
bool quest_msg_proc_client::send_require_npc_quest_bind(Game_Logic::Game_Interface& gm_interface)
{
    //CCLog("-------------------->quest_msg_proc_client::send_require_npc_quest_bind ---to game");
    vector<uint64> para;
    gm_interface.get_para(para);
    if(para.size() < 1 )
        return false;

    int player_id = (int)para[0];

    vector<int> npc_vec;
    npc_vec.clear();
	
#ifdef GAME_CLIENT
    map<int,int> npc_map;
    map<int,int>::iterator iti;

    Game_Utils::instance()->get_npc_list( npc_map );
    for( iti = npc_map.begin(); iti != npc_map.end(); ++iti)
    {
        npc_vec.push_back(iti->first);
    }


    int instance_npc_id = 0;
    for(iti = npc_map.begin(); iti != npc_map.end(); ++iti )
    {
        instance_npc_id = iti->second;
        Game_Utils::instance()->set_sprite_info(instance_npc_id , "",true);
    }
#endif
    if( npc_vec.size() <= 0 )
        return false;
    int npc_size = npc_vec.size();
    //send msg to server
    char body[256] = {0};
    message_stream body_ms(body, sizeof(body));
    body_ms << CLIENT_REQUIRE_NPC_QUEST_LIST << player_id << npc_size;

    vector<int>::iterator itv;
    for( itv = npc_vec.begin(); itv != npc_vec.end(); ++ itv)
    {
        body_ms << (*itv);
    }

    CNetManager::GetMe()->send_msg( body_ms );
    return true;
}
