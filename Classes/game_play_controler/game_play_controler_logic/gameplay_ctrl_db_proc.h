// -*- C++ -*-


#ifndef GAMEPLAY_CTRL_DB_PROC_H_
#define GAMEPLAY_CTRL_DB_PROC_H_

#include "game_play_controler/game_play_controler_data/gameplay_ctrl_data_mgr.h"
#ifdef GAME_SERVER
#include <json/json.h>
#else
#include "json/json_header.h"
#include "cocos2d.h"
#endif
#include "Game_Interface/common.h"
/**
 * @class gameplay_ctrl_db_proc
 * 
 * @privide proc about db operating
 */

class gameplay_ctrl_db_proc
{
public:
	
	gameplay_ctrl_db_proc(void)
	{
#ifdef YN_LINUX
		pthread_mutex_init(&ctrl_db_mutex_,NULL);
#endif
	}
	~gameplay_ctrl_db_proc(void)
	{
#ifdef YN_LINUX
		pthread_mutex_destroy(&ctrl_db_mutex_);
#endif
		if( instance_ )
			delete instance_;
	}
	
	static gameplay_ctrl_db_proc* instance(void);
	
  int load_activity_data();
  
  void load_role_record(int p_role_id);
  
public: 
#ifdef GAME_SERVER
  int add_record(int p_role_id,
                        uint p_act_id);

  int add_record(const record* p_rec);

  int del_record_item(int p_role_id,
                             uint p_act_id);

  int del_record_all(int p_role_id);

  int inc_record_count(int p_role_id,
                              uint p_act_id);
#endif
private:
  
  int load_act_item(activity* p_act, 
                           Json::Value& p_act_value);

 	void load_time(time_stamp& p_time_stamp, 
                        Json::Value& p_time_value);
                        	
  void maintiance_role_record(vec_record& p_old_vec_rec,
                                     vec_record*& p_new_vec_rec);
  
  int logic_valid(const record* rec);
  
  static gameplay_ctrl_db_proc* instance_;
 #ifdef YN_LINUX
  pthread_mutex_t  ctrl_db_mutex_;
#endif
};

#endif // GAMEPLAY_CTRL_DB_PROC_H_

