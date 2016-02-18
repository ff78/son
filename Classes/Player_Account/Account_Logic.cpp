
#include "Account_Logic.h"

#include "Game_Interface/event_define.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_mgr.h"

#include "Player_Account/Account_Data.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Player_Account/Account_Msg_Proc.h"
#include "Player_Account/RecentlyServer.h"

//#include "UI/Actor_Mgr.h"
#include "Item_System/Item_Mgr_Cl.h"
#include "Item_Container_System/Item_Container_Mgr_Cl.h"
//#include "Fight_System/Offline_Fight_Mgr_Cl.h"
//#include "Fight_System/Offline_Fight_Record_Mgr_Cl.h"
#include "Acupoint_System/Acupoint_Mgr_Cl.h"
#include "Character_System/Character_Mgr.h"
//#include "Skill_System/Buff/Buff_Mgr.h"
//#include "Skill_System/Skill/Skill_Mgr.h"
#include "quest_system/quest_data/quest_data_mgr.h"
#include "Play_System/Instance_Data_Mgr.h"

//#include "FSM_Game.h"

Account_Logic* Account_Logic::instance_ = 0;
Account_Logic::Account_Logic()
{

}

Account_Logic::~Account_Logic()
{

}

Account_Logic* Account_Logic::instance()
{
    if(NULL == instance_)
        instance_ = new Account_Logic;

    return instance_;

}

bool Account_Logic::connect_to_gate_server(Game_Logic::Game_Interface& gm_interface)
{
	//CCLog("---------------->bool Account_Logic::connect_to_gate_server");
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 0 )
        return false;

    Server_List_Data sld;
    sld.reset();

    //if( -1 == Account_Data_Mgr::instance()->get_server_list_by_id( (int)para[0], sld))
	if (-1 == Account_Data_Mgr::instance()->get_server_list_by_id(1000, sld))
        return false;
	//CCLog("Account_Data_Mgr::instance()->get_server_list_by_id( (int)para[0], sld)");


    para.clear();
    para.push_back(sld.get_server_port());
	//CCLog("--------------------->%d",sld.get_server_port());
//    if(Game_Logic::Game_Content_Interface::instance()->exec_interface("doconnectgate", para, sld.get_server_ip()))
//    {
        //CCLOG( "---------------------->connect to gate succesful" );
        para.clear();

		RecentlyServer::addServer(sld);
		log("----------------------RecentlyServer::addServer(sld);");
#if(CC_TARGET_PLATFORM==CC_PLATFORM_WIN32||CC_TARGET_PLATFORM==CC_PLATFORM_IOS||CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
        para.push_back(sld.get_next_ui());
        Game_Logic::Game_Content_Interface::instance()->exec_interface("shownextui", para);
#endif
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
		//Account_Msg_Proc::send_player_login();
#endif
	
        return true;
//    }
//	//CCLog("----------------------------end connect_to_gate_server");
//    return false;
}

bool Account_Logic::on_finish_load_scene( const Game_Logic::Game_Event& gm_evt )
{

   int player_id = Account_Data_Mgr::instance()->get_current_role_id();

    vector<uint64> para;
    para.push_back( player_id );

    Game_Logic::Game_Content_Interface::instance()->exec_interface("sendreqnpcquest",para);

    return true;
}

void Account_Logic::releaseData()
{
    ITEM_MGR::instance()->release();
    ITEM_CONTAINER_MGR::instance()->release();
    ACUPOINT_MGR::instance()->release();
    //OFFLINE_FIGHT_MGR::instance()->release();
    //OFFLINE_FIGHT_RECORD_MGR::instance()->release();
    //BUFF_MGR::instance()->cleanup();
    //SKILL_MGR::instance()->cleanup();
    Game_Data::quest_data_mgr::instance()->release();
    INSTANCE_DATA_MGR::instance()->release();
    //ACTOR_MGR::instance()->clear_all_actor();
    CHARACTER_MGR::instance()->release();

    //FSM::Game::instance()->process_event(FSM::Event::Main_Scence());
}