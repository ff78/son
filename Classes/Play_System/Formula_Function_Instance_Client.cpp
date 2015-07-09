
#include "Formula_Function_Instance_Client.h"

#include "Game_Interface/event_define.h"
#include "Game_Interface/game_element.h"
#include "Game_Interface/game_condition.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_mgr.h"
#include "Game_Interface/Game_Element_Parse.h"
#include "Game_Interface/game_event_response.h"
#include "Instance_Data_Mgr.h"
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
//#include "UI/GameUI_Layer.h"

#include "ClientLogic/FightDefine.h"
#include "DataModule/BattleField.h"
#include "Network_Common/NetManager.h"
#else
#include "Character_System/Player_Logic.h"
#include "Item_System/Item_Mgr_Sv.h"
#include "Common/Tool.h"
#endif

/*************************************************** dely **************************************************/
#include "ClientLogic/GameScene/ResultLayer.h"
/*************************************************** dely **************************************************/

Formula_Function_Instance_Client* Formula_Function_Instance_Client::instance_ =0;
Formula_Function_Instance_Client::Formula_Function_Instance_Client()
{
#ifdef YN_LINUX		
    pthread_mutex_init(&fomula_function_mutex_,NULL);
#endif

}

Formula_Function_Instance_Client::~Formula_Function_Instance_Client()
{
#ifdef YN_LINUX			
    pthread_mutex_destroy(&fomula_function_mutex_);
#endif
}

Formula_Function_Instance_Client* Formula_Function_Instance_Client::instance()
{
    if( NULL == instance_ )
        instance_ = new Formula_Function_Instance_Client;

    return instance_;
}


bool Formula_Function_Instance_Client::reg_monster_die_envent(Game_Logic::Game_Interface& gm_interface)
{

    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 2 )
        return false;

    int player_id = (int)para[0];
    int instance_id = (int)para[1];

    current_instance_data cid;
    if( -1 == INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid))
    {
        return false;
    }

    if( cid.get_instance_id() != instance_id )
        return false;

    vector<Game_Data::Game_Element> monster_lst;
    cid.get_monster_lst(monster_lst);
    vector<Game_Data::Game_Element>::iterator itm;
    Game_Logic::Game_Event event;
    for( itm = monster_lst.begin(); itm != monster_lst.end(); ++ itm )
    {
        event.reset();
        event.set_para(para);
        event.set_char_type(Game_Logic::Game_Event::EVENT_TYPE_PLAYER);
        event.set_char_id( player_id );
        event.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_INSTANCE);
        event.set_event_owner_id(instance_id);
        event.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_KILLMONSTER);
        event.set_event_active_id((*itm).get_cell_id());

        Game_Logic::Game_Event_Mgr::instance()->reg_event("monster", Formula_Function_Monster_Wave::proc_monster_die_envent, event);
    }


    return true;
}

bool Formula_Function_Instance_Client::proc_enter_instance(Game_Logic::Game_Interface& gm_interface)
{
	/************************************************************************/
	// 接收从Client_Instance_Msg_Proc处理的副本信息的消息
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 6 )
        return false;
    int idx = 0;
    int player_id       = (int)para[idx]; idx++;
    int instance_id     = (int)para[idx];idx++;
    int scene_id        = (int)para[idx];idx++;
    int time_limit      = (int)para[idx];idx++;
    int instance_first  = (int)para[idx];idx++;
    int monster_wave    = (int)para[idx];idx++;

    if((int)para.size() < idx + monster_wave)
        return false;

    vector<int> monster_wave_list;
    for( int i = 0; i < monster_wave; i++ )
    {
        monster_wave_list.push_back( (int)para[idx+i] );
    }

	/************************************************************************/
	// 对接收的数据进行存储并处理
	// 1. 清除玩家副本数据
    INSTANCE_DATA_MGR::instance()->remove_player_instance_data( player_id );

	// 2. 设置当前副本ID
    INSTANCE_DATA_MGR::instance()->set_current_instance_id(instance_id);

	// 3. 添加玩家副本的部分数据（副本ID，场景ID，怪物波数）
    INSTANCE_DATA_MGR::instance()->add_player_instance( player_id, instance_id, scene_id, monster_wave);

	// 4. 玩家第次进入副本重新注册副本事件
	// 这一步不太懂
	// 潘杰（12.05）
	// ...
	instance()->reg_instance_event_when_first_enter(player_id, instance_id, scene_id, para);

    current_instance_data cid;
    if( -1 == INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid))
    {
        return false;
    }

   
	// 5. 处理副本其余数据
    vector<int>::iterator iti;
    for( iti = monster_wave_list.begin(); iti != monster_wave_list.end(); ++ iti)
    {
        cid.add_monster_wave_id(*iti);
    }
    cid.set_instance_current_time_limit(time_limit);
    cid.set_saved_instance(instance_first);
    cid.set_instance_state(current_instance_data::INSTANCT_STATE_PROC);

    INSTANCE_DATA_MGR::instance()->modi_player_instance(player_id, cid);

	// 6. 获取敌人相关信息并存储
    instance()->proc_monster_wave_when_load_scene( player_id, instance_id, scene_id );

    //Runtime::instance()->enter_game_scene(scene_id);

    //ACTOR_MGR::instance()->clear_all_actor();
//    INSTANCE_DATA_MGR::instance()->set_instance_state(IS_GOING);

    
    Game_Logic::Game_Event event;
    event.reset();
    event.add_para(0);
    event.set_char_type(Game_Logic::Game_Event::EVENT_TYPE_PLAYER);
    event.set_char_id( player_id );
    event.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_INSTANCE);
    event.set_event_owner_id(instance_id);
    event.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_INSTANCE_DIALOG_FINISH);
    event.set_event_active_id(instance_id);
    //Game_Logic::Game_Event_Mgr::instance()->reg_event("instancetimerbegin", Formula_Function_Instance_Client::proc_instance_timer_begin, event);
    
    BattleField::instance()->setSceneId(instance_id);
    
    EventCustom evt(ENTER_FIGHT_NETOVER);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&evt);

    return true;
}

bool Formula_Function_Instance_Client::proc_player_die_envent( const Game_Logic::Game_Event& /*gm_evt*/ )
{

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    int instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();

    current_instance_data cid;
    if( -1 == INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid))
    {
        return false;
    }

    cid.add_total_player_die();
    INSTANCE_DATA_MGR::instance()->modi_player_instance(player_id, cid);

    //send to server
    vector<uint64> para;
    para.push_back(player_id);
    para.push_back(instance_id);
    Game_Logic::Game_Content_Interface::instance()->exec_interface("sendinstanceplayerdie", para);

    return true;
}

bool Formula_Function_Instance_Client::remove_instance_data(Game_Logic::Game_Interface& /*gm_interface*/)
{

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    int instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
    Game_Logic::Game_Event event;
    event.reset();
    event.set_char_type(Game_Logic::Game_Event::EVENT_TYPE_PLAYER);
    event.set_char_id( player_id );
    event.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_INSTANCE);
    event.set_event_owner_id(instance_id);
    Game_Logic::Game_Event_Mgr::instance()->remove_event(player_id, event);

    INSTANCE_DATA_MGR::instance()->remove_player_instance_data(player_id);

    return true;
}

bool Formula_Function_Instance_Client::on_finish_load_scene(const Game_Logic::Game_Event& gm_evt)
{

    //cout << "---------------Client_Instance_Msg_Proc::on_finish_load_scene------------------" <<endl;

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    int instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();

    if( 0 == instance_id )
        return false;


    if( instance()->process_instance_dialog( player_id, instance_id ) )
    {
        return true;
    }

    //process instance time limit display
    instance()->show_instance_time_limit(player_id);

    instance()->to_do_init_monster_wave(player_id, instance_id);

    return true;
}

int Formula_Function_Instance_Client::show_instance_time_limit(int player_id)
{
    current_instance_data cid;
    if( 0 == INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid))
    {

        int time_limit = cid.get_instance_current_time_limit();
        if( time_limit > 0)
        {

            UI_TimeLimitedInstance_Layer::sharedInstance()->showTime(time_limit);
            return 0;
        }
    }
    return -1;
}

bool Formula_Function_Instance_Client::proc_instance_fail(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 1 )
        return false;

    int rst = (int)para[0];

    int dic = 0;

    UI_TimeLimitedInstance_Layer::sharedInstance()->removeTime();

    if(  current_instance_data::INSTANCE_STATE_FAILE_OVER_TIME == rst )
    {
        dic = 90301;
    }
    else if( current_instance_data::INSTANCE_STATE_FAILE == rst )
    {
        dic = 90300;
    }
    const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(dic);
    UI_ModalDialogue_Layer::DoModal("", szString, UI_ModalDialogue_Layer::DT_OK, [&]()
    { 
        vector<uint64> para;
        para.clear();
        para.push_back(current_instance_data::INSTANCE_STATE_FAILE);
        Game_Logic::Game_Content_Interface::instance()->exec_interface("oninstancefinish", para);

        para.clear();
        para.push_back(1);

        Game_Logic::Game_Content_Interface::instance()->exec_interface("enterscene", para);

        //Game_Utils::instance()->reset_role_actor();
    } 
    );
    return true;
}
bool Formula_Function_Instance_Client::proc_instance_finish(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 4 )
        return false;
    int player_id = (int)para[0];
    int instance_id = (int)para[1];
    int instance_score = (int)para[2];
    int instance_state = (int)para[3];
    
    current_instance_data cid_new;
    cid_new.reset();


    /****************************************** dely ****************************************/
    if (-1 == INSTANCE_DATA_MGR::instance()->get_player_instance(player_id, cid_new))
    {
        cid_new.set_instance_id(instance_id);
        cid_new.set_instance_score(instance_score );
        INSTANCE_DATA_MGR::instance()->add_player_instance(player_id, cid_new);
    }
    else
    {
        cid_new.set_instance_id(instance_id);
        cid_new.set_instance_score(instance_score );
        INSTANCE_DATA_MGR::instance()->modi_player_instance(player_id, cid_new);
    }
    /****************************************** dely ****************************************/
    #if 1//yyp
    if (instance_state == current_instance_data::INSTANCE_STATE_SUC) {
        if( -1 == INSTANCE_DATA_MGR::instance()->get_player_instance_from_list(player_id, cid_new))
        {
            cid_new.set_instance_id(instance_id);
            cid_new.set_instance_score(instance_score );
            cid_new.set_instance_state(instance_state);
            INSTANCE_DATA_MGR::instance()->add_player_instance_lst(player_id, cid_new);
        }
        else
        {
            cid_new.set_instance_id(instance_id);
            cid_new.set_instance_score(instance_score );
            cid_new.set_instance_state(instance_state);
            INSTANCE_DATA_MGR::instance()->modi_player_instance_list(player_id, cid_new);
        }
    }
    
     #endif
//    UI_TimeLimitedInstance_Layer::sharedInstance()->removeTime();
	if (current_instance_data::INSTANCE_STATE_FAILE_OVER_TIME == instance_state || current_instance_data::INSTANCE_STATE_FAILE == instance_state)
	{
		ResultLayer::sWinOrLose = false;	
	}
	else
	{
		ResultLayer::sWinOrLose = true;
	}

//    ,,.,,,.,./,.,/
/************************************* dely ***********************************/
//	Game_Logic::Game_Content_Interface::instance()->exec_interface("pop_result", para);
    EventCustom evt(FIGHT_RESUTLT_NETOVER);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&evt);
/************************************* dely ***********************************/
    

    //Game_Utils::instance()->kill_all_monster();
    //Game_Utils::instance()->add_image_to_scene("shengfuyifen.png",SHOW_WIN_DELAY);
    //Game_Utils::instance()->instance_dialog_after_fight(player_id,instance_id,instance_state);
    
    
    /*
     if(UI_FuBenDialog::sharedUI_FuBenDialog()->get_is_show() || instance()->process_instance_dialog( player_id, instance_id, 1 ) )
     {
     return true;
     }*/
    /*
     current_instance_data cid;
     if(0 == INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid) )
     {
     cid.set_instance_state(instance_state);
     INSTANCE_DATA_MGR::instance()->modi_player_instance( player_id, cid );
     }
     
     if(current_instance_data::INSTANCE_STATE_SUC == instance_state )
     Game_Utils::instance()->show_win();
     
     Game_Logic::Game_Event_Response::instance()->on_update_game_ui_child_info(player_id);
     */
    return true;
}

int Formula_Function_Instance_Client::process_instance_dialog( int player_id, int instance_id, int instance_finish )
{
    current_instance_data cid;
    if( -1 == INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid))
    {
        return false;
    }

    // not first enter instance, ignor display instance dialog
    if( current_instance_data::INSTANCE_FIRST != cid.get_saved_instance())
    {
        return false;
    }

    int dialog_id = Game_Data::Formula_Mgr::instance()->get_instance_dialog_id( player_id, instance_id, instance_finish );

    if( -1 == dialog_id )
        return false;

    instance_dialog id_data;
    if( -1 == Instance_Data_Mgr::instance()->get_instance_dialog_data_by_id( dialog_id, id_data ) )
        return false;

    Instance_Data_Mgr::instance()->clear_current_dialog();

    std::list< Game_Data::Game_Command_Element> gce_list;
    id_data.get_command_element_list(gce_list);
    std::list< Game_Data::Game_Command_Element>::iterator itg;
    list<Game_Data::Game_Element>::iterator ite;
    list<Game_Data::Game_Element> ge_lst;

    for( itg = gce_list.begin(); itg != gce_list.end(); ++ itg )
    {
        ge_lst.begin();
        (*itg).get_game_element_data(ge_lst);
        for( ite = ge_lst.begin(); ite != ge_lst.end(); ++ ite )
        {
            Instance_Data_Mgr::instance()->push_current_dialog((*ite));
        }
    }

    Game_Logic::Game_Event event;
    event.reset();
    event.add_para(instance_finish);
    event.set_char_type(Game_Logic::Game_Event::EVENT_TYPE_PLAYER);
    event.set_char_id( player_id );
    event.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_INSTANCE);
    event.set_event_owner_id(instance_id);
    event.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_INSTANCE_DIALOG_FINISH);
    event.set_event_active_id(instance_id);
    Game_Logic::Game_Event_Mgr::instance()->reg_event("instancedialogfinish", Formula_Function_Instance_Client::proc_instance_dialog_finish_envent, event);

    vector<uint64> para;
    /*Game_Logic::Game_Content_Interface::instance()->exec_interface("showinstancedialog", para);

    UI_FuBenDialog::sharedUI_FuBenDialog()->set_is_show(true);*/
    return true;
}

bool Formula_Function_Instance_Client::proc_instance_dialog_finish_envent( const Game_Logic::Game_Event& gm_evt )
{
    vector<uint64> para;
    gm_evt.get_para(para);
    if( para.size() < 1 )
        return false;
    
    int instance_finish_state = (int)para[0];
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    int instance_id = gm_evt.get_event_owner_id();
    if( 0 == instance_finish_state ) //display when enter instance
    {
        UI_FuBenDialog::sharedUI_FuBenDialog()->removeDialog();

        int instance_type;
        int time_limit = Game_Data::Formula_Mgr::instance()->get_time_limit( instance_id, instance_type );
        if( time_limit > 0 )
        {
            current_instance_data cid;
            if( -1 == INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid))
            {
                return false;
            }
            cid.set_instance_current_time_limit(time_limit);
            INSTANCE_DATA_MGR::instance()->modi_player_instance(player_id, cid);

            instance()->show_instance_time_limit( player_id);
            para.clear();
            para.push_back( player_id );
            para.push_back(instance_id);
            Game_Logic::Game_Content_Interface::instance()->exec_interface("sendbegininstancetimer", para);
        }

        instance()->to_do_init_monster_wave(player_id, instance_id);
    }
    else  //display finish 
    {
        UI_FuBenDialog::sharedUI_FuBenDialog()->removeDialog();
        current_instance_data cid;
        if(0 == INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid) )
        {
            cid.set_instance_state(current_instance_data::INSTANCE_STATE_SUC);
            INSTANCE_DATA_MGR::instance()->modi_player_instance( player_id, cid );
        }

       //Game_Utils::instance()->show_win();

        Game_Logic::Game_Event_Response::instance()->on_update_game_ui_child_info(player_id);
    }

    Game_Logic::Game_Event_Mgr::instance()->remove_event(player_id, gm_evt);

    return true;
}

int Formula_Function_Instance_Client::to_do_init_monster_wave(int player_id, int instance_id)
{

    //Game_Utils::instance()->init_monser_wave();

    Game_Logic::Game_Event event;
    event.reset();
    event.set_char_type(Game_Logic::Game_Event::EVENT_TYPE_PLAYER);
    event.set_char_id( player_id );
    event.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_INSTANCE);
    event.set_event_owner_id(instance_id);
    event.set_event_active_type(Game_Logic::Game_Event::EVENT_FINISH_SCENE_LOAD);
    event.set_event_active_id(0);
    Game_Logic::Game_Event_Mgr::instance()->remove_event(player_id, event);

    current_instance_data cid;
    if( 0 == INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid))
    {

        vector<uint64> para;
        para.push_back( cid.get_monster_wave() + 1 );
        para.push_back( cid.get_monster_wave_require() );
        Game_Logic::Game_Content_Interface::instance()->exec_interface("showmonsterwave", para);
    }

    return 0;
}

bool Formula_Function_Instance_Client::show_monster_wave(Game_Logic::Game_Interface& gm_interface)
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 2 )
        return false;

    int cur_monster_wave        = (int)para[0];
    int require_monster_wave    = (int)para[1];

    if( cur_monster_wave == 0 && require_monster_wave == 0)
    {
        UI_Message::sharedInstance()->removeMessage();
        return false;
    }

    if(cur_monster_wave > require_monster_wave)
        return false;

    UI_Message::sharedInstance()->showMessage(90302, cur_monster_wave, require_monster_wave);

    return true;
}

bool Formula_Function_Instance_Client::show_instance_dialog(Game_Logic::Game_Interface& /*gm_interface*/)
{

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();

    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if (player == NULL)
    {
        return false;
    }  

    if( 0 == Instance_Data_Mgr::instance()->is_current_dialog_empty() )
    {
        int instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
        Game_Logic::Game_Event_Response::instance()->on_finish_show_dialog(player_id, instance_id);

        UI_FuBenDialog::sharedUI_FuBenDialog()->set_is_show(false);
        return true;
    }
    Game_Data::Game_Element ge;
    ge.reset();
    Instance_Data_Mgr::instance()->pop_current_dialog(ge);
    vector<uint> para;
    ge.get_para_list_in_vector( para );
    string left_str = "dialogleft";
    string right_str = "dialogright";
    string player_left_str = "player_dialogleft";
    string player_right_str = "player_dialogright";
    bool left = false;
    int head_id = 0, dic_id = 0;
    if( !left_str.compare(ge.get_command()))
    {
        left = true;

        if( para.size() < 2 )
            return false;
        head_id = para[0];
        dic_id = para[1];
    }
    else if( !right_str.compare(ge.get_command()))
    {
        left = false;

        if( para.size() < 2 )
            return false;

        head_id = para[0];
        dic_id = para[1];
    }
    else if( !player_left_str.compare(ge.get_command()))
    {
        left = true;

        instance()->get_instance_dialog_data(player, head_id, dic_id,  para );

    }
    else if( !player_right_str.compare(ge.get_command()))
    {
        left = false;

        instance()->get_instance_dialog_data(player, head_id, dic_id,  para );

    }
    else 
        return false;


    UI_FuBenDialog::sharedUI_FuBenDialog()->showDialogMessage(left, head_id,  dic_id);

    return true;
}

void Formula_Function_Instance_Client::get_instance_dialog_data( Game_Data::Player* player, int& head_id, int& dic_id, vector<uint>& para )
{

    if( para.size() < 3 )
        return ;

    if (player->get_sex() == 1)
    {

        head_id = para[0];
    }
    else
        head_id = para[1];
    dic_id = para[2];
}

int Formula_Function_Instance_Client::proc_monster_wave_when_load_scene( int player_id, int instance_id, int scene_id )
{
	/************************************************************************/
	// 获取敌人相关信息并存储
    current_instance_data cid;
    if( -1 == INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid))
    {
        CCLOG( "Error load current instance_data" );

        return false;
    }

    vector<int> monster_wave_lst;
    cid.get_monster_wave_id_list( monster_wave_lst );

    list<Game_Data::Game_Command_Element> gce_lst;
    list<Game_Data::Game_Command_Element>::iterator itc;
    list<Game_Data::Game_Element>::iterator ite;
    vector<int>::iterator iti;
    int total_monster_wave_require = 0; int total_scene = 0;
    for( iti = monster_wave_lst.begin(); iti != monster_wave_lst.end(); ++ iti )
    {
        //Monster_Wave_Config* mwc_data = Monster_Wave_Cfg_Data_Mgr::shared_instance()->get_monster_wave_data_by_id(*iti);
        //if( NULL == mwc_data )
        //    continue;

        gce_lst.clear();
        //mwc_data->get_command_element_list(gce_lst);
        cid.set_scene_config( ++ total_scene , gce_lst.size());
        for( itc = gce_lst.begin(); itc != gce_lst.end(); ++ itc )
        {
            total_monster_wave_require ++;

        }
    }
    cid.set_monster_wave_require( total_monster_wave_require);
    INSTANCE_DATA_MGR::instance()->modi_player_instance( player_id, cid );

    return 0;
}

bool Formula_Function_Instance_Client::process_instance_player_back_home(Game_Logic::Game_Interface& gm_interface)
{

    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 2 )
        return false;
    int player_id = (int)para[0];
    int instance_id = (int)para[1];

    INSTANCE_DATA_MGR::instance()->remove_player_instance_data( player_id );
    //send instance result to game server

    return true;
}

int Formula_Function_Instance_Client::reg_instance_event_when_first_enter( int player_id, int instance_id,int /*scene_id*/, vector<uint64>& para )
{
    Game_Logic::Game_Event event;
    event.reset();
    event.set_para(para);
    event.set_char_type(Game_Logic::Game_Event::EVENT_TYPE_PLAYER);
    event.set_char_id( player_id );
    event.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_INSTANCE);
    event.set_event_owner_id(instance_id);
    event.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_PLAYER_DIE);
    event.set_event_active_id(player_id);
#ifdef GAME_CLIENT
    Game_Logic::Game_Event_Mgr::instance()->reg_event("playerdie", Formula_Function_Instance_Client::proc_player_die_envent, event);
#endif
    //wait scene load over and to process monster msg
    event.reset();
    event.set_para(para);
    event.set_char_type(Game_Logic::Game_Event::EVENT_TYPE_PLAYER);
    event.set_char_id( player_id );
    event.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_INSTANCE);
    event.set_event_owner_id(instance_id);
    event.set_event_active_type(Game_Logic::Game_Event::EVENT_FINISH_SCENE_LOAD);
    event.set_event_active_id(0);

#ifdef GAME_CLIENT
    Game_Logic::Game_Event_Mgr::instance()->reg_event("finishi_load_scene", Formula_Function_Instance_Client::on_finish_load_scene, event);
#endif
    return 0;
}


void Formula_Function_Instance_Client::notifyServerTime()
{
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    int instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
    
    Game_Logic::Game_Event ge;
    
    ge.reset();
    ge.set_char_id(player_id);
    ge.set_char_type(Game_Logic::Game_Event::EVENT_TYPE_PLAYER);
    ge.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_INSTANCE_DIALOG_FINISH);
    ge.set_event_active_id(instance_id);
    Game_Logic::Game_Event_Mgr::instance()->proc_event(player_id,"instancedialogfinish",ge);
}
void Formula_Function_Instance_Client::notifyServerLose()
{
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    int instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
    current_instance_data cid;
    //if (-1 == INSTANCE_DATA_MGR::instance()->get_player_instance(player_id, cid))
    //{
    //	//return false;
    //	return;
    //}
    /*cid.add_monster_counter(monster_id);
     cid.add_total_monster_kill();*/
    vector<uint64> para;

    para.clear();
    para.push_back(player_id);//old
    para.push_back(instance_id);//new
    
	para.push_back(current_instance_data::INSTANCE_STATE_FAILE);
    
    Game_Logic::Game_Content_Interface::instance()->exec_interface("sendfinishinstance", para);//success
}

void Formula_Function_Instance_Client::notifyServerWin()
{
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    int instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
    current_instance_data cid;
    //if (-1 == INSTANCE_DATA_MGR::instance()->get_player_instance(player_id, cid))
    //{
    //	//return false;
    //	return;
    //}
    /*cid.add_monster_counter(monster_id);
     cid.add_total_monster_kill();*/
    vector<uint64> para;

    para.clear();
    para.push_back(player_id);//old
    para.push_back(instance_id);//new
    
    para.push_back(current_instance_data::INSTANCE_STATE_SUC);
    
    Game_Logic::Game_Content_Interface::instance()->exec_interface("sendfinishinstance", para);//success
    
    //para.clear();
    //Game_Logic::Game_Content_Interface::instance()->exec_interface("remvoeinstancedata", para);
}

void Formula_Function_Instance_Client::waitPacket()
{
    CNetManager::GetMe()->WaitPacket();

}

void Formula_Function_Instance_Client::requireSelStage()
{
    vector<uint64> para;
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    para.push_back( player_id );
    para.push_back(1000);
    
    Game_Logic::Game_Content_Interface::instance()->exec_interface("sendrequireallstage", para);
}
