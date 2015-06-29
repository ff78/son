#include "game_event_response.h"
#include "game_event_mgr.h"
#include "game_content_interface.h"
#ifdef GAME_CLIENT
//#include "AI_System/Game_Utils.h"
#include "Player_Account/Account_Data_Mgr.h"
#include "Play_System/Instance_Data_Mgr.h"
#endif

namespace Game_Logic
{

    Game_Event_Response* Game_Event_Response::instance_p_ = 0;

    Game_Event_Response::Game_Event_Response(void)
    {
#ifdef YN_LINUX		
        //pthread_mutex_init(&game_event_response_mutex_,NULL);
#endif
    }

    Game_Event_Response::~Game_Event_Response(void)
    {
#ifdef YN_LINUX		
        //pthread_mutex_destroy(&game_event_response_mutex_);
#endif
        if( instance_p_ )
            delete instance_p_;
    }

    Game_Event_Response* Game_Event_Response::instance(void)
    {
        if( NULL == instance_p_ )
        {
            instance_p_ = new Game_Event_Response;
        }

        return instance_p_;
    }

    int Game_Event_Response::on_hurt( const int char_type, const int char_id )
    {
        Game_Event ge;
        ge.set_char_id(char_id);
        ge.set_char_type(char_type);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_HURT);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(-1,"monsterattack",ge);

        return 0;
    }
    void Game_Event_Response::on_collided_something(int item_id,int player_id)
    {

        //服务端自己的事情
        vector<uint64> para;
        para.push_back(item_id);

        Game_Logic::Game_Event ge;
        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Logic::Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_COLLIDED_SOMETHING);
        ge.set_event_active_id(item_id);
        ge.set_para(para);
        Game_Logic::Game_Event_Mgr::instance()->proc_event(player_id,"collided_something",ge);
        //////////////////////////////////////////////////////////////////////////////////////////
    }
    void Game_Event_Response::on_useitem_something(int item_id,int player_id)
    {
        //服务端自己的事情
        vector<uint64> para;
        para.push_back(item_id);

        Game_Logic::Game_Event ge;
        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Logic::Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_USEITEM);
        ge.set_event_active_id(item_id);
        ge.set_para(para);
        Game_Logic::Game_Event_Mgr::instance()->proc_event(player_id,"useitem",ge);
        //////////////////////////////////////////////////////////////////////////////////////////
    }
    int Game_Event_Response::on_finish_show_dialog( int player_id, int instance_id )
    {
        Game_Event ge;

        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_INSTANCE_DIALOG_FINISH);
        ge.set_event_active_id(instance_id);
        Game_Event_Mgr::instance()->proc_event(player_id,"instancedialogfinish",ge);

        return 0;
    }

    int Game_Event_Response::on_character_die( const int char_id, const int char_type, float posX,float posY,int player_id)
    {
#ifdef GAME_CLIENT
        player_id = Account_Data_Mgr::instance()->get_current_role_id();
#endif
        Game_Event ge;
        if( char_type == Game_Event::EVENT_TYPE_MONSTER)
        {
            ge.reset();
            ge.set_char_id(player_id);
            ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
            ge.set_event_active_type(Game_Event::EVENT_TYPE_KILLMONSTER);
            ge.set_event_active_id(char_id);
            ge.add_para((int)posX);
            ge.add_para((int)posY);
            Game_Event_Mgr::instance()->proc_event(player_id,"monster",ge);

            return 0;
        }
        else if( char_type == Game_Event::EVENT_TYPE_PLAYER )
        {
            ge.reset();
            ge.set_char_id(player_id);
            ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
            ge.set_event_active_type(Game_Event::EVENT_TYPE_PLAYER_DIE);
            ge.set_event_active_id(player_id);
            Game_Event_Mgr::instance()->proc_event(player_id,"playerdie",ge);
            return 0;
        }

        return -1;
    }

    int Game_Event_Response::on_kill_monster( int player_id, int monster_id, int kill_counts )
    {
        vector<uint64> para;
        para.push_back(kill_counts);
        Game_Event ge;
        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_KILLMONSTER);
        ge.set_event_active_id(monster_id);
        ge.set_para(para);
        Game_Event_Mgr::instance()->proc_event(player_id,"monster",ge);
        return 0;
    }

    void Game_Event_Response::on_update_main_ui_info(int player_id)
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_UI_MIAN);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"update_main_ui_info",ge);
    }

    void Game_Event_Response::on_update_item_ui_info(int player_id)
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_UI_ITEM);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"update_item_ui_info",ge);
    }

    void Game_Event_Response::on_update_game_ui_child_info(int player_id)
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_UI_GAME_CHILD);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"update_game_ui_child_info",ge);
    }

    int Game_Event_Response::on_finish_scene_load( void )
    {
#ifdef GAME_CLIENT
        int player_id =  Account_Data_Mgr::instance()->get_current_role_id();
        int instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Logic::Game_Event::EVENT_FINISH_SCENE_LOAD);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"finishi_load_scene",ge);
#endif
        return 0;
    }

    void Game_Event_Response::on_update_skill(int player_id)
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_SKILL);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"update_skill",ge);
    }

    void Game_Event_Response::on_update_npcdialog(int player_id)
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_UI_NPCDIALOG);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"update_npcdialog",ge);
    }

    void Game_Event_Response::on_update_arena(int player_id)
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_ARENA);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"update_arena",ge);
    }

    void Game_Event_Response::on_update_count_down_time(int player_id,int time)
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_COUNT_DOWN_TIME);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
        ge.set_event_active_id(0);

        vector<uint64>  para;
        para.push_back(time);
        ge.set_para(para);
        Game_Event_Mgr::instance()->proc_event(player_id,"update_count_down_time",ge);
    }

    void Game_Event_Response::on_update_instance_stage_info( int player_id )
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_INSTANCE_STAGE);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"update_instance_stage",ge);
    }
    void Game_Event_Response::on_update_stage_all(int player_id)
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_STAGE_ALL);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"update_stage_all",ge);
    }
#if 1//MISSION_DIALOG

    void Game_Event_Response::on_update_mission_dialog(int player_id,int quest_id)
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_MISSION_DIALOG);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
		ge.set_event_active_id(quest_id);
        Game_Event_Mgr::instance()->proc_event(player_id,"update_mission_dialog",ge);
    }
	#endif
    void Game_Event_Response::on_update_stage( int player_id )
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_STAGE);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"update_stage",ge);
    }

    void Game_Event_Response::on_update_friend_ui_list(int player_id)
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_FRIEND_LIST);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"update_friend_list",ge);
    }

    void Game_Event_Response::on_update_role_quality_up(int player_id)
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_UI_ROLE_QUALITY_UP);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"update_role_quality_up",ge);
    }

    void Game_Event_Response::on_update_compound_fragment(int player_id,int change)
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_UI_COMPOUND_FRAGMENT);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
        ge.set_event_active_id(0);

        vector<uint64>  para;
        para.push_back(change);
        ge.set_para(para);
        Game_Event_Mgr::instance()->proc_event(player_id,"update_compound_fragment",ge);
    }

    void Game_Event_Response::on_update_fate(int player_id)
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_UI_FATE);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"update_fate",ge);
    }

    void Game_Event_Response::on_update_banks(int player_id)
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_UI_BANKS);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"update_banks",ge);
    }

    void Game_Event_Response::on_update_rank(int player_id,int rank_type)
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_UI_RANK);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
        ge.set_event_active_id(0);

        vector<uint64>  para;
        para.push_back(rank_type);
        ge.set_para(para);
        Game_Event_Mgr::instance()->proc_event(player_id,"update_rank",ge);
    }

    //---------------------------------------------------------------------------

    int Game_Event_Response::on_item( int player_id, int item_id )
    {
        Game_Event ge;

        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_ITEM);
        ge.set_event_active_id(item_id);
        Game_Event_Mgr::instance()->proc_event(player_id,"item",ge);
        return 0;
    }
    int Game_Event_Response::on_book_equip( int player_id, int item_id )
    {
        Game_Event ge;

        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_BOOK_EQUIP);
        ge.set_event_active_id(item_id);
        Game_Event_Mgr::instance()->proc_event(player_id,"book_equip",ge);

        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_BOOK_QUALITY_UP);
        ge.set_event_active_id(item_id);
        Game_Event_Mgr::instance()->proc_event(player_id,"equipbookreqqa",ge);
        return 0;
    }
    int Game_Event_Response::on_instance_suc( int player_id, int instance_id )
    {
        Game_Event ge;

        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_INSTANCE_SUC);
        ge.set_event_active_id(instance_id);
        Game_Event_Mgr::instance()->proc_event(player_id,"instance",ge);
        return 0;
    }
    int Game_Event_Response::on_item_equip( int player_id, int item_id )
    {
        Game_Event ge;

        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_ITEM_EQUIP);
        ge.set_event_active_id(item_id);
        Game_Event_Mgr::instance()->proc_event(player_id,"itemequip",ge);

        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_ITEM_EQUIP_ALL);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"item_equip_all",ge);
        return 0;
    }
    int Game_Event_Response::on_book_fragment_compound( int player_id, int item_id )
    {
        Game_Event ge;

        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_BOOK_FRAGMENT_COMPOUND);
        ge.set_event_active_id(item_id);
        Game_Event_Mgr::instance()->proc_event(player_id,"book_fragment_compound",ge);
        return 0;
    }
    int Game_Event_Response::on_material_fragment_compound( int player_id, int item_id )
    {
        Game_Event ge;

        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_MATERIAL_FRAGMENT_COMPOUND);
        ge.set_event_active_id(item_id);
        Game_Event_Mgr::instance()->proc_event(player_id,"material_fragment_compound",ge);
        return 0;
    }
    int Game_Event_Response::on_skill_upgrade( int player_id, int skill_id )
    {
        Game_Event ge;

        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_SKILL_UPGRADE);
        ge.set_event_active_id(skill_id);
        Game_Event_Mgr::instance()->proc_event(player_id,"skill_up",ge);
        Game_Event_Mgr::instance()->proc_event(player_id,"skillreqlevel",ge);
        return 0;
    }
    int Game_Event_Response::on_book_level_up( int player_id, int item_id )
    {
        Game_Event ge;

        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_BOOK_LEVEL_UP);
        ge.set_event_active_id(item_id);
        Game_Event_Mgr::instance()->proc_event(player_id,"book_level_up",ge);
        return 0;
    }

    int Game_Event_Response::on_equipment_level_up( int player_id, int item_id )
    {
        Game_Event ge;

        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_EQUIPMENT_LEVEL_UP);
        ge.set_event_active_id(item_id);
        Game_Event_Mgr::instance()->proc_event(player_id,"equipment_level_up",ge);
        return 0;
    }
    int Game_Event_Response::on_equipment_quality_up( int player_id, int item_id )
    {
        Game_Event ge;

        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_EQUIPMENT_QUALITY_UP);
        ge.set_event_active_id(item_id);
        Game_Event_Mgr::instance()->proc_event(player_id,"equipment_quality_up",ge);
        Game_Event_Mgr::instance()->proc_event(player_id,"allequipreqqa",ge);
        return 0;
    }
    int Game_Event_Response::on_pk_finish( int player_id )
    {
        Game_Event ge;

        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_PK_PLAYER);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"pk_player",ge);
        return 0;
    }
    int Game_Event_Response::on_fight_general( int player_id )
    {
        Game_Event ge;

        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_FIGHT_GENERAL);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"fight_general",ge);
        return 0;
    }
    int Game_Event_Response::on_acupoint_open( int player_id )
    {
        Game_Event ge;

        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_ACUPOINT_OPEN);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"acupoint_open",ge);
        return 0;
    }
    int Game_Event_Response::on_addfriends( int player_id )
    {
        Game_Event ge;

        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_ADDFRIENDS);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"friends",ge);
        return 0;
    }
    int Game_Event_Response::on_cost_gold( int player_id )
    {
        Game_Event ge;

        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_COST_GOLD);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"costgold",ge);
        return 0;
    }
    int Game_Event_Response::on_player_quality_up( int player_id )
    {
        Game_Event ge;

        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_PLAYER_QUALITY_UP);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"player_quality_up",ge);
        return 0;
    }
    int Game_Event_Response::on_book_quality_up( int player_id, int book_id )
    {
        Game_Event ge;

        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_BOOK_QUALITY_UP);
        ge.set_event_active_id(book_id);
        Game_Event_Mgr::instance()->proc_event(player_id,"book_quality_up",ge);
        Game_Event_Mgr::instance()->proc_event(player_id,"equipbookreqqa",ge);
        return 0;
    }
    int Game_Event_Response::on_gerneral_qa_up( int player_id )
    {
        Game_Event ge;

        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_GERNERAL_REQ_QA);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"gerneralreqqa",ge);
        return 0;
    }
    int Game_Event_Response::on_add_money( int player_id )
    {
        Game_Event ge;

        ge.reset();
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Event::EVENT_TYPE_MONEY_REQ);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"moneyreq",ge);
        return 0;
    }
    //----------------------------------------------------------------------------

    bool  Game_Event_Response::on_complete_quest( const int player_id, const int quest_id,bool /*give_up_quest*/, int /*ring_quest_id*/ )
    {
        Game_Event gm_para;
        gm_para.set_char_id( player_id );
        gm_para.set_char_type( Game_Event::EVENT_TYPE_PLAYER );
        gm_para.set_event_active_type( Game_Event::EVENT_TYPE_QUEST_COMPLETE );
        gm_para.set_event_active_id( quest_id );
        Game_Event_Mgr::instance()->proc_event( player_id, "questcomplete",gm_para);

        return true;
    }

    void Game_Event_Response::on_update_selected_relation_spine( int player_id )
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_FRIEND_DETAIL);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"update_selected_relation_spine",ge);
    }

	void Game_Event_Response::on_update_login_award( int player_id )
	{
		Game_Event ge;
		ge.set_char_id(player_id);
		ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
		ge.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_UI_LOGIN_AWARD);
		ge.set_event_owner_id (0);
		ge.set_event_active_type(0);
		ge.set_event_active_id(0);
		Game_Event_Mgr::instance()->proc_event(player_id,"update_login_award",ge);
	}

    void Game_Event_Response::on_update_instance_sweep( int player_id )
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_UI_INSTANCE_SWEEP);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"update_instance_sweep",ge);
    }

    void Game_Event_Response::on_update_gem_inlay( int player_id ,int gem_pos)
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_UI_GEM_INLAY);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
        ge.set_event_active_id(0);

        if (gem_pos >= 0)
        {
            vector<uint64>  para;
            para.push_back(gem_pos);
            ge.set_para(para);
        }
        
        Game_Event_Mgr::instance()->proc_event(player_id,"update_gem_inlay",ge);
    }

    void Game_Event_Response::on_update_operate_gem(int player_id,int gem_id)
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_active_type(Game_Logic::Game_Event::EVENT_TYPE_UI_OPERATE_GEM);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
        ge.set_event_active_id(0);

        vector<uint64>  para;
        para.push_back(gem_id);
        ge.set_para(para);
        Game_Event_Mgr::instance()->proc_event(player_id,"update_operate_gem",ge);
    }

    void Game_Event_Response::on_update_gem_level_up( int player_id )
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_UI_GEM_LEVEL_UP);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"update_gem_level_up",ge);
    }

    void Game_Event_Response::on_update_shop( int player_id )
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_UI_SHOP);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"update_shop",ge);
    }

    void Game_Event_Response::on_update_daily_task( int player_id )
    {
        Game_Event ge;
        ge.set_char_id(player_id);
        ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
        ge.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_UI_DAILY_TASK);
        ge.set_event_owner_id (0);
        ge.set_event_active_type(0);
        ge.set_event_active_id(0);
        Game_Event_Mgr::instance()->proc_event(player_id,"update_daily_task",ge);
    }

	/***********************  dely ************************/
	void Game_Event_Response::on_update_chat(int player_id)
	{
		Game_Event ge;
		ge.set_char_id(player_id);
		ge.set_char_type(Game_Event::EVENT_TYPE_PLAYER);
		ge.set_event_owner_type(Game_Logic::Game_Event::EVENT_TYPE_UI_CHAT);
		ge.set_event_owner_id(0);
		ge.set_event_active_type(0);
		ge.set_event_active_id(0);
		Game_Event_Mgr::instance()->proc_event(player_id, "update_chat", ge);
	}
	/***********************  dely ************************/
}