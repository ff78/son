
#include "Formula_Function_Monster_Wave.h"


#include "Player_Account/Account_Data_Mgr.h"
#include "Instance_Data_Mgr.h"
#include "Game_Interface/game_content_interface.h"
#ifdef GAME_CLIENT
//#include "AI_System/Game_Utils.h"
//#include "UI/GameUI_Layer.h"
//#include "Game_Utils.h"
//#include "UI/GameUI_Layer.h"
//#include "Monster_Cfg_Data_Mgr.h"
#endif
Formula_Function_Monster_Wave* Formula_Function_Monster_Wave::instance_ = 0;
Formula_Function_Monster_Wave::Formula_Function_Monster_Wave()
{

}



Formula_Function_Monster_Wave::~Formula_Function_Monster_Wave()
{

}

Formula_Function_Monster_Wave* Formula_Function_Monster_Wave::instance()
{
    if( NULL == instance_ )
        instance_ = new Formula_Function_Monster_Wave;

    return instance_;
}

bool  Formula_Function_Monster_Wave::process_next_wave_monster(Game_Logic::Game_Interface& gm_interface )
{
    //Game_Utils::instance()->init_monser_wave();
    return true;
}

bool Formula_Function_Monster_Wave::on_finish_create_monster(Game_Logic::Game_Interface& gm_interface)
{
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    int instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
    //call to refresh monster
    current_instance_data cid;
    if( -1 == INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid))
    {
        return false;
    }
#ifdef GAME_CLIENT
    // get monster id list and call to reg event
    map<int,int> monster_lst; monster_lst.clear();
    //Game_Utils::instance()->get_monster_prototype_map(monster_lst);
    vector<uint64> para;
    para.clear();
    para.push_back(player_id);
    para.push_back(instance_id);
    map<int,int>::iterator iti;
    Game_Data::Game_Element ge;
    cid.clear_monster_counter_lst();
    for( iti = monster_lst.begin(); iti != monster_lst.end(); ++iti)
    {
        ge.reset();
        ge.set_cell_id(iti->first);
        ge.set_count_require(iti->second);
        cid.instert_monster_counter_lst(ge);
    }
    
    int cur_lock_scene = instance()->get_current_locked_screen(cid);

  
    if( cur_lock_scene > 0 && cur_lock_scene != cid.get_current_lock_scene_id() )
    {
        cid.set_current_lock_scene_id(cur_lock_scene); 
        //Game_Utils::instance()->locked_screen(true, cur_lock_scene);
    }

    INSTANCE_DATA_MGR::instance()->modi_player_instance(player_id, cid);
    Game_Logic::Game_Content_Interface::instance()->exec_interface("regmonsterdie",para);

#endif  
 return true;
}

int Formula_Function_Monster_Wave::get_current_locked_screen(current_instance_data& cid)
{
    int monster_wave = cid.get_monster_wave();
    int cur_scene_count = 0;
    map<int,int> scene_lst;
    cid.get_scene_config_list( scene_lst );
    map<int,int>::iterator iti;
    int cur_lock_scene = 0;
    int monser_wave_count = 0;
    for( iti = scene_lst.begin(); iti != scene_lst.end(); ++iti)
    {
        monser_wave_count += iti->second;
        if( monster_wave + 1 <= monser_wave_count )
        {
            cur_lock_scene = iti->first;
            break;
        }
 
    }
    return cur_lock_scene;
}

bool Formula_Function_Monster_Wave::proc_monster_die_envent(const Game_Logic::Game_Event& gm_evt)
{

    int player_id = gm_evt.get_char_id();
    int instance_id = gm_evt.get_event_owner_id();
    current_instance_data cid;
    if( -1 == INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid))
    {
        return false;
    }
    if( cid.get_instance_id() != instance_id)
        return false;

    int monster_id = gm_evt.get_event_active_id();
    cout << " on monster die " <<  monster_id << endl;
    cid.add_monster_counter( monster_id );
    cid.add_total_monster_kill();

    bool is_end = false;
    //monster_config* config = Monster_Cfg_Data_Mgr::instance()->get_monster_config(monster_id);
    //if (config->type_ == MT_BOSS)
    //{
    //    is_end = true;
    //    instance()->to_send_monster_kill(player_id, cid);
    //    instance()->proc_finish_instance(player_id, cid, current_instance_data::INSTANCE_STATE_SUC);
    //}

    if( 0 == cid.is_couter_full() )
    {
        instance()->proc_monster_wave(player_id, cid ,is_end);
    }
    else
    {
        INSTANCE_DATA_MGR::instance()->modi_player_instance( player_id, cid );
    }

    return true;
}
int Formula_Function_Monster_Wave::proc_monster_wave(int player_id, current_instance_data& cid,bool is_end)
{
    //send monster kill data
    to_send_monster_kill(player_id, cid);

    //if have next wave
    //cout << "!!!!!!!!!!!!!!!!!!!!!!!!----------------add monster wave --------------------!!!!!!!!!!!!!!!!!" << cid.get_monster_wave() <<  endl;
    cid.add_monster_wave();

    vector<uint64> para;
    para.push_back( cid.get_monster_wave() + 1 );
    para.push_back( cid.get_monster_wave_require() );
    Game_Logic::Game_Content_Interface::instance()->exec_interface("showmonsterwave", para);

    if(cid.get_monster_wave() == cid.get_monster_wave_require())
    {
        if (!is_end)
        {
            proc_finish_instance(player_id, cid, current_instance_data::INSTANCE_STATE_SUC);
        }

        return 0;
    }
    else
    {
        if( -1 == instance()->proc_next_monster_wave( player_id, cid ) )
        {
            INSTANCE_DATA_MGR::instance()->modi_player_instance( player_id, cid );
            para.clear();
            Game_Logic::Game_Content_Interface::instance()->exec_interface("nextmonsterwave", para);
        }
        else
        {
            INSTANCE_DATA_MGR::instance()->modi_player_instance( player_id, cid );
        }
    }

    return 0;
}
bool  Formula_Function_Monster_Wave::on_instance_finish( Game_Logic::Game_Interface& gm_interface )
{
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() < 1 )
        return false;
    int state = (int)para[0];

    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    int instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();

    current_instance_data cid;
    if( -1 == INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid))
    {
        return false;
    }

    instance()->proc_finish_instance(player_id, cid, state);

    return true;

}

int Formula_Function_Monster_Wave::proc_finish_instance(int player_id, current_instance_data &cid, int state)
{
    vector<uint64> para;
    para.clear();
    para.push_back( 0 );
    para.push_back( 0 );
    Game_Logic::Game_Content_Interface::instance()->exec_interface("showmonsterwave", para);

    INSTANCE_DATA_MGR::instance()->set_instance_state(IS_COMPLETE);

    para.clear();
    para.push_back(player_id);
    para.push_back(cid.get_instance_id());
    para.push_back(state);
    Game_Logic::Game_Content_Interface::instance()->exec_interface("sendfinishinstance", para);
    return 0;
}
int Formula_Function_Monster_Wave::to_send_monster_kill(int player_id, current_instance_data &cid)
{
    vector<Game_Data::Game_Element> counter_lst;
    cid.get_monster_lst(counter_lst);

    if( counter_lst.size() <= 0)
        return -1;
    vector<uint64> para;
    para.push_back( player_id );
    para.push_back( counter_lst.size());
    vector<Game_Data::Game_Element>::iterator itg;
    for(itg = counter_lst.begin(); itg != counter_lst.end(); ++ itg )
    {
        para.push_back( (*itg).get_cell_id());
        para.push_back( (*itg).get_count());
    }

    Game_Logic::Game_Content_Interface::instance()->exec_interface("sendmonsterkill", para);
    return 0;
}

int Formula_Function_Monster_Wave::proc_next_monster_wave( int player_id, current_instance_data& cid )
{
    int cure_lock_scene_id = get_current_locked_screen(cid);
    if( cure_lock_scene_id == cid.get_current_lock_scene_id() )
    {
        return -1;
    }
    //Game_Utils::instance()->pre_locked_screen(true, cure_lock_scene_id, Formula_Function_Monster_Wave::on_finish_move_to_next_scene);
    return 0;
}

void Formula_Function_Monster_Wave::on_finish_move_to_next_scene( void )
{
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    int instance_id = INSTANCE_DATA_MGR::instance()->get_current_instance_id();
    current_instance_data cid;
    if( -1 == INSTANCE_DATA_MGR::instance()->get_player_instance( player_id, cid))
    {
        return;
    }
   cid.clear_monster_counter();
    INSTANCE_DATA_MGR::instance()->modi_player_instance( player_id, cid );
    vector<uint64> para; para.clear();
    Game_Logic::Game_Content_Interface::instance()->exec_interface("nextmonsterwave", para);
    cout << " process next monster wave " << endl;
}
