//#define _CRT_SECURE_NO_WARNINGS
//#include "db/dbquery.h"
#include "gameplay_ctrl_tool.h"
#include "gameplay_ctrl_data_mgr.h"
#include <iostream>

#ifdef GAME_SERVER
#include "player_manager.h"
#include "role_att.h"
#include "role_act_rec.h"
#endif

#ifdef YN_LINUX
#include <stdlib.h>
#endif
time_stamp gameplay_ctrl_tool::get_time_stamp()
{
  time_stamp cur_time;
  time_t stime = time(NULL);
  struct tm* cur_tm = localtime(&stime);
  cur_time.year_ = cur_tm->tm_year + 1900;
  cur_time.month_ = cur_tm->tm_mon + 1;
  cur_time.day_ = cur_tm->tm_mday;
  cur_time.hour_ = cur_tm->tm_hour;
  cur_time.minute_ = cur_tm->tm_min;
  cur_time.second_ = cur_tm->tm_sec;
  cur_time.day_of_week_ = cur_tm->tm_wday;

  return cur_time;
}

time_t gameplay_ctrl_tool::get_sys_time()
{
  return time(NULL);
}

int gameplay_ctrl_tool::db_add_record(const record* p_rec)
{
	//return hoyosvr::DBQuery::instance()->play_ctrl_add(p_rec->role_id_, p_rec->act_id_, p_rec->repeat_count_, p_rec->commit_time_);
   //1. get the game_db by role_id (p_rec->role_id_)
#ifdef GAME_SERVER
   player_ptr player =  PLAYER_MANAGER::instance()->find(p_rec->role_id_);
   if (player)
   {
     game_db * gdb = player->worker_->db();
     if (gdb)
     {
      role_act_rec trec;
      trec.role_id_ = p_rec->role_id_;
      trec.act_id_  = p_rec->act_id_;
      trec.repeat_count_ = p_rec->repeat_count_;
      trec.commit_time_  = p_rec->commit_time_;
      
      return gdb->add_role_record(&trec);
     }
   }
#endif
   return -1;
}

int gameplay_ctrl_tool::db_del_record_item(int p_role_id,
                             uint p_act_id)
{
	//return hoyosvr::DBQuery::instance()->play_ctrl_remove( p_role_id, p_act_id );
  //1. get the game_db by role_id
#ifdef GAME_SERVER
   player_ptr player =  PLAYER_MANAGER::instance()->find(p_role_id);
   if (player)
   {
     game_db * gdb = player->worker_->db();
     if (gdb)
     {
       role_act_rec trec;
       trec.role_id_ = p_role_id;
       trec.act_id_  = p_act_id;
       
       return gdb->del_role_rec_item(&trec);
     }
   }
#endif
   return -1;
}

int gameplay_ctrl_tool::db_del_record_all(int p_role_id)
{
	//return hoyosvr::DBQuery::instance()->play_ctrl_remove_all( p_role_id);
  //1. get the game_db by role_id
#ifdef GAME_SERVER
   player_ptr player =  PLAYER_MANAGER::instance()->find(p_role_id);
   if (player)
   {
     game_db * gdb = player->worker_->db();
     if (gdb)
     { 
       role_act_rec trec;
       trec.role_id_ = p_role_id;
       
       return gdb->del_role_rec_all(&trec);
     }
   }
#endif
   return -1;
}

int gameplay_ctrl_tool::db_inc_record_count(int p_role_id,
                              uint p_act_id)
{
#ifdef GAME_SERVER
	record* rec = gameplay_ctrl_data_mgr::get_role_record(p_role_id, p_act_id);
	//return hoyosvr::DBQuery::instance()->play_ctrl_update(p_role_id, p_act_id,  rec->repeat_count_ );
  //1. get the game_db by role_id

   player_ptr player =  PLAYER_MANAGER::instance()->find(p_role_id);
   if (player && rec)
   {
     game_db * gdb = player->worker_->db();
     if (gdb)
     {
       role_act_rec trec;
       trec.role_id_ = p_role_id;
       trec.act_id_  = p_act_id;
       trec.repeat_count_ = rec->repeat_count_;

       return gdb->inc_rec_count(&trec);
     }
   }
#endif
   return -1;
}

int gameplay_ctrl_tool::time_valid(const activity* p_act)
{
  const time_stamp curt = get_time_stamp();
  
  if (p_act->start_time_.day_of_week_ == 8)
  {
  	//the activity's time : [every day] hh-mm-ss
  	if (time_equal_late_than(curt, p_act->start_time_, 0)
  		  && time_equal_late_than(p_act->stop_time_, curt, 0))
  		return 0;
  	return -1;
  }
  else if (p_act->start_time_.day_of_week_ == 0)
  {
  	  //the activity's time: yy-mm-dd hh-mm-ss
      if (time_equal_late_than(curt, p_act->start_time_)
          && time_equal_late_than(p_act->stop_time_, curt))
          return 0;
      return -1;
  }
  else
  {
    //the activity's time : [weekday] hh-mm-ss
    if (time_equal_late_than(curt, p_act->start_time_, 1)
        && time_equal_late_than(p_act->stop_time_, curt, 1))
        return 0;
    return -1;
  }
}

bool gameplay_ctrl_tool::time_equal_late_than(const time_stamp& ltime,
                                             const time_stamp& rtime,
                                             int flag)
{
	if (flag == 0)
	{
			if (ltime.hour_ > rtime.hour_)
			return true;
			if (ltime.hour_ == rtime.hour_)
			{
				if (ltime.minute_ > rtime.minute_)
					 return true;
				if (ltime.minute_ == rtime.minute_)
				{
					if (ltime.second_ >= rtime.second_)
						 return true;
				}
			}
	}
	else if (flag == 1)
	{
		if (ltime.day_of_week_ > rtime.day_of_week_)
			 return true;
		if (ltime.day_of_week_ == rtime.day_of_week_)
		{
			if (ltime.hour_ > rtime.hour_)
				 return true;
			if (ltime.hour_ == rtime.hour_)
			{
				if (ltime.minute_ > rtime.minute_)
					 return true;
				if (ltime.minute_ == rtime.minute_)
				{
					if (ltime.second_ >= rtime.second_)
						 return true;
				}
			}
		}
    return false;
	}
	else
	{
			if (ltime.year_ > rtime.year_)
				 return true;
			if (ltime.year_ == rtime.year_)
			{
				if (ltime.month_ > rtime.month_)
					 return true;
				if (ltime.month_ == rtime.month_)
				{
					if (ltime.day_ > rtime.day_)
						 return true;
					if (ltime.day_ == rtime.day_)
					{
						if (ltime.hour_ > rtime.hour_)
				            return true;
			            if (ltime.hour_ == rtime.hour_)
			            {
			 	            if (ltime.minute_ > rtime.minute_)
					          return true;
				            if (ltime.minute_ == rtime.minute_)
				            {
					             if (ltime.second_ >= rtime.second_)
						           return true;
				            }
			            }
					}
				}
			}
	}
	 return false;
}

int gameplay_ctrl_tool::load_role_record(int p_role_id, vec_record& p_vec_rec)
{
	//return hoyosvr::DBQuery::instance()->play_ctrl_query( p_role_id, p_vec_rec );
	 //1. get the game_db by role_id
#ifdef GAME_SERVER
   player_ptr player =  PLAYER_MANAGER::instance()->find(p_role_id);
   if (player)
   {   	
     game_db * gdb = player->worker_->db();
     if (gdb)
     {
     	 std::vector<role_act_rec*> vec;
       gdb->get_role_act_record(p_role_id, vec); 
       //copy
       std::vector<role_act_rec*>::iterator it;
       for (it = vec.begin(); it != vec.end(); it++)
       {
       	 role_act_rec *trec = *it;
       	 record *rec = new record;
       	 rec->role_id_      = trec->role_id_;
       	 rec->act_id_       = trec->act_id_;
       	 rec->repeat_count_ = trec->repeat_count_;

#ifdef YN_LINUX
		 rec->commit_time_  = trec->commit_time_;
#endif
#ifdef YN_WINDOWS
		 rec->commit_time_  = (__time32_t)trec->commit_time_;
#endif
       	 
       	 
       	 p_vec_rec.push_back(rec);
       	 
       	 delete trec;
       }
       
       if (p_vec_rec.size() > 0)
       	return 0;
     }
   }
#endif
   return -1;
}

int gameplay_ctrl_tool::analysis_act_bind(const std::string& p_bind,
                                          std::string& p_type,
                                          int& p_last_quest_id)
{
  using namespace std;
  size_t pos = p_bind.find_first_of('(');
  if (pos == string::npos) return -1;
  p_type = p_bind.substr(0,pos);

  size_t qpos = p_bind.find_last_of(',');
  if (qpos == string::npos)
  {
  	  string str_id = p_bind.substr(pos+1, p_bind.length()-1-pos-1);
      p_last_quest_id = atoi(str_id.c_str());
  }
  else
  {
  	  string str_id = p_bind.substr(qpos+1, p_bind.length()-1-qpos-1);
      p_last_quest_id = atoi(str_id.c_str());
  }
  return 0;
}                               

