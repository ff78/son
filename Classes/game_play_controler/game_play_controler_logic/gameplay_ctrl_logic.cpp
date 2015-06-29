#include "gameplay_ctrl_logic.h"
#include "gameplay_ctrl_db_proc.h"
#include "game_play_controler/game_play_controler_data/gameplay_ctrl_data_mgr.h"
#include "game_play_controler/game_play_controler_data/gameplay_ctrl_tool.h"
#include "gameplay_ctrl_event_proc.h"
#include "Game_Interface/game_event_mgr.h"
#include "gameplay_ctrl_fun_proc.h"


gameplay_ctrl_logic* gameplay_ctrl_logic::instance_p_ = 0;
	gameplay_ctrl_logic::gameplay_ctrl_logic()
	{
	}
	gameplay_ctrl_logic::~gameplay_ctrl_logic()
	{
		if( NULL != instance_p_)
			delete instance_p_;
	}
gameplay_ctrl_logic* gameplay_ctrl_logic::instance ( void )
{
	if ( NULL == instance_p_)
		instance_p_ = new gameplay_ctrl_logic;
	return instance_p_;
}

int gameplay_ctrl_logic::ctrl_init()
{
  /*if (gameplay_ctrl_db_proc::instance()->load_activity_data() == -1)
    return -1;*/
  
  game_player_ctrl_handle_.clear();

  reg_act_function_callback("quest_bind",			gameplay_ctrl_func_proc::gameplayer_ctrl_fun_quest_bind );
  reg_act_function_callback("ring_quest_bind",		gameplay_ctrl_func_proc::gameplayer_ctrl_fun_ring_quest_bind );
  reg_act_function_callback("item_bind",			gameplay_ctrl_func_proc::gameplayer_ctrl_fun_item_bind );
  reg_act_function_callback("award_bind",			gameplay_ctrl_func_proc::gameplayer_ctrl_fun_daily_reward_bind );
  //othre init logic
  //
  //
  return 0;
}

bool gameplay_ctrl_logic::reg_act_function_callback ( const char* cmd,  Game_Logic::game_interface_handler_t handle )
{
	 Game_Logic::game_interface_handler_map_t::iterator itgm;
	itgm = game_player_ctrl_handle_.find( cmd );
	if( itgm != game_player_ctrl_handle_.end() )
	{
		return false; 
	}
	else
	{
		game_player_ctrl_handle_.insert( make_pair( cmd, handle ) );
	}	
	return true;
}

int gameplay_ctrl_logic::can_accept_act(int p_role_id,
                                        uint p_act_id)
{
  //check the time
  const activity *act = gameplay_ctrl_data_mgr::get_activity_by_id(p_act_id);
  if (!act) return -1;
  if (gameplay_ctrl_tool::time_valid(act) == -1) return -1;
  //check the state
  record *rec = gameplay_ctrl_data_mgr::get_role_record(p_role_id, p_act_id);
  if (!rec)
  {
    //1. no this record yet, then check rank or other condation
    //now do nothing
    //
    return 0;
  }
  else if (rec->repeat_count_ >= act->repeat_)
  {
    //the activity record is full(can not play again)
    return -1;
  }
  else
  	return 0;
}

int gameplay_ctrl_logic::do_accept_act(int p_role_id,
                                     uint p_act_id)
{

	record *rec = gameplay_ctrl_data_mgr::get_role_record(p_role_id, p_act_id);
  if (!rec)
  {
    //1. no this record yet, then check rank or other condation
    //add a record for the role
    record *rec = gameplay_ctrl_data_mgr::add_role_record(p_role_id, p_act_id);
    if (!rec)
    {

#ifdef GAME_SERVER
    	//gameplay_ctrl_tool::get_ctrl_log()->trace("data_mgr add role record [%d-%d] failed.", p_role_id, p_act_id);
#endif
    	return -1;
    }

#ifdef GAME_SERVER    
    if (gameplay_ctrl_db_proc::instance()->add_record(rec) != 0)
    {
    	//gameplay_ctrl_tool::get_ctrl_log()->trace("db add role record [%d-%d] failed.", p_role_id, p_act_id);
    	gameplay_ctrl_data_mgr::del_role_record_all(p_role_id);
    	return -1;
    }
    #endif
    return 0;
  }

  const activity *act = gameplay_ctrl_data_mgr::get_activity_by_id(p_act_id);
  if (!act)
  {
#ifdef GAME_SERVER
    	//gameplay_ctrl_tool::get_ctrl_log()->trace("get activity [%d] failed.--before register event", p_act_id);
#endif
    	return -1;
  }
  //2. register event and callback
  register_event(p_role_id, act);
    
  return 0;
}

void gameplay_ctrl_logic::register_event(int p_role_id, const activity* p_act)
{
  //1. get activity's bind content
  std::string type;
  int ctrl_id;
  if (gameplay_ctrl_tool::analysis_act_bind(p_act->bind_, type, ctrl_id) != 0)
    return;
  
  //2. register

	vector<uint64> para_vec;
	para_vec.push_back(p_role_id);
	para_vec.push_back(ctrl_id);
	para_vec.push_back(p_act->id_);
	Game_Logic::Game_Interface gm_arg;
	gm_arg.set_para( para_vec );
	Game_Logic::game_interface_handler_map_t::iterator itgm;
	itgm = game_player_ctrl_handle_.find( type.data() );
	if( itgm != game_player_ctrl_handle_.end() )
	{
		(*itgm->second)(gm_arg);
	}


  //else
  //other register
  //
  //
}

int gameplay_ctrl_logic::add_rec_count(int p_role_id,
                                       uint p_act_id)
{
  //data_mgr add
  if (gameplay_ctrl_data_mgr::inc_record_count(p_role_id, p_act_id) != 0)
    return -1;
  //db add
  #ifdef GAME_SERVER
  if (gameplay_ctrl_db_proc::instance()->inc_record_count(p_role_id, p_act_id) != 0)
  {
    //data_mgr recover maybe
    //now do nothing

    return -1;
  }
  #endif
  return 0;
}

int gameplay_ctrl_logic::player_login(int p_role_id)
{
	//load role's record first(if has)
	gameplay_ctrl_db_proc::instance()->load_role_record(p_role_id);
	
	return 0;
}

int gameplay_ctrl_logic::player_logout(int p_role_id)
{
	//unload role's record(if has)
	gameplay_ctrl_data_mgr::del_role_record_all(p_role_id);
	
	return 0;
}

int gameplay_ctrl_logic::giveup_act(int p_role_id,
                                    uint p_act_id)
{
	//give up the activity
	//1. data_mgr del the record
	gameplay_ctrl_data_mgr::del_role_record_item(p_role_id, p_act_id);
		
	//2. db del the record
  #ifdef GAME_SERVER
	gameplay_ctrl_db_proc::instance()->del_record_item(p_role_id, p_act_id);
	#endif
	
	return 0;
}

void gameplay_ctrl_logic::get_role_act_status(const int p_role_id, 
                                const int p_act_id,
                                int& current_count, //参加该活动的次数
                                int& total_count)  //该活动的总次数 
{
	const activity *act = gameplay_ctrl_data_mgr::get_activity_by_id(p_act_id);
  if (!act)
  {
#ifdef GAME_SERVER
    	//gameplay_ctrl_tool::get_ctrl_log()->trace("get activity [%d] failed.--get_role_act_status", p_act_id);
#endif
    	current_count = 0;
    	total_count = 0;
  }
  else
  	total_count = (int)act->repeat_;
  
  record *rec = gameplay_ctrl_data_mgr::get_role_record(p_role_id, p_act_id);
  if (!rec)
  	current_count = 0;
  else
  	current_count = (int)rec->repeat_count_;
} 
















